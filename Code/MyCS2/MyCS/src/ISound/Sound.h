///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/21 21:52
//Describe: …˘“Ù µœ÷
///////////////////////////////////////////////////////////////////////

#ifndef  CSound_h
#define  CSound_h
#pragma once

#include "../../include/ISound.h"
#include <klang include/irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
using namespace irrklang;
namespace ISound
{
	class CSound
	{
	public:
		CSound(void);
		~CSound(void);
		static void Init();
		static void Release();
	public:
		static irrklang::ISoundEngine*	g_engine;
		static irr::scene::ISceneNode*	g_node;
		static irrklang::ISoundSource*	g_source[SND_Count];

	};
}
#endif