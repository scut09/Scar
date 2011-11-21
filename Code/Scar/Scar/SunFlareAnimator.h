#ifndef SunFlareAnimator_h__
#define SunFlareAnimator_h__

/********************************************************************
	��������:	2011/11/21
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\SunFlareAnimator.h
	����:		������
	
	����:		������η�λ����ʹ̫��������Ծ�ͷ���־�ֹ
*********************************************************************/

#include "ISceneNode.h"
#include "MyIrrlichtEngine.h"
using namespace irr;

class SunFlareAnimator : public ISceneNodeAnimator
{


public:
	virtual void animateNode( ISceneNode* node, u32 timeMs ) 
	{
		MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
		scene::ISceneManager* smgr = pEngine->GetSceneManager();

		core::vector3df SunPos = smgr->getSceneNodeFromName("Sun")->getAbsolutePosition();
		core::vector3df CamPos = smgr->getActiveCamera()->getAbsolutePosition();
		core::vector3df SunDir = ( SunPos - CamPos ).normalize();

		node->setPosition( CamPos + SunDir * 250 );
	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

};

#endif // SunFlareAnimator_h__
