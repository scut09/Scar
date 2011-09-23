#include <irrlicht.h>
#include <cstdio>
#include <iostream>
#include "EventListener.h"
#include "IMissile.h"
#include "ModuleControl.h"
#include <map>
#include <list>
#include <string>
#include <set>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

const u32 npcNum = 20;

scene::ISceneNode* SkyBox = 0;
IrrlichtDevice *device;
video::IVideoDriver* driver;
scene::ISceneManager* smgr;
scene::ICameraSceneNode* camera;
scene::ISceneNode* aircraftNode = 0;
scene::ISceneNode* pNPCNode[npcNum] = {0}; 

MyEventReceiver receiver;
ModuleControl* pModule;

std::map<ISceneNode*, std::string> g_modelList;


int Init()
{
	Missile::m_pModels = &g_modelList;

	// ask user for driver
	video::E_DRIVER_TYPE driverType = (video::E_DRIVER_TYPE)5;//driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	device = createDevice(driverType, core::dimension2d<u32>(800, 640), 16, false, false, false, &receiver );

	if (device == 0)
		return 1; // could not create selected driver.

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	Missile::m_pColMan = smgr->getSceneCollisionManager();

	SkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture("../../media/irrlicht2_up.jpg"),
		driver->getTexture("../../media/irrlicht2_dn.jpg"),
		driver->getTexture("../../media/irrlicht2_lf.jpg"),
		driver->getTexture("../../media/irrlicht2_rt.jpg"),
		driver->getTexture("../../media/irrlicht2_ft.jpg"),
		driver->getTexture("../../media/irrlicht2_bk.jpg"));

	//SkyBox = smgr->addSkyBoxSceneNode(
	//	driver->getTexture("../../media/stars_up.jpg"),
	//	driver->getTexture("../../media/stars_dn.jpg"),
	//	driver->getTexture("../../media/stars_lf.jpg"),
	//	driver->getTexture("../../media/stars_rt.jpg"),
	//	driver->getTexture("../../media/stars_fr.jpg"),
	//	driver->getTexture("../../media/stars_bk.jpg"));

	// 初始化照相机
	camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, 0, 0, false, 3.f);
	//camera->setPosition(core::vector3df(150,50,60));
	//camera->setTarget(core::vector3df(0,0,0));

	pModule = new ModuleControl;


	device->getCursorControl()->setVisible(false);

	return 0;
}

int LoadWomen()
{
	IAnimatedMesh* mesh = smgr->getMesh("../../media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
	}

	g_modelList[ node ] = "sydney";

	scene::ITriangleSelector* selector = smgr->createTriangleSelector( (scene::IAnimatedMeshSceneNode*)node );
	node->setTriangleSelector(selector);
	selector->drop();
}

int LoadAircraft()
{
	IAnimatedMesh * pMesh = smgr->getMesh( "1234.obj" );
	aircraftNode = smgr->addAnimatedMeshSceneNode( pMesh );

	aircraftNode->setScale( core::vector3df( 2.f, 2.f, 2.f ) );

	g_modelList[ aircraftNode ] = "aircraftNode";

	//camera->addChild( aircraftNode );
	pModule->Initialize(camera, aircraftNode);
	pModule->setCamaraPos(vector3df(0.f, 0.f, 0.f));
	pModule->setModuleposRelateToCamara(vector3df(0.f, -10.f, 50.f));

	return 0;
}

int LoadModel()
{
	LoadWomen();

	LoadAircraft();

	return 0;
}

int loadNPC()
{
	IAnimatedMesh * pMesh = smgr->getMesh( "1234.obj" );
	scene::ISceneNodeAnimator* anim;
	for (int i = 0; i < npcNum; i++)
	{
		anim = smgr->createFlyCircleAnimator(core::vector3df(rand() % 100, rand() % 100, rand() % 100), rand() % 100);
		pNPCNode[ i ] = smgr->addAnimatedMeshSceneNode(pMesh);
		pNPCNode[ i ]->addAnimator(anim);
		anim->drop();

		scene::ITriangleSelector* selector = smgr->createTriangleSelector( (scene::IAnimatedMeshSceneNode*)pNPCNode[ i ] );
		pNPCNode[ i ]->setTriangleSelector(selector);
		selector->drop();

		g_modelList[ pNPCNode[ i ] ] = "pNPCNode";
	}
	return 0;
}

int LoadLight()
{
	SLight light;
	light.AmbientColor = SColor( 0, 255, 255, 255 );
	light.DiffuseColor = SColor( 0, 128, 128, 128 );
	light.SpecularColor = SColor( 0, 128, 128, 128 );
	ILightSceneNode * pLight = smgr->addLightSceneNode( 0, vector3df( -10, 200.0f, -100 ) );
	pLight->getLightData() = light;

	return 0;
}



std::list<ISceneNode*>	g_MissileList;
std::list<IMissile*>	g_Mis;

