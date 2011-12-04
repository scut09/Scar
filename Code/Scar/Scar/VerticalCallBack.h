#ifndef VerticalCallBack_h__
#define VerticalCallBack_h__

/********************************************************************
	创建日期:	2011/12/04
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\VerticalCallBack.h
	作者:		屠文翔
	
	描述:		
*********************************************************************/

#include "SceneNodeShader.h"

// CallBacks
// 通用型Shader回调函数
// 需传入参数：目标节点
// 内含世界矩阵，投影矩阵，纹理，时钟
class VerticalCallBack : public irr::video::IShaderConstantSetCallBack
{

public:
	VerticalCallBack()
	{

	}
private:
	virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
	{
		MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
		IVideoDriver* driver = pEngine->GetVideoDriver();
		ISceneManager* smgr = pEngine->GetDevice()->getSceneManager();

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

		//摄像机朝向
		vector3df cameraDir = ( smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getPosition() ).normalize();
		services->setVertexShaderConstant( "CameraDir", reinterpret_cast<f32*>(&cameraDir), 3);

		////摄像机绕Z轴旋转矩阵
		//matrix4 rotMat;
		//rotMat.makeIdentity();
		//vector3df OldYAsis = smgr->getActiveCamera()->getUpVector();
		//vector3df OldXAsis = OldYAsis.crossProduct( cameraDir );
		//vector2df NewYAsis = vector2df( OldYAsis.X, OldYAsis.Y ).normalize();
		//vector2df NewXAsis = vector2df( OldXAsis.X, OldXAsis.Y ).normalize();
		//rotMat[0] = NewXAsis.X;		rotMat[1] = NewYAsis.X;
		//rotMat[4] = NewXAsis.Y;		rotMat[5] = NewYAsis.Y;
		////rotMat.makeInverse();
		//services->setVertexShaderConstant( "RotMat", rotMat.pointer(), 16);

		////...
		//matrix4 offsetMat;
		//offsetMat.makeIdentity();
		//offsetMat.setTranslation( vector3df(0, 0, 10) );
		//matrix4 myTransMat;
		////myTransMat = driver->getTransform( ETS_PROJECTION );
		////myTransMat *= driver->getTransform( ETS_VIEW );
		//myTransMat *= smgr->getActiveCamera()->getAbsoluteTransformation();
		//myTransMat *= offsetMat;
		//myTransMat *= rotMat;
		//services->setVertexShaderConstant( "MyTransMat", myTransMat.pointer(), 16);
		
		//鼠标向量
		vector2df mouseVec = pEngine->GetDevice()->getCursorControl()->getRelativePosition();
		mouseVec -= vector2df( 0.5f );
		services->setVertexShaderConstant( "MouseVec", reinterpret_cast<f32*>(&mouseVec), 2);
	}
};

#endif // VerticalCallBack_h__
