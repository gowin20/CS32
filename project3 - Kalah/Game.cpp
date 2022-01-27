#include "Game.h"
#include <iostream>
using namespace std;

//	Display the game's board in a manner of your choosing, 
// provided you show the names of the players and a reasonable representation of the state of the board. 
void Game::display() const
{
	cout << "   " << m_North->name() << endl << " ";

	for (int i = 1; i <= m_board.holes(); i++)
		cout << "  " << m_board.beans(NORTH, i); //top line (north's holes)
	cout << endl;

	cout << " " << m_board.beans(NORTH, 0);
	for (int i = 1; i <= m_board.holes(); i++) //middle line (pots)
		cout << "   ";
	cout << " " << m_board.beans(SOUTH, 0) << endl << " ";

	for (int i = 1; i <= m_board.holes(); i++)
		cout << "  " << m_board.beans(SOUTH, i); //bottom line (south's holes)
	cout << endl;

	cout << "   " << m_South->name() << endl;
}


//	If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. 
// Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. 
// If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side. 
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	over = false;
	if (m_board.beansInPlay(NORTH) > 0 && m_board.beansInPlay(SOUTH) > 0)
		return;

	over = true;
	hasWinner = true;

	Side offSide = m_Turn == SOUTH ? NORTH : SOUTH;
	int otherBeans = m_board.totalBeans() / 2; //this is equal to half of all total beans, which is how the win condition is determined
	int hisbeans = m_board.beans(m_Turn, 0) + m_board.beansInPlay(m_Turn);


	if (hisbeans == otherBeans)
		hasWinner = false;
	else if (hisbeans > otherBeans)
		winner = m_Turn;
	else
		winner = offSide;
}

//	If the game is over, return false. Otherwise, make a complete move for the player whose turn it is(so that it becomes the other player's turn) and return true.
//"Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. 
//If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
bool Game::move()
{
	bool running = true, winner;
	Side Eside;
	Player* mover = m_Turn == SOUTH ? m_South : m_North; //figure out who's acting

	while (running) //core move loop. Runs only once unless the player obtains extra turns
	{
		status(running, winner, Eside);
		if (running) //if the game ends on a move, move everything to the pot and return false
		{
			Player* sweptboy = (m_board.beansInPlay(SOUTH) > 0 ? m_South : m_North);
			cout << "Sweeping remaining beans into " << sweptboy->name() << "'s pot" << endl;
			for (int i = 1; i <= m_board.holes(); i++)
			{
				m_board.moveToPot(NORTH, i, NORTH);
				m_board.moveToPot(SOUTH, i, SOUTH);
			}
			return false;
		}
			
		if (mover->isInteractive())
			cout << "Select a hole, " << mover->name() << ": "; //prompt the human player
		
		int selectedhole = mover->chooseMove(m_board, m_Turn); //choose a move

		if (!(mover->isInteractive()))
			cout << mover->name() << " chooses hole " << selectedhole << endl; //tell the human player what the computer is up to

		int Ehole = -1;

		m_board.sow(m_Turn, selectedhole, Eside, Ehole); //sow the board. If it doesn't sow, that means the human has entered an invalid hole, and will be prompted again
	
		Side otherside = m_Turn == SOUTH ? NORTH : SOUTH;
		
		//case for captures
		if (Eside == m_Turn && m_board.beans(m_Turn, Ehole) == 1 && m_board.beans(otherside, Ehole) > 0) 
		{
//			cout << "Capture!" << endl;
			m_board.moveToPot(m_Turn, Ehole, m_Turn);
			m_board.moveToPot(otherside, Ehole, m_Turn);
		}
		
		status(running, winner, Eside); //if the game ended during this move, running will be set to true and the game will end after cleanup
		
		//case for additional turns
		if (Ehole == 0)
		{
			cout << mover->name() << " gets another turn." << endl;
			running = true;
			display();
		}
		
	}
	if (m_Turn == SOUTH) //once the turn is over, swap the turn to the next person
		m_Turn = NORTH;
	else m_Turn = SOUTH;

	return true;
}


//	Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. 
// If neither player is interactive, then to keep the display from quickly scrolling through the whole game, 
// it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. 
// (The ignore function for input streams is useful here.) Announce the winner at the end of the game. 
// You can apportion to your liking the responsibility for displaying the board between this function and the move function. 
// (Note: If when this function is called, South has no beans in play, so can't make the first move, 
// sweep any beans on the North side into North's pot and act as if the game is thus over.) 
void Game::play()
{
	bool over = false;
	bool hasWinner = false;
	Side winningSide = SOUTH;

	display();
	while (true)
	{
		if (!move())
			break;

		display();

		if ((!m_South->isInteractive()) && !(m_North->isInteractive()))
		{
			cout << "Press ENTER to continue.";
			cin.ignore(1000, '\n');
		}
	}

	status(over, hasWinner, winningSide);

	display();
	if (hasWinner)
		cout << "The winner is " << (winningSide == SOUTH ? m_South->name() : m_North->name()) << endl;
	else
		cout << "It's a tie!" << endl;
}

//	Return the number of beans in the indicated hole or pot of the game's board, 
//	or -1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
int Game::beans(Side s, int hole) const
{
	if (hole > m_board.holes() || hole < 0)
		return -1;

	return m_board.beans(s, hole);
}

