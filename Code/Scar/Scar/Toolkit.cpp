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
	// ������ά��������Ļ�ϵ�����
	if ( !To2DScreamPos(pNode->getPosition(), &(pNode2DInfo->pos)) )
	{
		return false;
	}

	s32 width, height;

	width = m_pDriver->getViewPort().getWidth();
	height = m_pDriver->getViewPort().getHeight();

	// ��������ӿ�,�򷵻�false
	if ( pNode2DInfo->pos.X >= width || pNode2DInfo->pos.Y >= height )
	{
		return false;
	}

	vector3df pEdges[8];
	position2d<s32> pEdgesPos[8];
	// ȥ����İ�Χ�У����ڼ�����������Ļ�ϵ�2D��С
	pNode->getTransformedBoundingBox().getEdges(pEdges);
	
	for (int i = 0; i < 8; i++)
	{
		if ( !To2DScreamPos(pEdges[i], &pEdgesPos[i]) )
			return false;
	}

	// ��Χ�е���С���������0��7
	pNode2DInfo->width = abs(pEdgesPos[0].X - pEdgesPos[7].X);
	pNode2DInfo->height = abs(pEdgesPos[0].Y - pEdgesPos[7].Y);

	return true;
}

/************************************************************************/
/* ���ߣ������
   ������ͨ��3D������������Ļ����
*/
/************************************************************************/
bool Toolkit::To2DScreamPos(vector3df v, position2d<s32>* p)
{
	s32 width, height;

	width = m_pDriver->getViewPort().getWidth();
	height = m_pDriver->getViewPort().getHeight();

	f32 in[4];
	in[0] = v.X;
	in[1] = v.Y;
	in[2] = v.Z;
	in[3] = 1.0;

	matrix4 ModleView;
	matrix4 Project;

	// �õ���������������
	ModleView = m_pCamara->getViewMatrix();

	ModleView.multiplyWith1x4Matrix(in);

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
}
