///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/22 14:08
//Describe: 地图模块		对lua地图脚本操作进行封装
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
		///	@brief 加载一张地图
		///	@param [in] mapname:地图名字 地图应该对于一个lua 文件和 3DS 文件 放在 model/map/ 文件夹下
		///				\n 如果有纹理文件 则对应一张 jpg 文件 几个文件名必须相同
		///	@return void
		//////////////////////////////
		virtual void LoadMap(const char* mapname) = 0;

		//////////////////////////////
		///	@brief 是否资源
		///	@return void
		//////////////////////////////
		virtual void Release() = 0;

		//////////////////////////////
		///	@brief 判断是否获胜
		///	@param [in] winner:	获胜的位设置为true
		///	@return bool:如果获胜 返回true,否则false
		//////////////////////////////
		virtual bool IsWin(bool* winner) = 0;

		//////////////////////////////
		///	@brief	设置玩家列表
		///	@param [in] playerlist:玩家列表 用于判断是否获胜
		///	@return void
		//////////////////////////////
		virtual void SetPlayerList(void** playerlist) = 0;

		//////////////////////////////
		///	@brief 获得起始位置
		///	@param [in] index:
		///	@return 起始位置
		//////////////////////////////
		virtual core::vector3df GetStartPostion(int index) = 0;

		//////////////////////////////
		///	@brief	设置设备环境
		///	@param [in] device:鬼火引擎设备指针
		///	@return void
		//////////////////////////////
		virtual void SetDevice(IrrlichtDevice* device) = 0;

	};
	//////////////////////////////
	///	@brief	创建一个IMap指针	
	///	@return void
	//////////////////////////////
	extern "C" IMAP_API IMap* CreateMap();
}

#endif