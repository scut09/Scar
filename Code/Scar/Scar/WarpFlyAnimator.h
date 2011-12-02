#ifndef WarpFlyAnimator_h__
#define WarpFlyAnimator_h__

//×÷Õß£º ÑîÐñè¤

#include "ISceneNode.h"
#include "MyIrrlichtEngine.h"

using namespace irr;


class WarpTubeCallBack : public video::IShaderConstantSetCallBack
{
private:
	f32  Begin;
	bool IsFirst;
	s32  State;
	f32  Alpha;
	f32  Duration;
	f32  Speed;
	f32  IncreasingRate;

public:
	WarpTubeCallBack(f32 d = 15000) : IsFirst( true ), State(-1), Alpha(1.0f), Duration(d), Speed(0.0f), IncreasingRate(1.0f){}

	void SetState( s32 s ){ State = s; IsFirst = true; }

	virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
	{
		switch( State )
		{
		case 0:
			if (IsFirst)
			{
				Alpha = 0.0f;
				IsFirst = false;
			}
			Alpha += 0.005f;
			Speed += 0.001f * IncreasingRate;
			if (Alpha > 1)
			{
				Alpha = 1.0f;
				Speed += 0.001f * IncreasingRate;
				
				if (IncreasingRate < 10)
				{
					IncreasingRate+=0.01f;
				}
				else
				{
					State = 1;
					IsFirst = true;
					break;
				}
			}
			if (IncreasingRate < 10)
			{
				IncreasingRate+=0.01f;
			}
			break;

		case 1:
			Alpha = 1.0f;
			IncreasingRate = 10.f;
			Speed += 0.001f * IncreasingRate;
			IsFirst = true;
			break;

		case 2:
			if (IsFirst)
			{
				Alpha = 1.0f;
				IncreasingRate = 10.f;
				IsFirst = false;
			}
			Alpha -= 0.005f;
			Speed += 0.001f * IncreasingRate;
			if (Alpha <= 0.0f)
			{
				Alpha = 0.0f;
				Speed += 0.001f * IncreasingRate;
				if (IncreasingRate > 1.0f )
				{
					IncreasingRate-=0.01f;
				}
				else
				{
					State = 3;
					break;
				}
				
			}
			if (IncreasingRate > 1.0f)
			{
				IncreasingRate-=0.01f;
			}
			break;

		case 3:
			return;
			break;

		default:
			return;
		}

		IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetDevice()->getSceneManager();
		

		//ÎÆÀí
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

		services->setPixelShaderConstant( "Speed", (f32*)&Speed, 1);

		services->setPixelShaderConstant( "Alpha", (f32*)&Alpha, 1);



	}
};




class WarpFlyAnimator : public ISceneNodeAnimator
{


public:
	WarpFlyAnimator()
	{
		m_pSmgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
		m_pDriver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
	}

	virtual void animateNode( ISceneNode* node, u32 timeMs ) 
	{
		m_pShip = MyIrrlichtEngine::GetEngine()->GetCurrentPlayer()->GetShip();
		node->setPosition( m_pShip->getAbsolutePosition() );
		node->setRotation( m_pShip->getRotation() );
	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

private:
	IShip* m_pShip;
	ISceneManager* m_pSmgr;
	irr::video::IVideoDriver* m_pDriver;

};

#endif // WarpFlyAnimator_h__
