#ifndef PokerCard_Header
#define PokerCard_Header
#include <phevaluator/phevaluator.h>

class cPokerCard : public phevaluator::Card
{
public:
	std::array<float, 2> FloatEncoding();
};

#endif