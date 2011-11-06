#include "SpriteFlame.h"
#include "SceneNodeShader.h"
#include "MyIrrlichtEngine.h"
#include "FlameAnimator.h"


SpriteFlame::SpriteFlame( vector3df offset /*= vector3df(0,0,-30)*/, vector3df color /*= vector3df(1, 0.8f, 0.1f)*/, vector3df hicolor /*= vector3df(0.8f) */ )
	: Offset( offset ), Color( color ), HiColor( hicolor )
{
	ShaderFileV = "Shader/Flame.vert";
	ShaderFileF = "Shader/Flame.frag";
}

void SpriteFlame::SetOffset( const vector3df& offset )
{
	Offset = offset;
}

void SpriteFlame::SetColor( const vector3df& color )
{
	Color = color;
}

void SpriteFlame::SetHiColor( const vector3df& hicolor )
{
	HiColor = hicolor;
}

void SpriteFlame::SetVertexShaderFile( const io::path& file )
{
	ShaderFileV = file;
}

void SpriteFlame::SetFragmentSHaderFile( const io::path& file )
{
	ShaderFileF = file;
}

void SpriteFlame::AddFlameToShip( IShip* ship, ISceneManager* smgr )
{
	// 创建Shader回调函数
	class FlameCallBack : public IShaderConstantSetCallBack
	{
		vector3df cb_color;
		vector3df cb_hicolor;
	public:
		FlameCallBack( vector3df col, vector3df hicol )
			: cb_color( col ), cb_hicolor( hicol )
		{

		}

		virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
		{
			IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();

			//世界投影矩阵
			matrix4 worldViewProj;
			worldViewProj = driver->getTransform( ETS_PROJECTION );
			worldViewProj *= driver->getTransform( ETS_VIEW );
			worldViewProj *= driver->getTransform( ETS_WORLD );
			services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

			//纹理, 最多支持四重纹理
			int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
			services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
			services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
			services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
			services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

			//时钟
			f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
			services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);

			//火焰颜色
			services->setPixelShaderConstant("LoColor", reinterpret_cast<f32*>(&cb_color), 3);
			services->setPixelShaderConstant("HiColor", reinterpret_cast<f32*>(&cb_hicolor), 3);
		}
	};

	IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();

	// 创建尾焰节点
	ISceneNode* flame = smgr->addMeshSceneNode( smgr->getMesh("../media/Flame/tree2.3ds"), ship,
		-1, Offset );
	flame->setScale( vector3df(8,8,20) );
	flame->setMaterialFlag( EMF_LIGHTING, false );
	flame->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
	flame->setMaterialTexture( 0, driver->getTexture("../media/Flame/outburst13.tga") );
	flame->setMaterialTexture( 1, driver->getTexture("../media/Flame/flame.tga") );
	
	// 根据飞船速度来改变尾焰大小
	FlameAnimator* fla = new FlameAnimator( ship, Offset );
	flame->addAnimator( fla );
	fla->drop();

	// 使用纹理来模拟粒子效果
	video::IGPUProgrammingServices* gpu = MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getGPUProgrammingServices();
	if( gpu )
	{
		FlameCallBack* cb = new FlameCallBack( Color, HiColor );
		auto newMaterialType = gpu->addHighLevelShaderMaterialFromFiles( ShaderFileV,"VertexMain",EVST_VS_1_1,
			ShaderFileF,"PixelMain",EPST_PS_1_1, cb, EMT_TRANSPARENT_ADD_COLOR );
		flame->setMaterialType( (video::E_MATERIAL_TYPE)newMaterialType );
		cb->drop();
	}


}
