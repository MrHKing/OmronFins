/*
*********************************************************************************
*
*版权：黄凯
*
*********************************************************************************
*
*创建人：黄凯
*创建时间：2015.05.06
*
*********************************************************************************
*
*功能描述：封装了欧姆龙PLC以太网协议
*
*********************************************************************************
*
*
*
*********************************************************************************
*/

#include "stdafx.h"
#include "COmronFins.h"
#include "Enum.h"

namespace Omron
	{

	CCOmronFins::CCOmronFins(void)
		{
		CmdHead[0] = 0x80;	//ICF
		CmdHead[1] = 0x00;	//RSV
		CmdHead[2] = 0x02;	//GCT
		CmdHead[3] = 0x02;	//DNA
		CmdHead[4] = 0x02;	//DA1
		CmdHead[5] = 0x00;	//DA2
		CmdHead[6] = 0x00;	//SNA
		CmdHead[7] = 0x01;	//SA1
		CmdHead[8] = 0x01;	//SA2
		CmdHead[9] = 0x00;	//SID
		}


	CCOmronFins::~CCOmronFins(void)
		{
		m_SocketCLient.CloseClientSocket();
		}

	void CCOmronFins::Read(CString addrPLC, CString &Value)
		{
		PlcDateGet(0,2,1000,m_CmdBuf,m_RspBuf);
		CString dataValue;

		dataValue.Format("%f", m_ReadDate[0]);
		Value = dataValue;
	
		}

	void CCOmronFins::Write(CString addrPLC, CString &Value)
		{

		}

	CCOmronFins* CCOmronFins::Create()
		{
		CCOmronFins *omron = new CCOmronFins();
		if(omron)
			{
			return omron;
			}
		else
			{
			return nullptr;
			}
		}

	void CCOmronFins::ConnectPLC(int port, char *IP)
		{
		m_SocketCLient.CreateClientSocket(port,IP);
		if(m_SocketCLient.ConnectServer())
			{
			printf("Connect Error!");
			}
		}

	int CCOmronFins::MakeCmd(int cmd, unsigned short nch, unsigned short addr, LPVOID pParam, LPVOID pCmd)
		{
		int length = 0;
		FINS_CMD_0101	*p0101;
		FINS_CMD_0102	*p0102;

		switch(cmd){
			case CMD_FINS_0101:
				{
				p0101 = (FINS_CMD_0101 *)pCmd;
				memcpy(&p0101->stHead,&CmdHead,sizeof(FINS_HEAD));
				p0101->cKind = 0x82;
				*((short *)p0101->pAddr) = htons(addr);
				p0101->pAddr[2] = 0x00;
				*((short *)p0101->pNch) = htons(nch);
				p0101->pCmd[0] = 0x01;
				p0101->pCmd[1] = 0x01;

				length = sizeof(FINS_CMD_0101);
				break;
				}
			case CMD_FINS_0102:
				{
				p0102 = (FINS_CMD_0102 *)pCmd;
				memcpy(&p0102->stHead,&CmdHead,sizeof(FINS_HEAD));
				p0102->cKind = 0x82;
				*((short *)p0102->pAddr) = htons(addr);
				p0102->pAddr[2] = 0x00;
				*((short *)p0102->pNch) = htons(nch);
				p0102->pCmd[0] = 0x01;
				p0102->pCmd[1] = 0x02;
				length = sizeof(FINS_CMD_0102) - ((FINS_MAX_CH - nch)*2);
				break;
				}
			default:
				length = 0;
			}

		return length;
		}

	int CCOmronFins::PlcDateGet(int type, int tagsize, unsigned short addr, LPVOID pCmd, LPVOID pRsp)
		{
		int ret = 0, len, send, cmd, nIn, nOut;
		unsigned short nch, leftch, max;
		DWORD	dwSt, dwEd;

		FINS_RSP_0101 *pRsp0101;
		LPSTR pData;

		char	buffMel[1024];

		unsigned short	address;			

		/*if (type == KOUMOKU_AI ||
			type == KOUMOKU_AO )
			{
			leftch = tagsize * 2;
			}
		else if (type == KOUMOKU_DI)
			{
			leftch = tagsize / 16;
			if ((tagsize % 16) != 0) leftch++;
			}
		else
			{*/
			leftch = tagsize;
			//}

		max = FINS_MAX_CH;
		cmd = CMD_FINS_0101;
		nIn = sizeof(FINS_CMD_0101);
		nOut = sizeof(FINS_RSP_0101);

		dwSt = GetTickCount();

		send = 0;

		while (leftch > 0)
			{
			if (leftch > max)
				nch = max;
			else
				nch = leftch;

			address = addr + (send*max);	

			len = MakeCmd(cmd, nch, address, NULL, pCmd);	
			//发送数据
			ret = PlcSendRecv(nIn, (LPSTR)pCmd, nOut, (LPSTR)pRsp);

			if (ret < 0) goto TERM;

			pRsp0101 = (FINS_RSP_0101 *)pRsp;
			if (*((short *)pRsp0101->pRsp) != 0){
				ret = *((short *)pRsp0101->pRsp);
				goto TERM;
				}
			pData = (LPSTR)pRsp0101->pData;

			m_ReadDate.push_back(CvtPlcToDbl_2WORD(pData));

			leftch -= nch;
			send++;
			}

		dwEd = GetTickCount();
TERM:
		return ret;
		}

	int CCOmronFins::PlcSendRecv(int nSbuf,LPSTR lpSbuf,int nRbuf,LPSTR lpRbuf)
		{
		INT		errcd = ERROR_SUCCESS;
		DWORD	dwSend,dwFlag,dwRecv,nTransfer,dwWflag;
		WSABUF	wSendBuf,wRecvBuf;
		unsigned char  ssid,rsid;

		//Socket Close
		if (m_SocketCLient.m_Client == 0) return PLCDATA_ERROR;

		//
		// FINS协议帧发送
		//
		errcd = m_SocketCLient.SendFrameValue((char *)lpSbuf, nSbuf, 0);

		// FINS协议帧应答
		//
		errcd = m_SocketCLient.RecvFrameValue(lpRbuf, nRbuf, 0);

		return errcd;
		}

	double CCOmronFins::CvtPlcToDbl_2WORD(LPSTR ptr)
		{
		double	cvtval;
		char	szVal[8];

		if( ptr[2] & 0x80 ) return OMRON_NA;

		memset(szVal,0x00,8);
		szVal[0] = (( ptr[0] >> 4 ) & 0x0f) | 0x30;
		szVal[1] = ( ptr[0] & 0x0f) | 0x30;
		szVal[2] = ( ( ptr[1] >> 4 ) & 0x0f) | 0x30;
		szVal[3] = ( ptr[1] & 0x0f) | 0x30;

		cvtval = atof(szVal);

		switch (ptr[3])
			{
			case 0x01: break;
			case 0x02: cvtval = cvtval / 10.0;		break;
			case 0x04: cvtval = cvtval / 100.0;		break;
			case 0x08: cvtval = cvtval / 1000.0;	break;
			case 0x10: cvtval = cvtval / 10000.0;	break;
			default:   return  OMRON_NA; //
			}

		if (ptr[2] == 0x01) cvtval = cvtval * -1.0;

		return  cvtval;
		}
	}
