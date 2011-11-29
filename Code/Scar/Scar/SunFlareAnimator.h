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
		f32 r = 30.f; // 太阳半径
		f32 K = 1.0;// 缩放系数
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
		// 计算太阳的二维坐标
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

		// 计算空间中可视物体的二维信息
		for ( core::list<ISceneNode*>::Iterator it = nodeli.begin(); it != nodeli.end(); it++ )
		{
			// ID = 10  是光环节点
			if ( (*it)->getID() > 4000 && (*it)->getID() < 5000 || (*it)->getParent()->getID() > 4001 && (*it)->getParent()->getID() < 5000 )
				continue;
			if( (*it)->getAbsolutePosition() != SunPos && (*it)->getAbsolutePosition() != node->getAbsolutePosition() && (*it)->getAbsolutePosition() != CamPos )
			{
				nodetemp = node->getChildren();
				for (core::list<ISceneNode*>::Iterator ite = nodetemp.begin(); ite != nodetemp.end(); ite++)
				{
					if ((*it)->getAbsolutePosition() != (*ite)->getAbsolutePosition())
					{
						// 视线被挡住,阳光看不见
						//(*it)->setScale( vector3df( 0.7f ) );
						//if ( (*it)->getTransformedBoundingBox().intersectsWithLine(eyeline) )
						//{
						//	// billboard消失
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
			// 太阳被完全挡住
			if (tool.IsPosInCorners(sunPos2D, it->corner))
			{
				// 太小的物体挡不住太阳
				if (  (tool.GetRectArea(&(*it))  > tool.GetCircleArea(r) / 8)  )
				{
					// billboard消失
					((IBillboardSceneNode*)node)->setSize(dimension2df(0.f, 0.f));
					nodetemp = ((IBillboardSceneNode*)node)->getChildren();
					for ( core::list<ISceneNode*>::Iterator it = nodetemp.begin(); it != nodetemp.end(); it++ )
					{
						((IBillboardSceneNode*)(*it))->setSize(dimension2df(0.f, 0.f));
					}
					return;
				}
			}// 可能挡住一部分
			else
			{
				// 计算缩放系数K
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

		// billboard缩放
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
		// 是叶子节点
		if ( tli.getSize() == 0)
		{
			if (pNode->isVisible())
			{
				pNodeli->push_back(pNode);
			}
			
		}
		else // 内部节点
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
