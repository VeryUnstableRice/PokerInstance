#ifndef PokerInstance_Header
#define PokerInstance_Header
#include <memory>
#include <vector>
#include "PokerDeck.h"

using RankAndPlayerIndex = std::pair<phevaluator::Rank, std::uint32_t>;


class cPokerInstance
{
	cPokerDeck m_deck;

	std::vector<std::shared_ptr<class cAbstractPokerPlayer>> m_players;
	std::array<cPokerCard, 5> m_communityCards;
public:
	//we use this to shuffle the deck and deal the cards to the community and players;
	void DealCards();
	//this sorts players by ranks, the first player is always the winner
	std::vector<RankAndPlayerIndex> GetRanksAndPlayers();
	//get player rank
	phevaluator::Rank GetPlayerRank(cAbstractPokerPlayer* player) const;
	//print players and ranks
	void PrintPlayersAndRanks();
	void InitTestPlayers();
	

};

#endif