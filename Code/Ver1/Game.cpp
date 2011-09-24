/*
	这只是一个原型，试验场。
*/


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
#include <boost/python.hpp>  
#include <Windows.h>

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

/*
** 名字：Init()
** 说明：初始化
**
*/
int Init()
{
	Missile::m_pModels = &g_modelList;

	// ask user for driver
	video::E_DRIVER_TYPE driverType = (video::E_DRIVER_TYPE)5;//driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	device = createDevice(driverType, core::dimension2d<u32>(1000, 640), 16, false, false, false, &receiver );

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


/*
** 名字：LoadWomen()
** 说明：加载那个女人的模型
**
*/
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

/*
** 名字：LoadAircraft()
** 说明：加载自己的飞机
**
*/
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


/*
** 名字：loadNPC()
** 说明：加载乱飞的飞机
**
*/
int loadNPC()
{
	IAnimatedMesh * pMesh = smgr->getMesh( "1234.obj" );
	scene::ISceneNodeAnimator* anim;
	for (int i = 0; i < npcNum; i++)
	{
		anim = smgr->createFlyCircleAnimator(core::vector3df(rand() % 10000, rand() % 10000, rand() % 10000), rand() % 100);
		pNPCNode[ i ] = smgr->addAnimatedMeshSceneNode(pMesh);
		pNPCNode[ i ]->addAnimator(anim);
		anim->drop();

		pNPCNode[ i ]->setScale( vector3df( 20.f, 20.f, 20.f ) );

		scene::ITriangleSelector* selector = smgr->createTriangleSelector( (scene::IAnimatedMeshSceneNode*)pNPCNode[ i ] );
		pNPCNode[ i ]->setTriangleSelector(selector);
		selector->drop();

		g_modelList[ pNPCNode[ i ] ] = "pNPCNode";
	}
	return 0;
}


/*
** 名字：LoadLight()
** 说明：加载光源
**
*/
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


/*
** 名字：LoadModel()
** 说明：加载所有模型
**
*/
int LoadModel()
{
	LoadWomen();

	LoadAircraft();

	LoadLight();

	loadNPC();

	return 0;
}




std::list<ISceneNode*>	g_MissileList;
std::list<IMissile*>	g_Mis;


/*
** 名字：shoot()
** 说明：射击
**
*/
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

}


f32 g_speed = 0.f;
bool bShoot = false;

/*
** 名字：KeyDownHandler()
** 说明：处理按键消息
**
*/
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

/*
** 名字：CreateBullet()
** 说明：创建一个爆炸的粒子系统
**
*/
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


/*
** 名字：RunMissile()
** 说明：移动飞弹，计算碰撞
**
*/
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
			bullet->setParent( (*iter)->GetSceneNode() );
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






float x = rand();
float y = rand();
float z = rand();

CRITICAL_SECTION lock;

DWORD WINAPI ThreadFUnc( PVOID param )
{
	while ( 1 )
	{
		float tx, ty, tz;
		std::cin >> tx >> ty >> tz;
		EnterCriticalSection( &lock );
		x = tx;
		y = ty;
		z = tz;
		LeaveCriticalSection( &lock );
	}

	return 0;
}


std::map<int, vector3df> g_userMap;
//std::list<std::string> m_users;

void update_user( int id, float x, float y, float z )
{
	g_userMap[ id ] = vector3df( x, y, z );
}



BOOST_PYTHON_MODULE(emb)  
{  
	boost::python::def( "update_user", update_user );  
}  




int main()
{
	Init();	

	LoadModel();

	Py_Initialize();  
	initemb();
	PyEval_InitThreads(); 
	InitializeCriticalSection( &lock );

	//initemb();  

	using namespace boost::python;

	object main_module = import("__main__");  
	object main_namespace = main_module.attr("__dict__");  
	//object run = exec_file( "client.py", main_namespace, main_namespace );


	object main = import("client");
	object id = main.attr("Connect")();

	object Run = main.attr("Run");
	object Send = main.attr("Send");
	object SetPos = main.attr("SetPos");

	std::cout << extract<char*>(id) << std::endl;


	while(device->run())
	{
		if (device->isWindowActive())
		{
			// 发送位置
			vector3df pos = camera->getPosition();
			float tx, ty, tz;
			EnterCriticalSection( &lock );
			tx = pos.X;
			ty = pos.Y;
			tz = pos.Z;
			LeaveCriticalSection( &lock );

			try
			{
				SetPos( tx, ty, tz );
				object info = Run();
				//std::cout << extract<char*>( info ) << std::endl;
				std::cout << "Run() returns\n";
				//for ( int i = 0; i < boost::python::len( info ); i++ )
				//{
				//	//std::cout << extract<int>( info[ i ] ) << std::endl;
				//}

				//boost::python::dict result = boost::python::extract<boost::python::dict>(info.attr("__list__"));

				Send();
			}
			catch(...)  
			{  
				PyErr_Print();  
			}  


			/////////

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
