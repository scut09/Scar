#ifndef SunFlareAnimator_h__
#define SunFlareAnimator_h__

/********************************************************************
	创建日期:	2011/11/21
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\SunFlareAnimator.h
	作者:		屠文翔
	
	描述:		计算光晕方位，并使太阳光晕相对镜头保持静止
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
