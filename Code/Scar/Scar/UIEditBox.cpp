#include "UIEditBox.h"
#include "MyIrrlichtEngine.h"
#include "Keycodes.h"
#include "CGUITTFont.h"

#pragma comment(lib, "freetype247MT.lib")

#define FONT_PATH L"..\\media\\msyh.ttf"

void updateICPos(void* hWnd, s32 x, s32 y, s32 height);

UIEditBox::UIEditBox( IUIObject* parent, s32 width, s32 height, stringw text, SColor color, u32 fontsie /*= 14*/, s32 order /*= 0*/, int shape /*= SQUARE*/, const vector2d<f32>& position /*= vector2d<f32>(0,0)*/, f32 rotdeg /*= 0*/, const vector2d<f32>& scale /*= vector2d<f32>(1,1) */ )
	: IUIObject( parent, width, height, order, shape, position, rotdeg, scale ),MouseMarking(false),
	OverrideColorEnabled(false), MarkBegin(0), MarkEnd(0),
	OverrideColor(video::SColor(101,255,255,255)), OverrideFont(0), LastBreakFont(0),
	Operator(0), BlinkStartTime(0), CursorPos(0), HScrollPos(0), VScrollPos(0), Max(0),
	WordWrap(false), MultiLine(false), AutoScroll(true),
	HAlign(EGUIA_UPPERLEFT), VAlign(EGUIA_CENTER),
	CurrentTextRect(0,0,1,1)
{
	Text = text;
	Color = color;
	FontSize = fontsie;
	Guienv = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();
	Skin = Guienv->getSkin();
	Operator = Guienv->getOSOperator();
	if ( Operator )
		Operator->grab();
	Font = CGUITTFont::createTTFont( Guienv, FONT_PATH, FontSize );
	Skin->setFont(Font);
	CurrentTextRect = rect<s32>( 0, 0, 1, 1 );
	breakText();

	calculateScrollPos();
}



void UIEditBox::Draw()
{
	UpdateAbsolutePosition();
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

	rect<s32> intrec( intDstQuar[0], intDstQuar[2] );

	const bool focus = Focus;

	IGUISkin* skin = Skin;

	IGUIFont* font = Font;
	if ( LastBreakFont != font )
		breakText();

	stringw *txtLine = &Text;
	s32 startPos = 0;
	stringw s, s2;

	const bool ml = ( WordWrap || MultiLine );
	const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
	const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;
	const s32 hlineStart = ml ? getLineFromPos( realmbgn ) : 0;
	const s32 hlineCount = ml ? getLineFromPos( realmend ) - hlineStart + 1 : 1;
	const s32 lineCount = ml ? BrokenText.size() : 1;

	s32 cursorLine = 0;
	s32 charcursorpos = 0;

	const bool prevOver = OverrideColorEnabled;
	const video::SColor prevColor = OverrideColor;

	core::rect<s32> localClipRect;
	localClipRect.UpperLeftCorner.X = (s32)DestinationQuadrangle[0].X;
	localClipRect.UpperLeftCorner.Y = (s32)DestinationQuadrangle[0].Y;
	localClipRect.LowerRightCorner.X = (s32)DestinationQuadrangle[2].X;
	localClipRect.LowerRightCorner.Y = (s32)DestinationQuadrangle[2].Y;

	if (Text.size())
	{
		for (s32 i=0; i < lineCount; ++i)
		{
			setTextRect(i);

			// clipping test - don't draw anything outside the visible area
			core::rect<s32> c = intrec;
			c.clipAgainst(CurrentTextRect);
			if (!c.isValid())
				continue;

			// get current line
			txtLine = ml ? &BrokenText[i] : &Text;
			startPos = ml ? BrokenTextPositions[i] : 0;


			// draw normal text
			font->draw(txtLine->c_str(), CurrentTextRect,
				OverrideColorEnabled ? OverrideColor : skin->getColor(EGDC_BUTTON_TEXT),
				false, true, &intrec);

			// draw mark and marked text
			if (focus && MarkBegin != MarkEnd && i >= hlineStart && i < hlineStart + hlineCount)
			{

				s32 mbegin = 0, mend = 0;
				s32 lineStartPos = 0, lineEndPos = txtLine->size();

				if (i == hlineStart)
				{
					// highlight start is on this line
					s = txtLine->subString(0, realmbgn - startPos);
					mbegin = font->getDimension(s.c_str()).Width;

					// deal with kerning
					mbegin += font->getKerningWidth(
						&((*txtLine)[realmbgn - startPos]),
						realmbgn - startPos > 0 ? &((*txtLine)[realmbgn - startPos - 1]) : 0);

					lineStartPos = realmbgn - startPos;
				}
				if (i == hlineStart + hlineCount - 1)
				{
					// highlight end is on this line
					s2 = txtLine->subString(0, realmend - startPos);
					mend = font->getDimension(s2.c_str()).Width;
					lineEndPos = (s32)s2.size();
				}
				else
					mend = font->getDimension(txtLine->c_str()).Width;

				CurrentTextRect.UpperLeftCorner.X += mbegin;
				CurrentTextRect.LowerRightCorner.X = CurrentTextRect.UpperLeftCorner.X + mend - mbegin;


				// draw marked text
				s = txtLine->subString(lineStartPos, lineEndPos - lineStartPos);

				if (s.size())
					font->draw(s.c_str(), CurrentTextRect,
					OverrideColorEnabled ? OverrideColor : skin->getColor(EGDC_HIGH_LIGHT_TEXT),
					false, true, &intrec);

			}
		}

		// Return the override color information to its previous settings.
		OverrideColorEnabled = prevOver;
		OverrideColor = prevColor;
	}

	// draw cursor

	if (WordWrap || MultiLine)
	{
		cursorLine = getLineFromPos(CursorPos);
		txtLine = &BrokenText[cursorLine];
		startPos = BrokenTextPositions[cursorLine];
	}
	s = txtLine->subString(0,CursorPos-startPos);
	charcursorpos = font->getDimension(s.c_str()).Width +
		font->getKerningWidth(L"|", CursorPos-startPos > 0 ? &((*txtLine)[CursorPos-startPos-1]) : 0);

	if (focus && (MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime() - BlinkStartTime) % 700 < 350)
	{
		setTextRect(cursorLine);
		CurrentTextRect.UpperLeftCorner.X += charcursorpos;

		font->draw(L"|", CurrentTextRect,
			OverrideColorEnabled ? OverrideColor : skin->getColor(EGDC_BUTTON_TEXT),
			false, true, &localClipRect);
	}
}

