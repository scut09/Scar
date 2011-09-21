#include "Sound.h"
namespace ISound
{
	irrklang::ISoundEngine* CSound::g_engine = NULL;
	irr::scene::ISceneNode* CSound::g_node  = NULL;
	irrklang::ISoundSource*	CSound::g_source[SND_Count];

	//////////////////////////////
	///	@brief	播放声音资源
	///	@parm [in] mied:声音类型
	///	@parm [in] position:声音发生的位置
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void MyPlaySound( SOUND_TYPE mied, irr::core::vector3df position)
	{
		if (position.X == 0 && position.Y == 0 && position.Z == 5)
		{
			vec3df tagpos(position.X, position.Y, 0.2f);
			CSound::g_engine->play3D(CSound::g_source[mied], tagpos);
		}
		else
		{
			irr::core::vector3df pos = position - CSound::g_node->getPosition();
			pos.rotateXZBy(CSound::g_node->getRotation().Y);
			vec3df tagpos(pos.X/1000, pos.Y/1000, pos.Z/1000);
			CSound::g_engine->play3D(CSound::g_source[mied], tagpos);
		}
		
	}

	//////////////////////////////
	///	@brief	设置声音收听者
	///	@parm [in] node:收听者场景节点
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void SetListener( irr::scene::ISceneNode* node)
	{
		CSound::g_node = node;
	}

	//////////////////////////////
	///	@brief	设置声音收听者
	///	@parm [in] node:收听者场景节点
	///	@return void
	//////////////////////////////
	extern "C" ISOUND_API void Init()
	{
		CSound::Init();
	}

	CSound::CSound(void)
	{
	}

	CSound::~CSound(void)
	{
	}

	void CSound::Init()
	{
		g_engine = createIrrKlangDevice();
		g_source[SND_Move] = g_engine->addSoundSourceFromFile("sound/move.wav");
		g_source[SND_MinMove] = g_engine->addSoundSourceFromFile("sound/minmove.wav");
		g_source[SND_Shoot1] = g_engine->addSoundSourceFromFile("sound/shoot.wav");
		g_source[SND_Shoot2] = g_engine->addSoundSourceFromFile("sound/shoot2.wav");
		g_source[SND_ChangeBullet] = g_engine->addSoundSourceFromFile("sound/changebullet.wav");
		g_source[SND_NoBullet] = g_engine->addSoundSourceFromFile("sound/nobullet.wav");
		g_engine->setSoundVolume(1.0f);
		CSound::g_engine->setListenerPosition(vec3df(0,0,0), vec3df(0,0,1));

	}

	void CSound::Release()
	{
		for (int i = 0; i < SND_Count; i++)
		{
			g_source[i]->drop();
		}
		g_engine->drop();
	}
}
