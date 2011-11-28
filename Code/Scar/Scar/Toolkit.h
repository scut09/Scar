/*
** 作者：杨旭瑜
** 说明：工具类，提供辅助功能
**
*/

#ifndef _TOOLKIT_H_
#define _TOOLKIT_H_

#include <cmath>
#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace video;

using core::vector3df;
using core::aabbox3df;
using core::dimension2df;
using core::position2df;

struct Node2DInfo
{
	s32 width;
	s32 height;
	core::position2df pos;
	core::position2df corner[4];
};



class Toolkit
{
public:
	Toolkit(ICameraSceneNode* pCamara, IVideoDriver* pDriver);
	~Toolkit(void);
	bool GetNode2DInfo(ISceneNode* pNode, Node2DInfo* pNode2DInfo);
	bool To2DScreamPos(vector3df v, core::position2df* p);
	bool IsPosInCorners(core::position2df v, core::position2df p[4]);
	f32 GetCircleArea(f32 r);
	f32 GetRectArea(Node2DInfo* pNode2DInfo);
	f32 GetDistance(position2df p1, position2df p2);
	f32 GetMinDistance(position2df p, Node2DInfo* pNode2DInfo);
private:
	ICameraSceneNode*	m_pCamara;
	IVideoDriver*		m_pDriver;
};

#endif
