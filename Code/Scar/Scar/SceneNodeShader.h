#ifndef SceneNodeShader_h__
#define SceneNodeShader_h__

/********************************************************************
	����ʱ��:	2011/11/01
	�ļ�����: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\SceneNodeShader.h
	����:		$������$
	
	����:		Ϊ����Ӧ��shader
*********************************************************************/

#include <irrlicht.h>
#include <iostream>
#include "MyIrrlichtEngine.h"

using namespace irr;
using namespace irr::video;
using namespace irr::scene;

class SceneNodeShader
{
	IGPUProgrammingServices* Gpu;			// gpu�豸
	s32 newMaterialType;					// 

public:
	SceneNodeShader();

	void ApplyShaderToSceneNode( ISceneNode* node, IShaderConstantSetCallBack* mc = 0, 
		const io::path& vsFileName = "",
		const io::path& psFileName = "",
		E_MATERIAL_TYPE baseType = EMT_SOLID );
};

#endif // SceneNodeShader_h__
