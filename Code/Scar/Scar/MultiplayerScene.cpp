/********************************************************************
    ����ʱ��: 2011-10-8   16:01
    �ļ���:   MultiplayerScene.cpp
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������Ϸ����

*********************************************************************/

#include "MultiplayerScene.h"
#include "PythonManager.h"
#include "EngineHeader.h"
#include <iostream>
#include "Aircraft.h"
#include "FlyBehavior.h"



void MultiplayerScene::Run()
{

}

void MultiplayerScene::Init()
{
	PythonManager* p = PythonManager::GetPythonManager();

	object modelLoader = p->GetModelLoader();
	object MultiplayerLoad = modelLoader.attr( "MultiplayerLoad" );
	MultiplayerLoad();

	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	scene::ISceneManager* smgr = pEngine->GetSceneManager();

	smgr->addCameraSceneNodeFPS();

	ModelManager* modelMan = pEngine->GetModelManager();

	scene::ISceneNode* node = modelMan->AddSceneNodeFromMesh( "bottle" );

	shared_ptr<Aircraft> bottle( new Aircraft );
	bottle->LoadSceneNode( node );
	bottle->SetSpeed( vector3df( 0.01, 0.1, 0 ) );
	shared_ptr<FlyStraightBehavior> beh( new FlyStraightBehavior );
	bottle->AddFlyBehavior( beh );

	AnimationManager* aniMan = pEngine->GetAnimationManager();
	aniMan->AddMovableNode( node, bottle );


	ModuleControl control;



}

void MultiplayerScene::Release()
{

}

