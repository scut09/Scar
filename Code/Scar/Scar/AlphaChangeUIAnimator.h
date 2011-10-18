#ifndef AlphaChangeUIAnimator_h__
#define AlphaChangeUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class AlphaChangeUIAnimator;

//////////////////////////////////////////////////////////////////
//名称：AlphaChangeUIAnimator
//描述：alpha值修改动画
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
class AlphaChangeUIAnimator : public IUIAnimator
{
private:
	u32 Begin;
	u32 Duration;
	u32 LastTime;
	f32 SrcAlpha;
	f32 TarAlpha;
	f32 AlphaFactor;
	bool Loop;

public:
	AlphaChangeUIAnimator( u32 begin, u32 duration, f32 srcalpha,
		f32 taralpha, bool loop = false );
	~AlphaChangeUIAnimator();

	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual AlphaChangeUIAnimator* Clone();
};

#endif // AlphaChangeUIAnimator_h__