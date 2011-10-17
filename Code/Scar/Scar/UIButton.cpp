#include "UIButton.h"
#include "MyIrrlichtEngine.h"


UIButton::UIButton( IUIObject* parent, s32 width, s32 height, s32 order /*= 0*/, int shape,
	const vector2d<f32>& position /*= vector2d<f32>(0,0)*/,
	f32 rotdeg /*= 0*/,
	const vector2d<f32>& scale /*= vector2d<f32>(1,1) */ )
	: IUIObject( parent, width, height, order, shape, position, rotdeg, scale )
{
	IsMouseIn = false;
}

//����
void UIButton::Draw()
{
	UpdateAbsolutePosition();

	if (Image==NULL)
		return;
	int h = Image->getSize().Height;
	int w = Image->getSize().Width;
	rect<s32>r(0, 0, w, h);

	vector2d<s32> intDstQuar[4];
	ub::vector<f32> temp(3);
	temp(2) = 1;
	//std::cout<<AbsoluteTransformation<<std::endl;
	for( int i=0; i<4; i++)
	{
		temp(0) = DestinationQuadrangle[i].X;
		temp(1) = DestinationQuadrangle[i].Y;
		temp = prod( temp, AbsoluteTransformation );
		intDstQuar[i].set( (s32)temp(0), (s32)temp(1) );
	}

	SColor colors[4];
	for (int i=0; i<4; i++)
	{
		colors[i] = SColor((u32)GetAbsoluteAlpha(),255,255,255);
	}

	Driver->draw2DImage( Image, intDstQuar, rect<s32>(0,0,w,h), 0, colors, true );
}

void UIButton::OnMouseMove( const irr::SEvent::SMouseInput& event )
{
	if ( IsPointIn( event.X, event.Y ) )
	{
		if( !IsMouseIn )
		{
			IsMouseIn = true;
			OnMouseMoveIn();
		}
		else
		{
			//����дOnMouseMove���߼�
			try
			{
				std::string eventName = "OnMouseMove";
				auto func = FuncMap.find( eventName );
				if ( func != FuncMap.end() )
				{
					using namespace boost::python;
					auto FuncInfo = FuncMap[ eventName ];
					object module = import( FuncInfo.ModuleName.c_str() );
					object fun = module.attr( FuncInfo.FuncName.c_str() );
					fun( boost::ref( this ) );
				}
			}
			catch ( ... )
			{
				PyErr_Print();
			}
		}
		
	}
	else if ( IsMouseIn )
	{
		IsMouseIn = false;
		OnMouseMoveOut();
	}
}

void UIButton::OnMouseLeftButtonUp( const irr::SEvent::SMouseInput& event )
{
	if( IsMouseIn )
	{
		try
		{
			std::string eventName = "OnMouseLeftButtonUp";
			auto func = FuncMap.find( eventName );
			if ( func != FuncMap.end() )
			{
				using namespace boost::python;
				auto FuncInfo = FuncMap[ eventName ];
				object module = import( FuncInfo.ModuleName.c_str() );
				object fun = module.attr( FuncInfo.FuncName.c_str() );
				fun( boost::ref( this ) );
			}
		}
		catch ( ... )
		{
			PyErr_Print();
		}
	}
}

void UIButton::OnMouseLeftButtonDown( const irr::SEvent::SMouseInput& event )
{
	if( IsMouseIn )
	{
		try
		{
			std::string eventName = "OnMouseLeftButtonDown";
			auto func = FuncMap.find( eventName );
			if ( func != FuncMap.end() )
			{
				using namespace boost::python;
				auto FuncInfo = FuncMap[ eventName ];
				object module = import( FuncInfo.ModuleName.c_str() );
				object fun = module.attr( FuncInfo.FuncName.c_str() );
				fun( boost::ref( this ) );
			}
		}
		catch ( ... )
		{
			PyErr_Print();
		}
	}
}

void UIButton::OnMouseRightButtonUp( const irr::SEvent::SMouseInput& event )
{
	try
	{
		std::string eventName = "OnMouseRightButtonUp";
		auto func = FuncMap.find( eventName );
		if ( func != FuncMap.end() )
		{
			using namespace boost::python;
			auto FuncInfo = FuncMap[ eventName ];
			object module = import( FuncInfo.ModuleName.c_str() );
			object fun = module.attr( FuncInfo.FuncName.c_str() );
			fun( boost::ref( this ) );
		}
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

void UIButton::OnMouseRightButtonDown( const irr::SEvent::SMouseInput& event )
{
	try
	{
		std::string eventName = "OnMouseRightButtonDown";
		auto func = FuncMap.find( eventName );
		if ( func != FuncMap.end() )
		{
			using namespace boost::python;
			auto FuncInfo = FuncMap[ eventName ];
			object module = import( FuncInfo.ModuleName.c_str() );
			object fun = module.attr( FuncInfo.FuncName.c_str() );
			fun( boost::ref( this ) );
		}
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

void UIButton::OnMouseMoveIn()
{
	try
	{
		std::string eventName = "OnMouseMoveIn";
		auto func = FuncMap.find( eventName );
		if ( func != FuncMap.end() )
		{
			using namespace boost::python;
			auto FuncInfo = FuncMap[ eventName ];
			object module = import( FuncInfo.ModuleName.c_str() );
			object fun = module.attr( FuncInfo.FuncName.c_str() );
			fun( boost::ref( this ) );
		}
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

void UIButton::OnMouseMoveOut()
{
	try
	{
		std::string eventName = "OnMouseMoveOut";
		auto func = FuncMap.find( eventName );
		if ( func != FuncMap.end() )
		{
			using namespace boost::python;
			auto FuncInfo = FuncMap[ eventName ];
			object module = import( FuncInfo.ModuleName.c_str() );
			object fun = module.attr( FuncInfo.FuncName.c_str() );
			fun( boost::ref( this ) );
		}
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

