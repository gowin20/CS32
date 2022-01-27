
#include "Sequence.h"
#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	ScoreList math;
	math.add(96);
	math.add(56);
	math.add(4);
	math.add(56);
	math.add(2);
	cout << "the maximum is: " << math.maximum() << endl;

	math.remove(96);

	cout << "the maximum is: " << math.maximum() << endl;

}