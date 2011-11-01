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
		IVideoDriver* Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		IrrlichtDevice* device = MyIrrlichtEngine::GetEngine()->GetDevice();
		core::matrix4 invWorld = Driver->getTransform(video::ETS_WORLD);
		invWorld.makeInverse();


			services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);

		// set clip matrix

		core::matrix4 worldViewProj;
		worldViewProj = Driver->getTransform(video::ETS_PROJECTION);
		worldViewProj *= Driver->getTransform(video::ETS_VIEW);
		worldViewProj *= Driver->getTransform(video::ETS_WORLD);

			services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);

		// set camera position

		core::vector3df pos = device->getSceneManager()->
			getActiveCamera()->getAbsolutePosition();

			services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32*>(&pos), 3);

		// set light color

		video::SColorf col(0.0f,1.0f,1.0f,0.0f);

			services->setVertexShaderConstant("mLightColor",
			reinterpret_cast<f32*>(&col), 4);

		// set transposed world matrix

		core::matrix4 world = Driver->getTransform(video::ETS_WORLD);
		world = world.getTransposed();

			services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);

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
		if ( gpu )
		{ 
			MyShaderCallBack* mc = new MyShaderCallBack();
			newMaterialType = gpu->addHighLevelShaderMaterialFromFiles( "Shader/ShaderTest.txt","vMain",
				EVST_VS_1_1,"","pMain",EPST_PS_1_1, mc );
		}
	}

public:
	PlanetAtmosphere()
	{
		Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		newMaterialType = 0;
	}

	void Apply( ISceneNode* node ) 
	{
		CreateMaterial();
		node->setMaterialType( (video::E_MATERIAL_TYPE)newMaterialType );
	}
};

#endif // PlanetAtmosphere_h__
