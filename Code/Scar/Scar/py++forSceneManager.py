
import os
from pyplusplus import module_builder

#Creating an instance of class that will help you to expose your declarations
mb = module_builder.module_builder_t( 
    [    
		r"./MySceneManager.h",
		r"./IWeapon.h",
		r"./IShip.h",
		#r"./",
		#r"./",
		r"/media/DATA/VS 2010/OpenGL-scut/Code/include/ISceneNode.h"
		#r"/media/DATA/VS 2010/OpenGL-scut/Code/include",
		#r"/media/DATA/VS 2010/OpenGL-scut/Code/include"
    ]
    , gccxml_path=r"" 
    , working_directory=r"/media/DATA/VS 2010/OpenGL-scut/Code/Scar/Scar"
    , include_paths=['/usr/include/python2.7', 
                    '/media/DATA/VS 2010/OpenGL-scut/Code/include',
                    '/media/DATA/VS 2010/OpenGL-scut/Code/boost-1_47/include', 
                    '/media/DATA/VS 2010/OpenGL-scut/Code/Scar/Scar']
    , define_symbols=[] )


#Well, don't you want to see what is going on?
mb.print_declarations()

#Creating code creator. After this step you should not modify/customize declarations.
mb.build_code_creator( module_name='PythonSceneMgr' )

#Writing code to file.
mb.write_module( './PythonSceneMgr.cpp' )

