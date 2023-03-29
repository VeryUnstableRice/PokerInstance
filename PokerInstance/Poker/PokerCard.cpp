#include "PokerCard.h"
#include "PokerCard.h"

std::array<float, 2> cPokerCard::FloatEncoding()
{
	return std::array<float, 2>((float)describeRank()/13.0f, (float)id_*0.25f);
}

