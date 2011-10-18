#ifndef AlphaChangeUIAnimator_h__
#define AlphaChangeUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class AlphaChangeUIAnimator;

//////////////////////////////////////////////////////////////////
//���ƣ�AlphaChangeUIAnimator
//������alphaֵ�޸Ķ���
//���ߣ������裬�����
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