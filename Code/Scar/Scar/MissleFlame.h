#ifndef MissleFlame_h__
#define MissleFlame_h__

#include "irrlicht.h"
#include "IShip.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MissleFlame
{
	vector3df Color;			// ������ɫ
	vector3df HiColor;			// ����߹���ɫ
	vector3df Offset;			// ��������ڷɴ�λ��
	io::path ShaderFileV;		// ����shader�ļ�·��
	io::path ShaderFileF;		// Ƭ��Shader�ļ�·��

public:
	MissleFlame( vector3df offset = vector3df(0,0,0),
		vector3df color = vector3df(1, 0.8f, 0.1f), vector3df hicolor = vector3df(0.8f) );

	void SetOffset( const vector3df& offset );

	void SetColor( const vector3df& color );

	void SetHiColor( const vector3df& hicolor );

	void SetVertexShaderFile( const io::path& file );

	void SetFragmentSHaderFile( const io::path& file );

	// Ϊ�ɴ���ӻ���
	void AddFlameToScene( ISceneNode* scenenode, ISceneManager* smgr );

};
#endif // MissleFlame_h__
