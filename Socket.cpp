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

#include "stdafx.h"
#include "Socket.h"
namespace Omron
	{

	CInitSock theInitSocket;

	Socket::Socket(void)
		{
		m_sListen = NULL;
		}

	Socket::~Socket(void)
		{
		closesocket(m_Client);
		}

	void Socket::CreateServerSocket(int Port, int listenNum)
		{
		//创建一个socket套接字 
		m_sListen = ::socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);	
		if (m_sListen == INVALID_SOCKET) 
			{
#ifdef _DEBUG
			printf("创建请求策略套接字失败!!!!!!\n");
#endif 
			WSACleanup();
			return;
			}

		//绑定服务端口和链接设置
		m_SocketAddr.sin_family = AF_INET;
		m_SocketAddr.sin_port =ntohs(Port);
		m_SocketAddr.sin_addr.S_un.S_addr = INADDR_ANY;

		//绑定服务设置和socket套接字
		if (SOCKET_ERROR == bind(m_sListen, (sockaddr*)&m_SocketAddr, sizeof(m_SocketAddr)))
			{
#ifdef _DEBUG
			printf("绑定请求策略文件服务套接字失败!!!!!!\n");
#endif
			return;
			}
		if (SOCKET_ERROR==listen(m_sListen, listenNum))
			{
#ifdef _DEBUG
			printf("请求数据服务器监听套接字失败!!!!!!\n");
#endif
			}

		}

	void Socket::CreateClientSocket(int Port, char* IP)
		{
		m_Client = socket(AF_INET, SOCK_DGRAM, 0);
		if(m_Client == INVALID_SOCKET)
			{
			printf("create client socket error\n");
			return ;
			}


		m_ClientSocketAddr.sin_family = AF_INET;
		m_ClientSocketAddr.sin_addr.S_un.S_addr = inet_addr(IP);
		m_ClientSocketAddr.sin_port= htons(Port);

		}

	int Socket::ConnectServer()
		{
		if(connect(m_Client, (sockaddr*)&m_ClientSocketAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
			{
			printf("connect failed\n");
			return 1;
			}
		else
			{
			return 0;
			}
		}

	int Socket::SendFrameValue(char *bufFrame,int lengthFrame, int flagFrame)
		{
		int retFrame = 0;
		retFrame = send(m_Client, bufFrame, lengthFrame, flagFrame);
		if(retFrame == 0 || retFrame == SOCKET_ERROR)
			{
			closesocket(m_Client);
			return 0;
			}
		else
			{
			return retFrame;
			}
		}

	int Socket::RecvFrameValue(char *bufFrame,int lengthFrame, int flagFrame)
		{
		int retFrame = 0;
		retFrame = recv(m_Client, bufFrame, lengthFrame, flagFrame);
		if(retFrame == 0 || retFrame == SOCKET_ERROR)
			{
			closesocket(m_Client);
			return 0;
			}
		else
			{
			bufFrame[retFrame] = '\0';
			return retFrame;
			}
		}

	void Socket::CloseClientSocket()
		{
		closesocket(m_Client);
		}

	}