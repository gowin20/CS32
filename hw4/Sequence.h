// Sequence.h

#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

template <typename T>
class Sequence
{
  public:
    Sequence();          // Create an empty sequence (i.e., one whose size() is 0).
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.

    int insert(int pos, const T& value);
      // Insert value into the sequence so that it becomes the item at
      // position pos.  The original item at position pos and those that
      // follow it end up at positions one higher than they were at before.
      // Return pos if 0 <= pos <= size() and the value could be
      // inserted.  (It might not be, if the sequence has a fixed capacity,
      // e.g., because it's implemented using a fixed-size array.)  Otherwise,
      // leave the sequence unchanged and return -1.  Notice that
      // if pos is equal to size(), the value is inserted at the end.

    int insert(const T& value);
      // Let p be the smallest integer such that value <= the item at
      // position p in the sequence; if no such item exists (i.e.,
      // value > all items in the sequence), let p be size().  Insert
      // value into the sequence so that it becomes the item at position
      // p.  The original item at position p and those that follow it end
      // up at positions one higher than before.  Return p if the value
      // was actually inserted.  Return -1 if the value was not inserted
      // (perhaps because the sequence has a fixed capacity and is full).

    bool erase(int pos);
      // If 0 <= pos < size(), remove the item at position pos from
      // the sequence (so that all items that followed that item end up at
      // positions one lower than they were at before), and return true.
      // Otherwise, leave the sequence unchanged and return false.

    int remove(const T& value);
      // Erase all items from the sequence that == value.  Return the
      // number of items removed (which will be 0 if no item == value).

    bool get(int pos, T& value) const;
      // If 0 <= pos < size(), copy into value the item at position pos
      // of the sequence and return true.  Otherwise, leave value unchanged
      // and return false.

    bool set(int pos, const T& value);
      // If 0 <= pos < size(), replace the item at position pos of the
      // sequence with value and return true.  Otherwise, leave the sequence
      // unchanged and return false.

    int find(const T& value) const;
      // Let p be the smallest integer such that value == the item at
      // position p in the sequence; if no such item exists, let p be -1.
      // Return p.

    void swap(Sequence& other);
      // Exchange the contents of this sequence with the other one.

      // Housekeeping functions
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs);

  private:
      // Representation:
      //   a circular doubly-linked list with a dummy node.
      //   m_head points to the dummy node.
      //   m_head->m_prev->m_next == m_head and m_head->m_next->m_prev == m_head
      //   m_size == 0  iff  m_head->m_next == m_head->m_prev == m_head
      //   if m_size > 0
      //       m_head->next points to the node at position 0.
      //       m_head->prev points to the node at position m_size-1.

    struct Node
    {
        T m_value;
        Node*    m_next;
        Node*    m_prev;
    };

    Node* m_head;
    int   m_size;

    void createEmpty();
      // Create an empty list.  (Should be called only by constructors.)

    void insertBefore(Node* p, const T& value);
      // Insert value in a new Node before Node p, incrementing m_size.

    Node* doErase(Node* p);
      // Remove the Node p, decrementing m_size.  Return the Node that
      // followed p.

    Node* nodeAtPos(int pos) const;
      // Return pointer to Node at position pos.  If pos == m_size, return
      // m_head.  (Will be called only when 0 <= pos <= size().)
};

// Template implementations

template <class T>
int Sequence<T>::size() const
{
    return m_size;
}


template <class T>
bool Sequence<T>::empty() const
{
    return size() == 0;
}

template <class T>
Sequence<T>::Sequence()
{
	createEmpty();
}

template <class T>
Sequence<T>::~Sequence()
{
	// Delete all Nodes from first non-dummy up to but not including
	// the dummy

	while (m_head->m_next != m_head)
		doErase(m_head->m_next);

	// Delete the dummy

	delete m_head;
}

template <class T>
Sequence<T>::Sequence(const Sequence& other)
{
	createEmpty();

	// Copy all non-dummy other Nodes.  (This sets m_size.)
	// Inserting each new node before the dummy node that m_head points to
	// puts the new node at the end of the list.

	for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next)
		insertBefore(m_head, p->m_value);
}

template <class T>
Sequence<T>& Sequence<T>::operator=(const Sequence& rhs)
{
	if (this != &rhs)
	{
		Sequence temp(rhs);
		swap(temp);
	}
	return *this;
}

template <class T>
int Sequence<T>::insert(int pos, const T& value)
{
	if (pos < 0 || pos > m_size)
		return -1;

	Node* p = nodeAtPos(pos);
	insertBefore(p, value);

	return pos;
}

template <class T>
int Sequence<T>::insert(const T& value)
{
	// Find the Node before which to insert
	Node* p;
	int pos;
	for (p = m_head->m_next, pos = 0; p != m_head &&
		value > p->m_value; p = p->m_next, pos++)
		;

	// Insert the value there
	insertBefore(p, value);
	return pos;
}

template <class T>
bool Sequence<T>::erase(int pos)
{
	if (pos < 0 || pos >= m_size)
		return false;

	Node* p = nodeAtPos(pos);
	doErase(p);

	return true;
}

