#include "AbstractPokerPlayer.h"

cAbstractPokerPlayer::cAbstractPokerPlayer(std::uint32_t stackSize) : m_stackSize(stackSize)
{
	m_currentBet = 0;
}

std::uint32_t cAbstractPokerPlayer::ConsumeBet()
{
	std::uint32_t OldBet = m_currentBet;
	m_stackSize -= m_currentBet;
	m_currentBet = 0;
	return OldBet;
}