UIEditBox::~UIEditBox()
{
	if ( OverrideFont )
		OverrideFont->drop();

	if ( Operator )
		Operator->drop();
}

void UIEditBox::setOverrideFont( IGUIFont* font /*= 0*/ )
{
	if (OverrideFont == font )
		return;
	
	if ( OverrideFont )
		OverrideFont->drop();

	OverrideFont = font;

	if( OverrideFont )
		OverrideFont->grab();
	
	breakText();
}

void UIEditBox::setOverrideColor( SColor color )
{
	OverrideColor = color;
	OverrideColorEnabled = true;
}

void UIEditBox::enableOverrideColor( bool enable )
{
	OverrideColorEnabled = enable;
}

void UIEditBox::setWordWrap( bool enalble )
{
	WordWrap = enalble;
	breakText();
}

bool UIEditBox::isWordWrapEnalbled() const
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return WordWrap;
}

void UIEditBox::setMultiLine( bool enable )
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	MultiLine = enable;
}

void UIEditBox::SetTextAlign( EGUI_ALIGNMENT horizontal, EGUI_ALIGNMENT vertical )
{
	HAlign = horizontal;
	VAlign = vertical;
}

void UIEditBox::OnEvent( const SEvent& event )
{
	switch( event.EventType )
	{
	case EET_IMPUT_METHOD_EVENT:
			  if ( processIMEEvent( event ) )
				  return;
		break;
	case EET_KEY_INPUT_EVENT:
		if ( processKey( event ) )
			return;
		break;
	case EET_MOUSE_INPUT_EVENT:
		/*if ( processMouse( event ) )
			return;*/
		break;
	default:
		break;
	}
	IUIObject::OnEvent( event );
}


