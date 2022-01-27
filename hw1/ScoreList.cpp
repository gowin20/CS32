#include "ScoreList.h"

ScoreList::ScoreList()
{
	
}
	// Create an empty score list.

bool ScoreList::add(unsigned long score)
{
	if (score > 100)
		return false;
	if (m_list.insert(score) == -1)
		return false;
	return true;

}
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.

bool ScoreList::remove(unsigned long score)
{
	int firstscore = m_list.find(score);
	if (firstscore == -1)
		return false;
	m_list.erase(firstscore); //can't use the deceptively named sequence.remove, for that removes all instances from the list
	return true;
}


// Return the number of scores in the list.
int ScoreList::size() const
{
	return m_list.size();
}



//find the lowest number
unsigned long ScoreList::minimum() const
{
	if (m_list.size() == 0)
		return NO_SCORE;
	unsigned long min;
	m_list.get(0, min);
	unsigned long dummy;
	for (int i = 0; i < m_list.size(); i++)
	{
		m_list.get(i, dummy);
		if (dummy < min)
			min = dummy;
	}
	return min;
}

//functionally the same as minimum, with a > instead of <
unsigned long ScoreList::maximum() const
{
	if (m_list.size() == 0)
		return NO_SCORE;
	unsigned long max;
	m_list.get(0, max);
	unsigned long dummy;
	for (int i = 0; i < m_list.size(); i++)
	{
		m_list.get(i, dummy);
		if (dummy > max)
			max = dummy;
	}
	return max;
}