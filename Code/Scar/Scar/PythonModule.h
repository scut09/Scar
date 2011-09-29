/********************************************************************
	创建时间: 2011-9-29   9:59
	文件名:   PythonModule.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     将C++的类导出到Python中

*********************************************************************/


#ifndef PythonModule_h__
#define PythonModule_h__

#include "PythonWrapper.h"

BOOST_PYTHON_MODULE( Engine )
{
	using namespace boost::python;

	class_< ModelManagerSlaver >( "ModelMan", "Help to load model" )
		.def( "AddMesh", &ModelManagerSlaver::AddMesh, (arg("meshID"), ("meshFilename"), ("textureFilename")) )
		.def( "AddSceneNodeByMeshID", &ModelManagerSlaver::AddSceneNodeByMeshID, arg("meshID"), arg("bTestCollision") = false )
		.def( "AddLight", &ModelManagerSlaver::AddLight, (arg("light"), ("x"), ("y"), ("z")) );

	class_< PythonSColor >( "SColor", "fake SColor" )
		.def_readwrite( "alpha", &PythonSColor::alpha )
		.def_readwrite( "red", &PythonSColor::red )
		.def_readwrite( "green", &PythonSColor::green )
		.def_readwrite( "blue", &PythonSColor::blue );

	class_< PythonSLight >( "SLight", "fake SLight" )
		.def_readwrite( "AmbientColor", &PythonSLight::AmbientColor )
		.def_readwrite( "DiffuseColor", &PythonSLight::DiffuseColor )
		.def_readwrite( "SpecularColor", &PythonSLight::SpecularColor );

	class_< PythonVector3df >( "vector3df", "fake vector3df" )
		.def_readwrite( "x", &PythonVector3df::x )
		.def_readwrite( "y", &PythonVector3df::y )
		.def_readwrite( "z", &PythonVector3df::z );

	class_< PythonSceneNode >( "ISceneNode", "fake ISceneNode" )
		.def( "SetPosition", &PythonSceneNode::SetPosition )
		.def( "GetPosition", &PythonSceneNode::GetPosition )
		.def( "SetRotation", &PythonSceneNode::SetRotation )
		.def( "GetRotation", &PythonSceneNode::GetRotation )
		.def( "Grab", &PythonSceneNode::Grab )
		.def( "Drop", &PythonSceneNode::Drop )
		.def( "Remove", &PythonSceneNode::Remove );
}


#endif // PythonModule_h__