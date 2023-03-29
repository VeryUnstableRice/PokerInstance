#ifndef AbstractPokerPlayer_Header
#define AbstractPokerPlayer_Header
#include <cinttypes>
#include "PokerDeck.h"
#include <memory>

enum class ePokerPlayer_Response
{
	Fold,
	Call_Check,
	Bet,
	Raise_Amount
};

struct sPokerPlayerResponse
{
	ePokerPlayer_Response m_response;
	float m_raiseAmount; //normalized
};

class cAbstractPokerPlayer
{
	std::uint32_t m_stackSize;
	std::uint32_t m_currentBet;
	std::array<cPokerCard, 2> m_playerCards;
public:
	cAbstractPokerPlayer(std::uint32_t stackSize = 0);

	void SetPlayerCards(const std::array<cPokerCard, 2>& cards) { m_playerCards = cards; };
	const std::array<cPokerCard, 2>& GetPlayerCards() const { return m_playerCards; }
	std::uint32_t GetStackSize() const { return m_stackSize; };
	std::uint32_t GetCurrentBet() const { return m_currentBet; };
	bool SetCurrentBet(std::uint32_t value);
	void ResetBet() { m_currentBet = 0; };

	sPokerPlayerResponse GetPlayerResponse(const std::array<cPokerCard, 5>& community_cards, std::vector<std::uint32_t> oponent_stacks, std::uint32_t pot_size);
};

inline bool cAbstractPokerPlayer::SetCurrentBet(std::uint32_t value)
{
	if (value > m_stackSize)
		return false;
	m_currentBet = value;
	return true;
}

#endif