#include <irrlicht.h>
#include <cstdio>
#include <iostream>
#include "EventListener.h"
#include <map>
#include <list>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

scene::ISceneNode* SkyBox = 0;
IrrlichtDevice *device;
video::IVideoDriver* driver;
scene::ISceneManager* smgr;
scene::ICameraSceneNode* camera;
scene::ISceneNode* aircraftNode = 0;

MyEventReceiver receiver;


int Init()
{
	// ask user for driver
	video::E_DRIVER_TYPE driverType = (video::E_DRIVER_TYPE)5;//driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	device = createDevice(driverType, core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver );

	if (device == 0)
		return 1; // could not create selected driver.

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	SkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture("../../media/irrlicht2_up.jpg"),
		driver->getTexture("../../media/irrlicht2_dn.jpg"),
		driver->getTexture("../../media/irrlicht2_lf.jpg"),
		driver->getTexture("../../media/irrlicht2_rt.jpg"),
		driver->getTexture("../../media/irrlicht2_ft.jpg"),
		driver->getTexture("../../media/irrlicht2_bk.jpg"));

	// 初始化照相机
	camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, 0, 0, false, 3.f);
	camera->setPosition(core::vector3df(150,50,60));
	camera->setTarget(core::vector3df(0,0,0));

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
}

int LoadAircraft()
{
	IAnimatedMesh * pBottleMesh = smgr->getMesh( "1234.obj" );
	aircraftNode = smgr->addAnimatedMeshSceneNode( pBottleMesh );

	aircraftNode->setScale( core::vector3df( 2.f, 2.f, 2.f ) );


	camera->addChild( aircraftNode );

	aircraftNode->setPosition(vector3df(0.f, -10.f, 50.f));

	return 0;
}

int LoadModel()
{
	LoadWomen();

	LoadAircraft();

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

int CalPos()
{
	core::vector3df targetVec = camera->getTarget();
	core::vector3df camVec = camera->getPosition();
	core::vector3df posVec = targetVec - camVec;
	posVec.Y = 0;
	posVec = posVec.normalize();
	posVec *= 50.f;
	posVec.Y = -60.f;

	aircraftNode->setRotation( camera->getRotation() );
	aircraftNode->setPosition( camera->getPosition() + posVec/*core::vector3df( 0.f, 60.f, 50.f )*/ );

	return 0;
}

std::list<ISceneNode*> g_MissileList;

void shoot()
{
	vector3df pos = aircraftNode->getPosition();

	ISceneNode* pMissileNode = smgr->addAnimatedMeshSceneNode( smgr->getMesh("mayabottle.obj") );

	// get line of camera

	core::vector3df start = camera->getPosition();
	core::vector3df end = (camera->getTarget() - start);
	end.normalize();
	start += end * 8.0f;
	end = start + (end * camera->getFarValue());

	core::line3d<f32> line(start, end);

	scene::ISceneNodeAnimator* anim = 0;

	// set flight line
	f32 length = (f32)(end - start).getLength();
	const f32 speed = 0.6f;
	u32 time = (u32)(length / speed);

	anim = smgr->createFlyStraightAnimator(start, end, time);
	pMissileNode->addAnimator(anim);
	anim->drop();

	pMissileNode->grab();
	g_MissileList.push_back( pMissileNode );
}



int KeyDownHandler()
{
	if ( receiver.IsKeyDown( irr::KEY_KEY_F ) )
	{
		shoot();
	}

	return 0;
}

void HitTest()
{
	for ( auto iter = g_MissileList.begin(); iter != g_MissileList.end(); ++iter )
	{
	}
}

int main()
{
	Init();	

	LoadModel();

	LoadLight();

	while(device->run())
	{
		if (device->isWindowActive())
		{
			//CalPos();

			KeyDownHandler();

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
