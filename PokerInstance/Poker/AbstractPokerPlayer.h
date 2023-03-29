#ifndef AbstractPokerPlayer_Header
#define AbstractPokerPlayer_Header
#include <cinttypes>
#include "PokerDeck.h"
#include <memory>

enum class PokerPlayer_Response
{
	Fold,
	Call,

};

class cAbstractPokerPlayer
{
	std::uint32_t m_stackSize;
	std::array<cPokerCard, 2> m_playerCards;
public:
	cAbstractPokerPlayer(std::uint32_t stackSize = 0);

	void SetPlayerCards(const std::array<cPokerCard, 2>& cards) { m_playerCards = cards; };
	const std::array<cPokerCard, 2>& GetPlayerCards() const { return m_playerCards; }
	std::uint32_t GetStackSize() const { return m_stackSize; };
};

#endif