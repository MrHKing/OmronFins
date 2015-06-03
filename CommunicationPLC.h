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
*����������PLC���Ӷ�ȡ�ӿ�
*
*********************************************************************************
*
*
*
*********************************************************************************
*/

#ifndef _COMMUNICATION_PLC_H
#define _COMMUNICATION_PLC_H

namespace Omron
	{

	interface CCommunicationPLC
		{

		public:
			/**
			* �����ݽӿ�
			*
			*
			* @param   addrPLC PLC��ַ
			* @param   Value ����ֵ
			* @return  void.
			*/
			virtual void Read(CString addrPLC, CString &Value){};

			/**
			* д���ݽӿ�
			*
			*
			* @param   addrPLC PLC��ַ
			* @param   Value д��ֵ
			* @return  void.
			*/
			virtual void Write(CString addrPLC, CString &Value){};
		};

	}

#endif	//_COMMUNICATION_PLC_H
