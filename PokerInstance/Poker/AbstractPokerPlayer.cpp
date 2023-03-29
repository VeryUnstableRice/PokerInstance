#include "AbstractPokerPlayer.h"

cAbstractPokerPlayer::cAbstractPokerPlayer(std::uint32_t stackSize) : m_stackSize(stackSize)
{
	m_currentBet = 0;
}
