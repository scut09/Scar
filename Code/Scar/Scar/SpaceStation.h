/********************************************************************
创建时间: 2011-10-22   14:56
文件名:   SpaceStation.h
作者:     杨旭瑜 Hurrmann	
说明:     天空站实体

*********************************************************************/

#ifndef _SPACESTATION_H
#define _SPACESTATION_H

#include <irrlicht.h>


using namespace irr;
using namespace scene;

class BuildSpaceStation 
{
public:

	BuildSpaceStation( ISceneManager* smgr, const irr::io::path &pFileName, s32 id = -1, 
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1,1,1) )
	{
		auto m_pCamera = smgr->getActiveCamera();
		if (!m_pCamera)
		{
			return;
		}

		auto m_pSpaceStationMesh = smgr->getMesh( pFileName );

		auto ss = smgr->addMeshSceneNode(
			m_pSpaceStationMesh
			, smgr->getRootSceneNode()
			, id
			, position
			, rotation
			, scale
			);

		auto TriangleSelector = smgr->createOctreeTriangleSelector( m_pSpaceStationMesh, ss, 128 );

		ss->setTriangleSelector( TriangleSelector );

		m_pCamera->addAnimator( smgr->createCollisionResponseAnimator( TriangleSelector, m_pCamera ) );

		TriangleSelector->drop();
	}
};

#endif