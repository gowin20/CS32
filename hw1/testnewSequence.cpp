#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Sequence a(1000);   // a can hold at most 1000 items
	Sequence b(5);      // b can hold at most 5 items
	Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
	ItemType v = 45;
	// No failures inserting 5 items into b
	for (int k = 0; k < 5; k++)
		assert(b.insert(v) != -1);

	assert(b.erase(3));

	assert(b.insert(4) == 0);

	assert(b.find(v) == 1);
	assert(b.find(1) == -1);

	ItemType value = 0;
	assert(b.get(3, value));
	assert(b.insert(2, v) == -1);
	assert(!b.empty());


	// When two Sequences' contents are swapped, their capacities are
	// swapped as well:
	a.swap(b);
	assert(a.insert(v) == -1 && b.insert(v) != -1);
	assert(a.insert(5, v) == -1);

	assert(a.set(1, 20));
	a.dump();
	b = a;
}