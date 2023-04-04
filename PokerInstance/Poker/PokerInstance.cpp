#include "PokerInstance.h"
#include "AbstractPokerPlayer.h"
#include <algorithm>
#include <iostream>

void cPokerInstance::Reset()
{
	m_state = ePokerInstanceState::Initialize;
	m_running = true;
	m_noBetsYet = true;
	m_communityCards.fill(cPokerCard(-1));
}

cPokerInstance::cPokerInstance(std::uint32_t min_stake, std::uint32_t max_stake)
{
	m_minStake = min_stake;
	m_maxStake = max_stake;
	m_dealerButton = 0;
	m_pot = 0;
	InitTestPlayers();
	Reset();
}

std::vector<RankAndPlayerIndex> cPokerInstance::GetRanksAndPlayers()
{
	std::vector<RankAndPlayerIndex> output;
	output.reserve(m_players.size());

	for (int i = 0; i < m_players.size(); ++i)
		if(m_players[i]->IsFolded())
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
			SetBlinds();
			ProceedToNextStage(ePokerInstanceState::Flop);
			break;
		case ePokerInstanceState::Flop:
			ProceedToNextStage(ePokerInstanceState::River);
			break;
		case ePokerInstanceState::River:
			ProceedToNextStage(ePokerInstanceState::Showdown);
			break;
		case ePokerInstanceState::Showdown:
			State_Showdown();
			break;
		}
	}
}

void cPokerInstance::State_Initialize()
{
	size_t player_num = m_players.size();
	m_dealerButton = (m_dealerButton + 1) % player_num;
	m_smallBlind = (m_dealerButton - 1) % player_num;
	m_bigBlind = (m_dealerButton - 2) % player_num;


	DealCardsToPlayers(); 

	m_state = ePokerInstanceState::Pre_Flop;
}

void cPokerInstance::DealCommunityCards(std::uint8_t amount)
{
	for (cPokerCard& card: m_communityCards)
	{
		if (amount <= 0)
			return;
		if (card == -1)
		{
			card = m_deck.PopCard();
			--amount;
		}
	}
}

void cPokerInstance::DealCardsToPlayers()
{
	for (auto& player : m_players)
	{
		player->SetPlayerCards({ m_deck.PopCard() ,m_deck.PopCard() });
	}
}

void cPokerInstance::SetBlinds()
{
	m_players[m_smallBlind]->SetCurrentBet(m_minStake);
	m_players[m_bigBlind]->SetCurrentBet(std::min(m_maxStake, m_players[m_bigBlind]->GetStackSize()));
}

void cPokerInstance::ProceedToNextStage(ePokerInstanceState nextState)
{
	LetPlayersAct();
	if (CanProceedToNextStage())
	{
		if (nextState == ePokerInstanceState::Flop) {
			DealCommunityCards(3);
		}
		else {
			DealCommunityCards();
		}
		AddBetsToPot();
		m_state = nextState;
	}
}

void cPokerInstance::State_Showdown()
{
	std::vector<RankAndPlayerIndex> sorted_players = GetRanksAndPlayers();
	//TODO: IMPLEMENT
}

bool cPokerInstance::AllPlayersActed() const
{
	for (auto& player : m_players)
	{
		if (!player->IsFolded() && player->GetCurrentBet() != 0)
		{
			return false;
		}
	}
	return true;
}

bool cPokerInstance::AllPlayersBetsEqualOrAllIn() const
{
	std::int32_t bet = -1;
	for (auto& player : m_players)
	{
		if (!player->IsFolded())
		{
			if (bet == -1)
			{
				bet = player->GetCurrentBet();
			}
			else if (bet != player->GetCurrentBet())
			{
				return false;
			}
		}
	}
	return true;
}

bool cPokerInstance::CanProceedToNextStage() const
{
	return AllPlayersActed() && AllPlayersBetsEqualOrAllIn();
}

void cPokerInstance::LetPlayersAct()
{
	for (auto& player : m_players)
	{
		if (player->IsFolded() || player->IsAllIn())
		{
			continue;
		}

		sPokerPlayerResponse response = player->GetPlayerAct(m_communityCards, this);
		switch (response.Response)
		{
		case ePokerPlayer_Response::Fold:
			player->Fold();
			break;

		case ePokerPlayer_Response::Call_Check:
		{
			if (m_noBetsYet)
			{
				m_noBetsYet = false;
				break;
			}

			std::uint32_t max_bet = 0;
			for (auto& bet_player : m_players)
				max_bet = std::max(max_bet, bet_player->GetCurrentBet());
			if (player->GetCurrentBet() < max_bet)
				player->SetCurrentBet(std::min(max_bet, player->GetStackSize()));

			break;
		}

		case ePokerPlayer_Response::Raise:
		{
			std::uint32_t current_bet = player->GetCurrentBet();
			std::uint32_t min_raise = 2 * current_bet;
			std::uint32_t desired_raise = current_bet + (player->GetStackSize() - current_bet) * response.RaiseAmount;
			if (desired_raise >= min_raise)
			{
				player->SetCurrentBet(std::min(desired_raise, player->GetStackSize()));
				m_noBetsYet = false;
			}
			break;

		}
		case ePokerPlayer_Response::Bet:
		{
			if (!m_noBetsYet)
			{
				// Cannot bet if there's already a bet in the current round
				break;
			}
			std::uint32_t bet_amount = player->GetStackSize() * response.RaiseAmount;
			player->SetCurrentBet(bet_amount);
			m_noBetsYet = false;
			break;
		}
		}
	}
}

void cPokerInstance::AddBetsToPot()
{
	for (auto& player : m_players)
	{
		std::uint32_t current_bet = player->GetCurrentBet();
		player->SetCurrentBet(0);
		m_pot += current_bet;
	}
}