bool UIEditBox::processKey( const SEvent& event )
{
	if (! event.KeyInput.PressedDown )
		return false;
	bool textChanged = false;
	s32 newMarkBegin = MarkBegin;
	s32 newMarkEnd = MarkEnd;

	if ( event.KeyInput.Control )
	{
		if ( event.KeyInput.Char == '\\' )
		{
			inputChar( event.KeyInput.Char );
			return true;
		}

		switch( event.KeyInput.Key )
		{
		case  KEY_KEY_A:
			{
				//全选
				newMarkBegin = 0;
				newMarkEnd = Text.size();
				break;
			}
		case KEY_KEY_C:
			{
				//复制
				if( Operator && MarkBegin != MarkEnd )
				{
					const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
					const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;

					stringw s;
					s = Text.subString( realmbgn, realmend - realmbgn );
					Operator->copyToClipboard(s.c_str());
				}
				break;
			}
		case KEY_KEY_X:
			{
				if ( Operator && MarkBegin != MarkEnd )
				{
					const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
					const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;

					stringw sc;
					sc = Text.subString( realmbgn , realmend - realmbgn );

					Operator->copyToClipboard(sc.c_str());

					//delete
					stringw s;
					s = Text.subString( 0 , realmbgn );
					s.append( Text.subString( realmend, Text.size() - realmend ));
					Text = s;

					CursorPos = realmbgn;
					newMarkBegin = 0;
					newMarkEnd = 0;
					textChanged = true;
				}
				break;
			}
		case KEY_KEY_V:
			{
				if ( Operator )
				{
					const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
					const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;

					const wchar_t* p = Operator->getTextFromClipboard();

					if (p)
					{
						if ( MarkBegin == MarkEnd )
						{

							stringw s = Text.subString( 0 , CursorPos );
							s.append( p );
							s.append( Text.subString( CursorPos, Text.size() - CursorPos ) );
							if (! Max || s.size() <= Max )
							{
								Text = s;
								s = p;
								CursorPos += s.size();
							}
						}
						else
						{
							stringw s = Text.subString( 0, realmbgn );
							s.append( p );
							s.append( Text.subString( realmend, Text.size() - realmend ) );
							if (! Max || s.size() <= Max )
							{
								Text = s;
								s = p;
								CursorPos += s.size();
							}
						}
					}
					newMarkBegin = 0;
					newMarkEnd = 0;
					textChanged = true;
				}
				break;
			}
		case KEY_HOME:
			{
				if ( event.KeyInput.Shift )
				{
					newMarkEnd = CursorPos;
					newMarkBegin = 0;
					CursorPos = 0;
				}
				else
				{
					CursorPos = 0;
					newMarkBegin = 0;
					newMarkEnd = 0;
				}
				break;
			}
		case KEY_END:
			{
				if ( event.KeyInput.Shift )
				{
					newMarkBegin = CursorPos;
					newMarkEnd =Text.size();
					CursorPos = 0;
				}
				else
				{
					newMarkBegin = 0;
					newMarkEnd = 0;
					CursorPos = Text.size();
				}
				break;
			}
		default:
			return false;
		}
	}
	else
		switch( event.KeyInput.Key )
		{
		case KEY_END:
			{
				s32 p = Text.size();
				if( WordWrap || MultiLine )
				{
					p = getLineFromPos( CursorPos );
					p = BrokenTextPositions[p] + (s32)BrokenText[p].size();
					if ( p > 0 && (Text[ p - 1 ] == L'\r' || Text[ p - 1 ] == L'\n'))
						p = -1;
				}

				if ( event.KeyInput.Shift )
				{
					if ( MarkBegin == MarkEnd )
						newMarkBegin = CursorPos;
					newMarkEnd = p;
				}
				else
				{
					newMarkBegin = 0;
					newMarkEnd = 0;
				}
				CursorPos = p;
				BlinkStartTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
			}
			break;
		case KEY_HOME:
			{
				s32 p = 0;
				if( WordWrap || MultiLine )
				{
					p = getLineFromPos( CursorPos );
					p = BrokenTextPositions[p];
				}
				if ( event.KeyInput.Shift )
				{
					if ( MarkBegin == MarkEnd )
						newMarkBegin = CursorPos;
					newMarkEnd = p;
				}
				else
				{
					 newMarkBegin = 0;
					 newMarkEnd = 0;
				}
				CursorPos = p;
				BlinkStartTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
			}
			break;
		case KEY_RETURN:
			if ( MultiLine )
			{
				inputChar(L'\n');
				return true;
			}
			else
			{
				//sendGuiEvent( EGET_EDITBOX_ENTER );
			}
			break;
		case KEY_LEFT:
			if (event.KeyInput.Shift)
			{
				if (CursorPos > 0)
				{
					if (MarkBegin == MarkEnd)
						newMarkBegin = CursorPos;

					newMarkEnd = CursorPos-1;
				}
			}
			else
			{
				newMarkBegin = 0;
				newMarkEnd = 0;
			}

			if (CursorPos > 0) CursorPos--;
			BlinkStartTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
			break;
		case KEY_RIGHT:
			if (event.KeyInput.Shift)
			{
				if (Text.size() > (u32)CursorPos)
				{
					if (MarkBegin == MarkEnd)
						newMarkBegin = CursorPos;

					newMarkEnd = CursorPos+1;
				}
			}
			else
			{
				newMarkBegin = 0;
				newMarkEnd = 0;
			}

			if (Text.size() > (u32)CursorPos) CursorPos++;
			BlinkStartTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
			break;
		case KEY_UP:
			if (MultiLine || (WordWrap && BrokenText.size() > 1) )
			{
				s32 lineNo = getLineFromPos(CursorPos);
				s32 mb = (MarkBegin == MarkEnd) ? CursorPos : (MarkBegin > MarkEnd ? MarkBegin : MarkEnd);
				if (lineNo > 0)
				{
					s32 cp = CursorPos - BrokenTextPositions[lineNo];
					if ((s32)BrokenText[lineNo-1].size() < cp)
						CursorPos = BrokenTextPositions[lineNo-1] + (s32)BrokenText[lineNo-1].size()-1;
					else
						CursorPos = BrokenTextPositions[lineNo-1] + cp;
				}

				if (event.KeyInput.Shift)
				{
					newMarkBegin = mb;
					newMarkEnd = CursorPos;
				}
				else
				{
					newMarkBegin = 0;
					newMarkEnd = 0;
				}

			}
			else
			{
				return false;
			}
			break;
		case KEY_DOWN:
			if (MultiLine || (WordWrap && BrokenText.size() > 1) )
			{
				s32 lineNo = getLineFromPos(CursorPos);
				s32 mb = (MarkBegin == MarkEnd) ? CursorPos : (MarkBegin < MarkEnd ? MarkBegin : MarkEnd);
				if (lineNo < (s32)BrokenText.size()-1)
				{
					s32 cp = CursorPos - BrokenTextPositions[lineNo];
					if ((s32)BrokenText[lineNo+1].size() < cp)
						CursorPos = BrokenTextPositions[lineNo+1] + BrokenText[lineNo+1].size()-1;
					else
						CursorPos = BrokenTextPositions[lineNo+1] + cp;
				}

				if (event.KeyInput.Shift)
				{
					newMarkBegin = mb;
					newMarkEnd = CursorPos;
				}
				else
				{
					newMarkBegin = 0;
					newMarkEnd = 0;
				}

			}
			else
			{
				return false;
			}
			break;

		case KEY_BACK:
			if (Text.size())
			{
				core::stringw s;

				if (MarkBegin != MarkEnd)
				{
					// delete marked text
					const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
					const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;

					s = Text.subString(0, realmbgn);
					s.append( Text.subString(realmend, Text.size()-realmend) );
					Text = s;

					CursorPos = realmbgn;
				}
				else
				{
					// delete text behind cursor
					if (CursorPos>0)
						s = Text.subString(0, CursorPos-1);
					else
						s = L"";
					s.append( Text.subString(CursorPos, Text.size()-CursorPos) );
					Text = s;
					--CursorPos;
				}

				if (CursorPos < 0)
					CursorPos = 0;
				BlinkStartTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
				newMarkBegin = 0;
				newMarkEnd = 0;
				textChanged = true;
			}
			break;
		case KEY_DELETE:
			if (Text.size() != 0)
			{
				core::stringw s;

				if (MarkBegin != MarkEnd)
				{
					// delete marked text
					const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
					const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;

					s = Text.subString(0, realmbgn);
					s.append( Text.subString(realmend, Text.size()-realmend) );
					Text = s;

					CursorPos = realmbgn;
				}
				else
				{
					// delete text before cursor
					s = Text.subString(0, CursorPos);
					s.append( Text.subString(CursorPos+1, Text.size()-CursorPos-1) );
					Text = s;
				}

				if (CursorPos > (s32)Text.size())
					CursorPos = (s32)Text.size();

				BlinkStartTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
				newMarkBegin = 0;
				newMarkEnd = 0;
				textChanged = true;
			}
			break;
		case KEY_ESCAPE:
		case KEY_TAB:
		case KEY_SHIFT:
		case KEY_F1:
		case KEY_F2:
		case KEY_F3:
		case KEY_F4:
		case KEY_F5:
		case KEY_F6:
		case KEY_F7:
		case KEY_F8:
		case KEY_F9:
		case KEY_F10:
		case KEY_F11:
		case KEY_F12:
		case KEY_F13:
		case KEY_F14:
		case KEY_F15:
		case KEY_F16:
		case KEY_F17:
		case KEY_F18:
		case KEY_F19:
		case KEY_F20:
		case KEY_F21:
		case KEY_F22:
		case KEY_F23:
		case KEY_F24:
			//忽略这些键
			return false;
		default:
			inputChar( event.KeyInput.Char );
			return true;
		}

		setTextMarkers( newMarkBegin, newMarkEnd );

		if( textChanged )
		{
			breakText();
			//sendGuiEvent( EGET_EDITBOX_CHANGED );
		}
		calculateScrollPos();

		switch ( event.KeyInput.Key )
		{
		case KEY_UP:
		case KEY_DOWN:
			if (MultiLine || (WordWrap && BrokenText.size() > 1) )
			{
				if(UTF16_IS_SURROGATE_LO(Text[CursorPos]))
				{
					SEvent leftEvent;
					leftEvent = event;
					leftEvent.KeyInput.Key = KEY_LEFT;
					Guienv->postEventFromUser(leftEvent);
				}
			}
			break;
			// If cursor points the surrogate low, send a same event.
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_DELETE:
			if(UTF16_IS_SURROGATE_LO(Text[CursorPos]))
				Guienv->postEventFromUser(event);
			break;
			// If cursor points front of the surrogate high, send a same event.
		case KEY_BACK:
			if(CursorPos>0)
				if(UTF16_IS_SURROGATE_HI(Text[CursorPos-1]))
					Guienv->postEventFromUser(event);
			break;
		default:
			break;
		}
	return true;
}

