#include <phevaluator/phevaluator.h>
#include <iostream>
#include <cassert>
#include "Poker/PokerInstance.h"

int main()
{
	cPokerInstance instance(1, 2);
	instance.Run();
	instance.PrintPlayersAndRanks();
}
