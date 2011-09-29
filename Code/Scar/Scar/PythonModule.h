/********************************************************************
	����ʱ��: 2011-9-29   9:59
	�ļ���:   PythonModule.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     Pythonģ���һЩ��ʼ��

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
		.def( "AddMesh", &ModelManagerSlaver::AddMesh, (arg("meshID"), ("meshFilename"), ("textureFilename")) );
}


#endif // PythonModule_h__