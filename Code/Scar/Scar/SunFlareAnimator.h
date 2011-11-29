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
#include "Toolkit.h"
using namespace irr;

class SunFlareAnimator : public ISceneNodeAnimator
{


public:
	virtual void animateNode( ISceneNode* node, u32 timeMs ) 
	{
		core::list<ISceneNode*> nodeli, nodetemp;
		core::list<Node2DInfo> node2dinfoli;
		Node2DInfo n2dinf;
		position2df sunPos2D;
		MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
		scene::ISceneManager* smgr = pEngine->GetSceneManager();
		Toolkit tool(smgr->getActiveCamera(), pEngine->GetVideoDriver());

		core::vector3df SunPos = smgr->getSceneNodeFromName("Sun")->getPosition();
		core::vector3df CamPos = smgr->getActiveCamera()->getPosition();
		core::vector3df SunDir = ( SunPos - CamPos ).normalize();
		f32 r = 30.f; // ̫���뾶
		f32 K = 1.0;// ����ϵ��
		node->setPosition( CamPos + SunDir * 250 );
		line3df eyeline;
		eyeline.start = CamPos;
		eyeline.end = SunPos;


		nodetemp = smgr->getRootSceneNode()->getChildren();
		for ( core::list<ISceneNode*>::Iterator it = nodetemp.begin(); it != nodetemp.end(); it++ )
		{
			ErgodicTree(&nodeli, *it);
		}

		
		nodetemp.clear();
		// ����̫���Ķ�ά����
		if (!tool.GetNode2DInfo(smgr->getSceneNodeFromName("Sun"), &n2dinf))
		{
			((IBillboardSceneNode*)node)->setSize(dimension2df(0.f, 0.f));
			nodetemp = ((IBillboardSceneNode*)node)->getChildren();
			for ( core::list<ISceneNode*>::Iterator it = nodetemp.begin(); it != nodetemp.end(); it++ )
			{
				((IBillboardSceneNode*)(*it))->setSize(dimension2df(0.f, 0.f));
			}
			return;
		}

		sunPos2D = n2dinf.pos;

		// ����ռ��п�������Ķ�ά��Ϣ
		for ( core::list<ISceneNode*>::Iterator it = nodeli.begin(); it != nodeli.end(); it++ )
		{
			// ID = 10  �ǹ⻷�ڵ�
			if ( (*it)->getID() > 4000 && (*it)->getID() < 5000 || (*it)->getParent()->getID() > 4001 && (*it)->getParent()->getID() < 5000 )
				continue;
			if( (*it)->getAbsolutePosition() != SunPos && (*it)->getAbsolutePosition() != node->getAbsolutePosition() && (*it)->getAbsolutePosition() != CamPos )
			{
				nodetemp = node->getChildren();
				for (core::list<ISceneNode*>::Iterator ite = nodetemp.begin(); ite != nodetemp.end(); ite++)
				{
					if ((*it)->getAbsolutePosition() != (*ite)->getAbsolutePosition())
					{
						// ���߱���ס,���⿴����
						//(*it)->setScale( vector3df( 0.7f ) );
						//if ( (*it)->getTransformedBoundingBox().intersectsWithLine(eyeline) )
						//{
						//	// billboard��ʧ
						//	((IBillboardSceneNode*)node)->setSize(dimension2df(0.f, 0.f));
						//	nodetemp = ((IBillboardSceneNode*)node)->getChildren();
						//	for ( core::list<ISceneNode*>::Iterator it = nodetemp.begin(); it != nodetemp.end(); it++ )
						//	{
						//		((IBillboardSceneNode*)(*it))->setSize(dimension2df(0.f, 0.f));
						//	}
						//	(*it)->setScale( vector3df( 1 ) );
						//	return;
						//}
						//(*it)->setScale( vector3df( 1 ) );
						/*if(tool.GetNode2DInfo((*it), &n2dinf))
						{
							f32 alpha = 0.9f;
							n2dinf.corner[0].X *= ( 1 + alpha);
							n2dinf.corner[0].Y *= ( 1 + alpha);

							n2dinf.corner[1].X *= ( 1 - alpha);
							n2dinf.corner[1].Y *= ( 1 + alpha);

							n2dinf.corner[2].X *= ( 1 - alpha);
							n2dinf.corner[2].Y *= ( 1 - alpha);

							n2dinf.corner[3].X *= ( 1 + alpha);
							n2dinf.corner[3].Y *= ( 1 - alpha);

							node2dinfoli.push_back(n2dinf);
							break;
						}*/

						if(tool.GetNode2DInfo((*it), &n2dinf))
						{
							f32 alpha = 0.7f;
							for ( int i=0; i<4; i++ )
							{
								n2dinf.corner[i].X -= n2dinf.pos.X;
								n2dinf.corner[i].X *= alpha;
								n2dinf.corner[i].X += n2dinf.pos.X;
								n2dinf.corner[i].Y -= n2dinf.pos.Y;
								n2dinf.corner[i].Y *= alpha;
								n2dinf.corner[i].Y += n2dinf.pos.Y;
							}
							node2dinfoli.push_back(n2dinf);
							break;
						}
					}

				}
			}
		}

		
		for (core::list<Node2DInfo>::Iterator it = node2dinfoli.begin(); it != node2dinfoli.end(); it++)
		{
			// ̫������ȫ��ס
			if (tool.IsPosInCorners(sunPos2D, it->corner))
			{
				// ̫С�����嵲��ס̫��
				if (  (tool.GetRectArea(&(*it))  > tool.GetCircleArea(r) / 8)  )
				{
					// billboard��ʧ
					((IBillboardSceneNode*)node)->setSize(dimension2df(0.f, 0.f));
					nodetemp = ((IBillboardSceneNode*)node)->getChildren();
					for ( core::list<ISceneNode*>::Iterator it = nodetemp.begin(); it != nodetemp.end(); it++ )
					{
						((IBillboardSceneNode*)(*it))->setSize(dimension2df(0.f, 0.f));
					}
					return;
				}
			}// ���ܵ�סһ����
			else
			{
				// ��������ϵ��K
				f32 minR = r;
				f32 k = 1.0f; 
				f32 t;
				t = tool.GetMinDistance(sunPos2D, &(*it));
				if ( t < minR)
				{
					minR = t;
				}
				if ( minR < r )
				{
					k = minR / r;
				}
				if ( K > k )
				{
					K = k;
				}

			}

		}

		// billboard����
		((IBillboardSceneNode*)node)->setSize(dimension2df(256.f * K, 256.f * K));
		nodetemp = ((IBillboardSceneNode*)node)->getChildren();
		for ( core::list<ISceneNode*>::Iterator it = nodetemp.begin(); it != nodetemp.end(); it++ )
		{
			((IBillboardSceneNode*)(*it))->setSize(dimension2df(256.f * K,256.f * K));
		}


	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

private:
	void ErgodicTree(core::list<ISceneNode*>* pNodeli, ISceneNode* pNode )
	{
		core::list<ISceneNode*> tli = pNode->getChildren();
		// ��Ҷ�ӽڵ�
		if ( tli.getSize() == 0)
		{
			if (pNode->isVisible())
			{
				pNodeli->push_back(pNode);
			}
			
		}
		else // �ڲ��ڵ�
		{
			if (pNode->isVisible())
			{
				pNodeli->push_back(pNode);
			}
			for ( core::list<ISceneNode*>::Iterator it = tli.begin(); it != tli.end(); it++ )
			{
				ErgodicTree(pNodeli, *it );
			}
		}
	}
};

#endif // SunFlareAnimator_h__
