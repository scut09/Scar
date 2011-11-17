#ifndef RunWay_h__
#define RunWay_h__

/********************************************************************
	��������:	2011/11/17
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\RunWay.h
	����:		������
	
	����:		����һ��Ư�����ܵ�
				Ĭ�ϳ��� ���� 0�� 0�� 1 ��
				��Ҫ�����ܵ��������ڸ��ڵ���Ӧ����ת
*********************************************************************/

#include "SceneNodeShader.h"
#include "irrlicht.h"
#include "MyIrrlichtEngine.h"
#include "SceneNodeShader.h"
using namespace irr;

// ���ܵ�Ӧ�õ�Shader�Ļص�����
class RunWayCallBack : public video::IShaderConstantSetCallBack
{
	f32 Num;				// ������ɫ�仯
	core::vector3df ColFrom;		// ��ʼ��ɫ
	core::vector3df ColOffset;		// ��ֹ��ɫ
	f32 Begin;						// ������ʼʱ��

public:
	RunWayCallBack( f32 num, core::vector3df colFrom, vector3df colOffset, f32 begin )
		: Num( num ), ColFrom( colFrom ), ColOffset( colOffset ), Begin( begin )
	{
		
	}

	virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
	{
		IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetDevice()->getSceneManager();

		//����
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

		// ��ɫ
		services->setPixelShaderConstant( "ColFrom", reinterpret_cast<f32*>(&ColFrom), 3);
		services->setPixelShaderConstant( "ColOffset", reinterpret_cast<f32*>(&ColOffset), 3);

		// �ڼ�����������ɫ�仯
		services->setPixelShaderConstant( "Num", (f32*)&Num, 1);

		// ʱ��
		f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		services->setPixelShaderConstant( "TimeMs", (f32*)&timeMs, 1);

		// ��ʼʱ��
		services->setPixelShaderConstant( "Begin", (f32*)&Begin, 1);
	}
};

// �ܵ����ֵĶ���
class RunWayBlink : public scene::ISceneNodeAnimator
{
	u32 Delay;
	u32 Begin;
	bool firstRun;
	SceneNodeShader shader;
	f32 Num;
	vector3df ColFrom;
	vector3df ColOffset;

public:
	RunWayBlink( u32 delay, f32 num, vector3df colFrom, vector3df colOffset )
		: Delay( delay ), firstRun( true ), ColFrom( colFrom ), ColOffset( colOffset ), Num( num )
	{

	}

	virtual void animateNode( ISceneNode* node, u32 timeMs ) 
	{
		if ( firstRun )
		{
			firstRun = false;
			Begin = timeMs + Delay + 2000/*��ʱ*/;
		}

		RunWayCallBack* cb = new RunWayCallBack( Num, ColFrom, ColOffset, (f32)Begin );
		shader.ApplyShaderToSceneNode( node, cb, "", "Shader/RunWay.frag", EMT_TRANSPARENT_ADD_COLOR );
		cb->drop();

		node->removeAnimator( this );
	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

};

//// �����ܵ������ظ��ڵ�
//ISceneNode* CreateRunWay( core::vector3df position = core::vector3df( 0 ),
//	f32 interval = 200, f32 width = 300,
//	core::vector3df colorFrom = core::vector3df( 0, 63, 255 ), core::vector3df colorTo = core::vector3df( 255, 255, 0 ),
//	s32 numOfArrows = 15 )
//{
//	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
//	ISceneManager* smgr = pEngine->GetSceneManager();
//	IVideoDriver* driver = pEngine->GetVideoDriver();
//	u32 TimeMs = pEngine->GetDevice()->getTimer()->getTime();
//	f32 delay = 100;
//
//	// �ܵ����ڵ�
//	ISceneNode* runWay = smgr->addEmptySceneNode();
//	runWay->setPosition( position );
//	// �����ƵĽڵ�
//	ISceneNode* node = smgr->addMeshSceneNode( smgr->getMesh( "../media/UnitModel/UnitPlane.obj" ), runWay );
//	node->setScale( vector3df( 90, 176, 1 ) );
//	node->setRotation( vector3df( 0, 45, 0 ) );
//	node->setMaterialTexture( 0, driver->getTexture( "../media/UIResource/Game/arrow.png" ) );
//	node->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
//	// �ڵ���ʱ����
//	ISceneNode* copy;
//	// Shader
//	SceneNodeShader shader;
//	// ɫ��ƫ����
//	vector3df colorOffset = ( colorTo - colorFrom ) / (f32)numOfArrows;
//	// ���ܵ�
//	for( int i=0; i<numOfArrows; i++ )
//	{
//		copy = node->clone();
//		copy->setPosition( vector3df( width / 2.f, 0, interval * i ) );
//		RunWayBlink* ani = new RunWayBlink( (u32)(delay * i), (f32)i, colorFrom, colorOffset );
//		copy->addAnimator( ani );
//		ani->drop();
//	}
//	node->setRotation( vector3df( 0, 45, 180 ) );
//	// ���ܵ�
//	for( int i=0; i<numOfArrows; i++ )
//	{
//		copy = node->clone();
//		copy->setPosition( vector3df( -width / 2.f, 0, interval * i ) );
//		RunWayBlink* ani = new RunWayBlink( (u32)(delay * i), (f32)i, colorFrom, colorOffset );
//		copy->addAnimator( ani );
//		ani->drop();
//	}
//	node->setVisible( false );
//
//	return runWay;
//}

#endif // RunWay_h__
