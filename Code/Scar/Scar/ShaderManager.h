#ifndef ShaderManager_h__
#define ShaderManager_h__

#include "SceneNodeShader.h"
#include "GeneralCallBack.h"
#include <string>


/*
** ���֣�ShaderManager
** ˵����shader�����࣬����Ӧ��shader
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