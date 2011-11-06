#ifndef SpriteFlame_h__
#define SpriteFlame_h__

/********************************************************************
	����ʱ��:	2011/11/06
	�ļ�����: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\SpriteFlame.h
	����:		$������$
	
	����:		��ͼƬ��ģ��ɻ�β���Ļ�������ϵͳ
*********************************************************************/

#include "irrlicht.h"
#include "IShip.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class SpriteFlame
{
	vector3df Color;			// ������ɫ
	vector3df HiColor;			// ����߹���ɫ
	vector3df Offset;			// ��������ڷɴ�λ��
	io::path ShaderFileV;		// ����shader�ļ�·��
	io::path ShaderFileF;		// Ƭ��Shader�ļ�·��

public:
	SpriteFlame( vector3df offset = vector3df(0,0,-30),
		vector3df color = vector3df(1, 0.8f, 0.1f), vector3df hicolor = vector3df(0.8f) );

	void SetOffset( const vector3df& offset );

	void SetColor( const vector3df& color );

	void SetHiColor( const vector3df& hicolor );

	void SetVertexShaderFile( const io::path& file );

	void SetFragmentSHaderFile( const io::path& file );

	// Ϊ�ɴ���ӻ���
	void AddFlameToShip( IShip* ship, ISceneManager* smgr );

};

#endif // SpriteFlame_h__
