///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/22 14:48
//Describe: ��ͼģ��ʵ��
///////////////////////////////////////////////////////////////////////

#ifndef  MyMap_CMyMap_h
#define  MyMap_CMyMap_h
#pragma once

#include "../../include/IMap.h"
#include <string>
#include "../MyCS/Ihreo.h"

extern "C"			//C���Կ� ��ֹ����������������
{
	#include <lua include/lua.h>
	#include <lua include/lualib.h>
	#include <lua include/lauxlib.h> 
	#pragma comment(lib, "lua51.lib") 
};



namespace MyMap
{
	int GetKillNum(lua_State* L);

	class CMyMap:public IMap
	{
	public:
		CMyMap(void);
		~CMyMap(void);

		//////////////////////////////
		///	@brief ����һ�ŵ�ͼ
		///	@param [in] mappath:	
		///	@return void
		//////////////////////////////
		void LoadMap(const char* mappath);

		//////////////////////////////
		///	@brief �Ƿ���Դ
		///	@return void
		//////////////////////////////
		void Release();

		//////////////////////////////
		///	@brief �ж��Ƿ��ʤ
		///	@param [in] winner:	��ʤ��λ����Ϊtrue
		///	@return bool:�����ʤ ����true,����false
		//////////////////////////////
		bool IsWin(bool* winner);

		//////////////////////////////
		///	@brief	��������б�
		///	@param [in] playerlist:����б� �����ж��Ƿ��ʤ
		///	@return void
		//////////////////////////////
		void SetPlayerList(void** playerlist);

		//////////////////////////////
		///	@brief �����ʼλ��
		///	@param [in] index:
		///	@return ��ʼλ��
		//////////////////////////////
		core::vector3df GetStartPostion(int index);

		//////////////////////////////
		///	@brief	�����豸����
		///	@param [in] device:��������豸ָ��
		///	@return void
		//////////////////////////////
		void SetDevice(IrrlichtDevice* device);
		friend int GetKillNum(lua_State* L);
	private:
		//////////////////////////////
		///	@brief ����λ����Ϣ
		///	@return void
		//////////////////////////////
		void LoadPosition();

		//////////////////////////////
		///	@brief	׷���ַ���
		///	@param [in] des:Ŀ���ַ���
		///	@param [in] src:Դ�ַ���
		///	@return ���س���
		//////////////////////////////
		int CharCpy(char* des, const char* src, int offset);
	public:
		static CMyMap*			g_obj;			//��������
	private:
		
		lua_State*				m_Lua;			//lua����
		scene::IMeshSceneNode*	m_node;			//��ͼ����
		core::vector3df			m_Postion[4];	//���λ��
		IHreo**					m_playerList;	//����б�

		static IrrlichtDevice*		g_device;
		static IGUIEnvironment*		g_guienv;		//�豸����
		static IVideoDriver*		g_driver;
		static ISceneManager*		g_smgr ;		//����������		

	};
}
#endif