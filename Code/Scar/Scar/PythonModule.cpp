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
#include "IUIObject.h"
#include "UIManager.h"
#include "GameSceneManager.h"

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

	boost::python::class_<std::vector<IUIObject*> >("IUIObjects")
		.def(boost::python::vector_indexing_suite<std::vector<IUIObject*> >());

	class_< PythonSLight >( "SLight", "fake SLight" )
		.def_readwrite( "AmbientColor", &PythonSLight::AmbientColor )
		.def_readwrite( "DiffuseColor", &PythonSLight::DiffuseColor )
		.def_readwrite( "SpecularColor", &PythonSLight::SpecularColor );

	class_< PythonVector3df >( "vector3df", "fake vector3df", init< f32, f32, f32 >() )
		.def_readwrite( "x", &PythonVector3df::x )
		.def_readwrite( "y", &PythonVector3df::y )
		.def_readwrite( "z", &PythonVector3df::z );


	class_< irr::core::vector2d<s32> >( "vector2d", "fake vector2d<s32>", init< s32, s32 >() )
		.def_readwrite( "X", &irr::core::vector2d<s32>::X )
		.def_readwrite( "Y", &irr::core::vector2d<s32>::Y )
		;

	class_< irr::core::dimension2df >( "dimension2df", "dimension2df", init< f32, f32 >() )
		.def_readwrite( "Width", &irr::core::dimension2df::Width )
		.def_readwrite( "Height", &irr::core::dimension2df::Height )
		;

	class_< irr::core::dimension2di >( "dimension2df", "dimension2df", init< s32, s32 >() )
		.def_readwrite( "Width", &irr::core::dimension2di::Width )
		.def_readwrite( "Height", &irr::core::dimension2di::Height )
		;

	class_< irr::core::vector2d<f32> >( "vector2df", "fake vector2d<f32>", init< f32, f32 >() )
		.def_readwrite( "X", &irr::core::vector2d<f32>::X )
		.def_readwrite( "Y", &irr::core::vector2d<f32>::Y )
		;


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

	def( "Float2Int", Float2Int, args("f"), "f 2 I" );

	def( "Int2Float", Int2Float, args( "s" ), "I 2 F" );

	def( "GetUIManager", GetUIManager, return_value_policy< reference_existing_object >() );

	def( "GetGameSceneManager", GetGameSceneManager, return_value_policy< reference_existing_object >() );


	

}