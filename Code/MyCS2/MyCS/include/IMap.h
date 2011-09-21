///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/22 14:08
//Describe: ��ͼģ��		��lua��ͼ�ű��������з�װ
///////////////////////////////////////////////////////////////////////

#ifndef  IMap_h
#define  IMap_h

#ifdef	IMAP_EXPORTS
#define IMAP_API __declspec(dllexport)
#else
#define IMAP_API __declspec(dllimport)
#endif

#include <irrlicht.h>
using namespace irr;

namespace MyMap
{
	class IMap
	{
	public:
		//////////////////////////////
		///	@brief ����һ�ŵ�ͼ
		///	@param [in] mapname:��ͼ���� ��ͼӦ�ö���һ��lua �ļ��� 3DS �ļ� ���� model/map/ �ļ�����
		///				\n ����������ļ� ���Ӧһ�� jpg �ļ� �����ļ���������ͬ
		///	@return void
		//////////////////////////////
		virtual void LoadMap(const char* mapname) = 0;

		//////////////////////////////
		///	@brief �Ƿ���Դ
		///	@return void
		//////////////////////////////
		virtual void Release() = 0;

		//////////////////////////////
		///	@brief �ж��Ƿ��ʤ
		///	@param [in] winner:	��ʤ��λ����Ϊtrue
		///	@return bool:�����ʤ ����true,����false
		//////////////////////////////
		virtual bool IsWin(bool* winner) = 0;

		//////////////////////////////
		///	@brief	��������б�
		///	@param [in] playerlist:����б� �����ж��Ƿ��ʤ
		///	@return void
		//////////////////////////////
		virtual void SetPlayerList(void** playerlist) = 0;

		//////////////////////////////
		///	@brief �����ʼλ��
		///	@param [in] index:
		///	@return ��ʼλ��
		//////////////////////////////
		virtual core::vector3df GetStartPostion(int index) = 0;

		//////////////////////////////
		///	@brief	�����豸����
		///	@param [in] device:��������豸ָ��
		///	@return void
		//////////////////////////////
		virtual void SetDevice(IrrlichtDevice* device) = 0;

	};
	//////////////////////////////
	///	@brief	����һ��IMapָ��	
	///	@return void
	//////////////////////////////
	extern "C" IMAP_API IMap* CreateMap();
}

#endif