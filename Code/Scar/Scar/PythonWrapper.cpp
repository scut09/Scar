/********************************************************************
	创建时间: 2011-9-29   19:32
	文件名:   PythonWrapper.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/


#include "PythonWrapper.h"
#include "MyIrrlichtEngine.h"
#include <boost/thread.hpp>
#include "EventListener.h"
#include "GameSceneManager.h"
#include "MySceneManager.h"

//////////////////////////////////////////////////////////////////////////
//
// Class ModelManagerSlaver
// 
void ModelManagerWrapper::AddMesh( const std::wstring& meshID, const std::wstring& meshFilename, const std::wstring& textureFilename )
{
	ModelManager* pModelMan = MyIrrlichtEngine::GetEngine()->GetModelManager();

	pModelMan->AddMesh( meshID, meshFilename, textureFilename );

}

void ModelManagerWrapper::AddLight( const PythonSLight& light, f32 x, f32 y, f32 z )
{
	auto assign = []( video::SColorf& scolor, const PythonSColor& pcolor )
	{
		scolor.set( pcolor.alpha, pcolor.red, pcolor.green, pcolor.blue );
	};
	auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

	scene::ILightSceneNode * pLight = smgr->addLightSceneNode( 0, core::vector3df( x, y, z ) );
	video::SLight slight;
	assign( slight.AmbientColor, light.AmbientColor );
	assign( slight.DiffuseColor, light.DiffuseColor );
	assign( slight.SpecularColor, light.SpecularColor );
	pLight->getLightData() = slight;

	//auto print = []( const PythonSColor& pcolor )
	//{
	//	std::cout << pcolor.alpha << ' ' <<  pcolor.red << ' ' <<  pcolor.green << ' ' <<  pcolor.blue << std::endl;
	//};

	//print( light.AmbientColor );
	//print( light.DiffuseColor );
	//print( light.SpecularColor );
	//std::cout << x << ' ' << y << ' ' << z << std::endl;
}

PythonSceneNode ModelManagerWrapper::AddSceneNodeByMeshID( const std::wstring& meshID, bool bTestCollision /*= false */ )
{
	ModelManager* pModelMan = MyIrrlichtEngine::GetEngine()->GetModelManager();

	PythonSceneNode node;
	scene::ISceneNode* pNode = pModelMan->AddSceneNodeFromMesh( meshID, bTestCollision );
	node.ptr = pNode;
	//pNode->drop();		// 引用减一
	return node;
}

//////////////////////////////////////////////////////////////////////////
//
// Class TimerWrapper
// 

TimerWrapper::TimerWrapper()
{
	m_timer = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer();
}

u32 TimerWrapper::GetTime()
{
	return m_timer->getTime();
}

u32 TimerWrapper::GetRealTime()
{
	return m_timer->getRealTime();
}


//////////////////////////////////////////////////////////////////////////
//
// Class Engine
// 
MyEngine::MyEngine()
{
	m_driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
}

irr::video::IVideoDriver* MyEngine::GetDriver()
{
	return m_driver;
}


void ChangeGameScene( GameScene* scene )
{
	MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->SetCurrentGameScene( scene );
}

irr::s32 Float2Int( f32 f )
{
	return (s32)f;
}

irr::f32 Int2Float( s32 s )
{
	return (f32)s;
}


UIManager* GetUIManager()
{
	return &*MyIrrlichtEngine::GetEngine()->GetUIManager();
}

GameSceneManager* GetGameSceneManager()
{
	return MyIrrlichtEngine::GetEngine()->GetGameSceneManager();
}

MySceneManager* GetMySceneManager()
{
	return MyIrrlichtEngine::GetEngine()->GetMySceneManager();
}

