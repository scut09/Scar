#include "RankForm.h"

CRankForm::CRankForm(IHreo** playerlist, GameLogic::IClient* client)
{
	m_client = client;
	m_playerlist = playerlist;
	m_isShow = false;
	m_window = g_guienv->addWindow(core::rect<s32>(350,300,650,500));
	m_window->setVisible(false);
	m_window->setDrawTitlebar(false);
	m_window->getCloseButton()->setVisible(false);
	m_listBox = g_guienv->addListBox(core::rect<s32>(10,10,280,180),m_window);
	m_listBox->setEnabled(false);

}

CRankForm::~CRankForm(void)
{
}

void CRankForm::Show( bool show )
{
	if (show == m_isShow)		//如果未改变就不处理
	{
		return;
	}
	m_isShow = show;
	if(m_isShow)		//显示对话框
	{
		Sort();
		m_listBox->clear();
		m_listBox->addItem(L"Name                        kill  / bekill");
		int i = 0;
		char str[50];
		while (m_sort[i] != NULL)
		{
			IHreo* hreo = (IHreo*) m_sort[i];
			memset(str,' ', 50);//清空内存
			memcpy(str,m_client->GetName(hreo->m_index),strlen(m_client->GetName(hreo->m_index)));
			itoa(hreo->m_killCount, &str[30],10);
			if (hreo->m_killCount < 10)			//
			{
				str[31] = ' ';
			}
			else if (hreo->m_killCount >= 10 && hreo->m_killCount < 100)
			{
				str[32] = ' ';
			}
			else
			{
				str[33] = ' ';
			}
			str[35] = '/';
			itoa(hreo->m_beKill, &str[40],10);
			wchar_t* buffer = CHelper::char_to_wchar(str);
			m_listBox->addItem(buffer);
			delete[] buffer;
			i++;
		}
		m_window->setVisible(true);
	}
	else				//隐藏
	{

		m_window->setVisible(false);
	}
}

int CRankForm::Sort()		//排序
{
	memset(m_sort,0, 16);	//清空内存
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (NULL != m_playerlist[i])
		{
			m_sort[count] = m_playerlist[i];
			count++;
		}
		
	}
	IHreo* temp;
	for (int i = 0; i < count - 1; i++)				//冒泡排序
	{
		for (int j = 0; j < count - 1 - i; j++)
		{			
			if (m_sort[j]->m_killCount < m_sort[j+1]->m_killCount )
			{
				temp = m_sort[j];
				m_sort[j] = m_sort[j+1];
				m_sort[j+1] = temp;
			}
			else if (m_sort[j]->m_killCount == m_sort[j+1]->m_killCount &&
				m_sort[j]->m_beKill > m_sort[j+1]->m_beKill)
			{
				temp = m_sort[j];
				m_sort[j] = m_sort[j+1];
				m_sort[j+1] = temp;
			}
		}
	}
	return count;
}

void CRankForm::Release()
{
	m_listBox->remove();
	m_window->remove();
}