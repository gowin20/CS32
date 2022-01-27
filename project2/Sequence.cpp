#include "Sequence.h"
#include <iostream> //don't need this in the final file

using namespace std;

Sequence::Sequence() //CONSTRUCTOR
{
	//initializing an empty sequence
	m_head = new Node; //head is a pointer to the list. In this implementation, the first actual item of the list is at location head->next (head->value is undefined, never called)
	m_size = 0; //used to easily track list size, lets size() return faster and makes for simple 'for' loops
}

Sequence::~Sequence() //DESTRUCTOR
{
	Node* ref = m_head;
	for (int i = 0; i < m_size; i++)
	{
		//deletes everything except the final node
		ref = ref->next;
		delete ref->prev;
	}
	delete ref; //delete the final node
}

Sequence::Sequence(const Sequence& original) //COPY CONSTRUCTOR
{
	if (original.empty())
		return;

	//copying values of private member variables
	m_size = original.m_size;
	m_head = new Node;
	
	//pointers used to index the linked lists
	Node* thisSeq = m_head;
	Node* origP = original.m_head;

	for (int i = 0; i < m_size; i++)
	{
		thisSeq->next = new Node; //allocating new memory space and connecting the next
		thisSeq->next->value = origP->next->value; //copying values over
		thisSeq->next->prev = thisSeq; //connecting the prev
		//cycling the lists
		thisSeq = thisSeq->next; 
		origP = origP->next;
	}
}

Sequence& Sequence::operator=(const Sequence &rhs) //ASSIGNMENT OPERATOR
{
	if (this != &rhs)
	{
		Sequence temp(rhs); //calls the copy constructor to make a sequence with the same values as rhs, within the scope of the assignment operator
		swap(temp); //swaps with the temp sequence. temp is deallocated once the function finishes
	}
	return *this;
}

bool Sequence::empty() const // Return true if the sequence is empty, otherwise false.
{
	if (m_size == 0)
		return true;
	return false;
}

int Sequence::size() const // Return the number of items in the sequence.
{
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value) //inserts value at position 'pos' in the list, moving what was at 'pos' previously and everything above it up one
{
	if (pos < 0 || pos > m_size) //error catching
		return -1;

	Node* p = m_head; //used to cycle through the list
	
	Node* newValue = new Node; //the value we're inserting
	newValue->value = value;

	for (int i = 0; i <= m_size; i++) //should ALWAYS insert something into the list
	{

		if (i == m_size) //adding something to the end of the list requires a special case
		{
			newValue->next = nullptr; //points to NOTHING
			newValue->prev = p;
			p->next = newValue;
			break;
		}
		else if (i == pos) //adding something within the list. this will never be called when something is added to the end
		{
			newValue->next = p->next; //adjusting pointers
			newValue->prev = p;
			p->next->prev = newValue;
			p->next = newValue;
			break;
		}
		p = p->next;
	}

	m_size++; //gotta increase the size of the list too
	return pos;
}

int Sequence::insert(const ItemType& value) //inserts 'value' into the list before the first value that is greater than it (if there are no items >= value, it goes at the end)
{
	
	int p = m_size;
	Node* ref = m_head; //head reference for cycling

	for (int i = 0; i < m_size; i++) //cycling through the list, i used to denote position
	{
		ref = ref->next; //value moves forward before the rest of the loop. works out so when i = 0, ref points to the item at position 0 in the list
		if (value <= ref->value)
		{
			p = i; //if the ref->value is greater than or equal to the value we're inserting, insert before ref
			break;
		}
	}
	return insert(p, value);

}

bool Sequence::erase(int pos) //erases the item at position 'pos' from the list
{
	if (pos < 0 || pos >= m_size) //boundary handler
		return false;

	Node* ref = m_head;
	for (int i = 0; i < m_size; i++) //cycling through the list, i used to denote position
	{
		ref = ref->next;
		if (pos == i) //if the value is found
		{
			ref->prev->next = ref->next; //make the previous pointer point to the next one - skip over this one
			if (ref->next != nullptr)
				ref->next->prev = ref->prev; //make the next pointer point to this one's previous, assuming the next one exists
			
			delete ref;
			m_size--; //adjust size accordingly
			return true;
		}
	}
	return false; //reaches here on empty lists
}

