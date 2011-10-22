/********************************************************************
����ʱ��: 2011-10-22   14:56
�ļ���:   SpaceStation.h
����:     ����� Hurrmann	
˵��:     ���վʵ��

*********************************************************************/

#ifndef _SPACESTATION_H
#define _SPACESTATION_H

#include <irrlicht.h>


using namespace irr;
using namespace core;
using namespace scene;

class SpaceStation : public ISceneNode
{
public:

	SpaceStation(ISceneNode* parent, ISceneManager* mgr, s32 id,
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1,1,1))
		: ISceneNode(parent, mgr, id, position, rotation, scale), m_pSmgr(mgr), 
						m_pCamara(0), m_pSpaceStationMesh(0) {}


	void setMesh(IMesh* mesh);

	virtual void render() {}

	virtual const core::aabbox3d<f32>& getBoundingBox() const 
	{
		return m_pSpaceStationMesh->getBoundingBox();
	}

	IMesh* getMesh(void);

	bool Initialize(const irr::io::path &pFileName);

	virtual ITriangleSelector* getTriangleSelector() const
	{
		return TriangleSelector;
	}

private:
	IMesh* m_pSpaceStationMesh;
	ISceneManager* m_pSmgr;
	ICameraSceneNode* m_pCamara;
	
	

};

#endif