#include "Board.h"

//Construct a Board with the indicated number of holes per side (not counting the pot!) 
//and initial number of beans per hole.If nHoles is not positive, act as if it were 1; 
//if nInitialBeansPerHole is negative, act as if it were 0.
Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles <= 0)
		nHoles = 1; 

	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0;

	m_nHoles = nHoles;

	nHoles += 1; //adding the pot into the array.

	m_SideN[0] = 0;
	m_SideS[0] = 0;

	for (int i = 1; i < nHoles; i++)
	{
		m_SideN[i] = nInitialBeansPerHole;
		m_SideS[i] = nInitialBeansPerHole;
	}

}

//return the number of beans in the indicated hole or pot, or -1 if the hole number is invalid
int Board::beans(Side s, int hole) const
{
	if (hole > m_nHoles || hole < 0)
		return -1;
	
	const int* wside = s == NORTH ? m_SideN : m_SideS; //choose which side to look at

	return wside[hole];
}

//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const
{
	const int* wside = s == NORTH ? m_SideN : m_SideS; //choose which side to look at
	int totalinHoles = 0;

	for (int i = 1; i <= m_nHoles; i++)
		totalinHoles += wside[i];

	return totalinHoles;
}

//Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const
{
	int grandTotal = 0;

	for (int i = 0; i <= m_nHoles; i++)
	{
		grandTotal += m_SideN[i];
		grandTotal += m_SideS[i];
	}
	return grandTotal;
}

//If the hole indicated by(s, hole) is empty or invalid or a pot, this function returns false without changing anything.
//Otherwise, it will return true after sowing the beans : the beans are removed from hole(s, hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. 
//The parameters endSide and endHole are set to the side and hole where the last bean was placed. 
//(This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, 
//so dealing with them should not be the responsibility of the Board class.) 
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (hole <= 0 || hole > m_nHoles)
		return false;

	int* iSide = m_SideS;
	if (s == NORTH)
	{
		iSide = m_SideN;
	}

	if (iSide[hole] == 0)
		return false; //if the hole is empty, there's nothing to sow

	endHole = -1; //now that the function has checked for invalid input, set endHole to -1;

	int beansToSow = iSide[hole]; //pick all the beans up out of the hole
	iSide[hole] = 0;

	while (beansToSow > 0)
	{
		if (iSide == m_SideS) //if we're on the south side, go up one hole index
			hole++;
		else
			hole--; //if we're on the north side, go down one hole index

		if (hole > m_nHoles) //if you've reached the end of the south side, switch to the north side
		{
			hole--;
			if (s == SOUTH && iSide == m_SideS)	//if the side is south, add a BEAN to the south pot
			{
				m_SideS[0]++;
				beansToSow--;
			}
			iSide = m_SideN;
		}
			
		if (hole < 1) //if you've reached the end of the north side, switch to the south side
		{
			hole++;
			if (s == NORTH && iSide == m_SideN) //if the side is north, add a BEAN to the north pot
			{
				m_SideN[0]++;
				beansToSow--;
			}
			iSide = m_SideS;
		}

		if (beansToSow > 0) //might not hold true if the function put a bean in a pot, and that was the final bean
		{
			iSide[hole]++;
			beansToSow--;
		}
		else //else condition triggers if the bean sown in the pot was the final bean
		{
			endHole = 0;
		}
	}
	if (iSide == m_SideN)
		endSide = NORTH;
	else
		endSide = SOUTH;
	if (endHole == -1)
		endHole = hole;

	return true;
	//first sows through all of side's holes, then into that side's pot, then into the opposite side's holes starting from the top. it has to loop infinitely

}

// If the indicated hole is invalid or a pot, return false without changing anything.
// Otherwise, move all the beans in hole(s, hole) into the pot belonging to potOwner and return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole <= 0 || hole > m_nHoles)
		return false;

	int* wside = s == NORTH ? m_SideN : m_SideS;
	int* targetSide = potOwner == NORTH ? m_SideN : m_SideS;
	
	targetSide[0] += wside[hole];
	wside[hole] = 0;

	return true;
}

//If the indicated hole is invalid or beans is negative, this function returns false without changing anything.
//Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. 
// (This may change what beansInPlay and totalBeans return if they are called later.) 
//This function exists solely so that we and you can more easily test your program : 
//None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. 
//(We'll show an example of its use below.) 
bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole < 0 || hole > m_nHoles || beans < 0)
		return false;

	int* wside = s == NORTH ? m_SideN : m_SideS; //choose which side to look at
	
	wside[hole] = beans;
	return true;
}