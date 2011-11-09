/********************************************************************
    创建时间: 2011-11-8   
    文件名:   UIBox.h
    作者:     谢骏飞
    说明:     装UI元件的盒子

*********************************************************************/
#ifndef CUIBox_H__
#define CUIBox_H__
#include "uiimage.h"
#include "UIBar.h"
 #include <boost/numeric/ublas/vector.hpp> 
#include <boost/numeric/ublas/vector_proxy.hpp> 
#include <boost/numeric/ublas/matrix.hpp> 
#include <boost/numeric/ublas/triangular.hpp> 
#include <boost/numeric/ublas/lu.hpp> 
#include <boost/numeric/ublas/io.hpp>
namespace ublas = boost::numeric::ublas;

class CUIBox :
	public IUIObject
{
public:
	CUIBox( IUIObject* parent, s32 width, s32 height, s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>( 0, 0 ),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>( 1.f, 1.f ) ) 
		: IUIObject( parent, width, height, order, shape, position, rotdeg, scale )
	{
		if ( parent )
		{
			parent->AddChild( this );
		}
	    f32 t = 0;
		BarWidthOrHeight = 10.0;
		HBar = new CUIBar(this,width,( s32 )BarWidthOrHeight,HBAR);
		HBar->SetPosition(vector2df ( 0, (f32) (0.5 * ( height - 10))));
		f32 hw = GetSize().Width / RelativeScale.X;
		VBar = new CUIBar(this,( s32 )BarWidthOrHeight,height - 2*( s32 )BarWidthOrHeight,VBAR );
		VBar->SetPosition( vector2df( f32( 0.5 * ( width  - BarWidthOrHeight)), 0));
		f32 vh = GetSize().Height/RelativeScale.Y;
		ItemSize.Height = (f32 )(height* 0.1);
		ItemSize.Width  = ( f32 )(width * 0.1);
		ViewportTranslation = vector2df( 0,0 );
		PreItemSize = ItemSize;
		rect<f32> p ;
		p.UpperLeftCorner = vector2df ( -( f32 )width / 2.f, - ( f32 )height/ 2.f);
		p.LowerRightCorner = vector2df ( ( f32 )width / 2.f,  ( f32 )height/ 2.f);
		SetClipRect(p) ;
		 ItemClipRect =*ClipRect;
		FirstItemPos = vector2df( 0.0 ,0.0);
		ItemNum = 0;
		RowNum = 5;
		RowGap =0.0;
		ColGap =0.0;
	};
	~CUIBox(void){};
	
	virtual IUIObject* Clone(){
		return NULL;
	}
	
	//添加窗口项
	virtual void AddItem( IUIObject* item );
	//删除窗口项
	virtual void DeleteItem( IUIObject*item );

	//设置窗口项大小
	virtual void SetItemSize( dimension2d<f32>& size )
	{
		ItemSize = size;
	}
	virtual dimension2d<f32> GetItemSize() const
	{
		return ItemSize;
	}
	 virtual void SetRowNum( s32 n)
	 {
		 RowNum = n;
	 }
	 virtual s32 GetRowNum() const 
	 {
		  return RowNum;
	 }
	//设置间隔
	virtual void SetRowGap( f32& rgap)
	{
		RowGap = rgap;
	}
	virtual void SetColGap( f32& cgap )
	{
		ColGap = cgap;
	}
	virtual f32 GetColGap() const
	{
		return ColGap;
	}
	virtual f32 GetRowGap() const
	{
		 return RowGap;
	}

	//设置窗口项起始位置
	virtual void SetFirstItemPos( vector2df & pos )
	{
		FirstItemPos = pos;
	}
	virtual vector2df GetFirstItemPos( ) const
	{
		return FirstItemPos;
	}

	virtual void OnAnimate( u32 time )
	{
		UpdateItemSize();
		MessageBetweenFatherAndBar();
		UpdateItemPos();
		MakeChildClipSameAsFather();

		IUIObject::OnAnimate( time );
	}

	virtual void Draw();

	//用于测试
	void test(int n)
	{
		for ( int i = 0; i<n; i++)
		{
			UIImage * temp = new UIImage(this, 30,30);
			temp->LoadImage( CUIBar::TopButtonTex );
			AddItem( temp );
		}
	}
	//防止裁剪区域被删
	virtual void RemoveClipRect(){ };
protected:
	
		/* 获取第i个位置*/
		virtual vector2df GetItemPosByNum(int inum) 
		{
			s32 ritem = inum % RowNum;
			s32 citem = ceil32(( f32 )inum /  RowNum )  - 1;
			if ( citem < 0)
			{
				citem = 0;
			}
			static u32 count = 0;
			vector2df pos = vector2df( FirstItemPos.X + ( f32 )ritem * ( ItemSize.Width + RowGap), FirstItemPos.Y + citem * (ItemSize.Height + ColGap));
			
			return pos;
		}

		//保持儿子与父亲的裁剪区域相同
		void MakeChildClipSameAsFather()
		{
			UpdateItemClipRect();
			if ( ClipRect )
			{
				for ( auto ater = Children.begin(); ater!= Children.end(); ater++ )
				{
					matrix<f32> mat = ( * ater )->GetRelativeTransformation();
					matrix<f32> invermat(mat);
					if(InvertMatrix(mat, invermat))
					{
						rect<f32> re;
						ub::vector<f32> temp(3);

						temp(2) = 1;
						temp(0) = ItemClipRect.UpperLeftCorner.X;
						temp(1) = ItemClipRect.UpperLeftCorner.Y;
						temp = prod( temp, invermat );
						re.UpperLeftCorner.X = temp(0);
						re.UpperLeftCorner.Y = temp(1);
						temp( 0) = ItemClipRect.LowerRightCorner.X;
						temp(1 ) = ItemClipRect.LowerRightCorner.Y;
						temp = prod( temp, invermat );
						re.LowerRightCorner.X = temp(0);
						re.LowerRightCorner.Y = temp( 1 );
						( *ater)->SetClipRect( re);
					}
				}


			}
		}

		//滚动条与窗口之间的信息传递
		virtual void MessageBetweenFatherAndBar()
		{
			//message 传递给滚动条
			f32 vh = GetOriginSize().Height;
			if ( HBar->GetVisible())
			{
				vh =vh -  (HBar->GetOriginSize().Height* HBar->GetScale().Y );
			}
		    VBar->SetViewportHeightOrWidth( vh  );	
			f32 hw = GetOriginSize().Width;
			if ( VBar->GetVisible() )
			{
				hw = hw - VBar->GetOriginSize().Width * VBar->GetScale().X;
			}
			HBar->SetViewportHeightOrWidth( hw );
			f32 pMaxWidth, pMaxHeight;
			s32 ritem = ((ItemNum % RowNum - 1) >0 ?(ItemNum % RowNum - 1) :0 );
			if ( ItemNum > 0)
			{
				if ( ItemNum % RowNum == 0)
				{
					ritem = RowNum -1;
				}
				else ritem =ItemNum % RowNum;
			}
			
			else ritem =0;
			if ( ItemNum > 0)
			{
				pMaxWidth = (f32 )(FirstItemPos.X> ItemSize.Width * 0.5 ? FirstItemPos.X :ItemSize.Width * 0.5 )  + ritem * ( ItemSize.Width + RowGap ) + ( f32 )0.5 * ItemSize.Width;
				s32 citem = ceil32(( f32 )ItemNum /  RowNum )  - 1;
				if ( citem < 0)
				{
					citem = 0;
				}
				pMaxHeight =( f32 ) (FirstItemPos.Y> ItemSize.Height * 0.5 ? FirstItemPos.X :ItemSize.Height * 0.5 ) + citem * ( ItemSize.Height + ColGap) + ( f32 )0.5 * ItemSize.Height;

			}
			else pMaxHeight = pMaxHeight = 0;
			VBar->SetLen( pMaxHeight );
			HBar->SetLen( pMaxWidth );

			//messege 由滚动条传递回来
			ViewportTranslation.X =  HBar->GetViewPortPosXOrY();
			ViewportTranslation.Y = VBar->GetViewPortPosXOrY();
		}

		//更新窗口项位置 ，大小
		virtual void UpdateItemPos()
		{
			u32 flag = 0;
			vector2df tFirstItemPos;
			for ( auto iter = Children.begin(); iter != Children.end(); iter++)
			{
				if ( VBar == (*iter)|| (*iter) == HBar)
				{
					continue;
				}
				if ( flag == 0 )
				{
					if ( FirstItemPos.X < 0.5 *ItemSize.Width)
					{
						FirstItemPos.X  = ( f32 )0.5 * ItemSize.Width;
					}
					if ( FirstItemPos.Y < ItemSize.Height * 0.5 )
					{
						FirstItemPos.Y = ( f32 ) 0.5 * ItemSize.Height;
					}
					tFirstItemPos = vector2df (- ( f32 )(0.5 *(GetOriginSize().Width  )), -(f32)( 0.5 *( GetOriginSize().Height  ) )) + FirstItemPos;
					( *iter)->SetPosition( tFirstItemPos -ViewportTranslation);
				
					flag++;
				}

				else
				{
					f32 ritem = (f32)floor32((f32)flag / ( f32 )RowNum);
					(*iter)->SetPosition( vector2df ( tFirstItemPos.X + (flag % RowNum) * (RowGap + ItemSize.Width ) , tFirstItemPos.Y +  ritem * ( ItemSize.Height   + ColGap )) -ViewportTranslation);
					flag++;
		       
				}
			}
		}
		virtual void UpdateItemSize();

		//由于滚动条的影响 更新item的裁剪区域
		virtual void UpdateItemClipRect();

		template<class T> 
		bool InvertMatrix (const ublas::matrix<T>& input, ublas::matrix<T>& inverse) 
		{ using namespace boost::numeric::ublas;
		typedef permutation_matrix<std::size_t> pmatrix; 
		// create a working copy of the input 
		matrix<T> A(input); 
		// create a permutation matrix for the LU-factorization 
		pmatrix pm(A.size1());

		// perform LU-factorization 
		int res = lu_factorize(A,pm); if( res != 0 ) return false;

		// create identity matrix of "inverse" 
		inverse.assign(ublas::identity_matrix<T>(A.size1()));

		// backsubstitute to get the inverse 
		lu_substitute(A, pm, inverse);

		return true; 
		}
protected:
	vector2df        ViewportTranslation;       //视口的平移向量           
	rect<f32>        ItemClipRect;              //窗口项的裁剪区域
	dimension2d<f32> ItemSize;                  //窗口项的大小
	vector2df        FirstItemPos;              //第一个窗口项的大小
	u32              RowNum;                     //行的最打窗口项
	u32              ItemNum;                    //窗口项总数
	CUIBar*          VBar;                       //滚动条 
	CUIBar*          HBar;                       //水平滚动条
	f32              RowGap;                     //行间隔
	f32              ColGap;                     // 竖间隔
	f32              BarWidthOrHeight;            //滚动条的窄度               
	dimension2d<f32> PreItemSize;                 //记录先前窗口项的大小
};

#endif