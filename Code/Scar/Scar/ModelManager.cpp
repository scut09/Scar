/********************************************************************
	����ʱ��: 2011-9-28   0:18
	�ļ���:   ModelManager.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/


#include "ModelManager.h"
#include "MyIrrlichtEngine.h"


void ModelManager::LoadModels()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	auto smgr = pEngine->GetSceneManager();
	auto driver = pEngine->GetVideoDriver();

	smgr->addSkyBoxSceneNode(
		driver->getTexture("../media/irrlicht2_up.jpg"),
		driver->getTexture("../media/irrlicht2_dn.jpg"),
		driver->getTexture("../media/irrlicht2_lf.jpg"),
		driver->getTexture("../media/irrlicht2_rt.jpg"),
		driver->getTexture("../media/irrlicht2_ft.jpg"),
		driver->getTexture("../media/irrlicht2_bk.jpg"));
}
