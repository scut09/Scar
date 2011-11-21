#ifndef SunFlareCallBack_h__
#define SunFlareCallBack_h__

/********************************************************************
	��������:	2011/11/21
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\SunFlareCallBack.h
	����:		������
	
	����:		�ṩ��̫�����ε�ר�ûص�����
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

		//����ͶӰ����
		matrix4 worldViewProj;
		worldViewProj = driver->getTransform( ETS_PROJECTION );
		worldViewProj *= driver->getTransform( ETS_VIEW );
		worldViewProj *= driver->getTransform( ETS_WORLD );
		services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

		////������������
		//matrix4 invWorld = driver->getTransform( ETS_WORLD );
		//invWorld.makeInverse();
		//services->setVertexShaderConstant( "InvWorld", invWorld.pointer(), 16);

		////�������ת�þ���
		//matrix4 transWorld = driver->getTransform( ETS_WORLD );
		//transWorld = transWorld.getTransposed();
		//services->setVertexShaderConstant( "TransWorld", transWorld.pointer(), 16);

		//����, ���֧����������
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		/*services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);*/

		////���������
		//vector3df cameraPos = smgr->getActiveCamera()->getAbsolutePosition();
		//services->setVertexShaderConstant( "CameraPos", reinterpret_cast<f32*>(&cameraPos), 3);

		////���������
		//vector3df cameraDir = ( smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getPosition() ).normalize();
		//services->setVertexShaderConstant( "CameraDir", reinterpret_cast<f32*>(&cameraDir), 3);

		////ʱ��
		//f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		//services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);

		//�ڵ㵽̫��λ�õķ���λ����
		ISceneNode* Sun = smgr->getSceneNodeFromName( "Sun" );
		vector3df sunNormal = ( Sun->getAbsolutePosition() - Node->getAbsolutePosition() ).normalize();
		services->setVertexShaderConstant( "SunNormal", reinterpret_cast<f32*>(&sunNormal), 3 );

		//����̫��λ�ò�ͬ���ı��Լ���λ��
		core::matrix4 offsetMat;
		offsetMat.makeIdentity();
		offsetMat.setTranslation( (sunNormal * 250) );
		services->setVertexShaderConstant( "OffsetMat", offsetMat.pointer(), 16);

	}

};

#endif // SunFlareCallBack_h__
