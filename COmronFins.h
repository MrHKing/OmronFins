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
			* CCOmronFins类构造函数
			*/
			CCOmronFins(void);

			/**
			* CCOmronFins类析构函数
			*/
			~CCOmronFins(void);

			/**
			* 读数据接口
			*
			*
			* @param   addrPLC PLC地址
			* @param   Value 返回值
			* @return  void.
			*/
			virtual void Read(CString addrPLC, CString &Value);

			/**
			* 写数据接口
			*
			*
			* @param   addrPLC PLC地址
			* @param   Value 写入值
			* @return  void.
			*/
			virtual void Write(CString addrPLC, CString &Value);

		public:
			UCHAR	CmdHead[10];				//发送帧头
			Socket	m_SocketCLient;				//创建socket类
			BYTE	m_CmdBuf[80];				//发送数据帧
			BYTE	m_RspBuf[2012];				//应答接收
			double	m_DIData;					//读取数据
			std::vector<double> m_ReadDate;		//读取的数据
		public:

			/**
			* 创建CCOmronFins对象
			*
			*
			* @return  void.
			*/
			static CCOmronFins* Create();		

			/**
			* 连接PLC
			*
			* @param  Port PLC端口号
			* @param  IP PLC服务IP
			* @return  void.
			*/
			void ConnectPLC(int port, char *IP);

			/**
			* 数据帧打包
			*
			* @param  cmd 打包方式命令
			* @param  nch 数据长度
			* @param  addr 起始位置
			* @param  pParam 保留
			* @param  pCmd 命令帧缓存
			* @return  void.
			*/
			int MakeCmd(int cmd, unsigned short nch, unsigned short addr, LPVOID pParam, LPVOID pCmd);

			/**
			* 获得数据
			*
			* @param  type 输入输出信号
			* @param  tagsize 数据大小
			* @param  addr 开始地址
			* @param  pCmd 数据帧
			* @param  pRsp 应答缓存
			* @return  int.
			*/
			int PlcDateGet(int type, int tagsize, unsigned short addr, LPVOID pCmd, LPVOID pRsp);

			/**
			* 读数据
			*
			*
			* @param   nsbuf PLC地址
			* @param   lpSbuf PLC地址
			* @param   nrbuf PLC地址
			* @param   lpRbuf 返回值
			* @return  int.
			*/
			int PlcSendRecv(int nSbuf,LPSTR lpSbuf,int nRbuf,LPSTR lpRbuf);

			/**
			* 应答解析
			*
			* @param   ptr 要解析的应答信息
			* @return  int.
			*/
			double CvtPlcToDbl_2WORD(LPSTR ptr);

		};

	}
#endif	//_CCOMRONFINS_H