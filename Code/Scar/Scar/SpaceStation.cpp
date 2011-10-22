#include "SpaceStation.h"

bool SpaceStation:: Initialize(const irr::io::path &pFileName)
{
	m_pCamara = m_pSmgr->getActiveCamera();
	if (!m_pCamara)
	{
		return false;
	}
	m_pSpaceStationMesh = m_pSmgr->getMesh(pFileName);
	TriangleSelector = m_pSmgr->createOctreeTriangleSelector(m_pSpaceStationMesh, this, 128);
	setTriangleSelector(TriangleSelector);
	m_pSmgr->addMeshSceneNode(m_pSpaceStationMesh);
	return true;
}

void SpaceStation:: setMesh(IMesh* mesh)
{
	m_pSpaceStationMesh =  mesh;
}


IMesh* SpaceStation:: getMesh(void)
{
	return m_pSpaceStationMesh;
}

