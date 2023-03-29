#include <phevaluator/phevaluator.h>
#include <iostream>
#include <cassert>
#include "Poker/PokerInstance.h"

int main()
{
	cPokerInstance instance;
	instance.InitTestPlayers();
	instance.DealCards();
	instance.PrintPlayersAndRanks();
}
