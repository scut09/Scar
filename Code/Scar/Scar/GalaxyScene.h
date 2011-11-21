/********************************************************************
    创建时间: 2011-11-10   15:57
    文件名:   GalaxyScene.h
    作者:     杨旭瑜 Hurrman
    说明:     阵营选择场景

*********************************************************************/

#ifndef GalaxyScene_h__
#define GalaxyScene_h__

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "PlayerHelper.h"
#include "PlayerManager.h"
#include "Boost_Client.h"
#include "Boost_Server.h"
#include "irrKlang.h"
#include "SceneNodeShader.h"


class GalaxyScene : public GameScene
{
	//AnimationManager*			m_pAnimationMan;
	scene::ICameraSceneNode*	m_pCamera;
	scene::ISceneNode*			m_pSkyBox;
	ModelManager*				m_pModelMan;

public:
	GalaxyScene() : m_pCamera( 0 ), m_pModelMan( 0 ), bRunOnce( true )
	{	
	}

	~GalaxyScene()
	{
		Release();
	}

	virtual void Run();
	virtual void Init();
	virtual void Release();
	virtual void Draw();

public:

	//测试用shader
	SceneNodeShader* shader;

	bool bRunOnce;

	// CallBacks
	// 通用型Shader回调函数
	// 需传入参数：目标节点
	// 内含世界矩阵，投影矩阵，纹理，时钟
	class GeneralCallBack : public video::IShaderConstantSetCallBack
	{
		ISceneNode* Node;

	public:
		GeneralCallBack( ISceneNode* node )
			: Node( node )
		{

		}
	private:
		virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
		{
			IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
			ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetDevice()->getSceneManager();

			//节点变换矩阵
			matrix4 transMatrix = Node->getAbsoluteTransformation();
			services->setVertexShaderConstant( "TransMatrix", transMatrix.pointer(), 16);

			//节点绝对坐标
			vector3df absPos = Node->getAbsolutePosition();
			services->setVertexShaderConstant( "AbsPos", reinterpret_cast<f32*>(&absPos), 3);

			//世界投影矩阵
			matrix4 worldViewProj;
			worldViewProj = driver->getTransform( ETS_PROJECTION );
			worldViewProj *= driver->getTransform( ETS_VIEW );
			worldViewProj *= driver->getTransform( ETS_WORLD );
			services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

			//世界矩阵逆矩阵
			matrix4 invWorld = driver->getTransform( ETS_WORLD );
			invWorld.makeInverse();
			services->setVertexShaderConstant( "InvWorld", invWorld.pointer(), 16);

			//世界矩阵转置矩阵
			matrix4 transWorld = driver->getTransform( ETS_WORLD );
			transWorld = transWorld.getTransposed();
			services->setVertexShaderConstant( "TransWorld", transWorld.pointer(), 16);

			//纹理, 最多支持四重纹理
			int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
			services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
			services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
			services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
			services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

			//摄像机坐标
			vector3df cameraPos = smgr->getActiveCamera()->getAbsolutePosition();
			services->setVertexShaderConstant( "CameraPos", reinterpret_cast<f32*>(&cameraPos), 3);

			//时钟
			f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
			services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);
		}
	};


	irr::gui::IGUIStaticText* console;
	void UpdateConsole()
	{
		if ( ! console->isVisible() )	return;
		std::string buf = MyIrrlichtEngine::Console_Buffer.str();
		if ( buf.empty() )	
			return;

		std::wstring str( buf.begin(), buf.end() );
		str = console->getText() + str;
		std::size_t remain = 800;
		if ( str.length() > remain )
		{
			std::size_t pos = str.length() - remain;
			while ( pos )
			{
				if ( str[ pos ] == _T('\n') )
				{
					break;
				}
				pos--;
			}
			str = str.substr( pos );
		}
		console->setText( str.c_str() );
		MyIrrlichtEngine::Console_Buffer.clear();
	}

};


#endif // GalaxyScene_h__

