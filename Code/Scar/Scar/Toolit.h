#pragma once
#include <cmath>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

class Toolit
{
public:
	static bool WorldPosToScream(vector3df AbsolutePos, matrix4 mProject, matrix4 mModuleView, 
		u32 clientWidth, u32 clientHeigh,u32* WinPosX, u32* WinPosY);

private:
	Toolit(void);
	~Toolit(void);
	
};

