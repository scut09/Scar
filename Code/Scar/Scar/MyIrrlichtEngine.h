/********************************************************************
	����ʱ��: 2011:9:27   14:54
	�ļ���:   MyIrrlichtEngine.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ����İ�װ

*********************************************************************/

#ifndef _MYIRRLICHTENGINE_H_
#define _MYIRRLICHTENGINE_H_

#include <irrlicht.h>
#include <functional>
#include "ModelManager.h"
#include "IMovable.h"
#include "AnimationManager.h"

using namespace irr;

typedef std::function< void*( void* ) > EngineRunCallbackFuncType;

/*
** ���֣�MyIrrlichtEngine
** ˵��������ģʽ
**
*/
class MyIrrlichtEngine
{
private:
	IrrlichtDevice*					m_pDevice;
	video::IVideoDriver*			m_pDriver;
	scene::ISceneManager*			m_pSmgr;
	scene::ISceneCollisionManager*	m_pColMan;
	scene::ICameraSceneNode*		m_pCamera;

	// ��ֱֹ�Ӵ���ʵ��
	MyIrrlichtEngine() {}

	static MyIrrlichtEngine*		m_pIrrlichtEngine;	// ����ģʽ��Ψһ������
	EngineRunCallbackFuncType		m_runCallbackFunc;  // ÿ��֡����ʱ������õĻص�����

public:
	static int						screen_width;
	static int						screen_height;
	static IEventReceiver*			pEventReceiver;
	static bool						bFullScreen;

public:

	// ��ȡ����ָ��
	static MyIrrlichtEngine* GetEngine();

	scene::ISceneManager* GetSceneManager();

	scene::ISceneCollisionManager* GetCollisionManager();

	video::IVideoDriver* GetVideoDriver();

	void Run();

	void SetCallbackFunc( EngineRunCallbackFuncType func );
};


#endif