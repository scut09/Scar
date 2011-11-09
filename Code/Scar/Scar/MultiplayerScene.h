/********************************************************************
    ����ʱ��: 2011-10-8   15:57
    �ļ���:   MultiplayerScene.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������Ϸ����Ϸ����

*********************************************************************/

#ifndef MultiplayerScene_h__
#define MultiplayerScene_h__

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "PlayerHelper.h"
#include "PlayerManager.h"
#include "Boost_Client.h"
#include "Boost_Server.h"
#include "irrKlang.h"
#include "SceneNodeShader.h"


class MultiplayerScene : public GameScene
{
	//AnimationManager*			m_pAnimationMan;
	scene::ICameraSceneNode*	m_pCamera;
	scene::ISceneNode*			m_pSkyBox;
	ModelManager*				m_pModelMan;



public:
	MultiplayerScene() : m_pCamera( 0 ), m_pModelMan( 0 ), bRunOnce( true )
	{	
	}

	~MultiplayerScene()
	{
		Release();
	}

	virtual void Run();
	virtual void Init();
	virtual void Release();
	virtual void Draw();

public:

	//boost::shared_ptr<Network::BoostClient> client;
	boost::shared_ptr<Network::BoostClient> client;

	boost::shared_ptr<Network::BoostServer> server;

	//scene::ISceneNode* node;

	IUIObject* root;	//������


	irrklang::ISoundEngine* pSoundEngine;
	irrklang::ISoundSource* fuck;

	//������shader
	SceneNodeShader* shader;
	//RobotManager robotManager;

	boost::shared_ptr<PlayerHelper>		m_playerHelper;
	boost::shared_ptr<PlayerManager>	m_playerManager;

	bool bRunOnce;

	// CallBacks
	// ͨ����Shader�ص�����
	// �贫�������Ŀ��ڵ�
	// �ں��������ͶӰ��������ʱ��
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

			//�ڵ�任����
			matrix4 transMatrix = Node->getAbsoluteTransformation();
			services->setVertexShaderConstant( "TransMatrix", transMatrix.pointer(), 16);

			//�ڵ��������
			vector3df absPos = Node->getAbsolutePosition();
			services->setVertexShaderConstant( "AbsPos", reinterpret_cast<f32*>(&absPos), 3);

			//����ͶӰ����
			matrix4 worldViewProj;
			worldViewProj = driver->getTransform( ETS_PROJECTION );
			worldViewProj *= driver->getTransform( ETS_VIEW );
			worldViewProj *= driver->getTransform( ETS_WORLD );
			services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

			//������������
			matrix4 invWorld = driver->getTransform( ETS_WORLD );
			invWorld.makeInverse();
			services->setVertexShaderConstant( "InvWorld", invWorld.pointer(), 16);

			//�������ת�þ���
			matrix4 transWorld = driver->getTransform( ETS_WORLD );
			transWorld = transWorld.getTransposed();
			services->setVertexShaderConstant( "TransWorld", transWorld.pointer(), 16);

			//����, ���֧����������
			int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
			services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
			services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
			services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
			services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

			//���������
			vector3df cameraPos = smgr->getActiveCamera()->getAbsolutePosition();
			services->setVertexShaderConstant( "CameraPos", reinterpret_cast<f32*>(&cameraPos), 3);

			//ʱ��
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


#endif // MultiplayerScene_h__