bool UIEditBox::processIMEEvent( const SEvent& event )
{
	switch(event.InputMethodEvent.Event)
	{
	case EIME_CHAR_INPUT:
		inputChar(event.InputMethodEvent.Char);
		return true;
	case EIME_CHANGE_POS:
		{
			core::position2di pos = calculateICPos();

			IGUIFont* font = OverrideFont;
			IGUISkin* skin = Skin;

			if (!OverrideFont)
				font = skin->getFont();

			updateICPos(event.InputMethodEvent.Handle, pos.X,pos.Y, font->getDimension(L"|").Height);

			return true;
		}
	default:
		break;
	}

	return false;
}

irr::core::position2di UIEditBox::calculateICPos()
{
	core::position2di pos;
	IGUIFont* font = OverrideFont;
	IGUISkin* skin = Skin;
	if (!OverrideFont)
		font = skin->getFont();

	//drop the text that clipping on the right side
	if(WordWrap | MultiLine)
	{
		// todo : It looks like a heavy drinker. Strange!!
		pos.X = CurrentTextRect.LowerRightCorner.X - font->getDimension(Text.subString(CursorPos, BrokenTextPositions[getLineFromPos(CursorPos)] + BrokenText[getLineFromPos(CursorPos)].size() - CursorPos).c_str()).Width;
		pos.Y = CurrentTextRect.UpperLeftCorner.Y + font->getDimension(L"|").Height + (Border ? 3 : 0) - ((MultiLine | WordWrap) ? 3 : 0);
	}
	else
	{
		pos.X = CurrentTextRect.LowerRightCorner.X - font->getDimension(Text.subString(CursorPos, Text.size() - CursorPos).c_str()).Width;
		rect<s32> AbsoluteRect;
		AbsoluteRect.UpperLeftCorner.X = (s32)DestinationQuadrangle[0].X;
		AbsoluteRect.UpperLeftCorner.Y = (s32)DestinationQuadrangle[0].Y;
		AbsoluteRect.LowerRightCorner.X = (s32)DestinationQuadrangle[2].X;
		AbsoluteRect.LowerRightCorner.Y = (s32)DestinationQuadrangle[2].Y;
		pos.Y = AbsoluteRect.getCenter().Y + (Border ? 3 : 0); //bug? The text is always drawn in the height of the center. SetTextAlignment() doesn't influence.
	}

	return pos;
}

