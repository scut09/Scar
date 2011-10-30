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
#include <list>
#include "def.h"
#include "ModelManager.h"
//#include "IMovable.h"
//#include "AnimationManager.h"
#include "GameScene.h"

class IUIObject;

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
	IrrlichtDevice*					m_pDevice;		// �豸
	video::IVideoDriver*			m_pDriver;		// ����
	scene::ISceneManager*			m_pSmgr;		// ����������
	scene::ISceneCollisionManager*	m_pColMan;		// ��ײ������
	scene::ICameraSceneNode*		m_pCamera;		// �������ʱû��

	static MyIrrlichtEngine*		m_pIrrlichtEngine;	// ����ģʽ��Ψһ������
	EngineRunCallbackFuncType		m_runCallbackFunc;  // ÿ��֡����ʱ������õĻص�����

	bool							m_bMotionBlur;		// �Ƿ����˶�ģ��

	// ��ֱֹ�Ӵ���ʵ��
	MyIrrlichtEngine() : m_lastUpdateTime( 0 ), m_bMotionBlur( false ) {}

private:
	ModelManager					m_ModelManager;
	//AnimationManager				m_AnimationManager;		// ��ʱ�����������ʹ��irrlicht�ڲ��Ķ�������
	u32								m_lastUpdateTime;
	std::list<IUIObject*>			m_IUIObjectDeleteionList;// ���IUIOjbect��ɾ���������
	std::list<scene::ISceneNode*>	m_ISceneNodeDeletionList;// ��ɾ���б���ÿ��������ѭ����һ��ѭ����������������
															// ʹ��������������ʵ��ͨ��IUIAnimator��ɾ��IUIObject
	std::list<GameScene*>			m_GameSceneDeletionList;// �ӳٳ���ɾ��


public:
	static int						screen_width;	// ��Ļ���
	static int						screen_height;	// ��Ļ�߶�
	static IEventReceiver*			pEventReceiver;	// ��Ϣ������
	static bool						bFullScreen;	// �Ƿ�ȫ��
	static GameScene*				currentScene;	// ��ǰ����

public:

	// ��ȡ����ָ��
	static MyIrrlichtEngine* GetEngine();

	scene::ISceneManager* GetSceneManager();

	scene::ISceneCollisionManager* GetCollisionManager();

	video::IVideoDriver* GetVideoDriver();

	IrrlichtDevice*	GetDevice();

	ModelManager* GetModelManager();

	// �����Ƿ����˶�ģ��
	void SetMotionBlur( bool bOpen = true );

	//AnimationManager* GetAnimationManager();	// ��ʷ���⣬����������

	void Run();

	void SetCallbackFunc( EngineRunCallbackFuncType func );

	// ��ӽڵ㵽ɾ��������
	void AddToDeletionQueue( scene::ISceneNode* node );
	void AddToDeletionQueue( IUIObject* node );
	void AddToDeletionQueue( GameScene* scene );

	// ɾ������ɾ�������еĽڵ㣬�������ÿ��ѭ���󱻵���
	void ClearDeletionList();
};


#endif