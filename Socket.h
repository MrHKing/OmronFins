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
*������������װ��Socket����
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
			* socket�๹�캯��
			*/
			Socket(void);

			/**
			* socket����������
			*/
			~Socket(void);

		public:

			/**
			* ������������socket
			*
			*
			* @param  Port �˿ں�
			* @param  listenNum ��������
			* @return  void.
			*/
			void CreateServerSocket(int Port, int listenNum);							

			/**
			* �����ͻ���socket
			*
			* @param  Port �˿ں�
			* @param  IP ����IP
			* @return  void.
			*/
			void CreateClientSocket(int Port, char* IP);								

			/**
			* ���ӷ�����
			*
			*
			* @param   
			* @return  void.
			*/
			int ConnectServer();										

			/**
			* ��������
			*
			*
			* @param   bufFrame Ҫ���͵�����ָ��
			* @param   lengthFrame ���ݳ���
			* @param   flagFrame ���õ�ִ�з�ʽ
			* @return  ���͵ĸ���.
			*/
			int SendFrameValue(char *bufFrame,int lengthFrame, int flagFrame);			

			/**
			* ��������
			*
			* @param   bufFrame Ҫ���յ�����ָ��
			* @param   lengthFrame ���ݳ���
			* @param   flagFrame ���õ�ִ�з�ʽ
			* @return  ���յĸ���.
			*/
			int RecvFrameValue(char *bufFrame,int lengthFrame, int flagFrame);			

			/**
			* �ر�����
			*
			*
			* @param   
			* @return  void.
			*/
			void CloseClientSocket();															//
		public:
			SOCKET m_sListen;															//��������������
			SOCKADDR_IN m_SocketAddr;													//������������ַ
			SOCKET m_Client;															//�����ͻ��˼���
			SOCKADDR_IN m_ClientSocketAddr;												//�����ͻ��˵�ַ
		};

	/*
	* ��ʼ��Socket
	*
	*/
	class CInitSock																	//
		{
		public:
			CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)
				{
				// ��ʼ��WS2_32.dll
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