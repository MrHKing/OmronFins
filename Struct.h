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
*功能描述：用于存储所有结构体类型
*
*********************************************************************************
*
*
*
*********************************************************************************
*/

#ifndef _STRUCT_H
#define _STRUCT_H
#include "Define.h"

//FINS头
typedef struct _FINS_HEAD{
	unsigned char	cICF; 
	unsigned char	cRSV; 
	unsigned char	cGCT; 
	unsigned char	cDNA; 
	unsigned char	cDA1; 
	unsigned char	cDA2; 
	unsigned char	cSNA; 
	unsigned char	cSA1; 
	unsigned char	cSA2; 
	unsigned char	cSID; 
}FINS_HEAD;

//FINS
typedef struct _FINS_CMD_0101{
	FINS_HEAD		stHead;
	unsigned char	pCmd[2];
	unsigned char	cKind;
	unsigned char	pAddr[3];
	unsigned char	pNch[2];
}FINS_CMD_0101;

//FINS
typedef struct _FINS_RSP_0101{
	FINS_HEAD		stHead;
	unsigned char	pCmd[2];
	unsigned char	pRsp[2];
	unsigned char	pData[FINS_MAX_CH*2];
}FINS_RSP_0101;

//FINS
typedef struct _FINS_CMD_0102{
	FINS_HEAD		stHead;
	unsigned char	pCmd[2];
	unsigned char	cKind;
	unsigned char	pAddr[3];
	unsigned char	pNch[2];
	unsigned char	pData[FINS_MAX_CH*2];
}FINS_CMD_0102;

//FINS
typedef struct _FINS_RSP_0102{
	FINS_HEAD		stHead;
	unsigned char	pCmd[2];
	unsigned char	pRsp[2];
	unsigned char	pNwErr[2];
}FINS_RSP_0102;

#endif