#ifndef RunWay_h__
#define RunWay_h__

/********************************************************************
	��������:	2011/11/17
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\RunWay.h
	����:		������
	
	����:		����һ��Ư�����ܵ�
*********************************************************************/

#include "SceneNodeShader.h"
#include "irrlicht.h"
#include "MyIrrlichtEngine.h"
using namespace irr;

ISceneNode* CreateRunWay( core::vector3df from = core::vector3df( 0 ), core::vector3df to = core::vector3df( 0, 0, 1000 ),
	video::SColorf colorFrom = video::SColorf( 1, 1, 0, 1 ), video::SColorf colorTo = video::SColorf( .1647f, 1, 0, 1 ),
	s32 numOfArrows = 15,
	f32 width = 300 )
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	ISceneManager* smgr = pEngine->GetSceneManager();
	IVideoDriver* driver = pEngine->GetVideoDriver();

	// �ܵ����ڵ�
	ISceneNode* runWay = smgr->addEmptySceneNode();
	ISceneNode* node = smgr->addMeshSceneNode( smgr->getMesh( "../media/UnitModel/UnitPlane.obj" ), runWay );
	node->setScale( vector3df( 90, 176, 1 ) );
	node->setPosition( vector3df( 0, 0, 50 ) );
	node->setMaterialTexture( 0, driver->getTexture( "../media/UIResource/Game/arrow.png" ) );
	node->setMaterialFlag( EMF_LIGHTING, false );
	node->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
	/*for( int i=0; i<numOfArrows; i++ )
	{
		
	}*/

	return runWay;
}

#endif // RunWay_h__
