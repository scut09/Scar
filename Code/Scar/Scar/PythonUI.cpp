//// This file has been generated by Py++.
//
//#define BOOST_PYTHON_STATIC_LIB
//
//#include <boost/python.hpp> //ǰ��������һ�����ö���Ϊ�˵������ͷ�ļ�����ؿ�  
//
////#include "boost/python.hpp"
//
//#include "__array_1.pypp.hpp"
//
//#include "DeletionUIAnimator.h"
//
//#include "IUIAnimator.h"
//
//#include "IUIObject.h"
//
//#include "RotateUIAnimator.h"
//
//#include "ScaleUIAnimator.h"
//
//#include "TranslateUIAnimator.h"
//
//#include "UIAnimators.h"
//
//#include "UIObject.h"
//
//namespace bp = boost::python;
//
//struct IUIAnimator_wrapper : IUIAnimator, bp::wrapper< IUIAnimator > {
//
//    IUIAnimator_wrapper()
//    : IUIAnimator()
//      , bp::wrapper< IUIAnimator >(){
//        // null constructor
//        
//    }
//
//    virtual ::IUIAnimator * Clone(  ){
//        bp::override func_Clone = this->get_override( "Clone" );
//        return func_Clone(  );
//    }
//
//    virtual bool animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ){
//        bp::override func_animateUIObject = this->get_override( "animateUIObject" );
//        return func_animateUIObject( boost::python::ptr(node), timeMS );
//    }
//
//};
//
//struct DeletionAnimator_wrapper : DeletionAnimator, bp::wrapper< DeletionAnimator > {
//
//    DeletionAnimator_wrapper(DeletionAnimator const & arg )
//    : DeletionAnimator( arg )
//      , bp::wrapper< DeletionAnimator >(){
//        // copy constructor
//        
//    }
//
//    DeletionAnimator_wrapper(::irr::u32 now, ::irr::u32 time )
//    : DeletionAnimator( now, time )
//      , bp::wrapper< DeletionAnimator >(){
//        // constructor
//    
//    }
//
//    virtual ::IUIAnimator * Clone(  ) {
//        if( bp::override func_Clone = this->get_override( "Clone" ) )
//            return func_Clone(  );
//        else{
//            return this->DeletionAnimator::Clone(  );
//        }
//    }
//    
//    ::IUIAnimator * default_Clone(  ) {
//        return DeletionAnimator::Clone( );
//    }
//
//    virtual bool animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ) {
//        if( bp::override func_animateUIObject = this->get_override( "animateUIObject" ) )
//            return func_animateUIObject( boost::python::ptr(node), timeMS );
//        else{
//            return this->DeletionAnimator::animateUIObject( boost::python::ptr(node), timeMS );
//        }
//    }
//    
//    bool default_animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ) {
//        return DeletionAnimator::animateUIObject( boost::python::ptr(node), timeMS );
//    }
//
//};
//
//struct IUIObject_wrapper : IUIObject, bp::wrapper< IUIObject > {
//
//    IUIObject_wrapper(::irr::video::IVideoDriver * driver, ::irr::core::vector2d< float > const & pos, ::irr::s32 width, ::irr::s32 height, ::irr::s32 order=0 )
//    : IUIObject( boost::python::ptr(driver), boost::ref(pos), width, height, order )
//      , bp::wrapper< IUIObject >(){
//        // constructor
//    
//    }
//
//    virtual void AddAnimator( ::IUIAnimator * ani ) {
//        if( bp::override func_AddAnimator = this->get_override( "AddAnimator" ) )
//            func_AddAnimator( boost::python::ptr(ani) );
//        else{
//            this->IUIObject::AddAnimator( boost::python::ptr(ani) );
//        }
//    }
//    
//    void default_AddAnimator( ::IUIAnimator * ani ) {
//        IUIObject::AddAnimator( boost::python::ptr(ani) );
//    }
//
//    virtual void AddChild( ::IUIObject * child ) {
//        if( bp::override func_AddChild = this->get_override( "AddChild" ) )
//            func_AddChild( boost::python::ptr(child) );
//        else{
//            this->IUIObject::AddChild( boost::python::ptr(child) );
//        }
//    }
//    
//    void default_AddChild( ::IUIObject * child ) {
//        IUIObject::AddChild( boost::python::ptr(child) );
//    }
//
//    virtual void Draw(  ){
//        bp::override func_Draw = this->get_override( "Draw" );
//        func_Draw(  );
//    }
//
//    virtual void DrawTree(  ) {
//        if( bp::override func_DrawTree = this->get_override( "DrawTree" ) )
//            func_DrawTree(  );
//        else{
//            this->IUIObject::DrawTree(  );
//        }
//    }
//    
//    void default_DrawTree(  ) {
//        IUIObject::DrawTree( );
//    }
//
//    virtual ::irr::s32 GetOrder(  ) const  {
//        if( bp::override func_GetOrder = this->get_override( "GetOrder" ) )
//            return func_GetOrder(  );
//        else{
//            return this->IUIObject::GetOrder(  );
//        }
//    }
//    
//    ::irr::s32 default_GetOrder(  ) const  {
//        return IUIObject::GetOrder( );
//    }
//
//    virtual void OnAnimate( ::irr::u32 time ) {
//        if( bp::override func_OnAnimate = this->get_override( "OnAnimate" ) )
//            func_OnAnimate( time );
//        else{
//            this->IUIObject::OnAnimate( time );
//        }
//    }
//    
//    void default_OnAnimate( ::irr::u32 time ) {
//        IUIObject::OnAnimate( time );
//    }
//
//    virtual void RemoveAll(  ) {
//        if( bp::override func_RemoveAll = this->get_override( "RemoveAll" ) )
//            func_RemoveAll(  );
//        else{
//            this->IUIObject::RemoveAll(  );
//        }
//    }
//    
//    void default_RemoveAll(  ) {
//        IUIObject::RemoveAll( );
//    }
//
//    virtual void RemoveAnimator( ::IUIAnimator * ani ) {
//        if( bp::override func_RemoveAnimator = this->get_override( "RemoveAnimator" ) )
//            func_RemoveAnimator( boost::python::ptr(ani) );
//        else{
//            this->IUIObject::RemoveAnimator( boost::python::ptr(ani) );
//        }
//    }
//    
//    void default_RemoveAnimator( ::IUIAnimator * ani ) {
//        IUIObject::RemoveAnimator( boost::python::ptr(ani) );
//    }
//
//    virtual void RemoveAnimators(  ) {
//        if( bp::override func_RemoveAnimators = this->get_override( "RemoveAnimators" ) )
//            func_RemoveAnimators(  );
//        else{
//            this->IUIObject::RemoveAnimators(  );
//        }
//    }
//    
//    void default_RemoveAnimators(  ) {
//        IUIObject::RemoveAnimators( );
//    }
//
//    virtual void RemoveChild( ::IUIObject * node ) {
//        if( bp::override func_RemoveChild = this->get_override( "RemoveChild" ) )
//            func_RemoveChild( boost::python::ptr(node) );
//        else{
//            this->IUIObject::RemoveChild( boost::python::ptr(node) );
//        }
//    }
//    
//    void default_RemoveChild( ::IUIObject * node ) {
//        IUIObject::RemoveChild( boost::python::ptr(node) );
//    }
//
//    virtual void SetOrder( ::irr::s32 order ) {
//        if( bp::override func_SetOrder = this->get_override( "SetOrder" ) )
//            func_SetOrder( order );
//        else{
//            this->IUIObject::SetOrder( order );
//        }
//    }
//    
//    void default_SetOrder( ::irr::s32 order ) {
//        IUIObject::SetOrder( order );
//    }
//
//    virtual void SetParent( ::IUIObject * parent ) {
//        if( bp::override func_SetParent = this->get_override( "SetParent" ) )
//            func_SetParent( boost::python::ptr(parent) );
//        else{
//            this->IUIObject::SetParent( boost::python::ptr(parent) );
//        }
//    }
//    
//    void default_SetParent( ::IUIObject * parent ) {
//        IUIObject::SetParent( boost::python::ptr(parent) );
//    }
//
//    virtual void remove(  ) {
//        if( bp::override func_remove = this->get_override( "remove" ) )
//            func_remove(  );
//        else{
//            this->IUIObject::remove(  );
//        }
//    }
//    
//    void default_remove(  ) {
//        IUIObject::remove( );
//    }
//
//    static pyplusplus::containers::static_sized::array_1_t< ::irr::core::vector2d<float>, 4>
//    pyplusplus_DstQuar_wrapper( ::IUIObject & inst ){
//        return pyplusplus::containers::static_sized::array_1_t< ::irr::core::vector2d<float>, 4>( inst.DstQuar );
//    }
//
//};
//
//struct RotateUIAnimator_wrapper : RotateUIAnimator, bp::wrapper< RotateUIAnimator > {
//
//    RotateUIAnimator_wrapper(RotateUIAnimator const & arg )
//    : RotateUIAnimator( arg )
//      , bp::wrapper< RotateUIAnimator >(){
//        // copy constructor
//        
//    }
//
//    RotateUIAnimator_wrapper(::irr::u32 begin, ::irr::u32 duration, ::irr::f32 angle, ::irr::core::vector2d< float > const & rotpoint, ::irr::core::vector2d< float > const & ObjCen, bool loop=false )
//    : RotateUIAnimator( begin, duration, angle, boost::ref(rotpoint), boost::ref(ObjCen), loop )
//      , bp::wrapper< RotateUIAnimator >(){
//        // constructor
//    
//    }
//
//    virtual ::RotateUIAnimator * Clone(  ) {
//        if( bp::override func_Clone = this->get_override( "Clone" ) )
//            return func_Clone(  );
//        else{
//            return this->RotateUIAnimator::Clone(  );
//        }
//    }
//    
//    ::RotateUIAnimator * default_Clone(  ) {
//        return RotateUIAnimator::Clone( );
//    }
//
//    virtual bool animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ) {
//        if( bp::override func_animateUIObject = this->get_override( "animateUIObject" ) )
//            return func_animateUIObject( boost::python::ptr(node), timeMS );
//        else{
//            return this->RotateUIAnimator::animateUIObject( boost::python::ptr(node), timeMS );
//        }
//    }
//    
//    bool default_animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ) {
//        return RotateUIAnimator::animateUIObject( boost::python::ptr(node), timeMS );
//    }
//
//};
////
////struct ScaleUIAnimator_wrapper : ScaleUIAnimator, bp::wrapper< ScaleUIAnimator > {
////
////    ScaleUIAnimator_wrapper(ScaleUIAnimator const & arg )
////    : ScaleUIAnimator( arg )
////      , bp::wrapper< ScaleUIAnimator >(){
////        // copy constructor
////        
////    }
////
////    ScaleUIAnimator_wrapper(::irr::u32 begin, ::irr::u32 duration, ::irr::core::vector2d< float > scale, ::irr::core::vector2d< float > const & scapoint, bool loop=false )
////    : ScaleUIAnimator( begin, duration, scale, boost::ref(scapoint), loop )
////      , bp::wrapper< ScaleUIAnimator >(){
////        // constructor
////    
////    }
////
////    virtual ::ScaleUIAnimator * Clone(  ) {
////        if( bp::override func_Clone = this->get_override( "Clone" ) )
////            return func_Clone(  );
////        else{
////            return this->ScaleUIAnimator::Clone(  );
////        }
////    }
////    
////    ::ScaleUIAnimator * default_Clone(  ) {
////        return ScaleUIAnimator::Clone( );
////    }
////
////    virtual bool animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ) {
////        if( bp::override func_animateUIObject = this->get_override( "animateUIObject" ) )
////            return func_animateUIObject( boost::python::ptr(node), timeMS );
////        else{
////            return this->ScaleUIAnimator::animateUIObject( boost::python::ptr(node), timeMS );
////        }
////    }
////    
////    bool default_animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ) {
////        return ScaleUIAnimator::animateUIObject( boost::python::ptr(node), timeMS );
////    }
////
////};
//
//struct TranslateUIAnimator_wrapper : TranslateUIAnimator, bp::wrapper< TranslateUIAnimator > {
//
//    TranslateUIAnimator_wrapper(TranslateUIAnimator const & arg )
//    : TranslateUIAnimator( arg )
//      , bp::wrapper< TranslateUIAnimator >(){
//        // copy constructor
//        
//    }
//
//    TranslateUIAnimator_wrapper(::irr::u32 begin, ::irr::u32 duration, ::irr::core::vector2d< int > const & offset, bool loop=false )
//    : TranslateUIAnimator( begin, duration, boost::ref(offset), loop )
//      , bp::wrapper< TranslateUIAnimator >(){
//        // constructor
//    
//    }
//
//    virtual ::TranslateUIAnimator * Clone(  ) {
//        if( bp::override func_Clone = this->get_override( "Clone" ) )
//            return func_Clone(  );
//        else{
//            return this->TranslateUIAnimator::Clone(  );
//        }
//    }
//    
//    ::TranslateUIAnimator * default_Clone(  ) {
//        return TranslateUIAnimator::Clone( );
//    }
//
//    virtual bool animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ) {
//        if( bp::override func_animateUIObject = this->get_override( "animateUIObject" ) )
//            return func_animateUIObject( boost::python::ptr(node), timeMS );
//        else{
//            return this->TranslateUIAnimator::animateUIObject( boost::python::ptr(node), timeMS );
//        }
//    }
//    
//    bool default_animateUIObject( ::IUIObject * node, ::irr::u32 timeMS ) {
//        return TranslateUIAnimator::animateUIObject( boost::python::ptr(node), timeMS );
//    }
//
//};
//
//struct UIImage_wrapper : UIImage, bp::wrapper< UIImage > {
//
//    UIImage_wrapper(UIImage const & arg )
//    : UIImage( arg )
//      , bp::wrapper< UIImage >(){
//        // copy constructor
//        
//    }
//
//    UIImage_wrapper(::irr::video::IVideoDriver * driver, ::irr::core::vector2d< float > const & pos, ::irr::s32 width, ::irr::s32 height, ::irr::s32 order=0 )
//    : UIImage( boost::python::ptr(driver), boost::ref(pos), width, height, order )
//      , bp::wrapper< UIImage >(){
//        // constructor
//    
//    }
//
//    virtual void Draw(  ) {
//        if( bp::override func_Draw = this->get_override( "Draw" ) )
//            func_Draw(  );
//        else{
//            this->UIImage::Draw(  );
//        }
//    }
//    
//    void default_Draw(  ) {
//        UIImage::Draw( );
//    }
//
//    virtual void AddAnimator( ::IUIAnimator * ani ) {
//        if( bp::override func_AddAnimator = this->get_override( "AddAnimator" ) )
//            func_AddAnimator( boost::python::ptr(ani) );
//        else{
//            this->IUIObject::AddAnimator( boost::python::ptr(ani) );
//        }
//    }
//    
//    void default_AddAnimator( ::IUIAnimator * ani ) {
//        IUIObject::AddAnimator( boost::python::ptr(ani) );
//    }
//
//    virtual void AddChild( ::IUIObject * child ) {
//        if( bp::override func_AddChild = this->get_override( "AddChild" ) )
//            func_AddChild( boost::python::ptr(child) );
//        else{
//            this->IUIObject::AddChild( boost::python::ptr(child) );
//        }
//    }
//    
//    void default_AddChild( ::IUIObject * child ) {
//        IUIObject::AddChild( boost::python::ptr(child) );
//    }
//
//    virtual void DrawTree(  ) {
//        if( bp::override func_DrawTree = this->get_override( "DrawTree" ) )
//            func_DrawTree(  );
//        else{
//            this->IUIObject::DrawTree(  );
//        }
//    }
//    
//    void default_DrawTree(  ) {
//        IUIObject::DrawTree( );
//    }
//
//    virtual ::irr::s32 GetOrder(  ) const  {
//        if( bp::override func_GetOrder = this->get_override( "GetOrder" ) )
//            return func_GetOrder(  );
//        else{
//            return this->IUIObject::GetOrder(  );
//        }
//    }
//    
//    ::irr::s32 default_GetOrder(  ) const  {
//        return IUIObject::GetOrder( );
//    }
//
//    virtual void OnAnimate( ::irr::u32 time ) {
//        if( bp::override func_OnAnimate = this->get_override( "OnAnimate" ) )
//            func_OnAnimate( time );
//        else{
//            this->IUIObject::OnAnimate( time );
//        }
//    }
//    
//    void default_OnAnimate( ::irr::u32 time ) {
//        IUIObject::OnAnimate( time );
//    }
//
//    virtual void RemoveAll(  ) {
//        if( bp::override func_RemoveAll = this->get_override( "RemoveAll" ) )
//            func_RemoveAll(  );
//        else{
//            this->IUIObject::RemoveAll(  );
//        }
//    }
//    
//    void default_RemoveAll(  ) {
//        IUIObject::RemoveAll( );
//    }
//
//    virtual void RemoveAnimator( ::IUIAnimator * ani ) {
//        if( bp::override func_RemoveAnimator = this->get_override( "RemoveAnimator" ) )
//            func_RemoveAnimator( boost::python::ptr(ani) );
//        else{
//            this->IUIObject::RemoveAnimator( boost::python::ptr(ani) );
//        }
//    }
//    
//    void default_RemoveAnimator( ::IUIAnimator * ani ) {
//        IUIObject::RemoveAnimator( boost::python::ptr(ani) );
//    }
//
//    virtual void RemoveAnimators(  ) {
//        if( bp::override func_RemoveAnimators = this->get_override( "RemoveAnimators" ) )
//            func_RemoveAnimators(  );
//        else{
//            this->IUIObject::RemoveAnimators(  );
//        }
//    }
//    
//    void default_RemoveAnimators(  ) {
//        IUIObject::RemoveAnimators( );
//    }
//
//    virtual void RemoveChild( ::IUIObject * node ) {
//        if( bp::override func_RemoveChild = this->get_override( "RemoveChild" ) )
//            func_RemoveChild( boost::python::ptr(node) );
//        else{
//            this->IUIObject::RemoveChild( boost::python::ptr(node) );
//        }
//    }
//    
//    void default_RemoveChild( ::IUIObject * node ) {
//        IUIObject::RemoveChild( boost::python::ptr(node) );
//    }
//
//    virtual void SetOrder( ::irr::s32 order ) {
//        if( bp::override func_SetOrder = this->get_override( "SetOrder" ) )
//            func_SetOrder( order );
//        else{
//            this->IUIObject::SetOrder( order );
//        }
//    }
//    
//    void default_SetOrder( ::irr::s32 order ) {
//        IUIObject::SetOrder( order );
//    }
//
//    virtual void SetParent( ::IUIObject * parent ) {
//        if( bp::override func_SetParent = this->get_override( "SetParent" ) )
//            func_SetParent( boost::python::ptr(parent) );
//        else{
//            this->IUIObject::SetParent( boost::python::ptr(parent) );
//        }
//    }
//    
//    void default_SetParent( ::IUIObject * parent ) {
//        IUIObject::SetParent( boost::python::ptr(parent) );
//    }
//
//    virtual void remove(  ) {
//        if( bp::override func_remove = this->get_override( "remove" ) )
//            func_remove(  );
//        else{
//            this->IUIObject::remove(  );
//        }
//    }
//    
//    void default_remove(  ) {
//        IUIObject::remove( );
//    }
//
//};
//
//BOOST_PYTHON_MODULE(UI){
//    bp::class_< IUIAnimator_wrapper, boost::noncopyable >( "IUIAnimator" )    
//        .def( 
//            "Clone"
//            , bp::pure_virtual( (::IUIAnimator * ( ::IUIAnimator::* )(  ) )(&::IUIAnimator::Clone) )
//			, bp::return_value_policy<bp::reference_existing_object>()
//                /* undefined call policies */ )    
//        .def( 
//            "animateUIObject"
//            , bp::pure_virtual( (bool ( ::IUIAnimator::* )( ::IUIObject *,::irr::u32 ) )(&::IUIAnimator::animateUIObject) )
//            , ( bp::arg("node"), bp::arg("timeMS") ) );
//
//    { //::IUIObject
//        typedef bp::class_< IUIObject_wrapper, boost::noncopyable > IUIObject_exposer_t;
//        IUIObject_exposer_t IUIObject_exposer = IUIObject_exposer_t( "IUIObject", bp::init< irr::video::IVideoDriver *, irr::core::vector2d< float > const &, irr::s32, irr::s32, bp::optional< irr::s32 > >(( bp::arg("driver"), bp::arg("pos"), bp::arg("width"), bp::arg("height"), bp::arg("order")=(::irr::s32)(0) )) );
//        bp::scope IUIObject_scope( IUIObject_exposer );
//        { //::IUIObject::AddAnimator
//        
//            typedef void ( ::IUIObject::*AddAnimator_function_type )( ::IUIAnimator * ) ;
//            typedef void ( IUIObject_wrapper::*default_AddAnimator_function_type )( ::IUIAnimator * ) ;
//            
//            IUIObject_exposer.def( 
//                "AddAnimator"
//                , AddAnimator_function_type(&::IUIObject::AddAnimator)
//                , default_AddAnimator_function_type(&IUIObject_wrapper::default_AddAnimator)
//                , ( bp::arg("ani") ) );
//        
//        }
//        { //::IUIObject::AddChild
//        
//            typedef void ( ::IUIObject::*AddChild_function_type )( ::IUIObject * ) ;
//            typedef void ( IUIObject_wrapper::*default_AddChild_function_type )( ::IUIObject * ) ;
//            
//            IUIObject_exposer.def( 
//                "AddChild"
//                , AddChild_function_type(&::IUIObject::AddChild)
//                , default_AddChild_function_type(&IUIObject_wrapper::default_AddChild)
//                , ( bp::arg("child") ) );
//        
//        }
//        { //::IUIObject::Draw
//        
//            typedef void ( ::IUIObject::*Draw_function_type )(  ) ;
//            
//            IUIObject_exposer.def( 
//                "Draw"
//                , bp::pure_virtual( Draw_function_type(&::IUIObject::Draw) ) );
//        
//        }
//        { //::IUIObject::DrawTree
//        
//            typedef void ( ::IUIObject::*DrawTree_function_type )(  ) ;
//            typedef void ( IUIObject_wrapper::*default_DrawTree_function_type )(  ) ;
//            
//            IUIObject_exposer.def( 
//                "DrawTree"
//                , DrawTree_function_type(&::IUIObject::DrawTree)
//                , default_DrawTree_function_type(&IUIObject_wrapper::default_DrawTree) );
//        
//        }
//        { //::IUIObject::GetAlpha
//        
//            typedef ::irr::f32 ( ::IUIObject::*GetAlpha_function_type )(  ) ;
//            
//            IUIObject_exposer.def( 
//                "GetAlpha"
//                , GetAlpha_function_type( &::IUIObject::GetAlpha ) );
//        
//        }
//        { //::IUIObject::GetAnimators
//        
//            typedef ::std::list< IUIAnimator* > const & ( ::IUIObject::*GetAnimators_function_type )(  ) const;
//            
//            IUIObject_exposer.def( 
//                "GetAnimators"
//                , GetAnimators_function_type(&::IUIObject::GetAnimators)
//                , bp::return_value_policy< bp::copy_const_reference >() );
//        
//        }
//        { //::IUIObject::GetCenter
//        
//            typedef ::irr::core::vector2d< float > const & ( ::IUIObject::*GetCenter_function_type )(  ) const;
//            
//            IUIObject_exposer.def( 
//                "GetCenter"
//                , GetCenter_function_type( &::IUIObject::GetCenter )
//                , bp::return_value_policy< bp::copy_const_reference >() );
//        
//        }
//        { //::IUIObject::GetChildren
//        
//            typedef ::std::list< IUIObject* > const & ( ::IUIObject::*GetChildren_function_type )(  ) const;
//            
//            IUIObject_exposer.def( 
//                "GetChildren"
//                , GetChildren_function_type(&::IUIObject::GetChildren)
//                , bp::return_value_policy< bp::copy_const_reference >() );
//        
//        }
//        { //::IUIObject::GetOrder
//        
//            typedef ::irr::s32 ( ::IUIObject::*GetOrder_function_type )(  ) const;
//            typedef ::irr::s32 ( IUIObject_wrapper::*default_GetOrder_function_type )(  ) const;
//            
//            IUIObject_exposer.def( 
//                "GetOrder"
//                , GetOrder_function_type(&::IUIObject::GetOrder)
//                , default_GetOrder_function_type(&IUIObject_wrapper::default_GetOrder) );
//        
//        }
//        { //::IUIObject::OnAnimate
//        
//            typedef void ( ::IUIObject::*OnAnimate_function_type )( ::irr::u32 ) ;
//            typedef void ( IUIObject_wrapper::*default_OnAnimate_function_type )( ::irr::u32 ) ;
//            
//            IUIObject_exposer.def( 
//                "OnAnimate"
//                , OnAnimate_function_type(&::IUIObject::OnAnimate)
//                , default_OnAnimate_function_type(&IUIObject_wrapper::default_OnAnimate)
//                , ( bp::arg("time") ) );
//        
//        }
//        { //::IUIObject::RemoveAll
//        
//            typedef void ( ::IUIObject::*RemoveAll_function_type )(  ) ;
//            typedef void ( IUIObject_wrapper::*default_RemoveAll_function_type )(  ) ;
//            
//            IUIObject_exposer.def( 
//                "RemoveAll"
//                , RemoveAll_function_type(&::IUIObject::RemoveAll)
//                , default_RemoveAll_function_type(&IUIObject_wrapper::default_RemoveAll) );
//        
//        }
//        { //::IUIObject::RemoveAnimator
//        
//            typedef void ( ::IUIObject::*RemoveAnimator_function_type )( ::IUIAnimator * ) ;
//            typedef void ( IUIObject_wrapper::*default_RemoveAnimator_function_type )( ::IUIAnimator * ) ;
//            
//            IUIObject_exposer.def( 
//                "RemoveAnimator"
//                , RemoveAnimator_function_type(&::IUIObject::RemoveAnimator)
//                , default_RemoveAnimator_function_type(&IUIObject_wrapper::default_RemoveAnimator)
//                , ( bp::arg("ani") ) );
//        
//        }
//        { //::IUIObject::RemoveAnimators
//        
//            typedef void ( ::IUIObject::*RemoveAnimators_function_type )(  ) ;
//            typedef void ( IUIObject_wrapper::*default_RemoveAnimators_function_type )(  ) ;
//            
//            IUIObject_exposer.def( 
//                "RemoveAnimators"
//                , RemoveAnimators_function_type(&::IUIObject::RemoveAnimators)
//                , default_RemoveAnimators_function_type(&IUIObject_wrapper::default_RemoveAnimators) );
//        
//        }
//        { //::IUIObject::RemoveChild
//        
//            typedef void ( ::IUIObject::*RemoveChild_function_type )( ::IUIObject * ) ;
//            typedef void ( IUIObject_wrapper::*default_RemoveChild_function_type )( ::IUIObject * ) ;
//            
//            IUIObject_exposer.def( 
//                "RemoveChild"
//                , RemoveChild_function_type(&::IUIObject::RemoveChild)
//                , default_RemoveChild_function_type(&IUIObject_wrapper::default_RemoveChild)
//                , ( bp::arg("node") ) );
//        
//        }
//        { //::IUIObject::SetAlpha
//        
//            typedef void ( ::IUIObject::*SetAlpha_function_type )( ::irr::f32 ) ;
//            
//            IUIObject_exposer.def( 
//                "SetAlpha"
//                , SetAlpha_function_type( &::IUIObject::SetAlpha )
//                , ( bp::arg("alpha") ) );
//        
//        }
//        { //::IUIObject::SetCenter
//        
//            typedef void ( ::IUIObject::*SetCenter_function_type )( ::irr::core::vector2d< float > const & ) ;
//            
//            IUIObject_exposer.def( 
//                "SetCenter"
//                , SetCenter_function_type( &::IUIObject::SetCenter )
//                , ( bp::arg("pos") ) );
//        
//        }
//        { //::IUIObject::SetImage
//        
//            typedef void ( ::IUIObject::*SetImage_function_type )( char * ) ;
//            
//            IUIObject_exposer.def( 
//                "SetImage"
//                , SetImage_function_type( &::IUIObject::SetImage )
//                , ( bp::arg("arg0") ) );
//        
//        }
//        { //::IUIObject::SetOrder
//        
//            typedef void ( ::IUIObject::*SetOrder_function_type )( ::irr::s32 ) ;
//            typedef void ( IUIObject_wrapper::*default_SetOrder_function_type )( ::irr::s32 ) ;
//            
//            IUIObject_exposer.def( 
//                "SetOrder"
//                , SetOrder_function_type(&::IUIObject::SetOrder)
//                , default_SetOrder_function_type(&IUIObject_wrapper::default_SetOrder)
//                , ( bp::arg("order") ) );
//        
//        }
//        { //::IUIObject::SetParent
//        
//            typedef void ( ::IUIObject::*SetParent_function_type )( ::IUIObject * ) ;
//            typedef void ( IUIObject_wrapper::*default_SetParent_function_type )( ::IUIObject * ) ;
//            
//            IUIObject_exposer.def( 
//                "SetParent"
//                , SetParent_function_type(&::IUIObject::SetParent)
//                , default_SetParent_function_type(&IUIObject_wrapper::default_SetParent)
//                , ( bp::arg("parent") ) );
//        
//        }
//        { //::IUIObject::remove
//        
//            typedef void ( ::IUIObject::*remove_function_type )(  ) ;
//            typedef void ( IUIObject_wrapper::*default_remove_function_type )(  ) ;
//            
//            IUIObject_exposer.def( 
//                "remove"
//                , remove_function_type(&::IUIObject::remove)
//                , default_remove_function_type(&IUIObject_wrapper::default_remove) );
//        
//        }
//        pyplusplus::containers::static_sized::register_array_1< ::irr::core::vector2d<float>, 4, bp::return_internal_reference< > >( "__array_1__scope_irr_scope_core_scope_vector2d_less_float_greater__4" );
//        { //IUIObject::DstQuar [variable], type=irr::core::vector2d<float>[4]
//        
//            typedef pyplusplus::containers::static_sized::array_1_t< ::irr::core::vector2d<float>, 4> ( *array_wrapper_creator )( ::IUIObject & );
//            
//            IUIObject_exposer.add_property( "DstQuar"
//                , bp::make_function( array_wrapper_creator(&IUIObject_wrapper::pyplusplus_DstQuar_wrapper)
//                                    , bp::with_custodian_and_ward_postcall< 0, 1 >() ) );
//        }
//    }
//
//	bp::class_< DeletionAnimator_wrapper, bp::bases< IUIAnimator > >( "DeletionAnimator", bp::init< irr::u32, irr::u32 >(( bp::arg("now"), bp::arg("time") )) )    
//		.def( 
//		"Clone"
//		, (::IUIAnimator * ( ::DeletionAnimator::* )(  ) )(&::DeletionAnimator::Clone)
//		, (::IUIAnimator * ( DeletionAnimator_wrapper::* )(  ) )(&DeletionAnimator_wrapper::default_Clone)
//		, bp::return_value_policy< bp::reference_existing_object >()
//		/* undefined call policies */ )    
//		.def( 
//		"animateUIObject"
//		, (bool ( ::DeletionAnimator::* )( ::IUIObject *,::irr::u32 ) )(&::DeletionAnimator::animateUIObject)
//		, (bool ( DeletionAnimator_wrapper::* )( ::IUIObject *,::irr::u32 ) )(&DeletionAnimator_wrapper::default_animateUIObject)
//		, ( bp::arg("node"), bp::arg("timeMS") ) );
//
//    bp::class_< RotateUIAnimator_wrapper, bp::bases< IUIAnimator > >( "RotateUIAnimator", bp::init< irr::u32, irr::u32, irr::f32, irr::core::vector2d< float > const &, irr::core::vector2d< float > const &, bp::optional< bool > >(( bp::arg("begin"), bp::arg("duration"), bp::arg("angle"), bp::arg("rotpoint"), bp::arg("ObjCen"), bp::arg("loop")=(bool)(false) )) )    
//        .def( 
//            "Clone"
//            , (::RotateUIAnimator * ( ::RotateUIAnimator::* )(  ) )(&::RotateUIAnimator::Clone)
//            , (::RotateUIAnimator * ( RotateUIAnimator_wrapper::* )(  ) )(&RotateUIAnimator_wrapper::default_Clone)
//			, bp::return_value_policy< bp::reference_existing_object >()
//                /* undefined call policies */ )    
//        .def( 
//            "animateUIObject"
//            , (bool ( ::RotateUIAnimator::* )( ::IUIObject *,::irr::u32 ) )(&::RotateUIAnimator::animateUIObject)
//            , (bool ( RotateUIAnimator_wrapper::* )( ::IUIObject *,::irr::u32 ) )(&RotateUIAnimator_wrapper::default_animateUIObject)
//            , ( bp::arg("node"), bp::arg("timeMS") ) );
//
//   // bp::class_< ScaleUIAnimator_wrapper, bp::bases< IUIAnimator > >( "ScaleUIAnimator", bp::init< irr::u32, irr::u32, irr::core::vector2d< float >, irr::core::vector2d< float > const &, bp::optional< bool > >(( bp::arg("begin"), bp::arg("duration"), bp::arg("scale"), bp::arg("scapoint"), bp::arg("loop")=(bool)(false) )) )    
//   //     .def( 
//   //         "Clone"
//   //         , (::ScaleUIAnimator * ( ::ScaleUIAnimator::* )(  ) )(&::ScaleUIAnimator::Clone)
//   //         , (::ScaleUIAnimator * ( ScaleUIAnimator_wrapper::* )(  ) )(&ScaleUIAnimator_wrapper::default_Clone)
//			//, bp::return_value_policy< bp::reference_existing_object >()
//   //             /* undefined call policies */ )    
//   //     .def( 
//   //         "animateUIObject"
//   //         , (bool ( ::ScaleUIAnimator::* )( ::IUIObject *,::irr::u32 ) )(&::ScaleUIAnimator::animateUIObject)
//   //         , (bool ( ScaleUIAnimator_wrapper::* )( ::IUIObject *,::irr::u32 ) )(&ScaleUIAnimator_wrapper::default_animateUIObject)
//   //         , ( bp::arg("node"), bp::arg("timeMS") ) );
//
//    bp::class_< TranslateUIAnimator_wrapper, bp::bases< IUIAnimator > >( "TranslateUIAnimator", bp::init< irr::u32, irr::u32, irr::core::vector2d< int > const &, bp::optional< bool > >(( bp::arg("begin"), bp::arg("duration"), bp::arg("offset"), bp::arg("loop")=(bool)(false) )) )    
//        .def( 
//            "Clone"
//            , (::TranslateUIAnimator * ( ::TranslateUIAnimator::* )(  ) )(&::TranslateUIAnimator::Clone)
//            , (::TranslateUIAnimator * ( TranslateUIAnimator_wrapper::* )(  ) )(&TranslateUIAnimator_wrapper::default_Clone)
//			, bp::return_value_policy< bp::manage_new_object >()
//                /* undefined call policies */ )    
//        .def( 
//            "animateUIObject"
//            , (bool ( ::TranslateUIAnimator::* )( ::IUIObject *,::irr::u32 ) )(&::TranslateUIAnimator::animateUIObject)
//            , (bool ( TranslateUIAnimator_wrapper::* )( ::IUIObject *,::irr::u32 ) )(&TranslateUIAnimator_wrapper::default_animateUIObject)
//            , ( bp::arg("node"), bp::arg("timeMS") ) );
//
//    bp::class_< UIImage_wrapper, bp::bases< IUIObject > >( "UIImage", bp::init< irr::video::IVideoDriver *, irr::core::vector2d< float > const &, irr::s32, irr::s32, bp::optional< irr::s32 > >(( bp::arg("driver"), bp::arg("pos"), bp::arg("width"), bp::arg("height"), bp::arg("order")=(::irr::s32)(0) )) )    
//        .def( 
//            "Draw"
//            , (void ( ::UIImage::* )(  ) )(&::UIImage::Draw)
//            , (void ( UIImage_wrapper::* )(  ) )(&UIImage_wrapper::default_Draw) )    
//        .def( 
//            "AddAnimator"
//            , (void ( ::IUIObject::* )( ::IUIAnimator * ) )(&::IUIObject::AddAnimator)
//            , (void ( UIImage_wrapper::* )( ::IUIAnimator * ) )(&UIImage_wrapper::default_AddAnimator)
//            , ( bp::arg("ani") ) )    
//        .def( 
//            "AddChild"
//            , (void ( ::IUIObject::* )( ::IUIObject * ) )(&::IUIObject::AddChild)
//            , (void ( UIImage_wrapper::* )( ::IUIObject * ) )(&UIImage_wrapper::default_AddChild)
//            , ( bp::arg("child") ) )    
//        .def( 
//            "DrawTree"
//            , (void ( ::IUIObject::* )(  ) )(&::IUIObject::DrawTree)
//            , (void ( UIImage_wrapper::* )(  ) )(&UIImage_wrapper::default_DrawTree) )    
//        .def( 
//            "GetAnimators"
//            , (::std::list< IUIAnimator* > const & ( ::IUIObject::* )(  ) const)(&::IUIObject::GetAnimators)
//            , bp::return_value_policy< bp::copy_const_reference >() )    
//        .def( 
//            "GetChildren"
//            , (::std::list< IUIObject* > const & ( ::IUIObject::* )(  ) const)(&::IUIObject::GetChildren)
//            , bp::return_value_policy< bp::copy_const_reference >() )    
//        .def( 
//            "GetOrder"
//            , (::irr::s32 ( ::IUIObject::* )(  ) const)(&::IUIObject::GetOrder)
//            , (::irr::s32 ( UIImage_wrapper::* )(  ) const)(&UIImage_wrapper::default_GetOrder) )    
//        .def( 
//            "OnAnimate"
//            , (void ( ::IUIObject::* )( ::irr::u32 ) )(&::IUIObject::OnAnimate)
//            , (void ( UIImage_wrapper::* )( ::irr::u32 ) )(&UIImage_wrapper::default_OnAnimate)
//            , ( bp::arg("time") ) )    
//        .def( 
//            "RemoveAll"
//            , (void ( ::IUIObject::* )(  ) )(&::IUIObject::RemoveAll)
//            , (void ( UIImage_wrapper::* )(  ) )(&UIImage_wrapper::default_RemoveAll) )    
//        .def( 
//            "RemoveAnimator"
//            , (void ( ::IUIObject::* )( ::IUIAnimator * ) )(&::IUIObject::RemoveAnimator)
//            , (void ( UIImage_wrapper::* )( ::IUIAnimator * ) )(&UIImage_wrapper::default_RemoveAnimator)
//            , ( bp::arg("ani") ) )    
//        .def( 
//            "RemoveAnimators"
//            , (void ( ::IUIObject::* )(  ) )(&::IUIObject::RemoveAnimators)
//            , (void ( UIImage_wrapper::* )(  ) )(&UIImage_wrapper::default_RemoveAnimators) )    
//        .def( 
//            "RemoveChild"
//            , (void ( ::IUIObject::* )( ::IUIObject * ) )(&::IUIObject::RemoveChild)
//            , (void ( UIImage_wrapper::* )( ::IUIObject * ) )(&UIImage_wrapper::default_RemoveChild)
//            , ( bp::arg("node") ) )    
//        .def( 
//            "SetOrder"
//            , (void ( ::IUIObject::* )( ::irr::s32 ) )(&::IUIObject::SetOrder)
//            , (void ( UIImage_wrapper::* )( ::irr::s32 ) )(&UIImage_wrapper::default_SetOrder)
//            , ( bp::arg("order") ) )    
//        .def( 
//            "SetParent"
//            , (void ( ::IUIObject::* )( ::IUIObject * ) )(&::IUIObject::SetParent)
//            , (void ( UIImage_wrapper::* )( ::IUIObject * ) )(&UIImage_wrapper::default_SetParent)
//            , ( bp::arg("parent") ) )    
//        .def( 
//            "remove"
//            , (void ( ::IUIObject::* )(  ) )(&::IUIObject::remove)
//            , (void ( UIImage_wrapper::* )(  ) )(&UIImage_wrapper::default_remove) );
//}