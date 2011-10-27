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

	//����
	virtual void Draw();

	//����ѡ������
	virtual void setOverrideFont( IGUIFont* font = 0);

	//����ѡ��������ɫ
	virtual void setOverrideColor( SColor color );

	//�Ƿ���ѡ������仯
	virtual void enableOverrideColor( bool enable );

	//���ÿ���ѡ�б�ɫ
	virtual void setWordWrap( bool enalble );

	//����Ƿ���ѡ�б�ɫ
	virtual bool isWordWrapEnalbled() const;

	//�����Ƿ�����������
	virtual void setMultiLine( bool enable );

	//����Ƿ�����������
	virtual bool isMultiLineEnabled() const;

	//�����Ƿ����Զ�����
	virtual void setAutoScroll( bool enable );

	//����Ƿ����Զ�����
	virtual bool isAutoScrollEnabled() const;

	//����ı������ش�С
	virtual dimension2du getTextDimension();

	//�����ı�����ģʽ
	virtual void SetTextAlign( EGUI_ALIGNMENT horizontal, EGUI_ALIGNMENT vertical );

	//�¼�����
	void OnEvent( const SEvent& event );

	//�����µ�Ԥ��ʾ�ı�
	virtual void setText( const wchar_t* text);

	//���������ʾ����
	virtual void setMax( u32 max );

	//��������ʾ����
	virtual u32 getMax() const;

protected:

	void breakText();

	//���������е�����
	void setTextRect( s32 line );

	//���ָ�����ڵ�����
	s32 getLineFromPos( s32 pos );

	//����һ���ַ�
	void inputChar( wchar_t c );

	//����Ŀǰ����λ��
	void calculateScrollPos();

	//�����ı����
	void setTextMarkers( s32 begin, s32 end );

	//��������¼�
	bool processKey( const SEvent& event );

	//��������¼�
	bool processMouse( const SEvent& event );

	bool processIMEEvent( const SEvent& event );

	position2di calculateICPos();

	//��ù��λ��
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