void shoot()
{
	vector3df pos = aircraftNode->getPosition();

	ISceneNode* pMissileNode = smgr->addAnimatedMeshSceneNode( smgr->getMesh("mayabottle.obj") );

	// get line of camera

	core::vector3df start = camera->getPosition();
	core::vector3df end = (camera->getTarget() - start);
	end.normalize();

	FlyStraightBehavior* pBehavior = new FlyStraightBehavior( end, 5.f );
	Missile* missile = new Missile;
	missile->AddBehavior( pBehavior );
	missile->SetPostion( camera->getPosition() );

	missile->LoadSceneNode( pMissileNode );

	g_Mis.push_back( missile );

	//

	//start += end * 8.0f;
	//end = start + (end * camera->getFarValue() * 10.f);
	//
	//scene::ISceneNodeAnimator* anim = 0;

	//// set flight line
	//f32 length = (f32)(end - start).getLength();
	//const f32 speed = 6.f;
	//u32 time = (u32)(length / speed);

	//anim = smgr->createFlyStraightAnimator(start, end, time);
	//pMissileNode->addAnimator(anim);
	//anim->drop();

	//pMissileNode->grab();
	//g_MissileList.push_back( pMissileNode );


		


}


f32 g_speed = 0.f;
bool bShoot = false;
int KeyDownHandler()
{
	if ( receiver.IsKeyDown( irr::KEY_NUMPAD0 ) )
	{
		bShoot = true;
	}

	if ( bShoot && ! receiver.IsKeyDown( irr::KEY_NUMPAD0 ) )
	{
		bShoot = false;
		shoot();
	}
	
	if ( receiver.IsKeyDown( irr::KEY_UP ) )
	{
		g_speed += 0.01f;
	}
	else if ( receiver.IsKeyDown( irr::KEY_DOWN ) )
	{
		g_speed -= 0.01f;
		if ( g_speed <= 0.f )
			g_speed = 0.f;
	}

	return 0;
}

void HitTest()
{
	for ( auto iter = g_MissileList.begin(); iter != g_MissileList.end(); ++iter )
	{
	}
}

scene::IParticleSystemSceneNode* CreateBullet()
{
	//初始化粒子系统
	scene::IParticleSystemSceneNode* m_bullet =
		smgr->addParticleSystemSceneNode(false);

	// create and set emitter
	scene::IParticleEmitter* em = m_bullet->createBoxEmitter(
		core::aabbox3d<f32>(-2,0,-2,2,1,2),
		core::vector3df(0.0f,0.03f,0.0f),
		10,50,
		video::SColor(0,255,255,255), video::SColor(0,255,255,255),
		400,1100);
	em->setMinStartSize(core::dimension2d<f32>(30.0f, 40.0f));
	em->setMaxStartSize(core::dimension2d<f32>(30.0f, 40.0f));

	m_bullet->setEmitter(em);
	em->drop();

	// create and set affector
	scene::IParticleAffector* paf = m_bullet->createFadeOutParticleAffector();
	m_bullet->addAffector(paf);
	paf->drop();

	// adjust some material settings
	m_bullet->setMaterialFlag(video::EMF_LIGHTING, false);
	m_bullet->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	m_bullet->setMaterialTexture(0, driver->getTexture("image/fireball.bmp"));
	m_bullet->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	m_bullet->setVisible(true);

	scene::ISceneNodeAnimator* anim = smgr->createDeleteAnimator(1000);
	m_bullet->addAnimator(anim);
	anim->drop();
	return m_bullet;
}

void RunMissile()
{
	std::list<IMissile*> delList;
	std::set<ISceneNode*> nodeList;
	ISceneNode* node = NULL;
	for ( auto iter = g_Mis.begin(); iter != g_Mis.end(); ++iter )
	{
		(*iter)->Move();
		if ( ( node = (*iter)->TestCollision() ) && node != aircraftNode )
		{			
			delList.push_back( *iter );
			//if ( node != aircraftNode )
			//	node->drop();
			
			//	(*iter)->Drop();	// 删除自己

			nodeList.insert( node );
			//node->setVisible( false );

			IParticleSystemSceneNode* bullet = CreateBullet();
			bullet->setParent( node );
		}
	}

	for ( auto iter = nodeList.begin(); iter != nodeList.end(); ++iter )
	{
		//(*iter)->setVisible( false );
		(*iter)->removeAnimators();
		//(*iter)->remove();
	}

	for ( auto iter = delList.begin(); iter != delList.end(); ++iter )
	{
		g_Mis.remove( *iter );		
	}
}

int main()
{
	Init();	

	LoadModel();

	LoadLight();

	loadNPC();

	while(device->run())
	{
		if (device->isWindowActive())
		{
			KeyDownHandler();

			pModule->MoveForward( g_speed );

			RunMissile();

			driver->beginScene(true, true, video::SColor(150,50,50,50));

			smgr->drawAll();	

			driver->endScene();

		}
	}

	device->drop();

	return 0;
}

/*
**/
