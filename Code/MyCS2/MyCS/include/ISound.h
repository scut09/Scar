///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/21 21:38
//Describe: ��������
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
		SND_Move,			//�ƶ�
		SND_MinMove,		//�����ƶ�
		SND_Shoot1,			//���1
		SND_Shoot2,			//���2
		SND_ChangeBullet,	//������
		SND_NoBullet,		//���пյ�����
		SND_Count,			//����
	};

	//////////////////////////////
	///	@brief	����������Դ
	///	@parm [in] mied:��������
	///	@parm [in] position:����������λ��
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void MyPlaySound( SOUND_TYPE mied, irr::core::vector3df position = irr::core::vector3df(0,0,5));

	//////////////////////////////
	///	@brief	��������������
	///	@parm [in] node:�����߳����ڵ�
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void SetListener( irr::scene::ISceneNode* node);

	//////////////////////////////
	///	@brief	��������������
	///	@parm [in] node:�����߳����ڵ�
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void Init();


}

#endif