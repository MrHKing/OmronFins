/*
*********************************************************************************
*
*��Ȩ���ƿ�
*
*********************************************************************************
*
*�����ˣ��ƿ�
*����ʱ�䣺2015.05.06
*
*********************************************************************************
*
*������������װ��ŷķ��PLC��̫��Э��
*
*********************************************************************************
*
*
*
*********************************************************************************
*/

#ifndef _CCOMRONFINS_H
#define _CCOMRONFINS_H

#include "CommunicationPLC.h"
#include "Struct.h"
#include "Socket.h"
#include <vector>

namespace Omron
	{

	class Socket;
	class CCommunicationPLC;

	class CCOmronFins : public CCommunicationPLC
		{
		public:
			/**
			* CCOmronFins�๹�캯��
			*/
			CCOmronFins(void);

			/**
			* CCOmronFins����������
			*/
			~CCOmronFins(void);

			/**
			* �����ݽӿ�
			*
			*
			* @param   addrPLC PLC��ַ
			* @param   Value ����ֵ
			* @return  void.
			*/
			virtual void Read(CString addrPLC, CString &Value);

			/**
			* д���ݽӿ�
			*
			*
			* @param   addrPLC PLC��ַ
			* @param   Value д��ֵ
			* @return  void.
			*/
			virtual void Write(CString addrPLC, CString &Value);

		public:
			UCHAR	CmdHead[10];				//����֡ͷ
			Socket	m_SocketCLient;				//����socket��
			BYTE	m_CmdBuf[80];				//��������֡
			BYTE	m_RspBuf[2012];				//Ӧ�����
			double	m_DIData;					//��ȡ����
			std::vector<double> m_ReadDate;		//��ȡ������
		public:

			/**
			* ����CCOmronFins����
			*
			*
			* @return  void.
			*/
			static CCOmronFins* Create();		

			/**
			* ����PLC
			*
			* @param  Port PLC�˿ں�
			* @param  IP PLC����IP
			* @return  void.
			*/
			void ConnectPLC(int port, char *IP);

			/**
			* ����֡���
			*
			* @param  cmd �����ʽ����
			* @param  nch ���ݳ���
			* @param  addr ��ʼλ��
			* @param  pParam ����
			* @param  pCmd ����֡����
			* @return  void.
			*/
			int MakeCmd(int cmd, unsigned short nch, unsigned short addr, LPVOID pParam, LPVOID pCmd);

			/**
			* �������
			*
			* @param  type ��������ź�
			* @param  tagsize ���ݴ�С
			* @param  addr ��ʼ��ַ
			* @param  pCmd ����֡
			* @param  pRsp Ӧ�𻺴�
			* @return  int.
			*/
			int PlcDateGet(int type, int tagsize, unsigned short addr, LPVOID pCmd, LPVOID pRsp);

			/**
			* ������
			*
			*
			* @param   nsbuf PLC��ַ
			* @param   lpSbuf PLC��ַ
			* @param   nrbuf PLC��ַ
			* @param   lpRbuf ����ֵ
			* @return  int.
			*/
			int PlcSendRecv(int nSbuf,LPSTR lpSbuf,int nRbuf,LPSTR lpRbuf);

			/**
			* Ӧ�����
			*
			* @param   ptr Ҫ������Ӧ����Ϣ
			* @return  int.
			*/
			double CvtPlcToDbl_2WORD(LPSTR ptr);

		};

	}
#endif	//_CCOMRONFINS_H