void UIEditBox::setText( const wchar_t* text )
{
	Text = text;
	if (u32(CursorPos) > Text.size())
		CursorPos = Text.size();
	HScrollPos = 0;
	breakText();
}

void UIEditBox::setAutoScroll( bool enable )
{
	AutoScroll = enable;
}

bool UIEditBox::isAutoScrollEnabled() const
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return AutoScroll;
}

irr::core::dimension2du UIEditBox::getTextDimension()
{
	rect<s32> ret;

	setTextRect(0);
	ret = CurrentTextRect;

	for (u32 i=1; i < BrokenText.size(); ++i)
	{
		setTextRect(i);
		ret.addInternalPoint(CurrentTextRect.UpperLeftCorner);
		ret.addInternalPoint(CurrentTextRect.LowerRightCorner);
	}

	return core::dimension2du(ret.getSize());
}

void UIEditBox::setMax( u32 max )
{
	Max = max;

	if (Text.size() > Max && Max != 0)
		Text = Text.subString(0, Max);
}

irr::u32 UIEditBox::getMax() const
{
	return Max;
}

bool UIEditBox::processMouse( const SEvent& event )
{

	rect<s32> AbsoluteClippingRect;
	AbsoluteClippingRect.UpperLeftCorner.X = (s32)DestinationQuadrangle[0].X;
	AbsoluteClippingRect.UpperLeftCorner.Y = (s32)DestinationQuadrangle[0].Y;
	AbsoluteClippingRect.LowerRightCorner.X = (s32)DestinationQuadrangle[2].X;
	AbsoluteClippingRect.LowerRightCorner.Y = (s32)DestinationQuadrangle[2].Y;
	switch(event.MouseInput.Event)
	{
	case irr::EMIE_LMOUSE_LEFT_UP:
		if ( Focus )
		{
			CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
			if(UTF16_IS_SURROGATE_LO(Text[CursorPos]))
			{
				if(CursorPos>0)
					--CursorPos;
			}
			if (MouseMarking)
			{
				setTextMarkers( MarkBegin, CursorPos );
			}
			MouseMarking = false;
			calculateScrollPos();
			return true;
		}
		break;
	case irr::EMIE_MOUSE_MOVED:
		{
			if (MouseMarking)
			{
				CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
				if(UTF16_IS_SURROGATE_LO(Text[CursorPos]))
				{
					if(CursorPos>0)
						--CursorPos;
				}
				setTextMarkers( MarkBegin, CursorPos );
				calculateScrollPos();
				return true;
			}
		}
		break;
	case irr::EMIE_LMOUSE_PRESSED_DOWN:
		if (!Focus)
		{
			
			BlinkStartTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
			MouseMarking = true;
			CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
			if(UTF16_IS_SURROGATE_LO(Text[CursorPos]))
			{
				if(CursorPos>0)
					--CursorPos;
			}
			setTextMarkers(CursorPos, CursorPos );
			calculateScrollPos();
			Focus = true;
			return true;
		}
		else
		{
			if (!AbsoluteClippingRect.isPointInside(
				core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y)))
			{
				return false;
			}
			else
			{
				// move cursor
				CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
				if(UTF16_IS_SURROGATE_LO(Text[CursorPos]))
				{
					if(CursorPos>0)
						--CursorPos;
				}

				s32 newMarkBegin = MarkBegin;
				if (!MouseMarking)
					newMarkBegin = CursorPos;

				MouseMarking = true;
				setTextMarkers( newMarkBegin, CursorPos);
				calculateScrollPos();
				return true;
			}
		}
	default:
		break;
	}

	return false;
}

