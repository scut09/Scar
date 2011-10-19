
import os
from pyplusplus import module_builder

#Creating an instance of class that will help you to expose your declarations
mb = module_builder.module_builder_t( 
    [    
	#	r"./Aircraft.h",
		r"./AllAnimators.h",
		r"./AllUIObjects.h",
		r"./AlphaChangeUIAnimator.h",
		r"./UIButton.h",
	#	r"./AnimationManager.h",
		r"./BlinkUIAnimator.h",
	#	r"./CSceneNodeAnimatorSelfDelFlyStraight.h",
	#	r"./CSceneNodeAutoTrackAnimator.h",
		r"./DeletionUIAnimator.h",
	#	r"./EngineHeader.h",
	#	r"./EventListener.h",
	#	r"./Flame.h",
	#	r"./FlyBehavior.h",
		r"./GameScene.h",
	#	r"./IAircraft.h",
	#	r"./IClient.h",
	#	r"./IFly.h",
	#	r"./IMissile.h",
	#	r"./IMovable.h",
	#	r"./ISceneNodeAnimatorFinishing.h",
	#	r"./IServer.h",
		r"./IUIAnimator.h",
		r"./IUIObject.h",
		r"./MenuScene.h",
	#	r"./ModelManager.h",
	#	r"./ModuleControl.h",
		r"./MultiplayerScene.h",
		r"./MyIReferenceCounted.h",
	#	r"./MyIrrlichtEngine.h",
	#	r"./PythonManager.h",
	#	r"./PythonModule.h",
	#	r"./PythonWrapper.h",
		r"./RotateUIAnimator.h",
		r"./ScaleUIAnimator.h",
		r"./StartScene.h",
#		r"./TestAnimator.h",
	#	r"./Toolit.h",
	#	r"./Toolkit.h",
		r"./TranslateUIAnimator.h",
		r"./UIAnimators.h",
		r"./UIButton.h",
		r"./UIImage.h"		#,
	#	r"./UIManager.h",
	#	r"./base.h",
	#	r"./def.h"

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
mb.write_module( './bindings.cpp' )
