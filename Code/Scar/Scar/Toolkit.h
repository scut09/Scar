/*
** ���ߣ������
** ˵���������࣬�ṩ��������
**
*/

#ifndef _TOOLKIT_H_
#define _TOOLKIT_H_

#include <cmath>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

struct Node2DInfo
{
	s32 width;
	s32 height;
	position2d<f32> pos;
};



class Toolkit
{
public:
	Toolkit(ICameraSceneNode* pCamara, IVideoDriver* pDriver);
	~Toolkit(void);
	bool GetNode2DInfo(ISceneNode* pNode, Node2DInfo* pNode2DInfo);

private:
	bool To2DScreamPos(vector3df v, position2d<f32>* p);

private:
	ICameraSceneNode*	m_pCamara;
	IVideoDriver*		m_pDriver;
};

#endif
