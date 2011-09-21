///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/10 16:39
//Describe: 游戏入口
///////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "InitUI.h"
#include "SelectGame.h"
#include "DoGame.h"
#include "IGlobe.h"

#include "MyEventReceiver.h"
#pragma comment (lib , "irrlicht.lib")

IMyUIScene*		g_currentUI = NULL;
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE , LPSTR ,  int )
{

	CMyEventReceiver receiver;
	IrrlichtDevice* device = createDevice( EDT_DIRECT3D9,dimension2d<u32>(1024,768),16,false,true);
	if (device == 0)
		return 0;

	// get the video driver
	video::IVideoDriver* driver = device->getVideoDriver();
	// get the scene manager
	scene::ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* env = device->getGUIEnvironment();

	env->getSkin()->setColor ( EGDC_BUTTON_TEXT, video::SColor(240,0xFF,0xFF,0xFF) );
	env->getSkin()->setColor ( EGDC_3D_HIGH_LIGHT, video::SColor(240,0x1f,0x26,0x24) );
	env->getSkin()->setColor ( EGDC_3D_FACE, video::SColor(240,0x4f,0x83,0x6c) );
	env->getSkin()->setColor ( EGDC_WINDOW, video::SColor(240,0x76,0x76,0x76) );
	
	device->setWindowCaption(L"My CS");

	env->getSkin()->setFont(env->getFont("font\\myfont.xml"));

	device->setEventReceiver(&receiver);

	CInitUI InitUI;
	CSelectGame selectGameUI;
	CDoGame		doGameUI;

	//------------------------------
	//Desc:初始化静态值
	//------------------------------
	IMyUIScene::m_device = device;
	IMyUIScene::m_driver = driver;
	IMyUIScene::m_smgr = smgr;
	IMyUIScene::m_guienv = env;
	IMyUIScene::m_event = &receiver;

	IGlobe::g_device = device;
	IGlobe::g_driver = driver;
	IGlobe::g_smgr = smgr;
	IGlobe::g_guienv = env;


	InitUI.m_next = &selectGameUI;
	selectGameUI.m_front = &InitUI;
	selectGameUI.m_next = &doGameUI;
	doGameUI.m_front = &selectGameUI;

	InitUI.InitUI();

	IMyUIScene::m_CurrentUI = &g_currentUI;

	g_currentUI = &InitUI;

	
	int lastFPS = 0;
	irr::ITimer* timer = device->getTimer();
	s32 oldtime = timer->getRealTime();
	s32 nowtime = 0;
	s32 bt;
	while(device->run())
	{
		nowtime = timer->getRealTime();
		bt = nowtime - oldtime;
		if (bt < 15)			//帧速控制
		{
			Sleep(1);			//让出CPU 防止CPU消耗
			continue;
		}
		oldtime = nowtime;		

		g_currentUI->Updata();

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		if (device->getGUIEnvironment() != NULL)
		{
			device->getGUIEnvironment()->drawAll(); 
		}		
		driver->endScene();

		/*int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = L"MyCS —— By Tian QQ:78001229 FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}*/
	}	
	return 0;
}