irr::s32 UIEditBox::getCursorPos( s32 x, s32 y )
{
	IGUIFont* font = OverrideFont;
	IGUISkin* skin = Skin;
	if (!OverrideFont)
		font = skin->getFont();

	const u32 lineCount = (WordWrap || MultiLine) ? BrokenText.size() : 1;

	core::stringw *txtLine=0;
	s32 startPos=0;
	x+=3;

	for (u32 i=0; i < lineCount; ++i)
	{
		setTextRect(i);
		if (i == 0 && y < CurrentTextRect.UpperLeftCorner.Y)
			y = CurrentTextRect.UpperLeftCorner.Y;
		if (i == lineCount - 1 && y > CurrentTextRect.LowerRightCorner.Y )
			y = CurrentTextRect.LowerRightCorner.Y;

		// is it inside this region?
		if (y >= CurrentTextRect.UpperLeftCorner.Y && y <= CurrentTextRect.LowerRightCorner.Y)
		{
			// we've found the clicked line
			txtLine = (WordWrap || MultiLine) ? &BrokenText[i] : &Text;
			startPos = (WordWrap || MultiLine) ? BrokenTextPositions[i] : 0;
			break;
		}
	}

	if (x < CurrentTextRect.UpperLeftCorner.X)
		x = CurrentTextRect.UpperLeftCorner.X;

	s32 idx = font->getCharacterFromPos(Text.c_str(), x - CurrentTextRect.UpperLeftCorner.X);

	// click was on or left of the line
	if (idx != -1)
		return idx + startPos;

	// click was off the right edge of the line, go to end.
	return txtLine->size() + startPos;
}

