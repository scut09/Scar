/********************************************************************
	创建时间: 2011-9-29   20:28
	文件名:   PythonModule.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     将C++的类导出到Python中

*********************************************************************/

#include "PythonWrapper.h"
#include "AnimationManager.h"
#include "GameScene.h"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

BOOST_PYTHON_MODULE( Engine )
{
	using namespace boost::python;

	class_< ModelManagerWrapper >( "ModelMan", "Help to load model" )
		.def( "AddMesh", &ModelManagerWrapper::AddMesh, (arg("meshID"), ("meshFilename"), ("textureFilename")) )
		.def( "AddSceneNodeByMeshID", &ModelManagerWrapper::AddSceneNodeByMeshID, arg("meshID"), arg("bTestCollision") = false )
		.def( "AddLight", &ModelManagerWrapper::AddLight, (arg("light"), ("x"), ("y"), ("z")) );

	class_< PythonSColor >( "SColorFake", "fake SColor" )
		.def_readwrite( "alpha", &PythonSColor::alpha )
		.def_readwrite( "red", &PythonSColor::red )
		.def_readwrite( "green", &PythonSColor::green )
		.def_readwrite( "blue", &PythonSColor::blue );

	class_< irr::video::SColor >( "SColor", "Fuck" )    
		.def( init< u32, u32, u32, u32 >( args( "a", "r", "g", "b" ) ) )
		.def( init< u32 >( arg( "clr" ) ) )
		;

	boost::python::class_<std::vector<GameScene*> >("GameScenes")
		.def(boost::python::vector_indexing_suite<std::vector<GameScene*> >());

//	class_< irr::video::SColor >( "SColor", "SColor" );
//	SColor() 

//	SColor (u32 a, u32 r, u32 g, u32 b)
//		: color(((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff)) {}

//	SColor(u32 clr)
//		: color(clr) {}


	class_< PythonSLight >( "SLight", "fake SLight" )
		.def_readwrite( "AmbientColor", &PythonSLight::AmbientColor )
		.def_readwrite( "DiffuseColor", &PythonSLight::DiffuseColor )
		.def_readwrite( "SpecularColor", &PythonSLight::SpecularColor );

	class_< PythonVector3df >( "vector3df", "fake vector3df", init< f32, f32, f32 >() )
		.def_readwrite( "x", &PythonVector3df::x )
		.def_readwrite( "y", &PythonVector3df::y )
		.def_readwrite( "z", &PythonVector3df::z );


	//class_< PythonVector2df >( "vector2df", "fake vector2df", init< f32, f32 >() )
	//	.def_readwrite( "x", &PythonVector2df::x )
	//	.def_readwrite( "y", &PythonVector2df::y );

	class_< irr::core::vector2d<s32> >( "vector2d", "fake vector2d<s32>", init< s32, s32 >() )
		;

	class_< irr::core::vector2d<f32> >( "vector2df", "fake vector2d<f32>", init< f32, f32 >() )
		;

	//class_< irr::video::IVideoDriver >( "IVideoDriver", "fake IVideoDriver" )
	//	;	

	class_< PythonSceneNode >( "ISceneNode", "fake ISceneNode" )
		.def( "SetPosition", &PythonSceneNode::SetPosition )
		.def( "GetPosition", &PythonSceneNode::GetPosition )
		.def( "SetRotation", &PythonSceneNode::SetRotation )
		.def( "GetRotation", &PythonSceneNode::GetRotation )
		.def( "AddAnimator", &PythonSceneNode::AddAnimator )
		.def( "RemoveAnimator", &PythonSceneNode::RemoveAnimator )
		.def( "Grab", &PythonSceneNode::Grab )
		.def( "Drop", &PythonSceneNode::Drop )
		.def( "Remove", &PythonSceneNode::Remove );

	//class_< AnimationManager >( "AnimationManager", "Animation" );

	class_< AnimatorWrapper >( "Animator", "fake Animator" )
		.def( "Drop", &AnimatorWrapper::Drop );

	class_< AnimationManagerWrapper >( "AnimationManager", "fake AnimationManager" )
		.def( "CreateFlyStraightAutoDelAnimator", &AnimationManagerWrapper::CreateFlyStraightAutoDelAnimator );

	class_< TimerWrapper >( "Timer", "fake Timer" )
		.def( "GetRealTime", &TimerWrapper::GetRealTime )
		.def( "GetTime", &TimerWrapper::GetTime );

	class_< MyEngine >( "MyEngine", "fake Engine" )
		.def( "GetDriver", &MyEngine::GetDriver, return_value_policy< reference_existing_object >() );

	def( "ChangeGameScene", ChangeGameScene, args("scene"), "change the game scene and initialize it " );

}