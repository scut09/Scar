#include "Toolkit.h"


Toolkit::Toolkit(ICameraSceneNode* pCamara, IVideoDriver* pDriver)
{
	m_pCamara = pCamara;
	m_pDriver = pDriver;
}


Toolkit::~Toolkit(void)
{
}

/************************************************************************/
/* 作者：杨旭瑜
   描述：得到模型在2D屏幕上的信息，包括在屏幕上的大小，在屏幕上的位置
*/
/************************************************************************/
bool Toolkit::GetNode2DInfo(ISceneNode* pNode, Node2DInfo* pNode2DInfo)
{

	// 计算三维物体在屏幕上的坐标
	position2df screamPoint;
	if ( !To2DScreamPos(pNode->getAbsolutePosition(), &(screamPoint)) )
	{
		return false;
	}

	pNode2DInfo->pos.X = screamPoint.X;
	pNode2DInfo->pos.Y = screamPoint.Y;
	s32 width, height;
	f32 xMax, xMin, yMax, yMin;
	xMin = xMax = yMin = yMax = 0;

	width = m_pDriver->getViewPort().getWidth();
	height = m_pDriver->getViewPort().getHeight();



	vector3df pEdges[8];
	position2df pEdgesPos[8];
	// 去物体的包围盒，用于计算物体在屏幕上的2D大小
	pNode->getTransformedBoundingBox().getEdges(pEdges);
	
	for (int i = 0; i < 8; i++)
	{
		if ( !To2DScreamPos(pEdges[i], &pEdgesPos[i]) )
			return false;
	}

	// 查找二维上相距最远的两个点
	xMin = xMax = pEdgesPos[0].X;
	yMin = yMax = pEdgesPos[0].Y;
	for ( int i = 0; i < 4; i++ )
	{
		pNode2DInfo->corner[i].X = xMin;
		pNode2DInfo->corner[i].Y = yMin;
	}

	for (int i = 0; i < 8; i++)
	{
		if(pEdgesPos[i].X > xMax)
		{
			xMax = pEdgesPos[i].X;
			pNode2DInfo->corner[1].X = xMax;
			pNode2DInfo->corner[2].X = xMax;
		}

		if (pEdgesPos[i].X < xMin)
		{
			xMin = pEdgesPos[i].X;
			pNode2DInfo->corner[0].X = xMin;
			pNode2DInfo->corner[3].X = xMin;
		}
		if (pEdgesPos[i].Y > yMax)
		{
			yMax = pEdgesPos[i].Y;
			pNode2DInfo->corner[2].Y = yMax;
			pNode2DInfo->corner[3].Y = yMax;
		}
		if (pEdgesPos[i].Y < yMin)
		{
			yMin = pEdgesPos[i].Y;
			pNode2DInfo->corner[0].Y = yMin;
			pNode2DInfo->corner[1].Y = yMin;
		}
	}

	if (xMax - xMin == 0 || yMax - yMin == 0)
	{
		return false;
	}

	pNode2DInfo->height = (s32)abs(yMax - yMin);
	pNode2DInfo->width = (s32)abs(xMax - xMin);
	
	return true;
}

/************************************************************************/
/* 作者：杨旭瑜
   描述：通过3D坐标计算出其屏幕坐标
*/
/************************************************************************/
bool Toolkit::To2DScreamPos(vector3df v, position2df* p)
{
	s32 width, height;

	width = m_pDriver->getViewPort().getWidth();
	height = m_pDriver->getViewPort().getHeight();

	f32 in[4];
	in[0] = v.X;
	in[1] = v.Y;
	in[2] = v.Z;
	in[3] = 1.0;
	 
	core::matrix4 ModleView;
	core::matrix4 Project;

	// 得到照相机的坐标矩阵
	ModleView = m_pCamara->getViewMatrix();

	ModleView.multiplyWith1x4Matrix(in);
	
	// 不在视域体内就不计算
	if ( in[2] < m_pCamara->getNearValue() || in[2] > m_pCamara->getFarValue() )
	{
		return false;
	}

	Project = m_pCamara->getProjectionMatrix();

	Project.multiplyWith1x4Matrix(in);

	//齐次向量的第四项不能为0
	if(in[3] == 0.0)
		return false;

	//向量齐次化标准化
	in[0] /= in[3];
	in[1] /= in[3];
	in[2] /= in[3];
	//视口向量的作用

	p->X = (1 + in[0]) * width / 2;
	p->Y = (1 + in[1]) * height / 2;

	p->Y = height - p->Y;

	return true;
}

/************************************************************************/
/* 作者：杨旭瑜
   描述：判断一个二维屏幕的点在不在一个由四个点围成的矩形中
*/
/************************************************************************/
bool Toolkit :: IsPosInCorners(core::position2df v, core::position2df p[4])
{
	int outsideweight[4] = {0};

	for (int i = 0; i < 4; i++)
	{
		if (v.Y < p[i].Y)
		{
			outsideweight[0]++;
		}
		if (v.X > p[i].X)
		{
			outsideweight[1]++;
		}
		if (v.Y > p[i].Y)
		{
			outsideweight[2]++;
		}
		if (v.X < p[i].X)
		{
			outsideweight[3]++;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (outsideweight[i] == 4)
		{
			return false;
		}
	}

	return true;
}

/************************************************************************/
/* 作者：杨旭瑜
   描述：计算圆的面积
*/
/************************************************************************/
f32 Toolkit :: GetCircleArea(f32 r)
{
	return 3.1415926f * r * r;
}

/************************************************************************/
/* 作者：杨旭瑜
   描述：3d物体在pin
*/
/************************************************************************/
f32 Toolkit :: GetRectArea(Node2DInfo* pNode2DInfo)
{
	return (f32)pNode2DInfo->height * pNode2DInfo->width; 
}

f32 Toolkit :: GetDistance(position2df p1, position2df p2)
{
	return (f32)sqrt( (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y));
}

f32 Toolkit :: GetMinDistance(position2df p, Node2DInfo* pNode2DInfo)
{
	core::line2df l[4];
	f32 minDis = 0.f;
	l[0].start = pNode2DInfo->corner[0];
	l[0].end = pNode2DInfo->corner[1];

	l[1].start = pNode2DInfo->corner[1];
	l[1].end = pNode2DInfo->corner[2];

	l[2].start = pNode2DInfo->corner[2];
	l[2].end = pNode2DInfo->corner[3];

	l[3].start = pNode2DInfo->corner[3];
	l[3].end = pNode2DInfo->corner[0];
	minDis = GetDistance(l[0].getClosestPoint(p), p);
	for (int i = 0; i < 4; i++)
	{
		f32 t = GetDistance(l[i].getClosestPoint(p), p);
		if ( minDis > t )
		{
			minDis = t;
		}
	}
	
	return minDis;
}