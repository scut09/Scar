#ifndef UIEditBox_h__
#define UIEditBox_h__

#include "IUIObject.h"
#include "IrrCompileConfig.h"
#include "IOSOperator.h"

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::gui;

class IUIObject;

class UIEditBox : public IUIObject
{
public:
	UIEditBox( IUIObject* parent, s32 width, s32 height,
		stringw text,
		SColor color,
		u32 fontsie = 14,
		s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>(0,0),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>(1,1)
		);

	~UIEditBox();

	//绘制
	virtual void Draw();

	//设置选中字体
	virtual void setOverrideFont( IGUIFont* font = 0);

	//设置选中字体颜色
	virtual void setOverrideColor( SColor color );

	//是否开启选中字体变化
	virtual void enableOverrideColor( bool enable );

	//设置开启选中变色
	virtual void setWordWrap( bool enalble );

	//获得是否开启选中变色
	virtual bool isWordWrapEnalbled() const;

	//设置是否开启多行输入
	virtual void setMultiLine( bool enable );

	//获得是否开启多行输入
	virtual bool isMultiLineEnabled() const;

	//设置是否开启自动换行
	virtual void setAutoScroll( bool enable );

	//获得是否开启自动换行
	virtual bool isAutoScrollEnabled() const;

	//获得文本的像素大小
	virtual dimension2du getTextDimension();

	//设置文本对齐模式
	virtual void SetTextAlign( EGUI_ALIGNMENT horizontal, EGUI_ALIGNMENT vertical );

	//事件监听
	void OnEvent( const SEvent& event );

	//设置新的预显示文本
	virtual void setText( const wchar_t* text);

	//设置最大显示字数
	virtual void setMax( u32 max );

	//获得最大显示字数
	virtual u32 getMax() const;

protected:

	void breakText();

	//设置所给行的区域
	void setTextRect( s32 line );

	//获得指针所在的行数
	s32 getLineFromPos( s32 pos );

	//增加一个字符
	void inputChar( wchar_t c );

	//计算目前换行位置
	void calculateScrollPos();

	//设置文本标记
	void setTextMarkers( s32 begin, s32 end );

	//处理键盘事件
	bool processKey( const SEvent& event );

	//处理鼠标事件
	bool processMouse( const SEvent& event );

	bool processIMEEvent( const SEvent& event );

	position2di calculateICPos();

	//获得光标位置
	s32 getCursorPos( s32 x, s32 y );

	bool MouseMarking;
	bool Border;
	bool OverrideColorEnabled;
	s32 MarkBegin;
	s32 MarkEnd;

	SColor OverrideColor;
	IGUIFont *OverrideFont, *LastBreakFont;
	IOSOperator* Operator;

	u32 BlinkStartTime;
	s32 CursorPos;
	s32 HScrollPos, VScrollPos;
	u32 Max;

	bool WordWrap, MultiLine, AutoScroll;
	EGUI_ALIGNMENT HAlign, VAlign;

	array< stringw > BrokenText;
	array< s32 > BrokenTextPositions;

	rect< s32 > CurrentTextRect;
private:
	stringw Text;
	SColor Color;
	u32 FontSize;
	IGUIEnvironment* Guienv;
	IGUIFont* Font;
	IGUISkin* Skin;
	bool Focus;
};


#endif // UIEditBox_h__
