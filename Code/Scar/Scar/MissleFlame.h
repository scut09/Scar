#ifndef MissleFlame_h__
#define MissleFlame_h__

#include "irrlicht.h"
#include "IShip.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MissleFlame
{
	vector3df Color;			// 火焰颜色
	vector3df HiColor;			// 火焰高光颜色
	vector3df Offset;			// 火焰相对于飞船位置
	io::path ShaderFileV;		// 顶点shader文件路径
	io::path ShaderFileF;		// 片段Shader文件路径

public:
	MissleFlame( vector3df offset = vector3df(0,0,0),
		vector3df color = vector3df(1, 0.8f, 0.1f), vector3df hicolor = vector3df(0.8f) );

	void SetOffset( const vector3df& offset );

	void SetColor( const vector3df& color );

	void SetHiColor( const vector3df& hicolor );

	void SetVertexShaderFile( const io::path& file );

	void SetFragmentSHaderFile( const io::path& file );

	// 为飞船添加火焰
	void AddFlameToScene( ISceneNode* scenenode, ISceneManager* smgr );

};
#endif // MissleFlame_h__
