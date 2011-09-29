/********************************************************************
	创建时间: 2011-9-29   9:59
	文件名:   PythonModule.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     Python模块的一些初始化

*********************************************************************/


#ifndef PythonModule_h__
#define PythonModule_h__

#include "ModelManager.h"

//ModelManagerSlaver& CreateModelManagerSlaver()
//{
//
//}

//void AddMesh( const std::string& meshFilename, const std::string& meshID, const std::string& textureFilename );
// 

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

}


#endif // PythonModule_h__