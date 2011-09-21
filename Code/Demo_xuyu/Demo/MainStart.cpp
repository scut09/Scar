#include <irrlicht.h>
#include "MessageHandler.cpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

IAnimatedMeshSceneNode* mapNode;
IAnimatedMeshSceneNode*	PlaneNode;
ICameraSceneNode* camNode;

int main()
{
	EventHandler EH;
	vector3df p;
	// ��ʼ���Կ��豸
	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
		false, false, false, 0);

	if (!device)
		return 1;

	device->setWindowCaption(L"Irrlicht Engine Demo");

	//���Կ��豸��ó����������Լ��������������
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"This my Demo!",
		rect<s32>(10,10,260,22), true);

	//����ģ��
	IAnimatedMesh* mesh = smgr->getMesh("1234.obj");
	if (!mesh)
	{
		device->drop();
		return 1;
	}

	//��ģ�ͷ��볡���ڵ���
	PlaneNode = smgr->addAnimatedMeshSceneNode( mesh );

	if (PlaneNode)
	{
		//PlaneNode->setMaterialFlag(EMF_LIGHTING, false);
		//PlaneNode->setMaterialTexture( 0, driver->getTexture("../../../media/terrain-heightmap.bmp") );
	//	PlaneNode->setMaterialTexture( 0, driver->getTexture("../../../module/caldarifighter.mtl") );

		
	}

	//��ѹ����ͼ�������ڴ���
	device->getFileSystem()->addZipFileArchive("../../../media/map-20kdm2.pk3");
	//���ڴ��м��أ�ע�⣺�����Ѿ�����
	IAnimatedMesh* Mapmesh = smgr->getMesh("20kdm2.bsp");

	if (!Mapmesh)
	{
		device->drop();
		return 1;
	}

	mapNode = smgr->addAnimatedMeshSceneNode(Mapmesh);

	if (mapNode)
	{
		mapNode->setMaterialFlag(EMF_LIGHTING, false);
		mapNode->setPosition(vector3df(-1300, -144, -1249));
	}

	//�ڳ����з����۾�
	smgr->addCameraSceneNode(0, vector3df(-300,3000,-400), vector3df(0,5,5));
	//ʹ�õ�һ�˳��ӽǿ����۾����ƶ�
	
	p = PlaneNode->getPosition();
	p.Y += 1;
	camNode = smgr->addCameraSceneNode(0, p, vector3df(200, 250, 250));
	smgr->addCameraSceneNodeFPS();

	device->getCursorControl()->setVisible(false);

	// Lights
	SLight light;
	light.AmbientColor = SColor( 0, 255, 255, 255 );
	light.DiffuseColor = SColor( 0, 128, 128, 128 );
	light.SpecularColor = SColor( 0, 128, 128, 128 );
	ILightSceneNode * pLight = smgr->addLightSceneNode( 0, vector3df( -10, 200.0f, -100 ) );
	pLight->getLightData() = light;


	while(device->run())
	{

		if (EH.IsKeyDown(KEY_KEY_W))
		{
			p = PlaneNode->getPosition();
			p.Y += 2.0;
			PlaneNode->setPosition(p);
		}
		if (EH.IsKeyDown(KEY_KEY_S))
		{
			p = PlaneNode->getPosition();
			p.Y -= 2.0;
			PlaneNode->setPosition(p);
		}
		if (EH.IsKeyDown(KEY_KEY_A))
		{
			p = PlaneNode->getPosition();
			p.X -= 2.0;
			PlaneNode->setPosition(p);
		}
		if (EH.IsKeyDown(KEY_KEY_D))
		{
			p = PlaneNode->getPosition();
			p.X -= 2.0;
			PlaneNode->setPosition(p);
		}
		if (EH.IsKeyDown(KEY_RIGHT))
		{
			p = camNode->getPosition();
			p.X += 2.0;
			camNode->setPosition(p);
		}
		if (EH.IsKeyDown(KEY_LEFT))
		{
			p = camNode->getPosition();
			p.Y += 2.0;
			camNode->setPosition(p);
		}
		if (EH.IsKeyDown(KEY_LEFT))
		{
			p = camNode->getPosition();
			p.X += 2.0;
			camNode->setPosition(p);
		}



		driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	device->drop();

	return 0;
}