void UIEditBox::breakText()
{
	IGUISkin* skin = Skin;

	if ((!WordWrap && !MultiLine) || !skin)
		return;

	BrokenText.clear(); // need to reallocate :/
	BrokenTextPositions.set_used(0);

	IGUIFont* font = OverrideFont;
	if (!OverrideFont)
		font = skin->getFont();

	if (!font)
		return;

	LastBreakFont = font;

	core::stringw line;
	core::stringw word;
	core::stringw whitespace;
	s32 lastLineStart = 0;
	s32 size = Text.size();
	s32 length = 0;
	s32 elWidth = DestinationQuadrangle[1].X - DestinationQuadrangle[0].X - 6;
	wchar_t c;

	for (s32 i=0; i<size; ++i)
	{
		c = Text[i];
		bool lineBreak = false;

		if (c == L'\r') // Mac or Windows breaks
		{
			lineBreak = true;
			c = ' ';
			if (Text[i+1] == L'\n') // Windows breaks
			{
				Text.erase(i+1);
				--size;
			}
		}
		else if (c == L'\n') // Unix breaks
		{
			lineBreak = true;
			c = ' ';
		}

		// don't break if we're not a multi-line edit box
		if (!MultiLine)
			lineBreak = false;

		if (c == L' ' || c == 0 || i == (size-1))
		{
			if (word.size())
			{
				// here comes the next whitespace, look if
				// we can break the last word to the next line.
				s32 whitelgth = font->getDimension(whitespace.c_str()).Width;
				s32 worldlgth = font->getDimension(word.c_str()).Width;

				if (WordWrap && length + worldlgth + whitelgth > elWidth)
				{
					// break to next line
					length = worldlgth;
					BrokenText.push_back(line);
					BrokenTextPositions.push_back(lastLineStart);
					lastLineStart = i - (s32)word.size();
					line = word;
				}
				else
				{
					// add word to line
					line += whitespace;
					line += word;
					length += whitelgth + worldlgth;
				}

				word = L"";
				whitespace = L"";
			}

			whitespace += c;

			// compute line break
			if (lineBreak)
			{
				line += whitespace;
				line += word;
				BrokenText.push_back(line);
				BrokenTextPositions.push_back(lastLineStart);
				lastLineStart = i+1;
				line = L"";
				word = L"";
				whitespace = L"";
				length = 0;
			}
		}
		else
		{
			// yippee this is a word..
			word += c;
		}
	}

	line += whitespace;
	line += word;
	BrokenText.push_back(line);
	BrokenTextPositions.push_back(lastLineStart);
}

void UIEditBox::setTextRect( s32 line )
{
	core::dimension2du d;

	rect<s32>FrameRect;
	FrameRect.UpperLeftCorner.X = (s32)DestinationQuadrangle[0].X;
	FrameRect.UpperLeftCorner.Y = (s32)DestinationQuadrangle[0].Y;
	FrameRect.LowerRightCorner.X = (s32)DestinationQuadrangle[2].X;
	FrameRect.LowerRightCorner.Y = (s32)DestinationQuadrangle[2].Y;

	IGUISkin* skin = Skin;
	if (!skin)
		return;

	IGUIFont* font = OverrideFont ? OverrideFont : skin->getFont();

	if (!font)
		return;

	// get text dimension
	const u32 lineCount = (WordWrap || MultiLine) ? BrokenText.size() : 1;
	if (WordWrap || MultiLine)
	{
		d = font->getDimension(BrokenText[line].c_str());
	}
	else
	{
		d = font->getDimension(Text.c_str());
		d.Height = FrameRect.getHeight();
	}
	d.Height += font->getKerningHeight();

	// justification
	switch (HAlign)
	{
	case EGUIA_CENTER:
		// align to h centre
		CurrentTextRect.UpperLeftCorner.X = (FrameRect.getWidth()/2) - (d.Width/2);
		CurrentTextRect.LowerRightCorner.X = (FrameRect.getWidth()/2) + (d.Width/2);
		break;
	case EGUIA_LOWERRIGHT:
		// align to right edge
		CurrentTextRect.UpperLeftCorner.X = FrameRect.getWidth() - d.Width;
		CurrentTextRect.LowerRightCorner.X = FrameRect.getWidth();
		break;
	default:
		// align to left edge
		CurrentTextRect.UpperLeftCorner.X = 0;
		CurrentTextRect.LowerRightCorner.X = d.Width;

	}

	switch (VAlign)
	{
	case EGUIA_CENTER:
		// align to v centre
		CurrentTextRect.UpperLeftCorner.Y =
			(FrameRect.getHeight()/2) - (lineCount*d.Height)/2 + d.Height*line;
		break;
	case EGUIA_LOWERRIGHT:
		// align to bottom edge
		CurrentTextRect.UpperLeftCorner.Y =
			FrameRect.getHeight() - lineCount*d.Height + d.Height*line;
		break;
	default:
		// align to top edge
		CurrentTextRect.UpperLeftCorner.Y = d.Height*line;
		break;
	}

	CurrentTextRect.UpperLeftCorner.X  -= HScrollPos;
	CurrentTextRect.LowerRightCorner.X -= HScrollPos;
	CurrentTextRect.UpperLeftCorner.Y  -= VScrollPos;
	CurrentTextRect.LowerRightCorner.Y = CurrentTextRect.UpperLeftCorner.Y + d.Height;

	CurrentTextRect += FrameRect.UpperLeftCorner;

}

