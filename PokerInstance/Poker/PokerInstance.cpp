#include "PokerInstance.h"
#include "AbstractPokerPlayer.h"
#include <algorithm>
#include <iostream>

void cPokerInstance::Reset()
{
	m_state = ePokerInstanceState::Initialize;
	InitTestPlayers();
	m_running = true;
}

cPokerInstance::cPokerInstance(std::uint32_t min_stake, std::uint32_t max_stake)
{
	m_minStake = min_stake;
	m_maxStake = max_stake;
	m_dealerButton = 0;
	Reset();
}

void cPokerInstance::DealCards()
{
	m_deck.Shuffle();

	for (int i = 0; i < 5; ++i)
		m_communityCards[i] = m_deck.PopCard();
	for (int i = 0; i < m_players.size(); ++i)
		m_players[i]->SetPlayerCards({ m_deck.PopCard(), m_deck.PopCard() });
}

std::vector<RankAndPlayerIndex> cPokerInstance::GetRanksAndPlayers()
{
	std::vector<RankAndPlayerIndex> output;
	output.reserve(m_players.size());

	for (int i = 0; i < m_players.size(); ++i)
		output.push_back(std::make_pair(GetPlayerRank(m_players[i].get()), i));
	std::sort(output.begin(), output.end(), [](const RankAndPlayerIndex& A, const RankAndPlayerIndex& B)
		{
			return A.first > B.first;
		});
	
	return output;
}

phevaluator::Rank cPokerInstance::GetPlayerRank(cAbstractPokerPlayer* player) const
{
	return phevaluator::EvaluateCards(m_communityCards[0], m_communityCards[1], m_communityCards[2], m_communityCards[3], m_communityCards[4], player->GetPlayerCards()[0], player->GetPlayerCards()[1]);
}

void cPokerInstance::PrintPlayersAndRanks()
{
	std::vector<RankAndPlayerIndex> players = GetRanksAndPlayers();

	for (int i = 0; i < players.size(); ++i)
	{
		std::cout << players[i].first.value() << ' ';

		cAbstractPokerPlayer* player = m_players[players[i].second].get();
		for (int j = 0; j < 5; ++j)
		{
			std::cout << m_communityCards[j].describeCard() << ' ';
		}
		std::cout << player->GetPlayerCards()[0].describeCard() << ' ' << player->GetPlayerCards()[1].describeCard() << ' ' << players[i].first.describeCategory() << std::endl;
	}
}

void cPokerInstance::InitTestPlayers()
{
	m_players.resize(10);
	for (int i = 0; i < 10; ++i)
		m_players[i] = std::make_shared< cAbstractPokerPlayer>();
}

void cPokerInstance::Run()
{
	while (m_running)
	{
		switch (m_state)
		{
		case ePokerInstanceState::Initialize:
			State_Initialize();
			break;
		case ePokerInstanceState::Pre_Flop:
			State_PreFlop();
			break;
		}
	}
}

void cPokerInstance::State_Initialize()
{
	size_t player_num = m_players.size();
	m_dealerButton = (m_dealerButton + 1) % player_num;
	m_smallBlind = m_dealerButton - 1;
	m_bigBlind = m_dealerButton - 2;

	if (m_smallBlind < 0)
		m_smallBlind += player_num;
	if (m_bigBlind < 0)
		m_bigBlind += player_num;


	DealCards();
}

void cPokerInstance::State_PreFlop()
{
	m_players[m_smallBlind]->SetCurrentBet(m_minStake);
	m_players[m_bigBlind]->SetCurrentBet(m_maxStake);
}