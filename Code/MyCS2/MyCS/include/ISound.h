///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/21 21:38
//Describe: 声音管理
///////////////////////////////////////////////////////////////////////

#ifndef  ISound_h
#define  ISound_h

#ifdef	ISOUND_EXPORTS
#define ISOUND_API __declspec(dllexport)
#else
#define ISOUND_API __declspec(dllimport)
#endif

#include <irrlicht.h>


namespace ISound
{
	enum SOUND_TYPE
	{
		SND_Move,			//移动
		SND_MinMove,		//缓慢移动
		SND_Shoot1,			//射击1
		SND_Shoot2,			//射击2
		SND_ChangeBullet,	//换弹夹
		SND_NoBullet,		//弹夹空的声音
		SND_Count,			//数量
	};

	//////////////////////////////
	///	@brief	播放声音资源
	///	@parm [in] mied:声音类型
	///	@parm [in] position:声音发生的位置
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void MyPlaySound( SOUND_TYPE mied, irr::core::vector3df position = irr::core::vector3df(0,0,5));

	//////////////////////////////
	///	@brief	设置声音收听者
	///	@parm [in] node:收听者场景节点
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void SetListener( irr::scene::ISceneNode* node);

	//////////////////////////////
	///	@brief	设置声音收听者
	///	@parm [in] node:收听者场景节点
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void Init();


}

#endif