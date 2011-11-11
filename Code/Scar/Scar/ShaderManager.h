#ifndef ShaderManager_h__
#define ShaderManager_h__

#include "SceneNodeShader.h"
#include "GeneralCallBack.h"
#include <irrlicht.h>
#include <string>

using namespace irr;
using namespace irr::scene;
using namespace irr::video;

/*
** 名字：ShaderManager
** 说明：shader管理类，负责应用shader
**
*/
class ShaderManager
{
public:


	void ApplyShaderGeneralCallback( ISceneNode* targetNode,
		const std::string& vert, const std::string& frag, E_MATERIAL_TYPE baseType = EMT_SOLID )
	{
		GeneralCallBack* cb = new GeneralCallBack( targetNode );
		shader.ApplyShaderToSceneNode( targetNode, cb, vert.c_str(), frag.c_str(), baseType );
		cb->drop();
	}


private:
	SceneNodeShader		shader;

};

#endif // ShaderManager_h__
