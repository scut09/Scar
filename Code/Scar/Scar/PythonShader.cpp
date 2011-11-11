// This file has been generated by Py++.

#include "def.h"

#include "ShaderManager.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(Shader){

	bp::enum_< irr::video::E_MATERIAL_TYPE>("E_MATERIAL_TYPE")
		.value("EMT_SOLID", irr::video::EMT_SOLID)
		.value("EMT_SOLID_2_LAYER", irr::video::EMT_SOLID_2_LAYER)
		.value("EMT_LIGHTMAP", irr::video::EMT_LIGHTMAP)
		.value("EMT_LIGHTMAP_ADD", irr::video::EMT_LIGHTMAP_ADD)
		.value("EMT_LIGHTMAP_M2", irr::video::EMT_LIGHTMAP_M2)
		.value("EMT_LIGHTMAP_M4", irr::video::EMT_LIGHTMAP_M4)
		.value("EMT_LIGHTMAP_LIGHTING", irr::video::EMT_LIGHTMAP_LIGHTING)
		.value("EMT_LIGHTMAP_LIGHTING_M2", irr::video::EMT_LIGHTMAP_LIGHTING_M2)
		.value("EMT_LIGHTMAP_LIGHTING_M4", irr::video::EMT_LIGHTMAP_LIGHTING_M4)
		.value("EMT_DETAIL_MAP", irr::video::EMT_DETAIL_MAP)
		.value("EMT_SPHERE_MAP", irr::video::EMT_SPHERE_MAP)
		.value("EMT_REFLECTION_2_LAYER", irr::video::EMT_REFLECTION_2_LAYER)
		.value("EMT_TRANSPARENT_ADD_COLOR", irr::video::EMT_TRANSPARENT_ADD_COLOR)
		.value("EMT_TRANSPARENT_ALPHA_CHANNEL", irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL)
		.value("EMT_TRANSPARENT_ALPHA_CHANNEL_REF", irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF)
		.value("EMT_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_TRANSPARENT_VERTEX_ALPHA)
		.value("EMT_TRANSPARENT_REFLECTION_2_LAYER", irr::video::EMT_TRANSPARENT_REFLECTION_2_LAYER)
		.value("EMT_NORMAL_MAP_SOLID", irr::video::EMT_NORMAL_MAP_SOLID)
		.value("EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR", irr::video::EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR)
		.value("EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA)
		.value("EMT_PARALLAX_MAP_SOLID", irr::video::EMT_PARALLAX_MAP_SOLID)
		.value("EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR", irr::video::EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR)
		.value("EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA", irr::video::EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA)
		.value("EMT_ONETEXTURE_BLEND", irr::video::EMT_ONETEXTURE_BLEND)
		.value("EMT_FORCE_32BIT", irr::video::EMT_FORCE_32BIT)
		.export_values()
		;

    bp::class_< ShaderManager >( "ShaderManager" )    
        .def( 
            "ApplyShaderGeneralCallback"
            , (void ( ::ShaderManager::* )( ::irr::scene::ISceneNode *,::std::string const &,::std::string const &,::irr::video::E_MATERIAL_TYPE ) )( &::ShaderManager::ApplyShaderGeneralCallback )
            , ( bp::arg("targetNode"), bp::arg("vert"), bp::arg("frag"), bp::arg("baseType")=::irr::video::EMT_SOLID ) );
}
