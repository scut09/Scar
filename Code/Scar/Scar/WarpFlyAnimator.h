#ifndef WarpFlyAnimator_h__
#define WarpFlyAnimator_h__

//作者： 杨旭瑜

#include "ISceneNode.h"
#include "MyIrrlichtEngine.h"

using namespace irr;


// 给跑道应用的Shader的回调函数
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
		f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		
		switch( State )
		{
		case 0:
			if (IsFirst)
			{
				Begin = timeMs;
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
				Begin = timeMs;
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
		

		//纹理
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

		services->setPixelShaderConstant( "Speed", (f32*)&Speed, 1);

		services->setPixelShaderConstant( "Alpha", (f32*)&Alpha, 1);

		printf("%f \n", Alpha);

	}
};




class WarpFlyAnimator : public ISceneNodeAnimator
{


public:
	WarpFlyAnimator()
	{

	}

	virtual void animateNode( ISceneNode* node, u32 timeMs ) 
	{


	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

private:
	
};

#endif // WarpFlyAnimator_h__
