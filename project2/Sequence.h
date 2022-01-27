#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>

using ItemType = std::string;


class Sequence
{
public:
	void dump(); //used for debugging
	~Sequence();//DESTRUCTOR
	Sequence(const Sequence& original); //COPY CONSTRUCTOR
	Sequence& operator=(const Sequence &rhs); //ASSIGNMENT OPERATOR
	Sequence(); //CONSTRUCTOR
	bool empty() const;
	int size() const;
	int insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);

private:
	struct Node
	{
		ItemType value;
		Node *next;
		Node *prev;
	};
	Node* m_head; //head does not point to a value of the array. the first value is at m_head->next
	int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif // SEQUECNE_H
