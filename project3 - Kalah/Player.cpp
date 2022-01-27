#include "Player.h"
#include <iostream>

int HumanPlayer::chooseMove(const Board& b, Side s) const //prompts the human player for a move
{
	if (b.beansInPlay(s) == 0)
		return -1;

	int selection;
	while (true)
	{
	std::cin >> selection;
	std::cin.ignore(1000, '\n');
	if (b.beans(s, selection) > 0) //don't need to check here, as it's being checked in game.move(). However, it IS checking here because Smallberg wants us to
		return selection;
	
	std::cout << "Invalid Move. Please select a legal hole that contains beans." << std::endl;
	}
}

int BadPlayer::chooseMove(const Board& b, Side s) const //the bad player selects a move at random from the available choices
{
	if (b.beansInPlay(s) == 0)
		return -1;

	srand(time(0));
	int selection;
	while (true)
	{
		selection = (rand() % b.holes() + 1);
		if (b.beans(s, selection) > 0)
			return selection;
	}
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	AlarmClock limit(4900); //initializing clock, can't take more than five seconds
	int bestHole = 1;
	int	Value = 0;


	moveChoose(b, s, limit, Value, bestHole, 16); //helper function does the meat of the work

	return bestHole;
}


void SmartPlayer::moveChoose(Board b, Side agent, AlarmClock& ac, int& value, int& besthole, int depth) const //find the best move
{
	//generate a game tree up to a point
	//evaluate the game tree starting from the bottom (leaves) and moving towards the roots
	//heuristic: number of beans in south's pot, minus the number in north's pot



	Side villian = agent == SOUTH ? NORTH : SOUTH; //find the person on the other side

	if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0) //if the game is over, figure out who won and return
	{
		besthole = -1;

		for (int i = 1; i <= b.holes(); i++)
		{
			b.moveToPot(NORTH, i, NORTH);
			b.moveToPot(SOUTH, i, SOUTH);
		}

		if (b.beans(SOUTH, 0) > b.beans(NORTH, 0)) value = (agent == SOUTH ? 1000000 : -1000000); //south wins = +inf for south, -inf for north

		else if (b.beans(SOUTH, 0) == b.beans(NORTH, 0)) value = (agent == SOUTH ? -1000000 : 1000000); //see ties as a loss

		else value = (agent == SOUTH ? -1000000 : 1000000); //north wins = -inf for south, + inf for north

		return;
	}

	if (ac.timedOut() || depth <= 0) //if we're out of time or reach max depth, return the falue of the leaf
	{
		besthole = -1;
		value = b.beans(SOUTH, 0) - b.beans(NORTH, 0);
		return;
	}

	Side endside = SOUTH;
	int endhole = 0, value2 = 0, hole2 = 0;

	bool initialvalue = true;

	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(agent, i) > 0)
		{

			if (ac.timedOut())
			{
				//besthole = -1;
				value = b.beans(SOUTH, 0) - b.beans(NORTH, 0);
				return;
			}

			// make a complete move on a new board
			Board branch = b;

			branch.sow(agent, i, endside, endhole);

			if (endhole == 0)
			{ //case for extra turns
				moveChoose(branch, agent, ac, value2, hole2, depth);
			}
			if (endside == agent && b.beans(agent, endhole) == 1 && b.beans(villian, endhole) > 0)
			{ //case for captures
				branch.moveToPot(agent, endhole, agent);
				branch.moveToPot(villian, endhole, agent);
			}
			//move is finished

			if (initialvalue) //the first value on this level of the branch is set to the best value initially, and other values are compared against it
			{
				initialvalue = false;
				besthole = i;
				value = b.beans(SOUTH, 0) - b.beans(NORTH, 0);
			}


			--depth;
			moveChoose(branch, villian, ac, value2, hole2, depth); //go a level deeper! checks by depth first, up to 'depth' levels. pass the opponent as actor so they take their turn


			if ((agent == SOUTH && value2 >= value) || (agent == NORTH && value2 <= value)) //if you find a hole that's better than the current one, make it the new best
			{
				besthole = i;
				value = value2;
			}
		}
	}
	return;
}