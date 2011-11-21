#ifndef SunFlareCallBack_h__
#define SunFlareCallBack_h__

/********************************************************************
	创建日期:	2011/11/21
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\SunFlareCallBack.h
	作者:		屠文翔
	
	描述:		提供给太阳光晕的专用回调函数
*********************************************************************/

#include <irrlicht.h>
#include <iostream>
#include "MyIrrlichtEngine.h"
using namespace irr;

class SunFlareCallBack : public video::IShaderConstantSetCallBack
{
	scene::ISceneNode* Node;
public:
	SunFlareCallBack( scene::ISceneNode* node )
		:Node( node )
	{

	}

	virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
	{
		video::IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		scene::ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetDevice()->getSceneManager();

		//世界投影矩阵
		matrix4 worldViewProj;
		worldViewProj = driver->getTransform( ETS_PROJECTION );
		worldViewProj *= driver->getTransform( ETS_VIEW );
		worldViewProj *= driver->getTransform( ETS_WORLD );
		services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

		////世界矩阵逆矩阵
		//matrix4 invWorld = driver->getTransform( ETS_WORLD );
		//invWorld.makeInverse();
		//services->setVertexShaderConstant( "InvWorld", invWorld.pointer(), 16);

		////世界矩阵转置矩阵
		//matrix4 transWorld = driver->getTransform( ETS_WORLD );
		//transWorld = transWorld.getTransposed();
		//services->setVertexShaderConstant( "TransWorld", transWorld.pointer(), 16);

		//纹理, 最多支持四重纹理
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		/*services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);*/

		////摄像机坐标
		//vector3df cameraPos = smgr->getActiveCamera()->getAbsolutePosition();
		//services->setVertexShaderConstant( "CameraPos", reinterpret_cast<f32*>(&cameraPos), 3);

		////摄像机朝向
		//vector3df cameraDir = ( smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getPosition() ).normalize();
		//services->setVertexShaderConstant( "CameraDir", reinterpret_cast<f32*>(&cameraDir), 3);

		////时钟
		//f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		//services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);

		//节点到太阳位置的方向单位向量
		ISceneNode* Sun = smgr->getSceneNodeFromName( "Sun" );
		vector3df sunNormal = ( Sun->getAbsolutePosition() - Node->getAbsolutePosition() ).normalize();
		services->setVertexShaderConstant( "SunNormal", reinterpret_cast<f32*>(&sunNormal), 3 );

		//根据太阳位置不同而改变自己的位置
		core::matrix4 offsetMat;
		offsetMat.makeIdentity();
		offsetMat.setTranslation( (sunNormal * 250) );
		services->setVertexShaderConstant( "OffsetMat", offsetMat.pointer(), 16);

	}

};

#endif // SunFlareCallBack_h__
