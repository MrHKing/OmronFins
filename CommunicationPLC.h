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
*功能描述：PLC连接读取接口
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
			* 读数据接口
			*
			*
			* @param   addrPLC PLC地址
			* @param   Value 返回值
			* @return  void.
			*/
			virtual void Read(CString addrPLC, CString &Value){};

			/**
			* 写数据接口
			*
			*
			* @param   addrPLC PLC地址
			* @param   Value 写入值
			* @return  void.
			*/
			virtual void Write(CString addrPLC, CString &Value){};
		};

	}

#endif	//_COMMUNICATION_PLC_H
