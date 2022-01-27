#include <string>
#include <iostream>
using namespace std;


bool somePredicate(string s) //predicate to check if the string has things in it. Returns true if the string is NOT empty, and false otherwise
{
	return !s.empty();
}

bool allTrue(const string a[], int n) // Return false if the somePredicate function returns false for at least one of the array elements; return true otherwise.
{
	if (!somePredicate(a[n - 1])) //if the item fails the predicate, return false
		return false;

	if ((n - 1) > 0) //if it doesn't fail and it's not the last item in the list, check the next one
		if (allTrue(a, n - 1))
			return true; //the return must be conditional on allTrue, not just after it, or the function returns true every time
}

int countFalse(const string a[], int n) // Return the number of elements in the array for which the somePredicate function returns false.
{
	int i = 0;
	if (n > 0)
	{
		if (!somePredicate(a[n - 1]))
			i += (1 + countFalse(a, n - 1));
		else
			i += (0 + countFalse(a, n - 1));
	}
	return i;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	if (n <= 0) 
		return -1;

	int x = firstFalse(a, n - 1);

	if (!somePredicate(a[n - 1]) && x == -1)
		return n - 1;
	return x;
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
	if (n <= 0)
		return -1;
	int i = 0;
	if (n - 1 > 0)
	{
		int comp = indexOfLeast(a, n - 1);
		if (a[comp] < a[n - 1])
			i = comp;
		else
			i = n - 1;
	}
	return i;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
	bool i = false;
	if (n1 > 0 && n2 > 0)
	{
		if (a1[0] == a2[0])
		{
			a2++;
			n2--;
		}
		a1++;
		n1--;
		i = includes(a1, n1, a2, n2);
	}
	if (n2 == 0)
		return true;
	else
		return i;
}
