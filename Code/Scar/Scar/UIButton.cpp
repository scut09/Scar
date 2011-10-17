#include "UIButton.h"
#include "MyIrrlichtEngine.h"


UIButton::UIButton( IUIObject* parent, s32 width, s32 height, s32 order /*= 0*/, int shape,
	const vector2d<f32>& position /*= vector2d<f32>(0,0)*/,
	f32 rotdeg /*= 0*/,
	const vector2d<f32>& scale /*= vector2d<f32>(1,1) */ )
	: IUIObject( parent, width, height, order, shape, position, rotdeg, scale )
{

}

//»æÖÆ
void UIButton::Draw()
{

}

