//ª§Œ¿Ω¢
#pragma once
#include "iship.h"
class CFrigate :
	public IShip
{
public:
	CFrigate(irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
	{
		initShip(L"ª§Œ¿Ω¢");
	}
	~CFrigate(void);
};

