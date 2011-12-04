#ifndef VerticalCallBack_h__
#define VerticalCallBack_h__

/********************************************************************
	��������:	2011/12/04
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\VerticalCallBack.h
	����:		������
	
	����:		
*********************************************************************/

#include "SceneNodeShader.h"

// CallBacks
// ͨ����Shader�ص�����
// �贫�������Ŀ��ڵ�
// �ں��������ͶӰ��������ʱ��
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

		//����ͶӰ����
		matrix4 worldViewProj;
		worldViewProj = driver->getTransform( ETS_PROJECTION );
		worldViewProj *= driver->getTransform( ETS_VIEW );
		worldViewProj *= driver->getTransform( ETS_WORLD );
		services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

		//����, ���֧����������
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);

		//���������
		vector3df cameraDir = ( smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getPosition() ).normalize();
		services->setVertexShaderConstant( "CameraDir", reinterpret_cast<f32*>(&cameraDir), 3);

		////�������Z����ת����
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
		
		//�������
		vector2df mouseVec = pEngine->GetDevice()->getCursorControl()->getRelativePosition();
		mouseVec -= vector2df( 0.5f );
		services->setVertexShaderConstant( "MouseVec", reinterpret_cast<f32*>(&mouseVec), 2);
	}
};

#endif // VerticalCallBack_h__
