#ifndef SIDE_H
#define SIDE_H

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}



//given a board, both Game::move and SmartPlayer::chooseMove may want to make a complete move on that board for a player. 
//You could have them both call a non-member function that takes a Board& parameter and uses only the public interface of Board. 


//helper function: determine legal move

#endif // !SIDE_H
