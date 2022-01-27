#include "owenhash.h"




/*

offset of 8


hash table


Read in the entire contents of the old file into a string. Read the entire contents of the new file into another string.
For all consecutive N-character sequences in the old file's string, insert that N-character sequence and the offset F where it was found in the old file's string, 
into a table (e.g. hash table or binary search tree). You might use 8 for N, or maybe 16.
Once you have filled up your table with all N-byte sequences from the source file, start processing the new file's string, starting from offset j=0, until j reaches the end of the string.
	Look up the N-byte sequence which starts at offset j ([j,j+N-1]) in the new file's string in the table you created from the old file's string.
	If you find this sequence in the table, you know that that sequence is present in both the old and new versions of the file.
		Determine how long the match goes on (it might be just N bytes long, or it might extend past the first N matching bytes to be many bytes longer).
		Once you have determined how long the match is (call this L), write a Copy instruction to the diff file to copy L bytes from offset F from the source file.
		Go back to step 3a, continuing at offset j = j + L in the new file's string.
	If you don't find the current sequence (new file's string [j,j+N-1]) in the table you created, you know that the first version of the file doesn't contain the current N byte sequence.
		Write an instruction to the diff file to Add the current character.
		Increment j by one to continue past the character used in the add instruction.
		Go back to step 3a, where we'll try to find the next N-byte sequence in our table.

*/

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
	if (!fold || !fnew)		        // Did opening the file fail?
	{
		cerr << "Error: Cannot open one or more source files!" << endl;
		return;
	}

	// Read the contents of the old file into oldContents
	std::string s;
	string oldContents;
	string newContents;
	while (getline(fold, s))
	{
		oldContents += s;
		oldContents += '\n';
	}
	while (getline(fnew, s))
	{
		newContents += s;
		newContents += '\n';
	}



	//Put the contents of oldContents into a hash map

	int max = oldContents.length();
	int numofBuckets = N*10; // this hash map uses buckets in multiples of 8. Once you reach an offset > numofbuckets * 8, it wraps back around to the first bucket

	Hash map(numofBuckets);
	{
		int length = 0;

		for (int i = 0; i < max; i++) //loop to insert all segments of old file into various buckets of the hash map
		{

			if (length == N || i == (max - 1))
			{
				//get the next sequence of eight chars
				int copylength = i == (max - 1) ? length + 1 : length; //exception handler to add the last character of the string to the array
				string section = oldContents.substr((i - length), copylength);

				//insert that sequence into the hashmap
				//int bucketindex = ((i - 1) / numofBuckets) % numofBuckets;
				
				Node value(section, i);
				
				map.insertItem(value);

				length = 0;
			}
			length++;
		}
	}

	//map.dumpHash();


	//create the diff file, based on the hash map and newfile string
	int newLength = newContents.length();
	int iter = 0;

	//counter to see how long the length is
	//if a match is found initially, set it to 8 and move down one. this probably has to be self-contained in its own loop within the loop.
	//iterate length by one for each subsequent matching string.

	string toAdd = ""; //keeps track of how many characters it's been since a copy was found. This is what you need to add.

	while (iter < newLength)
	{
		int copylength = (iter + N) > newLength ? newLength - iter : N;
		string section = newContents.substr(iter, copylength);
		
		
		
		
		int location = map.checkValue(section);
		
		
		
		
		if (location != -1) //if this is true, that means the section of N bytes was found in both old and new
		{
			//when you find a copy, add all the characters that need to be added
																	//	cout << endl;
			if (!toAdd.empty())
			{
				fdiff << 'A' << toAdd.length() << ':' << toAdd;
				toAdd = "";
			}
			//write a copy instruction
			
			int matchlength = N;
																	//cout << "initial match found: " << section << ", with length of " << matchlength << endl;
			iter += N; //advance iter past what we just looked at

			//----------------------------------------
			//find out how long the match goes on for
			//----------------------------------------
			int checkSize = N;
			while (checkSize > 0 && iter < newLength) //checking further in the hash table, initially in segments of N
			{
				section = newContents.substr(iter, checkSize);
				string match = oldContents.substr(location + matchlength, checkSize);
				if (match == section)
				{
					iter += checkSize;
					matchlength += checkSize;
					if (checkSize == N)
						continue; //if the segment matches completely, keep check the next complete sequence
					else
						break;
				}
				else  //once a non-matching setment is found, check subsequently smaller sections until a copy is found
				{
					checkSize--;
				}
			}
			//match length determined at this point
			// cout << "Found a match this long: " << matchlength << endl;
			
			fdiff << 'C' << matchlength << ',' << location; //write the complete copy instruction to the diff file			
		}
		else
		{
			toAdd += newContents[iter];
			iter++;
																		//		cout << "toAdd is " << toAdd << endl;
		}

		//probably want to delete an item once it's found in the hashmap
		//function that finds a string and returns its key, or -1 if it's not found

	}
	
	//add any remaining characters in another instruction
	if (!toAdd.empty())
		fdiff << 'A' << toAdd.length() << ':' << toAdd;



	//go down and compare each character to chars of the substrings in the buckets
	//you need to compare each section of the new file to ALL of the substrings in the buckets
	//copy the number of characters that match the most.
	//if there's multiple exact matches, it shouldn't matter

	//need to keep it chronological - how?
		//probably need the hashmap to be temporally ordered :(
	//newlines == next bucket?
	
	//map.dumpHash();

	return;
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
	
	//read files into strings
	if (!fold || !fdiff)
	{
		cerr << "Error opening one or more files!" << endl;
		return false;
	}
	string oldContents;
	string diffContents;
	string temp;
	while (getline(fold, temp))
	{
		oldContents += temp;
		oldContents += '\n';
	}
	oldContents.pop_back();
	while (getline(fdiff, temp))
	{
		diffContents += temp;
		diffContents += '\n';
	}
	diffContents.pop_back();

	int diffSize = diffContents.length();

	int i = 0;
	
	while (i < diffSize)
	{
		switch (diffContents[i])
		{
		case 'A':
		{
			//cout << "Time to add characters: ";

			++i;
			string numberString = "";
			while (isdigit(diffContents[i]))
			{
				numberString += diffContents[i];
				++i;
			}
			if (diffContents[i] != ':' || numberString == "") //check to make sure the add statement is formatted properly
				return false;
			
			int charsLeft = std::stoi(numberString); //charsLeft is now the amount of characters to add to the new file
																	//cout << charsLeft << endl;
			++i; //move past the ':'

			string newChars = diffContents.substr(i, charsLeft); //get all the characters to insert
			fnew << newChars; //insert them into the new file!
			i += charsLeft; //sequence down in the file that many characters, as you just looked at all of em
			break;
		}
			

		case 'C':
		{
			//cout << "Time to copy characters from offset: ";
			++i;
			string numberString = "";
			while (isdigit(diffContents[i]))
			{
				numberString += diffContents[i];
				++i;
			}
			if (diffContents[i] != ',' || numberString == "") //make sure the comma is present and there were numbers to read
				return false;
			
			int numOfChars = std::stoi(numberString);
																	//cout << numOfChars << endl;
			++i; //move past the comma

			numberString = "";

			while (isdigit(diffContents[i]))
			{
				numberString += diffContents[i];
				++i;
			}
			if (numberString == "")
				return false;

			int offset = std::stoi(numberString);

			//cout << "copying this many characters: " << numOfChars << ". They are: ";


			string copyChars = oldContents.substr(offset, numOfChars);

			//cout << copyChars << endl;

			fnew << copyChars;
			//don't need to increase the iterator any more, as copy instructions are short
			break;
		}


		case '\n':
		case '\r':
		{
			++i;
			continue;
			break;
		}
		
		default:
			return false;
		}

	}



	return true;
}


