/********************************************************************
    创建时间: 2011-11-8   
    文件名:   UIBar.h
    作者:     谢骏飞
    说明:     滚动条

*********************************************************************/
#ifndef CUIBar_H__
#define CUIBar_H__
#include "uibutton.h"
#ifndef  HBAR
#define  HBAR   0
#endif

#ifndef VBAR
#define VBAR    1
#endif
class CUIBar :
	public IUIObject
{
public:
	CUIBar( IUIObject* parent, s32 width, s32 height, u32 type =0, s32 order = 0, int shape = SQUARE, const vector2d<f32>& position = vector2d<f32>(0,0), f32 rotdeg = 0, const vector2d<f32>& scale = vector2d<f32>(1,1) ):  IUIObject( parent, width, height, order , shape, position,rotdeg,scale )
	{
		if ( parent )
		{
			parent->AddChild( this );
		}
		Type = type;
		if ( type == VBAR )
		{
			ScrollLenOnce  = ( f32 )( height/10.0>=1.0?( f32 )height/10.0:1.0);
		}
		 else
			 ScrollLenOnce  = ( f32 )( width/10.0>=1.0?( f32 )width/10.0:1.0);
		
		if ( Type == VBAR )
		{
			s32 temph = height - 2 * width;
			if ( temph < 0 )
			{
				temph = 0;
			}
			Scroll = new UIButton( this,  width  , temph );
			f32 tempposy = -( f32 )(( 0.5 * height- width)* 0.5);
			RefYOrX  = -( f32 ) ( 0.5 * height - width );
			Scroll->LoadImage( VScrollTex );
				f32 tempy = (f32 )0.5 * ( height - width) ;
			if ( tempy < 0 )
			{
				tempy = 0;
			}
			LoadImage( VBackGroundTex );
			LeftOrTopButton = new UIButton( this,width, width);
			LeftOrTopButton->LoadImage( TopButtonTex );
			LeftOrTopButton->SetPosition( vector2df( 0.0, -tempy ));
			RightOrDownButton = new UIButton( this,width, width );
			RightOrDownButton->SetPosition( vector2df( 0.0, tempy));
			RightOrDownButton->LoadImage( DownButtonTex );
			
			Len = ( f32 )height;
			ViewportHeightOrWidth = ( f32 )0.5 * Len;
			ScrollMaxRightDownPos = vector2df( ( f32 )0.5 * width, (f32)( 0.5 *  height - width));
			ScrollMaxLeftUpPos = vector2df(  -( f32 )0.5 * width, -( f32 )( 0.5 * height -width));
			
		}

		if ( Type == HBAR )
		{

			s32 tempw = width - 2 * height;
			if ( tempw < 0 )
			{
				tempw = 0;
			}
			RefYOrX = -( f32 ) ( 0.5 * width - height );
			f32 tempsposx = ( f32 )(( 0.5 * width - height)* 0.5);
			ScrollPos =  vector2df( -tempsposx, 0.0);
			Scroll = new UIButton( this, tempw , height );
			Scroll->LoadImage( HScrollTex );
			f32 tempbposx =  (f32)(0.5 * (width - height));
			if ( tempbposx < 0)
			{
				tempbposx = 0;
			}
			LoadImage( HBackGroundTex );
			LeftOrTopButton = new UIButton( this,height, height);
			LeftOrTopButton->SetPosition( vector2df( -tempbposx, 0));
			LeftOrTopButton->LoadImage( LefButtonTex );
			RightOrDownButton = new UIButton( this,height, height);
			RightOrDownButton->LoadImage( RightButtonTex );
			RightOrDownButton->SetPosition( vector2df ( tempbposx, 0.0));
			

			Len = ( f32 )width;
			ScrollMaxRightDownPos = vector2df( (f32)( 0.5 *  width - height), ( f32 )0.5 * height);
			ScrollMaxLeftUpPos = vector2df( -( f32 )( 0.5 * width -height), -( f32 )0.5 * height );
			
		}
		ViewportPosXOrY = 0;
		ViewportHeightOrWidth = ( f32) 0.5 * Len;
		
	}
	~CUIBar(void);


	virtual IUIObject* Clone()
	 {
		 return NULL;
	 }
	//获取滚动条的平移大小
	virtual f32 GetViewPortPosXOrY() const
	{
		return ViewportPosXOrY;
	}

	//设置滚动条的平移大小
	virtual void SetViewPortPosXOrY( f32& tl)
	{
		ViewportPosXOrY = tl;
		
	}

	 //设置滚动条逻辑长度
	 virtual void SetLen( f32& l)
	{
		Len = l;
	}
	 virtual f32 GetLen() const
	{
		return Len;
	}

	 virtual void OnMouseLeftButtonDown( const irr::SEvent::SMouseInput& event )
	{
		if ( !IsVisible ) return;
		if ( Type == HBAR )
		{
			if ( LeftOrTopButton->IsPointIn( event.X , event.Y ))
			{
				ViewportPosXOrY -= ScrollLenOnce;
				

			}
		   else if ( RightOrDownButton -> IsPointIn( event.X , event.Y ))
		    {
				ViewportPosXOrY += ScrollLenOnce;
				
		    }
			else if ( IsPointInRelativeRect(event.X, event.Y, rect<f32>(ScrollMaxLeftUpPos.X , ScrollMaxLeftUpPos.Y, ScrollPos.X - (f32)( 0.5 ) * Scroll->GetOriginSize().Width * Scroll->GetScale().X ,ScrollPos.Y + ( f32 )0.5 * Scroll->GetOriginSize().Height* Scroll->GetScale().Y )))
			{
				ViewportPosXOrY -= ViewportHeightOrWidth;
				
		   }
			else if ( IsPointInRelativeRect(event.X, event.Y, rect<f32>( ScrollPos.X + ( f32 )0.5 * Scroll->GetOriginSize().Width* Scroll->GetScale().X , ScrollPos.Y - ( f32 )0.5 * Scroll->GetOriginSize().Height * Scroll->GetScale().Y , ScrollMaxRightDownPos.X, ScrollMaxRightDownPos.Y )) )
			{
				ViewportPosXOrY += ViewportHeightOrWidth;
				
			}
			
		}

		if ( Type == VBAR)
		{

			if ( LeftOrTopButton->IsPointIn( event.X , event.Y ))
			{
				ViewportPosXOrY -= ScrollLenOnce;
				
			}
			else if ( RightOrDownButton -> IsPointIn( event.X , event.Y ))
			{
				ViewportPosXOrY += ScrollLenOnce;
				
			}
			else if ( IsPointInRelativeRect(event.X, event.Y, rect<f32>(ScrollMaxLeftUpPos.X , ScrollMaxLeftUpPos.Y, ScrollPos.X + (f32)( 0.5 ) * Scroll->GetOriginSize().Width * Scroll->GetScale().X,ScrollPos.Y - ( f32 )0.5 * Scroll->GetOriginSize().Height * Scroll->GetScale().Y)))
			{
				ViewportPosXOrY -= ViewportHeightOrWidth;
				
			}
			else if ( IsPointInRelativeRect(event.X, event.Y, rect<f32>( ScrollPos.X - ( f32 )0.5 * Scroll->GetOriginSize().Width * Scroll->GetScale().X , ScrollPos.Y + ( f32 )0.5 * Scroll->GetOriginSize().Height * Scroll->GetScale().Y , ScrollMaxRightDownPos.X, ScrollMaxRightDownPos.Y )) )
			{
				ViewportPosXOrY += ViewportHeightOrWidth;
				
			}


		}
		if ( ViewportPosXOrY < 0)
		{
			ViewportPosXOrY = 0;
		}
		
	    if ( Type == HBAR)
	    {
			f32 viewportlen = Scroll->GetSize().Width* Len / (Scroll->GetOriginSize().Width ) ;
			if ( ViewportPosXOrY > Len - viewportlen )
			{
				ViewportPosXOrY = Len - viewportlen;
			}
	    }
		else{
			f32 viewportlen = Scroll->GetSize().Height * Len/ ( Scroll->GetOriginSize().Height );
			if ( ViewportPosXOrY > Len - viewportlen )
			{
				ViewportPosXOrY = Len - viewportlen;
			}
		}
		/*UIButton::OnMouseLeftButtonDown(event);*/
	}

	 //设置滚动单位
	 virtual f32 GetScrollLenOnce ( ) const
	 {
		 return ScrollLenOnce;
	 }
	 virtual void SetScrollLenOnce( f32& l)
	 {
		 ScrollLenOnce = l;
	 }
	 

	 //设置视口的宽和高
	 virtual void SetViewportHeightOrWidth( f32& hOrw)
	 {
		 ViewportHeightOrWidth = hOrw;
	 }


	 virtual void OnAnimate( u32 time )
		 {
			 if ( ViewportHeightOrWidth >= Len )
			 {
				 SetVisible( false );
			 }

			 else 
			 {
				 UpdateScrollPos();
				 if ( Type == HBAR )
				 {
					 if (  Scroll->GetSize().Width   > Scroll->GetSize().Height )
					 {
						 Scroll->SetScale( vector2df( ViewportHeightOrWidth / Len, 1.0 ));
						 if ( Scroll->GetSize().Width < Scroll-> GetSize().Height )
						 {
							 Scroll->SetScale( vector2df (Scroll->GetOriginSize().Height / Scroll->GetOriginSize().Width , 1.0) );
						 }

					 }
				 }
				 else 
				 {
					 if (  Scroll->GetSize().Height > Scroll->GetSize().Width )
					 {
						 Scroll->SetScale( vector2df( 1.0, ViewportHeightOrWidth / Len ));
						 if ( Scroll->GetSize().Height < Scroll->GetSize().Width )
						 {
							 Scroll->SetScale( vector2df(1.0 , Scroll->GetOriginSize().Width / Scroll->GetOriginSize().Height));
						 }
					 }
				 }

				 SetVisible( true );
				  Scroll->SetPosition( ScrollPos);
			 }
			IUIObject::OnAnimate( time );
			
		 }

	 virtual void Draw()
	 {
		 UpdateAbsolutePosition();

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
	rect<f32> re ;
	rect<s32> * clipre = NULL;
	if ( ClipRect )
	{
		rect<f32> t= GetAbsoluteClipRect();
		rect<s32> re = rect<s32>( ( s32)t.UpperLeftCorner.X,( s32)t.UpperLeftCorner.Y,( s32)t.LowerRightCorner.X,( s32)t.LowerRightCorner.Y);
		clipre = &re;
	}
	
	Driver->draw2DImage( Image, intDstQuar, rect<s32>(0,0,w,h), clipre, colors, true );
	 }

protected:
	bool IsPointInRelativeRect(s32 x, s32 y, rect<f32> dest ) //屏幕坐标是否在这个类坐标系下的矩形区域中
			 {
				 ub::vector<f32> temp(3);
				 matrix<f32> mat = AbsoluteTransformation;
				 temp(2) = 1.0;
				 temp( 0 ) = dest.UpperLeftCorner.X;
				 temp( 1 ) = dest.UpperLeftCorner.Y;
				 temp = prod( temp , mat );
				 dest.UpperLeftCorner.X = temp( 0 );
				 dest.UpperLeftCorner.Y = temp( 1 );
				 temp( 0 ) = dest.LowerRightCorner.X;
				 temp( 1 ) = dest.LowerRightCorner.Y;
				 temp = prod( temp, mat );
				 dest.LowerRightCorner.X = temp( 0 );
				 dest.LowerRightCorner.Y = temp( 1 );
				 bool b = dest.isPointInside( vector2df( (f32)x, ( f32 )y ));
				 return b;
			 }

	//更新滚动条的建模位置
	virtual void UpdateScrollPos()
			 {
				 if ( Type == HBAR )
				 {
					 ScrollPos.X = (ViewportPosXOrY / Len * Scroll->GetOriginSize().Width + ( f32 )0.5*Scroll->GetSize().Width ) + RefYOrX;
					 ScrollPos.Y = 0;
				 }
				 else
				 {
					 ScrollPos.X = 0;
					 ScrollPos.Y = ( ViewportPosXOrY / Len * Scroll->GetOriginSize().Height +(f32)0.5 * Scroll->GetSize().Height) + RefYOrX;
				 }
			 }
			 
			 
public:
	//默认元件的文件名
	static char* LefButtonTex;                
	static char* RightButtonTex;              
	static char* TopButtonTex;               
	static char* DownButtonTex;
	static char* HScrollTex;
	static char* VScrollTex;
	static char* HBackGroundTex;
	static char* VBackGroundTex;
		 

protected:
	vector2df ScrollMaxLeftUpPos;             //滚动条最大的左上角位置
	vector2df ScrollMaxRightDownPos;          //滚动条最大的右下角位置
	f32 Len;                                  //页面的x或y最大长度
	f32 ScrollLenOnce;                        //滚动条每次平移的单位
	vector2df ScrollPos;                       //滚动条位置
	s32 Type;                                  //0 代表水平 其他代表垂直
	UIButton* LeftOrTopButton;                 //左或上控件
	UIButton* RightOrDownButton;               //右或下控件
	UIButton* Scroll;                          //滚动条
	f32 ViewportHeightOrWidth;                 //视口的宽或高
	f32 RefYOrX;                               //参考的位置
	f32 ViewportPosXOrY;	                   //视口的逻辑位置

	
	

};

#endif