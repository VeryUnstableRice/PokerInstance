#ifndef PokerDeck_Header
#define PokerDeck_Header
#include "PokerCard.h"

class cPokerDeck
{
	std::array<cPokerCard, 52> m_cards;
	size_t m_cardNum;
public:
	cPokerDeck();

	void Shuffle(); //resets the stack and shuffles it
	cPokerCard PopCard(); //pops the last card in the deck
};

#endif