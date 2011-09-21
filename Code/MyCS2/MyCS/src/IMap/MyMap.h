///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/22 14:48
//Describe: 地图模块实现
///////////////////////////////////////////////////////////////////////

#ifndef  MyMap_CMyMap_h
#define  MyMap_CMyMap_h
#pragma once

#include "../../include/IMap.h"
#include <string>
#include "../MyCS/Ihreo.h"

extern "C"			//C语言库 防止编译器重命名函数
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
		///	@brief 加载一张地图
		///	@param [in] mappath:	
		///	@return void
		//////////////////////////////
		void LoadMap(const char* mappath);

		//////////////////////////////
		///	@brief 是否资源
		///	@return void
		//////////////////////////////
		void Release();

		//////////////////////////////
		///	@brief 判断是否获胜
		///	@param [in] winner:	获胜的位设置为true
		///	@return bool:如果获胜 返回true,否则false
		//////////////////////////////
		bool IsWin(bool* winner);

		//////////////////////////////
		///	@brief	设置玩家列表
		///	@param [in] playerlist:玩家列表 用于判断是否获胜
		///	@return void
		//////////////////////////////
		void SetPlayerList(void** playerlist);

		//////////////////////////////
		///	@brief 获得起始位置
		///	@param [in] index:
		///	@return 起始位置
		//////////////////////////////
		core::vector3df GetStartPostion(int index);

		//////////////////////////////
		///	@brief	设置设备环境
		///	@param [in] device:鬼火引擎设备指针
		///	@return void
		//////////////////////////////
		void SetDevice(IrrlichtDevice* device);
		friend int GetKillNum(lua_State* L);
	private:
		//////////////////////////////
		///	@brief 加载位置信息
		///	@return void
		//////////////////////////////
		void LoadPosition();

		//////////////////////////////
		///	@brief	追加字符串
		///	@param [in] des:目标字符串
		///	@param [in] src:源字符串
		///	@return 返回长度
		//////////////////////////////
		int CharCpy(char* des, const char* src, int offset);
	public:
		static CMyMap*			g_obj;			//单例对象
	private:
		
		lua_State*				m_Lua;			//lua对象
		scene::IMeshSceneNode*	m_node;			//地图场景
		core::vector3df			m_Postion[4];	//玩家位置
		IHreo**					m_playerList;	//玩家列表

		static IrrlichtDevice*		g_device;
		static IGUIEnvironment*		g_guienv;		//设备对象
		static IVideoDriver*		g_driver;
		static ISceneManager*		g_smgr ;		//场景管理器		

	};
}
#endif