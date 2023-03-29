#ifndef PokerInstance_Header
#define PokerInstance_Header
#include <memory>
#include <vector>
#include "PokerDeck.h"

using RankAndPlayerIndex = std::pair<phevaluator::Rank, std::uint32_t>;

enum class ePokerInstanceState
{
	Initialize,
	Pre_Flop,
	Flop,
	Turn,
	River,
	Showdown
};

 
class cPokerInstance
{
	cPokerDeck m_deck;

	std::vector<std::shared_ptr<class cAbstractPokerPlayer>> m_players;
	std::array<cPokerCard, 5> m_communityCards;

	std::uint32_t m_minStake, m_maxStake;
	std::uint32_t m_smallBlind, m_bigBlind;
	std::uint32_t m_dealerButton;
	bool m_running;

	ePokerInstanceState m_state;

	void Reset();

	void State_Initialize();
	void State_PreFlop();

public:
	cPokerInstance(std::uint32_t min_stake, std::uint32_t max_stake);

	void Run();


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