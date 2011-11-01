#include "SceneNodeShader.h"


SceneNodeShader::SceneNodeShader()
{
	Gpu = MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getGPUProgrammingServices();
	newMaterialType = 0;
}

void SceneNodeShader::ApplyShaderToSceneNode( ISceneNode* node, IShaderConstantSetCallBack* mc /*= 0*/,
	const io::path& vsFileName /*= ""*/, const io::path& psFileName /*= ""*/, E_MATERIAL_TYPE baseType )
{
	if ( Gpu )
	{ 
		newMaterialType = Gpu->addHighLevelShaderMaterialFromFiles( vsFileName,"VertexMain",EVST_VS_1_1,
			psFileName,"PixelMain",EPST_PS_1_1, mc, baseType );
		node->setMaterialType( (video::E_MATERIAL_TYPE)newMaterialType );
	}
}