irr::s32 UIEditBox::getLineFromPos( s32 pos )
{
	if (!WordWrap && !MultiLine)
		return 0;

	s32 i=0;
	while (i < (s32)BrokenTextPositions.size())
	{
		if (BrokenTextPositions[i] > pos)
			return i-1;
		++i;
	}
	return (s32)BrokenTextPositions.size() - 1;
}

void UIEditBox::inputChar( wchar_t c )
{
	if (c != 0)
	{
		if (Text.size() < Max || Max == 0)
		{
			core::stringw s;

			if (MarkBegin != MarkEnd)
			{
				// replace marked text
				const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
				const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;

				s = Text.subString(0, realmbgn);
				s.append(c);
				s.append( Text.subString(realmend, Text.size()-realmend) );
				Text = s;
				CursorPos = realmbgn+1;
			}
			else
			{
				// add new character
				s = Text.subString(0, CursorPos);
				s.append(c);
				s.append( Text.subString(CursorPos, Text.size()-CursorPos) );
				Text = s;
				++CursorPos;
			}

			BlinkStartTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
			setTextMarkers(0, 0);
		}
	}
	breakText();
	//sendGuiEvent(EGET_EDITBOX_CHANGED);
	calculateScrollPos();
}

void UIEditBox::calculateScrollPos()
{
	if (!AutoScroll)
		return;
	rect<s32>FrameRect;
	FrameRect.UpperLeftCorner.X = (s32)DestinationQuadrangle[0].X;
	FrameRect.UpperLeftCorner.Y = (s32)DestinationQuadrangle[0].Y;
	FrameRect.LowerRightCorner.X = (s32)DestinationQuadrangle[2].X;
	FrameRect.LowerRightCorner.Y = (s32)DestinationQuadrangle[2].Y;
	// calculate horizontal scroll position
	s32 cursLine = getLineFromPos(CursorPos);
	setTextRect(cursLine);

	// don't do horizontal scrolling when wordwrap is enabled.
	if (!WordWrap)
	{
		// get cursor position
		IGUISkin* skin = Skin;
		if (!skin)
			return;
		IGUIFont* font = OverrideFont ? OverrideFont : skin->getFont();
		if (!font)
			return;

		core::stringw *txtLine = MultiLine ? &BrokenText[cursLine] : &Text;
		s32 cPos = MultiLine ? CursorPos - BrokenTextPositions[cursLine] : CursorPos;

		s32 cStart = CurrentTextRect.UpperLeftCorner.X + HScrollPos +
			font->getDimension(txtLine->subString(0, cPos).c_str()).Width;

		s32 cEnd = cStart + font->getDimension(L"_ ").Width;

		if (FrameRect.LowerRightCorner.X < cEnd)
			HScrollPos = cEnd - FrameRect.LowerRightCorner.X;
		else if (FrameRect.UpperLeftCorner.X > cStart)
			HScrollPos = cStart - FrameRect.UpperLeftCorner.X;
		else
			HScrollPos = 0;

		// todo: adjust scrollbar
	}

	// vertical scroll position
	if (FrameRect.LowerRightCorner.Y < CurrentTextRect.LowerRightCorner.Y + VScrollPos)
		VScrollPos = CurrentTextRect.LowerRightCorner.Y - FrameRect.LowerRightCorner.Y + VScrollPos;

	else if (FrameRect.UpperLeftCorner.Y > CurrentTextRect.UpperLeftCorner.Y + VScrollPos)
		VScrollPos = CurrentTextRect.UpperLeftCorner.Y - FrameRect.UpperLeftCorner.Y + VScrollPos;
	else
		VScrollPos = 0;

	// todo: adjust scrollbar
}

bool UIEditBox::isMultiLineEnabled() const
{
	return MultiLine;
}

void UIEditBox::setTextMarkers( s32 begin, s32 end )
{
	MarkBegin = begin;
	MarkEnd = end;
	return;
}
