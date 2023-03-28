#ifndef PokerInstance_Header
#define PokerInstance_Header
#include <memory>
#include <vector>

class cPokerInstance
{
	std::vector<std::shared_ptr<class cAbstractPokerPlayer>> m_players;
};

#endif