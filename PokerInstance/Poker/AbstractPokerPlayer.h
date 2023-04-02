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
	Raise
};

struct sPokerPlayerResponse
{
	ePokerPlayer_Response Response;
	float RaiseAmount; //normalized
};

class cAbstractPokerPlayer
{
	std::uint32_t m_stackSize;
	std::uint32_t m_currentBet;
	bool m_folded;
	std::array<cPokerCard, 2> m_playerCards;
public:
	cAbstractPokerPlayer(std::uint32_t stackSize = 0);
	
	std::uint32_t GetStackSize() const;
	std::uint32_t GetCurrentBet() const;
	bool SetCurrentBet(std::uint32_t value);
	std::uint32_t ConsumeBet();
	bool IsFolded() const;
	bool IsAllIn() const;
	void Fold();

	void SetPlayerCards(const std::array<cPokerCard, 2>& cards) { m_playerCards = cards; };
	const std::array<cPokerCard, 2>& GetPlayerCards() const { return m_playerCards; }

	virtual sPokerPlayerResponse GetPlayerAct(const std::array<cPokerCard, 5>& community_cards, class cPokerInstance* instace);
};

inline bool cAbstractPokerPlayer::SetCurrentBet(std::uint32_t value)
{
	if (value > m_stackSize)
		return false;
	m_currentBet = value;
	return true;
}

inline bool cAbstractPokerPlayer::IsAllIn() const
{ 
	return m_currentBet == m_stackSize; 
}

inline void cAbstractPokerPlayer::Fold() { m_folded = true; }

inline sPokerPlayerResponse cAbstractPokerPlayer::GetPlayerAct(const std::array<cPokerCard, 5>& community_cards, cPokerInstance* instace)
{
	return sPokerPlayerResponse();
}

inline bool cAbstractPokerPlayer::IsFolded() const { return m_folded; }
inline std::uint32_t cAbstractPokerPlayer::GetCurrentBet() const { return m_currentBet; }
inline std::uint32_t cAbstractPokerPlayer::GetStackSize() const { return m_stackSize; }


#endif