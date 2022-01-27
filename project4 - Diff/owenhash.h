#ifndef OWEN_H
#define OWEN_H

#include <string>
#include <list>
#include <iostream> //only declared for debug hash function
#include <fstream>
using namespace std;


const int N = 8;


struct Node
{
	string value;
	int offset;

	Node(string v, int o) : value(v), offset(o) {}
};

//my implementation of a hashmap
class Hash
{
private:
	int BUCKET;



public:
	//this probably isn't good practice in gneral, but works exceedingly well for this project
	list<Node> *table;

	// Constructor 
	Hash(int b) : BUCKET(b) { table = new list<Node>[BUCKET]; }


	~Hash() { delete[] table; }


	unsigned int hashFunction(Node item) //node-parameter overload of hashFunction
	{
		string word = item.value;
		return hashFunction(word);
	}

	unsigned int hashFunction(string word)  //the location of items in the string is dependent on the STRING in the node - not the offset. Makes searching faster
	{
		int sum = 0;
		for (unsigned int k = 0; k < word.length(); k++)
			sum = sum + int(word[k]);
		return  sum % BUCKET;
	}

	// insert a key into hash table 
	void insertItem(Node key)
	{
		int index = hashFunction(key);
		string value = key.value;
		table[index].push_back(key);
	}

	int checkValue(string val) //1-argument overload of checkValue
	{
		int index = hashFunction(val);

		return checkValue(val, index);
	}


	//not strictly necessary in this project - use hashindex in the main function and search through the linkedlist there
	int checkValue(string val, int index) //looks for a value in the table, and returns the offset if found. Otherwise, returns -1
	{
		list<Node>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++) {
			if (i->value == val)
				break;
		}

		// if key is found in hash table, remove it 
		if (i != table[index].end())
			return (i->offset - val.length());
		else
			return -1;
	}

	string getValue(string val, int length) //returns the first 'length' characters of a node
	{
		if (length > N)
			return "that aint it chief";
	}

	//function that returns an item at a given offset. returns subsections of items if the offset specified is not the beginning of the entry
	string atOffset(int off, int length)
	{
		int index = ((off / N) % N); //find the bucket containing the item at offset 'off'

		//depth in the hash is dependent on N^2
		int depth = off / (N * N);

		list<Node>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			if (depth == 0)
				break;
			else
				depth--;
		}
		if (depth > 0)
		{
			//some fucky stuff went on here. I don't think this is even possible to reach
		}
		string item = i->value;
		
		if (length != N)
			return item.substr(0, length);
		else
			return item;
	}

	//function to print the hash, for debugging purposes
	void dumpHash()
	{
		for (int i = 0; i < BUCKET; i++) 
		{
			cerr << i;
			for (auto x : table[i])
				cerr << " --> " << x.value;
			cerr << endl;
		}
	}
};

/*

// deletes a key from hash table
void deleteItem(string key)
{
	// get the hash index of key
	int index = findIndex(key);

	index = (index / N) % N;

	// find the key in (inex)th list
	list <string> ::iterator i;
	for (i = table[index].begin(); i != table[index].end(); i++)
	{
		if (*i == key)
			break;
	}

	// if key is found in hash table, remove it
	if (i != table[index].end())
		table[index].erase(i);
}

void voidItem(string key)
{
	// get the hash index of key
	int index = findIndex(key);

	index = (index / N) % N;

	// find the key in (inex)th list
	list <string> ::iterator i;
	for (i = table[index].begin(); i != table[index].end(); i++)
	{
		if (*i == key)
			break;
	}

	// if key is found in hash table, remove it
	if (i != table[index].end())
		*i = ")(;|^&G7";

}


*/

//Declarations of non-member functions

void createDiff(istream& fold, istream& fnew, ostream& fdiff);

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);


#endif // !OWEN_H