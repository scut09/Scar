#ifndef SpriteFlame_h__
#define SpriteFlame_h__

/********************************************************************
	创建时间:	2011/11/06
	文件名称: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\SpriteFlame.h
	作者:		$屠文翔$
	
	描述:		用图片来模拟飞机尾部的火焰粒子系统
*********************************************************************/

#include "irrlicht.h"
#include "IShip.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class SpriteFlame
{
	vector3df Color;			// 火焰颜色
	vector3df HiColor;			// 火焰高光颜色
	vector3df Offset;			// 火焰相对于飞船位置
	io::path ShaderFileV;		// 顶点shader文件路径
	io::path ShaderFileF;		// 片段Shader文件路径

public:
	SpriteFlame( vector3df offset = vector3df(0,0,-30),
		vector3df color = vector3df(1, 0.8f, 0.1f), vector3df hicolor = vector3df(0.8f) );

	void SetOffset( const vector3df& offset );

	void SetColor( const vector3df& color );

	void SetHiColor( const vector3df& hicolor );

	void SetVertexShaderFile( const io::path& file );

	void SetFragmentSHaderFile( const io::path& file );

	// 为飞船添加火焰
	void AddFlameToShip( IShip* ship, ISceneManager* smgr );

};

#endif // SpriteFlame_h__
