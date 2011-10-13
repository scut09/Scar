#include "UIManager.h"
#include <iostream>


void UIManager::OnEvent( const SEvent& event )
{
	std::cout << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;



}