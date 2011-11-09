#include "UIBox.h"
#include "UIButton.h"



void CUIBox::AddItem( IUIObject* item )
{
	
	if ( item )
	{
		dimension2df size = item->GetSize();
		AddChild(item);
		f32 xrate = ItemSize.Width/size.Width;
		f32 yrate = ItemSize.Height/size.Height;
		item->SetScale(vector2d<f32>(xrate,yrate));
		if ( ClipRect )
		{
			item->SetClipRect(*ClipRect);
		}
		ItemNum++;

		item->SetPosition(GetItemPosByNum(ItemNum));
		item->drop();
		

	}
	
}

void CUIBox::DeleteItem( IUIObject*item )
{
	if ( item )
	{
		auto itr = std::find( Children.begin(), Children.end(), item);
		if ( itr == Children.end() )
		{
			return;
		}
		RemoveChild(item);
		ItemNum--;
	}
}









void CUIBox::UpdateItemSize()
{
	if ( PreItemSize != ItemSize )
	{
		f32 xrate = (f32)ItemSize.Width/(f32)PreItemSize.Width;
		f32 yrate = ( f32 )ItemSize.Height / (f32) PreItemSize.Height;
		for (auto iter = Children.begin(); iter != Children.end(); iter++ )
		{
			if ( (*iter) == VBar || ( *iter) == HBar)
			{
				continue;
			}
			( *iter)->SetScale( vector2df( xrate, yrate ));
		}

		PreItemSize = ItemSize;
	}
}




void CUIBox::UpdateItemClipRect()
{
	if ( ClipRect)
	{  
		//item
		ItemClipRect = *ClipRect;
		if ( VBar->GetVisible() )
		{
		    ItemClipRect.LowerRightCorner.X -= (VBar->GetSize().Width/VBar->GetScale().X);
		}
		if ( HBar->GetVisible() )
		{
			ItemClipRect.LowerRightCorner.Y -= (HBar->GetSize().Height /HBar->GetScale().Y);
		}
	}
}

void CUIBox::Draw()
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
	rect<s32>SrcRect( (s32)LeftTop.X, (s32)LeftTop.Y, (s32)RightBottom.X, (s32)RightBottom.Y );

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

	if ( bAntiAliasing )
	{
		Driver->enableMaterial2D();
	}
	rect<s32> * clipre = NULL;
	if ( ClipRect )
	{
		rect<f32> t= GetAbsoluteClipRect();
		rect<s32> re = rect<s32>( ( s32)t.UpperLeftCorner.X,( s32)t.UpperLeftCorner.Y,( s32)t.LowerRightCorner.X,( s32)t.LowerRightCorner.Y);
		clipre = &re;
	}
	Driver->draw2DImage( Image, intDstQuar, SrcRect, clipre, colors/*&SColor(Alpha,255,255,255)*/, true );
	if ( bAntiAliasing )
	{
		Driver->enableMaterial2D( false );
	}
}
