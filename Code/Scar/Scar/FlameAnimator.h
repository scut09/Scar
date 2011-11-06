#ifndef FlameAnimator_h__
#define FlameAnimator_h__

/********************************************************************
	创建时间:	2011/11/06
	文件名称: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\FlameAnimator.h
	作者:		$屠文翔$
	
	描述:		飞船尾焰会随着飞船速度变化而变化
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class FlameAnimator : public ISceneNodeAnimator
{

public:
	FlameAnimator();
};

#endif // FlameAnimator_h__