int Sequence::remove(const ItemType& value) //removes all instances of 'value' from the list
{
	int numremoved = 0;

	Node* ref = m_head;
	for (int i = 0; i < m_size; i++) //cycling through the list, i used to denote position
	{
		if (ref->next->value == value) //if it finds a value
		{
			erase(i);
			numremoved++;
			i--; //moves the counter back one to check the same location again - lets it catch cases where there're 2 of the desired value in a row
		}
		else //if it doesn't find a value, move to the next value in the list. Only moves when a value is not found because of ^
		{
			ref = ref->next;
		}		
	}
	return numremoved;
}

bool Sequence::get(int pos, ItemType& value) const //finds the value of the item at position 'pos' and copies it into value
{
	if (pos < 0 || pos >= m_size)
		return false;
	
	Node* ref = m_head;
	for (int i = 0; i < m_size; i++) //cycling through the list, i used to denote position
	{
		ref = ref->next;
		if (i == pos)
		{
			value = ref->value; //copy the value at position 'pos' into 'value'
			return true;
		}
	}
	return false; //shouldn't ever reach here
}

bool Sequence::set(int pos, const ItemType& value) //basically exactly the same as Sequence::get, with one line changed to set values instead of retrieve
{
	if (pos < 0 || pos >= m_size)
		return false;
	
	Node* ref = m_head;
	for (int i = 0; i < m_size; i++) //cycling through the list, i used to denote position
	{
		ref = ref->next;
		if (i == pos)
		{
			ref->value = value; //set the value at position 'pos' to 'value'
			return true;
		}
	}
	return false; //shouldn't ever reach here
}


int Sequence::find(const ItemType& value) const //returns the smallest value p such that p is equal to the location of 'value' in the sequence. if 'value' isn't found, -1 is returned.
{
	int p = -1;

	Node* ref = m_head;
	for (int i = 0; i < m_size; i++)
	{
		ref = ref->next;
		if (ref->value == value)
		{
			p = i; //sets p to the location of the value
			return p; //returns sooner if found
		}
	}
	return p;
}

void Sequence::swap(Sequence& other) // Exchange the contents of this sequence with the other one.
{
	//swap the heads of the list
	Node* temp = other.m_head;
	other.m_head = m_head;
	m_head = temp;
	
	//swap the other member variable
	int tempsize = other.m_size;
	other.m_size = m_size;
	m_size = tempsize;
}

void Sequence::dump() //function used for debugging purposes
{
	if (empty())
		return;
	cerr << "List is size: " << size() << endl;
	Node *p = m_head->next;
	for (int i = 0; i < m_size; i++)
	{
		cerr << p->value << " ";

		if (p->next != nullptr)
			p = p->next;
	}
	cerr << endl;
}


//	=======================================
//	=		  NON-MEMBER FUNCTIONS		  =
//	=======================================

int subsequence(const Sequence& seq1, const Sequence& seq2) 	//if seq2 is a consecutive subsequence of seq1, the function returns the earliest place in seq1 where that subsequence starts
{
	int location = -1;
	ItemType checkertwo;	//variables used to check values in the array
	ItemType checker;

	for (int i = 0; i < seq1.size(); i++) //run through every element of the larger sequence
	{
		for (int j = 0; j < seq2.size(); j++) //check it against the smaller sequence. unless the first values are equal, this will only run once
		{
			seq1.get(i + j, checker); //comparing the values in the sequences
			seq2.get(j, checkertwo);
			//cerr << "values: Sequence 1 is " << checker << " and Sequence 2 is " << checkertwo << endl;
			if (checker == checkertwo) 
			{
				if (j == (seq2.size() - 1))
				{
					location = i;
					return location; //return here so it gives the earliest place in seq1 (and runs faster)
				}
				continue;
			}
			break;
		}
	}
	return location;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) //produces a sequence that consists of the first item in seq1, then the first in seq2, then the second in seq1, then the second in seq2, etc.
{
	Sequence temp; //temp sequence to make the list
	ItemType value;

	int largersize = seq2.size();
	if (seq1.size() > seq2.size()) //determine which sequence is longer
		largersize = seq1.size();

	for (int i = (largersize - 1); i >= 0; i--) //run through the entire larger sequence, starting from the top
	{
		if (seq2.get(i, value)) //if there's a value there, copy it in -> if not, nothing happens
			temp.insert(0, value);
		if (seq1.get(i, value))
			temp.insert(0, value);
	}
	result = temp; //set result to the new list, removing any previous values
}