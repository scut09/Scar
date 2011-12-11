#ifndef BillBoardExplosionAnimator_h__
#define BillBoardExplosionAnimator_h__


#include "ISceneNode.h"
#include "MyIrrlichtEngine.h"
#include "Toolkit.h"

using namespace irr;

class BillBoardExplosionAnimator : public ISceneNodeAnimator
{


public:
	BillBoardExplosionAnimator(f32 d) : ChangeRate(1.0f), State(0), IsFirst(true)
	{
		MaxSize.Width = MaxSize.Height = d * 5;
	}

	virtual void animateNode( ISceneNode* node, u32 timeMs ) 
	{
		if (IsFirst)
		{
			OriginalSize = ((IBillboardSceneNode*)node)->getSize();
			MaxRate =  MaxSize.Width / OriginalSize.Width;
			IsFirst = false;
		}

		f32 increasestep, discreasestep;
		increasestep = MaxRate / 200;
		discreasestep = MaxRate / 150;
		increasestep *= 1.5f;
		discreasestep *= 1.5f;

		dimension2df size;
		switch( State )
		{
		case 0:
			size = OriginalSize * ChangeRate;
			ChangeRate += increasestep;
			if ( ChangeRate > MaxRate )
			{
				State = 1;
			}
			break;
		case 1:
			size = OriginalSize * ChangeRate;
			ChangeRate -= discreasestep;
			if ( ChangeRate < 1.50f )
			{
				((IBillboardSceneNode*)node)->setSize(dimension2df(0.f, 0.f));
				MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator(10);
				return;
			}
			break;
		}


		((IBillboardSceneNode*)node)->setSize(size);


	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}
private:
	f32 ChangeRate;
	f32 MaxRate;
	s32 State;
	dimension2df OriginalSize;
	bool IsFirst;
	dimension2df MaxSize;
	vector3df Pos;
};

#endif // BillBoardExplosionAnimator_h__
