#include "UIButton.h"
#include "MyIrrlichtEngine.h"


UIButton::UIButton( IUIObject* parent, s32 width, s32 height, s32 order /*= 0*/, int shape,
	const vector2d<f32>& position /*= vector2d<f32>(0,0)*/,
	f32 rotdeg /*= 0*/,
	const vector2d<f32>& scale /*= vector2d<f32>(1,1) */ )
	: IUIObject( parent, width, height, order, shape, position, rotdeg, scale )
{
	if ( parent )
	{
		parent->AddChild( this );
	}
	IsMouseIn = false;
}

//绘制
void UIButton::Draw()
{
	UpdateAbsolutePosition();

	// 如果大小为0，那就没必要画自己了
	/*if( DestinationQuadrangle[0] == DestinationQuadrangle[2] )
		return;*/

	if (Image==NULL)
	{
		
		return;
	}
		
	int h = Image->getSize().Height;
	int w = Image->getSize().Width;
	rect<s32>r(0, 0, w, h);

	vector2d<s32> intDstQuar[4];
	ub::vector<f32> temp(3);
	temp(2) = 1;
	
	temp(0) = DestinationQuadrangle[0].X + LeftTop.X;
	temp(1) = DestinationQuadrangle[0].Y + LeftTop.Y;
	temp = prod( temp, AbsoluteTransformation );
	intDstQuar[0].set( (s32)temp(0), (s32)temp(1) );
	temp(0) = DestinationQuadrangle[1].X + RightBottom.X - w;
	temp(1) = DestinationQuadrangle[1].Y + LeftTop.Y;
	temp = prod( temp, AbsoluteTransformation );
	intDstQuar[1].set( (s32)temp(0), (s32)temp(1) );
	temp(0) = DestinationQuadrangle[2].X + RightBottom.X - w;
	temp(1) = DestinationQuadrangle[2].Y + RightBottom.Y - h;
	temp = prod( temp, AbsoluteTransformation );
	intDstQuar[2].set( (s32)temp(0), (s32)temp(1) );
	temp(0) = DestinationQuadrangle[3].X + LeftTop.X;
	temp(1) = DestinationQuadrangle[3].Y + RightBottom.Y - h;
	temp = prod( temp, AbsoluteTransformation );
	intDstQuar[3].set( (s32)temp(0), (s32)temp(1) );

	SColor colors[4];
	for (int i=0; i<4; i++)
	{
		colors[i] = SColor((u32)GetAbsoluteAlpha(),255,255,255);
	}
	rect<f32> re ;
	rect<s32> * clipre = NULL;
	if ( ClipRect )
	{
		rect<f32> t= GetAbsoluteClipRect();
		rect<s32> re = rect<s32>( ( s32)t.UpperLeftCorner.X,( s32)t.UpperLeftCorner.Y,( s32)t.LowerRightCorner.X,( s32)t.LowerRightCorner.Y);
		clipre = &re;
	}
	
		Driver->enableMaterial2D();
	
	Driver->draw2DImage( Image, intDstQuar, rect<s32>(0,0,w,h), clipre, colors, true );
	
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
			//这里写OnMouseMove的逻辑
			PythonFunc( "OnMouseMove" );
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
		PythonFunc( "OnMouseLeftButtonUp" );
	}
}


void UIButton::OnMouseLeftButtonDown( const irr::SEvent::SMouseInput& event )
{
	if( IsMouseIn )
	{
		PythonFunc( "OnMouseLeftButtonDown" );
	}
}

void UIButton::OnMouseRightButtonUp( const irr::SEvent::SMouseInput& event )
{
	PythonFunc( "OnMouseRightButtonUp" );
}

void UIButton::OnMouseRightButtonDown( const irr::SEvent::SMouseInput& event )
{	
	PythonFunc( "OnMouseRightButtonDown" );
}

void UIButton::OnMouseMoveIn()
{
	PythonFunc( "OnMouseMoveIn" );
}

void UIButton::OnMouseMoveOut()
{	
	PythonFunc( "OnMouseMoveOut" );
}