template <class T>
int Sequence<T>::remove(const T& value)
{
	int count = 0;

	// Walk through the list, erasing matching items

	Node* p = m_head->m_next;
	while (p != m_head)
	{
		if (p->m_value == value)
		{
			count++;
			p = doErase(p); // p now points to successor of erased Node
		}
		else
			p = p->m_next;  // p now points to successor of non-erased Node
	}
	return count;
}

template <class T>
bool Sequence<T>::get(int pos, T& value) const
{
	if (pos < 0 || pos >= m_size)
		return false;

	Node* p = nodeAtPos(pos);
	value = p->m_value;

	return true;
}

template <class T>
bool Sequence<T>::set(int pos, const T& value)
{
	if (pos < 0 || pos >= m_size)
		return false;

	Node* p = nodeAtPos(pos);
	p->m_value = value;

	return true;
}

template <class T>
int Sequence<T>::find(const T& value) const
{
	// Walk through the list, keeping track of position

	int pos = 0;
	Node* p = m_head->m_next;
	for (; p != m_head && p->m_value != value; p = p->m_next, pos++)
		;
	return p == m_head ? -1 : pos;
}

template <class T>
void Sequence<T>::swap(Sequence& other)
{
	// Swap head pointers

	Node* p = other.m_head;
	other.m_head = m_head;
	m_head = p;

	// Swap sizes

	int s = other.m_size;
	other.m_size = m_size;
	m_size = s;
}

template <class T>
void Sequence<T>::createEmpty()
{
	m_size = 0;

	// Create dummy node

	m_head = new Node;
	m_head->m_next = m_head;
	m_head->m_prev = m_head;
}

template <class T>
void Sequence<T>::insertBefore(Node* p, const T& value)
{
	// Create a new node

	Node* newp = new Node;
	newp->m_value = value;

	// Insert new item before p

	newp->m_prev = p->m_prev;
	newp->m_next = p;
	newp->m_prev->m_next = newp;
	newp->m_next->m_prev = newp;

	m_size++;
}

template <class T>
typename Sequence<T>::Node* Sequence<T>::doErase(Node* p)
{
	// Save pointer to p's successor

	Node* pnext = p->m_next;

	// Unlink p from the list and destroy it

	p->m_prev->m_next = p->m_next;
	p->m_next->m_prev = p->m_prev;
	delete p;

	m_size--;

	return pnext;
}

template <class T>
typename Sequence<T>::Node* Sequence<T>::nodeAtPos(int pos) const
{
	Node* p;

	// If pos is closer to the head of the list, go forward to find it.
	// Otherwise, start from tail and go backward.

	if (pos <= m_size / 2)  // closer to head
	{
		p = m_head->m_next;
		for (int k = 0; k != pos; k++)
			p = p->m_next;
	}
	else  // closer to tail
	{
		p = m_head;
		for (int k = m_size; k != pos; k--)
			p = p->m_prev;
	}

	return p;
}

template <class T>
int subsequence(const Sequence<T>& seq1, const Sequence<T>& seq2)
{
	if (seq2.empty())
		return -1;

	// Walk through seq1

	for (int pos = 0; pos <= seq1.size() - seq2.size(); pos++)
	{
		// Assume there's a match starting at pos

		bool allMatched = true;

		// Check if all corresponding positions match

		for (int k = 0; k < seq2.size(); k++)
		{
			T v1;
			T v2;
			seq1.get(pos + k, v1);
			seq2.get(k, v2);
			if (v1 != v2)
			{
				allMatched = false;
				break;
			}
		}

		// If we never found a mismatch, we've found the match.

		if (allMatched)
			return pos;
	}

	// If we never found a match, there is none.

	return -1;
}



//implementations of non-member functions

template <class T>
void interleave(const Sequence<T>& seq1, const Sequence<T>& seq2, Sequence<T>& result)
{
	// Guard against the case that result is an alias for seq1 or seq2
	// (i.e., that result is a reference to the same sequence that seq1 or
	// seq2 refers to) by building the answer in a local variable res.  When
	// done, swap res with result; the old value of result (now in res) will
	// be destroyed when res is destroyed.

	Sequence<T> res;

	// Interleave elements until one or both sequences runs out.

	int n1 = seq1.size();
	int n2 = seq2.size();
	int nmin = (n1 < n2 ? n1 : n2);
	int resultPos = 0;
	for (int k = 0; k < nmin; k++)
	{
		T v;
		seq1.get(k, v);
		res.insert(resultPos, v);
		resultPos++;
		seq2.get(k, v);
		res.insert(resultPos, v);
		resultPos++;
	}

	// Append the remaining elements from the longer sequence.  (If the
	// sequences are the same length, this does nothing.)

	const Sequence<T>& s = (n1 > nmin ? seq1 : seq2);
	int n = (n1 > nmin ? n1 : n2);
	for (int k = nmin; k < n; k++)
	{
		T v;
		s.get(k, v);
		res.insert(resultPos, v);
		resultPos++;
	}

	result.swap(res);
}

#endif // SEQUENCE_INCLUDED
