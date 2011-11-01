#ifndef PlanetAtmosphere_h__
#define PlanetAtmosphere_h__

#include <irrlicht.h>
#include <iostream>
#include "MyIrrlichtEngine.h"
using namespace irr;
using namespace irr::video;
using namespace irr::scene;

class MyShaderCallBack : public video::IShaderConstantSetCallBack
{


	virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

};

class PlanetAtmosphere
{
	IVideoDriver* Driver;

	s32 newMaterialType;
	io::path vsFileName; // filename for the vertex shader
	io::path psFileName; // filename for the pixel shader

	void CreateMaterial()
	{
		video::IGPUProgrammingServices* gpu = Driver->getGPUProgrammingServices();
	}
public:
	PlanetAtmosphere()
	{
		Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
	}

	void Apply( ISceneNode* node )
	{
		node->setMaterialType( (video::E_MATERIAL_TYPE)newMaterialType );
	}
};

#endif // PlanetAtmosphere_h__
