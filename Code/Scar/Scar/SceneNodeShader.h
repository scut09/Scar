#ifndef SceneNodeShader_h__
#define SceneNodeShader_h__

/********************************************************************
	创建时间:	2011/11/01
	文件名称: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\SceneNodeShader.h
	作者:		$屠文翔$
	
	描述:		为顶点应用shader
*********************************************************************/

#include <irrlicht.h>
#include <iostream>
#include "MyIrrlichtEngine.h"

using namespace irr;
using namespace irr::video;
using namespace irr::scene;

class SceneNodeShader
{
	IGPUProgrammingServices* Gpu;			// gpu设备
	s32 newMaterialType;					// 

public:
	SceneNodeShader();

	void ApplyShaderToSceneNode( ISceneNode* node, IShaderConstantSetCallBack* mc = 0, 
		const io::path& vsFileName = "",
		const io::path& psFileName = "",
		E_MATERIAL_TYPE baseType = EMT_SOLID );
};

#endif // SceneNodeShader_h__
