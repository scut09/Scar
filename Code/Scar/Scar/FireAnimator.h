#ifndef FireAnimator_h__
#define FireAnimator_h__

/********************************************************************
	创建日期:	2011/10/27
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\FireAnimator.h
	作者:		屠文翔
	
	描述:		控制飞船开火
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class FireAnimator : public ISceneNodeAnimator
{
public:
	FireAnimator()
	{

	}

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // FireAnimator_h__
