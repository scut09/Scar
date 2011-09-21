///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/14 2:59
//description:	сно╥
///////////////////////////////////////////////////////

#ifndef IServer_h
#define IServer_h

namespace GameLogic
{
	class IServer
	{
	public:
		virtual void	CreateHost() = 0;
		
		virtual void	CancelHost() = 0;

		virtual void	BeignGame() = 0;
		
		virtual int		GetHostState() = 0;
	};
}

#endif