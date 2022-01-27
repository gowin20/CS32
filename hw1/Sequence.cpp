#include "Sequence.h"

#include <array>
#include <iostream>


using namespace std;

void Sequence::dump() const
{

	//testing code
	for (int i = 0; i < m_size; i++)
	{
		cerr << m_members[i] << " ";
	}
	cerr << endl;
}

Sequence::Sequence()
{
	//m_size is the number of elements of the array
	m_size = 0;
}

bool Sequence::empty() const
{
	return (m_size == 0);
}
// Return true if the sequence is empty, otherwise false.

int Sequence::size() const
{
	return m_size;
}
// Return the number of items in the sequence.


int Sequence::insert(int pos, const ItemType& value)
{
	//can't insert if pos is outside the bounds of the array, or if the array is already full
	//inserting thing at position (pos) of the array. 
	if (pos < 0 || pos > m_size || m_size >= DEFAULT_MAX_ITEMS)
		return -1;

	for (int i = m_size; i > pos; i--)
	{
		m_members[i] = m_members[i-1];
	}
	m_members[pos] = value;
	m_size++;
	return pos;
}

int Sequence::insert(const ItemType& value)
{
	//P is the smallest integer such that value <= m_members[p]; AKA the first item on the list that is less than value.
	int p = m_size;
	
	for (int i = m_size - 1; i >= 0; i--)
	{
//don't need any special checkers or cases because we're checking from the top down, and we want the number lowest on the list
		if (value <= m_members[i])
		{
			p = i;
		}
	}

	return insert(p, value);
}

bool Sequence::erase(int pos)
{
	if (pos < 0 || pos >= m_size)
		return false;

	//decrease size by 1, then copy all the items on the list (from pos to the end) down one
	m_size--;
	for (int i = pos; i < m_size; i++)
	{
		m_members[i] = m_members[i + 1];
	}
	return true;
}

int Sequence::remove(const ItemType& value)
{
	int numRemoved = 0;

	for (int i = 0; i < m_size; i++)
	{
		if (m_members[i] == value)
		{
			erase(i);
			i--; //dial i back one to check the same position again - when items are erased, the list shifts left one, and another target could end up in the same pos
			numRemoved++;
		}
	}
	return numRemoved;
}

//retrieve the value at position 'pos' and store it in 'value'
bool Sequence::get(int pos, ItemType& value) const
{
	if (pos < 0 || pos >= m_size)
		return false;

	value = m_members[pos];
	return true;
	
}

//set value at position "pos" to "value"
bool Sequence::set(int pos, const ItemType& value)
{
	if (pos < 0 || pos >= m_size)
		return false;

	m_members[pos] = value;
	return true;
}


int Sequence::find(const ItemType& value) const
{
	int p = -1;

	for (int i = m_size - 1; i >= 0; i--)
	{
		if (m_members[i] == value)
		{
			p = i;
		}
	}

	return p;
}

void Sequence::swap(Sequence& other)
{
	int topNote = m_size;
	ItemType filler;
	if (other.m_size > m_size)
		topNote = other.m_size;

	for (int i = 0; i < topNote; i++)
	{
		//swap each item in the list
		filler = m_members[i];
		m_members[i] = other.m_members[i];
		other.m_members[i] = filler;
	}
	//swap the list sizes
	m_size += other.m_size;
	other.m_size = m_size - other.m_size;
	m_size -= other.m_size;

}
// Exchange the contents of this sequence with the other one.
