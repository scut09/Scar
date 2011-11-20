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
#include "MySceneManager.h"
#include "IPlayer.h"
#include <irrlicht.h>

BOOST_PYTHON_MODULE( Engine )
{
	using namespace boost::python;
	namespace bp = boost::python;

	//class_< ModelManagerWrapper >( "ModelMan", "Help to load model" )
	//	.def( "AddMesh", &ModelManagerWrapper::AddMesh, (arg("meshID"), ("meshFilename"), ("textureFilename")) )
	//	.def( "AddSceneNodeByMeshID", &ModelManagerWrapper::AddSceneNodeByMeshID, arg("meshID"), arg("bTestCollision") = false )
	//	.def( "AddLight", &ModelManagerWrapper::AddLight, (arg("light"), ("x"), ("y"), ("z")) );

	//class_< PythonSColor >( "SColorFake", "fake SColor" )
	//	.def_readwrite( "alpha", &PythonSColor::alpha )
	//	.def_readwrite( "red", &PythonSColor::red )
	//	.def_readwrite( "green", &PythonSColor::green )
	//	.def_readwrite( "blue", &PythonSColor::blue );

	//////////////////////////////////////////////////////////////////////////
	
	{ //::irr::video::SColor
		typedef bp::class_< irr::video::SColor > SColor_exposer_t;
		SColor_exposer_t SColor_exposer = SColor_exposer_t( "SColor", bp::init< >() );
		bp::scope SColor_scope( SColor_exposer );
		SColor_exposer.def( bp::init< irr::u32, irr::u32, irr::u32, irr::u32 >(( bp::arg("a"), bp::arg("r"), bp::arg("g"), bp::arg("b") )) );
		SColor_exposer.def( bp::init< irr::u32 >(( bp::arg("clr") )) );
		bp::implicitly_convertible< irr::u32, irr::video::SColor >();
		{ //::irr::video::SColor::getAlpha

			typedef ::irr::u32 ( ::irr::video::SColor::*getAlpha_function_type )(  ) const;

			SColor_exposer.def( 
				"getAlpha"
				, getAlpha_function_type( &::irr::video::SColor::getAlpha ) );

		}
		{ //::irr::video::SColor::getAverage

			typedef ::irr::u32 ( ::irr::video::SColor::*getAverage_function_type )(  ) const;

			SColor_exposer.def( 
				"getAverage"
				, getAverage_function_type( &::irr::video::SColor::getAverage ) );

		}
		{ //::irr::video::SColor::getBlue

			typedef ::irr::u32 ( ::irr::video::SColor::*getBlue_function_type )(  ) const;

			SColor_exposer.def( 
				"getBlue"
				, getBlue_function_type( &::irr::video::SColor::getBlue ) );

		}
		{ //::irr::video::SColor::getGreen

			typedef ::irr::u32 ( ::irr::video::SColor::*getGreen_function_type )(  ) const;

			SColor_exposer.def( 
				"getGreen"
				, getGreen_function_type( &::irr::video::SColor::getGreen ) );

		}
		{ //::irr::video::SColor::getInterpolated

			typedef ::irr::video::SColor ( ::irr::video::SColor::*getInterpolated_function_type )( ::irr::video::SColor const &,::irr::f32 ) const;

			SColor_exposer.def( 
				"getInterpolated"
				, getInterpolated_function_type( &::irr::video::SColor::getInterpolated )
				, ( bp::arg("other"), bp::arg("d") ) );

		}
		{ //::irr::video::SColor::getInterpolated_quadratic

			typedef ::irr::video::SColor ( ::irr::video::SColor::*getInterpolated_quadratic_function_type )( ::irr::video::SColor const &,::irr::video::SColor const &,::irr::f32 ) const;

			SColor_exposer.def( 
				"getInterpolated_quadratic"
				, getInterpolated_quadratic_function_type( &::irr::video::SColor::getInterpolated_quadratic )
				, ( bp::arg("c1"), bp::arg("c2"), bp::arg("d") ) );

		}
		{ //::irr::video::SColor::getLightness

			typedef ::irr::f32 ( ::irr::video::SColor::*getLightness_function_type )(  ) const;

			SColor_exposer.def( 
				"getLightness"
				, getLightness_function_type( &::irr::video::SColor::getLightness ) );

		}
		{ //::irr::video::SColor::getLuminance

			typedef ::irr::f32 ( ::irr::video::SColor::*getLuminance_function_type )(  ) const;

			SColor_exposer.def( 
				"getLuminance"
				, getLuminance_function_type( &::irr::video::SColor::getLuminance ) );

		}
		{ //::irr::video::SColor::getRed

			typedef ::irr::u32 ( ::irr::video::SColor::*getRed_function_type )(  ) const;

			SColor_exposer.def( 
				"getRed"
				, getRed_function_type( &::irr::video::SColor::getRed ) );

		}
		SColor_exposer.def( bp::self != bp::self );
		SColor_exposer.def( bp::self + bp::self );
		SColor_exposer.def( bp::self < bp::self );
		SColor_exposer.def( bp::self == bp::self );
		{ //::irr::video::SColor::set

			typedef void ( ::irr::video::SColor::*set_function_type )( ::irr::u32,::irr::u32,::irr::u32,::irr::u32 ) ;

			SColor_exposer.def( 
				"set"
				, set_function_type( &::irr::video::SColor::set )
				, ( bp::arg("a"), bp::arg("r"), bp::arg("g"), bp::arg("b") ) );

		}
		{ //::irr::video::SColor::set

			typedef void ( ::irr::video::SColor::*set_function_type )( ::irr::u32 ) ;

			SColor_exposer.def( 
				"set"
				, set_function_type( &::irr::video::SColor::set )
				, ( bp::arg("col") ) );

		}
		{ //::irr::video::SColor::setAlpha

			typedef void ( ::irr::video::SColor::*setAlpha_function_type )( ::irr::u32 ) ;

			SColor_exposer.def( 
				"setAlpha"
				, setAlpha_function_type( &::irr::video::SColor::setAlpha )
				, ( bp::arg("a") ) );

		}
		{ //::irr::video::SColor::setBlue

			typedef void ( ::irr::video::SColor::*setBlue_function_type )( ::irr::u32 ) ;

			SColor_exposer.def( 
				"setBlue"
				, setBlue_function_type( &::irr::video::SColor::setBlue )
				, ( bp::arg("b") ) );

		}
		{ //::irr::video::SColor::setGreen

			typedef void ( ::irr::video::SColor::*setGreen_function_type )( ::irr::u32 ) ;

			SColor_exposer.def( 
				"setGreen"
				, setGreen_function_type( &::irr::video::SColor::setGreen )
				, ( bp::arg("g") ) );

		}
		{ //::irr::video::SColor::setRed

			typedef void ( ::irr::video::SColor::*setRed_function_type )( ::irr::u32 ) ;

			SColor_exposer.def( 
				"setRed"
				, setRed_function_type( &::irr::video::SColor::setRed )
				, ( bp::arg("r") ) );

		}
		{ //::irr::video::SColor::toA1R5G5B5

			typedef ::irr::u16 ( ::irr::video::SColor::*toA1R5G5B5_function_type )(  ) const;

			SColor_exposer.def( 
				"toA1R5G5B5"
				, toA1R5G5B5_function_type( &::irr::video::SColor::toA1R5G5B5 ) );

		}
		{ //::irr::video::SColor::toOpenGLColor

			typedef void ( ::irr::video::SColor::*toOpenGLColor_function_type )( ::irr::u8 * ) const;

			SColor_exposer.def( 
				"toOpenGLColor"
				, toOpenGLColor_function_type( &::irr::video::SColor::toOpenGLColor )
				, ( bp::arg("dest") ) );

		}
		SColor_exposer.def_readwrite( "color", &irr::video::SColor::color );
	}

	{ //::irr::video::SColorf
		typedef bp::class_< irr::video::SColorf > SColorf_exposer_t;
		SColorf_exposer_t SColorf_exposer = SColorf_exposer_t( "SColorf", bp::init< >() );
		bp::scope SColorf_scope( SColorf_exposer );
		SColorf_exposer.def( bp::init< irr::f32, irr::f32, irr::f32, bp::optional< irr::f32 > >(( bp::arg("r"), bp::arg("g"), bp::arg("b"), bp::arg("a")=1.0e+0f )) );
		SColorf_exposer.def( bp::init< irr::video::SColor >(( bp::arg("c") )) );
		bp::implicitly_convertible< irr::video::SColor, irr::video::SColorf >();
		{ //::irr::video::SColorf::getAlpha

			typedef ::irr::f32 ( ::irr::video::SColorf::*getAlpha_function_type )(  ) const;

			SColorf_exposer.def( 
				"getAlpha"
				, getAlpha_function_type( &::irr::video::SColorf::getAlpha ) );

		}
		{ //::irr::video::SColorf::getBlue

			typedef ::irr::f32 ( ::irr::video::SColorf::*getBlue_function_type )(  ) const;

			SColorf_exposer.def( 
				"getBlue"
				, getBlue_function_type( &::irr::video::SColorf::getBlue ) );

		}
		{ //::irr::video::SColorf::getGreen

			typedef ::irr::f32 ( ::irr::video::SColorf::*getGreen_function_type )(  ) const;

			SColorf_exposer.def( 
				"getGreen"
				, getGreen_function_type( &::irr::video::SColorf::getGreen ) );

		}
		{ //::irr::video::SColorf::getInterpolated

			typedef ::irr::video::SColorf ( ::irr::video::SColorf::*getInterpolated_function_type )( ::irr::video::SColorf const &,::irr::f32 ) const;

			SColorf_exposer.def( 
				"getInterpolated"
				, getInterpolated_function_type( &::irr::video::SColorf::getInterpolated )
				, ( bp::arg("other"), bp::arg("d") ) );

		}
		{ //::irr::video::SColorf::getInterpolated_quadratic

			typedef ::irr::video::SColorf ( ::irr::video::SColorf::*getInterpolated_quadratic_function_type )( ::irr::video::SColorf const &,::irr::video::SColorf const &,::irr::f32 ) const;

			SColorf_exposer.def( 
				"getInterpolated_quadratic"
				, getInterpolated_quadratic_function_type( &::irr::video::SColorf::getInterpolated_quadratic )
				, ( bp::arg("c1"), bp::arg("c2"), bp::arg("d") ) );

		}
		{ //::irr::video::SColorf::getRed

			typedef ::irr::f32 ( ::irr::video::SColorf::*getRed_function_type )(  ) const;

			SColorf_exposer.def( 
				"getRed"
				, getRed_function_type( &::irr::video::SColorf::getRed ) );

		}
		{ //::irr::video::SColorf::set

			typedef void ( ::irr::video::SColorf::*set_function_type )( ::irr::f32,::irr::f32,::irr::f32 ) ;

			SColorf_exposer.def( 
				"set"
				, set_function_type( &::irr::video::SColorf::set )
				, ( bp::arg("rr"), bp::arg("gg"), bp::arg("bb") ) );

		}
		{ //::irr::video::SColorf::set

			typedef void ( ::irr::video::SColorf::*set_function_type )( ::irr::f32,::irr::f32,::irr::f32,::irr::f32 ) ;

			SColorf_exposer.def( 
				"set"
				, set_function_type( &::irr::video::SColorf::set )
				, ( bp::arg("aa"), bp::arg("rr"), bp::arg("gg"), bp::arg("bb") ) );

		}
		{ //::irr::video::SColorf::setColorComponentValue

			typedef void ( ::irr::video::SColorf::*setColorComponentValue_function_type )( ::irr::s32,::irr::f32 ) ;

			SColorf_exposer.def( 
				"setColorComponentValue"
				, setColorComponentValue_function_type( &::irr::video::SColorf::setColorComponentValue )
				, ( bp::arg("index"), bp::arg("value") ) );

		}
		{ //::irr::video::SColorf::toSColor

			typedef ::irr::video::SColor ( ::irr::video::SColorf::*toSColor_function_type )(  ) const;

			SColorf_exposer.def( 
				"toSColor"
				, toSColor_function_type( &::irr::video::SColorf::toSColor ) );

		}
		SColorf_exposer.def_readwrite( "a", &irr::video::SColorf::a );
		SColorf_exposer.def_readwrite( "b", &irr::video::SColorf::b );
		SColorf_exposer.def_readwrite( "g", &irr::video::SColorf::g );
		SColorf_exposer.def_readwrite( "r", &irr::video::SColorf::r );
	}


	//////////////////////////////////////////////////////////////////////////
	
	boost::python::class_<std::vector<GameScene*> >("GameScenes")
		.def(boost::python::vector_indexing_suite<std::vector<GameScene*> >());

	boost::python::class_<std::vector<IUIObject*> >("IUIObjects")
		.def(boost::python::vector_indexing_suite<std::vector<IUIObject*> >());

	//class_< PythonSLight >( "SLight", "fake SLight" )
	//	.def_readwrite( "AmbientColor", &PythonSLight::AmbientColor )
	//	.def_readwrite( "DiffuseColor", &PythonSLight::DiffuseColor )
	//	.def_readwrite( "SpecularColor", &PythonSLight::SpecularColor );

	//class_< irr::core::vector3df >( "vector3df", "fake vector3df", init< f32, f32, f32 >() )
	//	.def_readwrite( "X", &irr::core::vector3df::X )
	//	.def_readwrite( "Y", &irr::core::vector3df::Y )
	//	.def_readwrite( "Z", &irr::core::vector3df::Z );

	class_< irr::core::vector3di >( "vector3di", "fake vector3df", init< s32, s32, s32 >() )
		.def_readwrite( "X", &irr::core::vector3di::X )
		.def_readwrite( "Y", &irr::core::vector3di::Y )
		.def_readwrite( "Z", &irr::core::vector3di::Z );


	class_< irr::core::vector2d<s32> >( "vector2d", "fake vector2d<s32>", init< s32, s32 >() )
		.def_readwrite( "X", &irr::core::vector2d<s32>::X )
		.def_readwrite( "Y", &irr::core::vector2d<s32>::Y )
		;

	//class_< irr::core::dimension2df >( "dimension2df", "dimension2df", init< f32, f32 >() )
	//	.def_readwrite( "Width", &irr::core::dimension2df::Width )
	//	.def_readwrite( "Height", &irr::core::dimension2df::Height )
	//	;

	class_< irr::core::dimension2di >( "dimension2df", "dimension2df", init< s32, s32 >() )
		.def_readwrite( "Width", &irr::core::dimension2di::Width )
		.def_readwrite( "Height", &irr::core::dimension2di::Height )
		;

	class_< irr::core::vector2d<f32> >( "vector2df", "fake vector2d<f32>", init< f32, f32 >() )
		.def_readwrite( "X", &irr::core::vector2d<f32>::X )
		.def_readwrite( "Y", &irr::core::vector2d<f32>::Y )
		;


	//class_< PythonSceneNode >( "ISceneNode", "fake ISceneNode" )
	//	.def( "SetPosition", &PythonSceneNode::SetPosition )
	//	.def( "GetPosition", &PythonSceneNode::GetPosition )
	//	.def( "SetRotation", &PythonSceneNode::SetRotation )
	//	.def( "GetRotation", &PythonSceneNode::GetRotation )
	//	.def( "AddAnimator", &PythonSceneNode::AddAnimator )
	//	.def( "RemoveAnimator", &PythonSceneNode::RemoveAnimator )
	//	.def( "Grab", &PythonSceneNode::Grab )
	//	.def( "Drop", &PythonSceneNode::Drop )
	//	.def( "Remove", &PythonSceneNode::Remove );


	/*class_< AnimatorWrapper >( "Animator", "fake Animator" )
		.def( "Drop", &AnimatorWrapper::Drop );

	class_< AnimationManagerWrapper >( "AnimationManager", "fake AnimationManager" )
		.def( "CreateFlyStraightAutoDelAnimator", &AnimationManagerWrapper::CreateFlyStraightAutoDelAnimator );*/

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

	def( "GetMySceneManager", GetMySceneManager, return_value_policy< reference_existing_object >() );

	def( "CreateRoom", CreateRoom );

	def( "GetCurrentPlayer", GetCurrentPlayer, return_value_policy< reference_existing_object >() );

}