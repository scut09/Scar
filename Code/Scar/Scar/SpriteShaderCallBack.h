#ifndef SpriteShaderCallBack_h__
#define SpriteShaderCallBack_h__

/********************************************************************
	创建时间:	2011/12/04
	文件名称: 	SpriteShaderCallBack
	作者:		屠文翔 - Kid
	
	描述:		当多帧图片集合成一个图片时，使用该回调函数控制当前绘制的行号列号
				专供片段选择器用
				使用SpriteControlAnimatorl来控制
*********************************************************************/

#include "SceneNodeShader.h"

//行和列的结构体
struct SpriteRowCol
{
	f32 col;	//列
	f32 row;	//行
};

class SpriteShaderCallBack : public irr::video::IShaderConstantSetCallBack
{
	SpriteRowCol* RowCol;

public:
	SpriteShaderCallBack( SpriteRowCol* rowCol )
	{

	}

private:
	virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
	{
		IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetDevice()->getSceneManager();

		//世界投影矩阵
		matrix4 worldViewProj;
		worldViewProj = driver->getTransform( ETS_PROJECTION );
		worldViewProj *= driver->getTransform( ETS_VIEW );
		worldViewProj *= driver->getTransform( ETS_WORLD );
		services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

		//纹理, 最多支持四重纹理
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

		//行列
		services->setVertexShaderConstant( "Col", (f32*)&RowCol->col, 1);
		services->setVertexShaderConstant( "Row", (f32*)&RowCol->row, 1);

		//时钟
		f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);
	}
};

#endif // SpriteShaderCallBack_h__
