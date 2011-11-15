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
/* ���ߣ������
   �������õ�ģ����2D��Ļ�ϵ���Ϣ����������Ļ�ϵĴ�С������Ļ�ϵ�λ��
*/
/************************************************************************/
bool Toolkit::GetNode2DInfo(ISceneNode* pNode, Node2DInfo* pNode2DInfo)
{
	core::aabbox3df ViewBox = m_pCamara->getViewFrustum()->getBoundingBox();
	if (!ViewBox.isPointInside(pNode->getPosition()))
	{
		return false;
	}
	
	// ������ά��������Ļ�ϵ�����
	position2df screamPoint;
	if ( !To2DScreamPos(pNode->getPosition(), &(screamPoint)) )
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

	// ��������ӿ�,�򷵻�false
	if ( pNode2DInfo->pos.X > width || pNode2DInfo->pos.Y > height ||  
		pNode2DInfo->pos.X < 0|| pNode2DInfo->pos.Y < 0 )
	{
		return false;
	}

	vector3df pEdges[8];
	position2df pEdgesPos[8];
	// ȥ����İ�Χ�У����ڼ�����������Ļ�ϵ�2D��С
	pNode->getTransformedBoundingBox().getEdges(pEdges);
	
	for (int i = 0; i < 8; i++)
	{
		if ( !To2DScreamPos(pEdges[i], &pEdgesPos[i]) )
			return false;
	}

	// ���Ҷ�ά�������Զ��������
	xMin = xMax = pEdgesPos[0].X;
	yMin = yMax = pEdgesPos[0].Y;

	for (int i = 0; i < 8; i++)
	{
		if(pEdgesPos[i].X > xMax)
		{
			xMax = pEdgesPos[i].X;
		}
		if (pEdgesPos[i].X < xMin)
		{
			xMin = pEdgesPos[i].X;
		}
		if (pEdgesPos[i].Y > yMax)
		{
			yMax = pEdgesPos[i].Y;
		}
		if (pEdgesPos[i].Y < yMin)
		{
			yMin = pEdgesPos[i].Y;
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
/* ���ߣ������
   ������ͨ��3D������������Ļ����
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

	// �õ���������������
	ModleView = m_pCamara->getViewMatrix();

	ModleView.multiplyWith1x4Matrix(in);
	
	// �����������ھͲ�����
	if ( in[2] < m_pCamara->getNearValue() || in[2] > m_pCamara->getFarValue() )
	{
		return false;
	}

	Project = m_pCamara->getProjectionMatrix();

	Project.multiplyWith1x4Matrix(in);

	//��������ĵ������Ϊ0
	if(in[3] == 0.0)
		return false;

	//������λ���׼��
	in[0] /= in[3];
	in[1] /= in[3];
	in[2] /= in[3];
	//�ӿ�����������

	p->X = (1 + in[0]) * width / 2;
	p->Y = (1 + in[1]) * height / 2;

	p->Y = height - p->Y;

	return true;
}
