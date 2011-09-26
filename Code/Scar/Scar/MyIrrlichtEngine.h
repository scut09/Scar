/*
** ���ߣ�����
** ˵��������İ�װ
**
*/

#ifndef _MYIRRLICHTENGINE_H_
#define _MYIRRLICHTENGINE_H_

#include <irrlicht.h>

using namespace irr;

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

public:
	static int						screen_width;
	static int						screen_height;
	static IEventReceiver*			pEventReceiver;
	static bool						bFullScreen;

public:
	// ��ȡ����ָ��
	MyIrrlichtEngine* GetEngine();

	scene::ISceneManager* GetSceneManager();

	scene::ISceneCollisionManager* GetCollisionManager();

	video::IVideoDriver* GetVideoDriver();


};


#endif