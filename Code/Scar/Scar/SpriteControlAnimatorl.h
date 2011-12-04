#ifndef SpriteControlAnimatorl_h__
#define SpriteControlAnimatorl_h__

/********************************************************************
	创建时间:	2011/12/05
	文件名称: 	SpriteControlAnimatorl
	作者:		屠文翔 - Kid
	
	描述:		用以控制SpriteShaderCallBack的行和列
*********************************************************************/

#include "ISceneNode.h"
#include "SpriteShaderCallBack.h"
#include "SceneNodeShader.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class SpriteControlAnimatorl : public ISceneNodeAnimator
{
	SpriteRowCol* RowCol;
	f32 Row, Col;
	u32 Interval;
	u32 LastTime;
	bool IsFirst;
	bool Loop;
	E_MATERIAL_TYPE EMT;
	io::path FilePath;

public:
	SpriteControlAnimatorl( f32 col, f32 row, u32 interval, io::path fragFilePath,
		E_MATERIAL_TYPE emt = EMT_TRANSPARENT_ADD_COLOR, bool loop = false )
	{
		Interval = interval;
		RowCol->col = 0;
		RowCol->row = 0;
		Row = row;
		Col = col;
		IsFirst = true;
		Loop = loop;
		EMT = emt;
		FilePath = fragFilePath;
	}

	virtual void animateNode( ISceneNode* node, u32 timeMs ) 
	{
		if ( IsFirst )
		{
			IsFirst = false;
			SceneNodeShader shader;
			auto cb = new SpriteShaderCallBack( RowCol );
			shader.ApplyShaderToSceneNode( node, cb, "", FilePath, EMT );
			LastTime = timeMs;
		}

		if ( timeMs - LastTime < Interval )
			return;
		LastTime = timeMs;

		RowCol->col++;
		if ( RowCol->col >= Col )
		{
			RowCol->col = 0;
			RowCol->row++;
			if ( RowCol->row >= Row )
			{
				if ( Loop )
					RowCol->row = 0;
				else
				{
					MyIrrlichtEngine::GetEngine()->GetSceneManager()->addToDeletionQueue( node );
				}
			}
		}

	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

};


#endif // SpriteControlAnimatorl_h__
