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
*功能描述：封装了Socket连接
*
*********************************************************************************
*
*
*
*********************************************************************************
*/

#ifndef _SOCKET_H
#define _SOCKET_H

namespace Omron
	{
	class Socket
		{
		public:
			/**
			* socket类构造函数
			*/
			Socket(void);

			/**
			* socket类析构函数
			*/
			~Socket(void);

		public:

			/**
			* 创建服务器端socket
			*
			*
			* @param  Port 端口号
			* @param  listenNum 监听个数
			* @return  void.
			*/
			void CreateServerSocket(int Port, int listenNum);							

			/**
			* 创建客户端socket
			*
			* @param  Port 端口号
			* @param  IP 服务IP
			* @return  void.
			*/
			void CreateClientSocket(int Port, char* IP);								

			/**
			* 连接服务器
			*
			*
			* @param   
			* @return  void.
			*/
			int ConnectServer();										

			/**
			* 发送数据
			*
			*
			* @param   bufFrame 要发送的数据指针
			* @param   lengthFrame 数据长度
			* @param   flagFrame 调用的执行方式
			* @return  发送的个数.
			*/
			int SendFrameValue(char *bufFrame,int lengthFrame, int flagFrame);			

			/**
			* 接受数据
			*
			* @param   bufFrame 要接收的数据指针
			* @param   lengthFrame 数据长度
			* @param   flagFrame 调用的执行方式
			* @return  接收的个数.
			*/
			int RecvFrameValue(char *bufFrame,int lengthFrame, int flagFrame);			

			/**
			* 关闭连接
			*
			*
			* @param   
			* @return  void.
			*/
			void CloseClientSocket();															//
		public:
			SOCKET m_sListen;															//创建服务器监听
			SOCKADDR_IN m_SocketAddr;													//创建服务器地址
			SOCKET m_Client;															//创建客户端监听
			SOCKADDR_IN m_ClientSocketAddr;												//创建客户端地址
		};

	/*
	* 初始化Socket
	*
	*/
	class CInitSock																	//
		{
		public:
			CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)
				{
				// 初始化WS2_32.dll
				WSADATA wsaData;
				WORD sockVersion = MAKEWORD(minorVer, majorVer);
				if(WSAStartup(sockVersion, &wsaData) !=0)
					{
#ifdef _DEBUG
					printf("Error at WSAStartup\n");
#endif
					exit(0);
					}
				}
			~CInitSock()
				{	
				::WSACleanup();	
				}
		};

	}
#endif	//_SOCKET_H