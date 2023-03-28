#ifndef AbstractPokerPlayer_Header
#define AbstractPokerPlayer_Header
#include <cinttypes>

class cAbstractPokerPlayer
{
	std::uint32_t m_stackSize;
public:
	cAbstractPokerPlayer(std::uint32_t stackSize);

	std::uint32_t GetStackSize() const { return m_stackSize; };
};

#endif