#include "Toolit.h"


Toolit::Toolit(void)
{
}


Toolit::~Toolit(void)
{
}


bool Toolit::WorldPosToScream(vector3df AbsolutePos, matrix4 mProject, matrix4 mModuleView, 
	u32 clientWidth, u32 clientHeight,u32* WinPosX, u32* WinPosY)
{
	f32 Pos[4];
	Pos[0] = AbsolutePos.X;
	Pos[1] = AbsolutePos.Y;
	Pos[2] = AbsolutePos.Z;
	Pos[3] = 1.0f;
	mModuleView.multiplyWith1x4Matrix(Pos);
	mProject.multiplyWith1x4Matrix(Pos);
	if (Pos[3] == 0)
	{
		return false;
	}

	Pos[0] /= Pos[3];
	Pos[1] /= Pos[3];
	Pos[2] /= Pos[3];

	//视口向量的作用
	*WinPosX = (1 + Pos[0]) * clientWidth / 2;

	*WinPosY = (1 + Pos[1]) * clientHeight / 2;

	*WinPosY = clientHeight - *WinPosY;
	return true;
}
