struct Target
{
//the things within the struct that are accessible to the public. That means the only way to modify things about target is by calling these interfaces/functions
public:
	Target(); //Constructor: automatically called every time a target is initialized, named after the struct
	void move(char dir);
	int position() const;
	void replayHistory() const;

//inaccessible to the public. Can't be modified by calling it.
//data members should always be private
private:
	//innvariant: 
		// history consists only of Rs and Ls
		// pos == number of Rs in history minus the number of Ls in history
	int pos;
	string history;
};
//any instance of a variable being called with this-> in these functions could be replaced by simply calling the variable without it, ex. this->pos == pos

Target::Target()
{
	this->pos = 0;
	this->history = "";
}

//Code to move a target around within a video game. The target is defined as a data type and this fcn is only specifically for targets.
bool Target::move(char dir)
{
	switch (dir)
	{
		case 'R':
		case 'r':
			this->pos++;
			break;
		case 'L':
		case 'l':
			this->pos--;
			break;
		default:
			return false;
	}
	this->history += toupper(dir);
	return true;
}



int Target::position() const
{
	return this->pos;
}

void Target::replayHistory() const
{
	for (int k = 0; k != this->history.size(); k++)
		cout << this->history[k] << endl;
}


void repeatMove(Target& x, char dir, int nTimes)
{
	for (int k = 0; k < nTimes; k++)
		x.move(dir);
}


int main()
{
	Target t;
	
	t.move('R');
	
	Target t2:
	t2.init();
	
	t2.replayHistory();
	
	char ch;
//	...read a char into ch...
	if (! t.move(ch))
		//...problem...

	
//	t.pos++;
	t.history += 'R';
}


void f()
{
	while (...)
		playGame();
}

void playGame()
{
	//built-in types are left uninitialized. creating objs specific class is expensive, but creating pointers to them is c h e a p
	Target* targets[1000];
	//process called a garbage collector gets rid of variables once the function/program/whatever it's in the scope of completes execution
	
	int nTargets = 0;
	...
	if (...)
		addTargets(targets, nTargets, 3);
	...
	int i;
	..... //something gives t a value
	targets[i]->move('R');
	..
	//delete gets rid of the pointer to the variable, basically deallocates the storage so it can be used by other stuff.
	delete targets[1];
	targets[1] = targets[2];
	nTargets--;
	targets[2] = nullptr; // unneccessary bc it's probably never gonna be a problem but it's "comforting to some"	
	
}
	
void addTargets(Target* ta[], int& nt, int howManyOnes)
{
	for (int k = 0; k < howManyOnes; k++)
	{
		//when you declare a named local variable, it only exists in the scope of the fcn. However, if you allocate storage with new, it doesn't go away when u leave the fcn.
		ta[nt] = new Target;
		nt++;
	}
}
	
class Person
{
	public:
		Person(string nm, int by);
		string name() const;
	private:
		string m_name;
		int m_birthyear;
		//common naming conventions: name_ trailing underscore. m_ for data members
};

string Person::name() const
{
	return m_name;
}

Person::Person(string nm, int by)
{
	m_name = nm;
	m_birthYear = by;
}
	
Person p("Fred", 1999);

cool door idea: all 3 of our names in a bunch of different languages