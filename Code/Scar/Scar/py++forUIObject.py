
import os
from pyplusplus import module_builder

#Creating an instance of class that will help you to expose your declarations
mb = module_builder.module_builder_t( 
    [
    	r"./MyIReferenceCounted.h",    
		#r"./AllUIObjects.h",
		#r"./AlphaChangeUIAnimator.h",
		#r"./DeletionUIAnimator.h",
		r"./IUIAnimator.h",
		r"./IUIObject.h",
		#r"./RotateUIAnimator.h",
		#r"./ScaleUIAnimator.h",
		#r"./TimelagUIAnimator.h",
		#r"./TranslateUIAnimator.h",
		#r"./UIAnimators.h",
		#r"./UIImage.h",
		r"./UIManager.h",
		#r"./UIStaticText.h"
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
mb.build_code_creator( module_name='pyplusplus' )

#Writing code to file.
mb.write_module( './PythonUIObject.cpp' )

