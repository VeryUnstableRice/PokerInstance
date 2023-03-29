#include "PokerDeck.h"
#include <random>

cPokerDeck::cPokerDeck()
{
	for (int i = 0; i < 52; ++i)
		m_cards[i] = cPokerCard(i);
	m_cardNum = 52;
}

void cPokerDeck::Shuffle()
{
	m_cardNum = 52;

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_cards.begin(), m_cards.end(), g);
}

cPokerCard cPokerDeck::PopCard()
{
	--m_cardNum;
	return m_cards[m_cardNum];
}