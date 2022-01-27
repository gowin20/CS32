CS32 NOTES

---------------------
Scheduling stuff

Course Website:
	http://cs.ucla.edu/classes/spring19/cs32/
	
Midterms: 
	Thurs, April 25
	Thurs, May 23
Final: 
	Sat, Jun 8
---------------------
Looking at:
	Fancier data structures
	More language features of C++

	
	
	

	use '\n', NOT '/n' - '/n' is out of date and can cause compiling errors
---------------------

#include <iostream>
#include <cstdlib> //declares the exit() function, which causes the program to terminate 
using namespace std; //all basic functions in c++ have the std:: header before them, this presumes that (ofc)

const double PI = 4 * atan(1.0);

class Circle
{
	public:
		Circle(double x, double y, double r);
		void scale(double factor);
		void draw() const;
		double radius() const;
		
	private:	
			//Class invariant:
			//		m_r > 0
		double m_x; 
		double m_y;
		double m_r;
};

double area(const Circle& x); //x is another name for the circle, and the circle will not change. 
//saying Circle x and const Circle& x are the same in that they will not modify the thing being passed to the function. "Circle x" creates
// a copy, while "const Circle& x" passes the actual object, but promises not to modify it. 

Circle::Circle(double x, double y, double r)
{
	if (r <= 0)
	{
		cerr << "Cannot create a circle with radius " << r << endl;
		exit(1);
	}
		m_x = x;
		m_y = y;
		m_r = r;
}
bool Circle::scale(double factor)
{
	if (factor <= 0)
		return false;
	m_r *= factor;
	return true;
}

double Circle::radius() const
{
	return m_r;
}

double area(const Circle& x)
{
	return PI * x.m_r * x.m_r;
}

int main()
{
	Circle blah(8, -3, 2.7)
	Circle c(-2, 5, 10);
	c.scale(2);
	c.draw();
	cout << area(c);
	cout << c.m_r;
	
	double x;
	cin >> x;
	if ( ! c.scale(x))
		exit(1);
}

=============================================
Creating a program with multiple source files
=============================================

Point.h
=========
class Point
{
	.....
};

Circle.h
=========
#include "Point.h"
class Circle
{
	...
	Point m_center;
	double m_radius
};


myapp.cpp
=========
#include "Circle.h"
#include "Point.h"

int main()
{
	Circle c;
	Point p;
}

//all the files included are linked together to make one executable
//tool that does this is called the LINKER
//benefit of splitting files:
//--easier to manage
//--CPP only needs to recompile files you're modifying. This means things compile way faster

class and struct ==== EXACTLY THE SAME THING IN C++
NOT the case in C#

if you use struct, it acts as if you started off saying public
if you use class, it acts as if you started off saying private

Class: generally used for more interesting things, as opposed to
struct: generally used for a simple collection of data

//should strive to have good standards for your programs
---------------------------------------------
Student.h
=========

#ifndef STUDENT_INCLUDED //this is an include guard. it prevents your program from including the header file multiple times
#define STUDENT_INCLUDED 	//-- if it hasn't been included (not defined), include and define it
#include "Course.h" //course.h also includes student.h -- this creates a CIRCULAR DEPENDENCY and breaks ya shit

class Student
{
	void enroll(Course* cp);
	...
	Course* m_studylist[10]
};

#endif // STUDENT_INCLUDED

Course.h
=========
#ifndef COURSE_INCLUDED
#define COURSE_INCLUDED
//#include "Student.h" <- don't do this
class student; //instead, have an empty declaration at the start of the function. This way, the compiler knows student is a class it can create objects with, but doesn't cause a circular spiral of death

class Course
{
	...
	Student* m_roster[100]
};

#endif // COURSE_INCLUDED

//If the file Foo.h defines the class Foo, when does another file require you to say 
#include "Foo.h"
//and when can you instead simply provide the incomplete type declaration
class Foo; 
//?

//You have to #include the header file defining a class whenever you:
	**Declare a data member of that class type
	**Declare a container (like a vector) of objects of that class type
	**Create an object of that class type
	**Use a member of that class type

class Blah
{
    ...
    void g(Foo f, Foo& fr, Foo* fp);  // just need to say   class Foo;
    ...
    Foo* m_fp;           // just need to say   class Foo; - because it's a pointer to the obj and not an actual obj
    Foo* m_fpa[10];      // just need to say   class Foo;
    vector<Foo*> m_fpv;  // just need to say   class Foo;
    Foo m_f;             // must #include Foo.h
    Foo m_fa[10];        // must #include Foo.h
    vector<Foo> m_fv;    // must #include Foo.h
};

void Blah::g(Foo f, Foo& fr, Foo* fp)
{
    Foo f2(10, 20);      // must #include Foo.h
    f.gleep();           // must #include Foo.h
    fr.gleep();          // must #include Foo.h
    fp->gleep();         // must #include Foo.h
}

=============================================
Steps of Constructing a Class/Struct Object:
=============================================

1. Construct the base part
2. Construct the data members, using the member initialization list; if a member is not listed these apply:
	* If a data member is a built-in type, it's left uninitialized
	* If a data member is of a class type, the default constructor is called for it
3. Execute the body of the constructor

struct Employee
{
	string name;
	double salary;
	int age;
};

Employee e; //Constructor for employee gets called when you run this

//there's no constructor for employee?
//if you declare no constructors for a class, the compiler writes a default(zero-argument) constructor for you.
//It looks like this:
Employee::Employee()
{}
======
class Circle
{
  public:
    Circle(double x, double y, double r);
      // no other Circle constructors are declared, so there's no default
      // constructor
    ...
  private:
    double m_x;
    double m_y;
    double m_r;
};

Circle::Circle(double x, double y, double r)
 : m_x(x), m_y(y), m_r(r)
{
    if (r <= 0)
    {
        ... write some error message ...
        exit(1);
    }
}

//Let's make a stick figure

class StickFigure
{
	public:
		StickFigure(double bl, double headDiameter, string nm, double hx, double hy);
		...
	private:
	string m_name;
	Circle m_head;
	double m_bodyLength;
}

StickFigure::StickFigure(double bl, double headDiameter, string nm, double hx, double hy)
{
	if (bl <= 0)
	{
		cerr << "hes too smol" << endl;
		exit(1);
	}
	m_name = mn;
	m_head = Circle(hx, hy, headDiameter/2);
	m_bodyLength = bl;
}

data members are destroyed in the opposite order in which they're constructed



====================
Resource Management
====================
//let's make a string object
class String
{
	public:
		String(const char* value); //default constructor
		~String(); //destructor
		String(const String& other); //copy constructor - called when creating a new string that's a copy of an existing string
		String& operator=(const String& rhs); //assignmnet operator - called when setting a string equal to another
		...
	private:
		//class invariant
		//	m_text points to a dynamically allocated array of m_len+1 chars
		//	m_len > 0
		//	m_text[m_len] == '\0'
		char* m_text;
		int m_len;	
}
//All strings have a pointer to a dynamically allocated array

String::String(const char* value) //default constructor 
{
	if (value == nullptr)
		value = "";
	m_len = strlen(value);
	m_text = value;
	strcpy(m_text, value);
}

String::~String() //destructor
{
	delete [] m_text;
}

String::String(const String& other) //copy constructor
{
	m_len = other.m_len;
	m_text = new char[m_len+1];
	strcpy(m_text, other.m_text);
}

String String::operator=(const String& rhs) //assignment operator
{
	delete [] m_text;
	m_len = rhs.m_len;
	m_text new char[m_len+1];
	strcpy(m_text, rhs.m_text);
	return *this;
}

//don't have to give a function all of its arguments every time: if you don't want to, you can assign default values to them in the function declaration

void mwah(int a, int b = 42, int c = 20)
mwah(10, 20, 30);
mwah(10, 39); //c is 20
mwah(10); //b is 42 and c is 20
//once you assign a default value to a parameter, all parameters afterwards have to have one as well! how would you call the function w/ them otherwise? (you can't)


//if you allocate a single object with new, you must use the single form of delete
	p = new blah;
	delete p;
//if you allocate an array of objects instead, you have to use the array form
	p = new blah[10];
	delete [] p;

//initialization != assignment

//initialization (copy constructor is called)
	string s("Hello");
	string s2(s);
	string s3 = s //this is the COPY CONSTRUCTOR
//assignment (assignment operator is called)
	s2 = s;
	
//RAII: /resource acquisition is initialization

====================
	Linked Lists
====================

//4 types of data structures we've learned so far
	:/Fixed-Size Array 
	:/Dynamically Allocated Array
	:/Resizeable array
	:/Linked List

Arrays: data structure w/ a collection of similar type data element
Linked Lists: data structure w/ a collection of unordered linked elements, aka nodes
	
//ADVANTAGES OF LINKED LISTS
	Linked Lists make it much easier to insert things into arrays/lists. Arrays have to shift all the objects down/deal with them in some way, but linked lists ya kinda just stick em in:
		-add an item
		-adjust some pointers
	Removing things from a linked lists: 
		-adjust the pointers
		-delete the node

//DISADVANTAGE OF LINKED LISTS:
	Don't have immediate access to an arbitrary element of the list. The only way to get to an item is to follow the chain of pointers.

	
struct Node //nodes form the building blocks of linked lists
{
	int data; //values of the list are stored in this->data
	Node* next; //the definition for Node contains a pointer to a node
}
Node* head; //the head of the linked list. This can act as a dummy node or the actual first element

//Linked List Advice
	-draw pictures!
	-set a node's pointer members before changing other pointers
	-order matters
	-any time you write p->, make sure:
		--p has previously been given a value
		--p is not nullptr

class LinkedList //a sample linked list
{
public:
	LinkedList();
	void addToFront(string v);
	void addToRear(string v);
	void deleteItem(string v);
	bool findItem(string v);
	void printItems();
	~LinkedList();	
private:
	Node* head;
	struct Node //nodes can act as a private member struct
	{
		string value;
		Node *next;
		Node *prev;
	}
}

//allocating new nodes
	Node *p = new Node;
	Node *q = new Node;

//change/access node p's value
	p->value = "blah";
	cout << p->value;

//make p link to another node at address q
	p->next = q;

//get the address of the node after p
	Node *r = p->next

//make node q a terminal node
	q->next = nullptr;

delete p;
delete q;

void deleteItem(string v) //function to delete an arbitrary element of a singly linked list
{
	Node *p = head;
	while (p != nullptr)
	{
		if (p->next != nullptr && p->next->value == v)
			break; //if you find the value, break - p points to the node above
		
		p = p->next; //don't find the value, go down one
	}
	if (p != nullptr) //when you find the value, delete it
	{
		Node *killMe = p->next;
		p->next = killMe->next;
		delete killMe;
	}
}

bool search(Node* head, string v) //function to find a string in a singly linked list
{
	for (node *p = head; p != nullptr; p = p->next)
	{
		if (p->value == v)
			return true;
	}
	return false;
}

:/Doubly linked list:
	//the next + previous pointers contained in each nodes
	//this->next points to the next item, this->prev points to the previous item
:/Circular doubly linked list
	//same as a DLL, but the last node in the array points to the first one.

:/Dummy Node == the first node
	//value isn't part of the list, and it's not initialized
	//first item of the list is at head->m_next;, last one's at head->m_prev

int cmpr(Node* head, int* arr, int arr_size) //function to compare an array and linked list and return the number of consecutive elements they share
{
	Node* p = head->next;	
	for (int sim = 0; sim < arr_size; sim++)
	{
		if ((p->value == nullptr) || (arr[sim] != p->value))
			break;
		p = p->next;
	}
	return sim - 1;
}


//Places to check behavior:
	typical situation (activity in middle)
	at the head
	at the tail
	empty list
	1-element list

	
	
	
	
	
	
	
====================
		STACKS
==================== //all interfaces allow these interactions with stacks:
	create an empty stack
	push an item onto the stack //items are always added to and removed from the TOP of the stack
	pop an item off the stack
	look at the top item of the stack
	is the stack empty?
------ //some interfaces let you do these:
	how many items are on the stack?
	look at any item on the stack
	
#include <stack>
using namespace std;

int main()
{
	stack<int> s;
	s.push(10);
	s.push(20);
	if (!s.empty())
		cout << s.size(); //size is 2
	s.pop(); //pop an item off the top
	int n = s.top(); //n is the top item on the stack, which is 10 here
	
}

QUEUES //like a stack but backwards
=========== //all interfaces allow these interactions with queues
	create an empty queue
	enqueue an item onto the queue //items are always added to and removed from the BACK of the queue
	dequeue an item from the queue
	look at the front item of the queue
	is the queue empty?
	------ //some interfaces let you do these
	how many items are in the queue?
	look at the back item of the queue
	look at any item in the queue

	
	
====================
Notations
====================
prefix notation:
f(x,y,z)
add(sub(8, div(6,2), 1) //also works: add sub 8 div 6 2 1		also works:	+ - 8 / 6 2 1

infix notation:	
8-6/2+1  //the same thing as the line above, can be more confusing for a human to parse sometimes?

postfix notation:
8 6 2 / - 1 +	//once again, the same thing
((8 (6 2 /) -) 1 +) //the associated groupings.
//Postfix notation doesn't need any additional specificity. To the computer, it's always unambiguous what it operates on
//postfix is actually easier to process than prefix/infix notation, runs faster than both. Common expression evaluation: given something in infix, translate it to postfix, then it's easy to evaluate
		
8 6 2 / - 1 +
//	evaluating a postfix sequence: (pseudocode)
	
	operand stack
	run through the postfix expression:
		when you encounter a number: push it onto the stack
		when you encounter an operand: pop off the top two numbers, run the expression, push the result back onto the stack
	if this is a valid postfix expression, the stack will have exactly one value on it (the value of the expression)
	
	
//	translating infix to postfix:
	
	make an operator stack and a postfix string
	
	run through the expression:
		numbers: push to the postfix string	
		operator:
			open parens ->always push
			top of stack is parens -> always push
			current operator has a higher precedence than top of stack: push
			close parens: pop the stack to the postfix string until you pop an open parens
	if the current operator is lower precedence than what's on top of the stack, it goes lower down	
	//try it with some numbers! - see if it works

==========================
Making a picture-drawing algorithm

class Shape //generalization of the idea of circles and rectangles
{
	void move(double xnew, double ynew);
	virtual void draw() const;	 //draw is called differently for each type of shape.
	double m_x;
	double m_y;
};

class Circle : public Shape //introducing a new type called circle, and it's a kind of shape
{
	virtual void draw() const;
	double m_r; //since circle is a type of shape, you only have to declare member functions that are unique to it. it already has move, m_x, m_y, etc. Draw seems to be a special case watch out.
};
	
class Rectangle : public Shape
{
	virtual void draw() const;
	double m_dx;
	double m_dy;
};	

Shape* pic[100];  //Shape is a heterogeneous collection of items in a strongly-typed language
pic[0] = new Circle; //circle "is-a-kind-of" // "is-a" shape
pic[1] = new Rectangle;
pic[2] = new Circle;
//data abstraction is pretty powerful


for (int k = 0; k < ...; k++)
	pic[k]->draw();

void f(Shape& s)
{
	s.move(10, 20);
	s.draw();
}

void Shape::move(double xnew, double ynew)
{ 
	m_x = xnew;
	m_y = ynew;
}

void Shape::draw() const
{
	...draw a cloud centered at m_x, m_y...
}

void Circle::draw() const
{
	...draw a circle...
}

void Rectangle::draw() const
{
	...draw a rectangle...
}

==
review sesh notes

member variables are constructed before the constructor is called -> inside out
member variables are destructed after the desctructor is called -> outside in

if member variables are dynamically allocated, they will not be deleted automatically when/after the destructor is called - gotta add that to the destructor yourself to get it to happen


default copy constructor just copies member variables from the existing object to the new one
you need your own copy constructor when:
	the object contains a pointer to something in memory. otherwise, the pointers will point to the same block of memory, instead of just being a copy. This means that when you modify one the other changes too.
	( ^ dynamic memory allocation)

	
	
==

Inheritance / Virtual Functions
//if a class is designed to be a base class, declare a virtual destructor and implement it
 STEPS OF CONSTRUCTING OBJECTS: THE FIRST STEP
	1. Construct the Base Part
	2. Construct the Data Members
	3. Execute the body of the constructor

 STEPS OF DESTRUCTION
	1. Execute the body of the destructor
	2. Destroy the data members
	3. Destroy the base part //new third step	

class Device //device is the base class for several other things.
{
	public:
	virtual ~Device(){}
	virtual void open() = 0;
	virtual void write(char c) = 0;
	virtual void close() = 0;
};

class BannerDisplay : public Device
{
public:
	virtual void open(); //implemented somewhere
	virtual void write(char c); //implemented somewhere
	virtual void close(); //implemented somewhere
private:
	...
};

class Modem : public Device
{
public:
	virtual void open(); //implemented somewhere
	virtual void write(char c); //implemented somewhere
	virtual void close(); //implemented somewhere
private:
	...
};

void writeString(Device& d, string msg)
{
	for (int k = 0; k != msg.size(); k++)
		d.write(msg[k]);
}


I want to sort a pile of N items:

	if (N > 1)
	{
		split the pile about evenly into two insorted piles
		sort the left subpile
		sort the right subpile
		merge the two sorted subpiles into one sorted pile
	}
//to debug, assume a recursive function works
	void sort(int a[], int b, int e)
	{
		if (e - b >= 2)
		{
			int mid = (b + e) / 2;
			sort(a, b, mid);
			sort(a, mid, e);
			merge(a, b, mid, e);
		}
	}
	
	int main()
	{
		int arr[5] = {40, 30, 20, 50, 10};
		sort(arr, 0, 5);
	}
	
	
	
	
To prove P(N) for all N >= 0:
	1. Prove: P(0)
	2. Prove: If P(k) is true for all k < N, then P(N)



	
	
	

======================
trees?
======================
it's basically just applied math, very little actual programming



N					2N^2+1000N+1000				3N^2-2N+5				10000N
------------------------------------------------------------------------------------
100						123,000						29,805				1,000,000
1000				  3,001,000					 2,998,005			   10,000,000
10000				210,001,000				   299,980,005			  100,000,000
100000			 20,100,001,000				29,999,800,005			1,000,000,000

Exponents totally dominate other terms when N is large (duh)


A function f(N) is O(g(N)) if there exist N0 and k such that for all N >= N0, |f(N)| <= k*g(N)

f(N) is "order g(N)"



for (int i = 0; i < N; i++) <-------------------- O(N)
	c[i] = a[i] * b[i]; <--------------- O(1)

for (int i = 0; i < N; i++) <----------------------------------------------- O(N^2) (since there's 2 O(N) in there)
{ <---------------------------------------------- O(N)
	a[i] *= 2;   <---------------------- O(1)
	for (int j = 0; j < N; j++)  <--------------- O(N)
		d[i][j] = a[i] * c[j]; <-------- O(1)
}

for (int i = 0; i < N; i++) <----------------------------------------------- O(N^2)
{ <-------------------------------------------- O(i)
	a[i] *= 2; <------------------------ O(1)
	for (int j = 0; j < i; j++) <-------------- O(i)
		d[i][j] = a[i] * c[j]; <-------- O(1)	
}

for (int i = 0; i < N; i++) <---------------------------------------------- O(N^2)
{
	if (std::find(a, a+N, 10*i) != a+N) <------- Condition: O(N) //how much time do if statements account for?
		count++; <---------------------- O(1)
}

for (int i = 0; i < N; i++) <-------------------------------------------------------- O(N^2 log N) 
{
	a[i] *= 2; <------------------------------------- O(1)
	for (int j = 0; j < N; j++) <-------------------------------- O(N log N)
		a[i][j] = f(a, N); //suppose f(a, N) is O(log N) <------ O(log N)
}

for (int i = 0; i < R; i++) <----------------------------------------- O(Rc log c) 
{
	a[i] *= 2; <------------------------------------- O(1)
	for (int j = 0; j < c; j++) <---------------------- O(c log c) //Insertion Sort can be based off a constant runtime - 'order N'
		... f(...c...)...; //this is o(log c)
}


there are actually tons of different sorting algorithms - the most efficient one is determined by the type and ordering of data
//compare an item to the ones before it, to figure out where it belongs. move accordingly
Selection Sort, Insertion Sort, Bubble Sort
insertion sort has a circumstance in which it's order N
Merge Sort - efficient, but needs additional space
quicksort is the fastest on average...


Quicksort is N log N!

// find a pivot, move everything smaller to the left and everything larger to the right
// do this recursively
 
//Best case: T(N) = O(N) + 2T(N/2) (time to pick a pivot is O(N), time to sort the halves is T(N/2)
{ _ _ _ _ _ _ _ _ _ }
 [-------] [-------]
 [--] [--] [--] [--]
 [][] [][] [][] [][]

//Worst case: O(N) + T(N - 1) + T(0)
{ _ _ _ _ _ _ _ _ _ }
 [-------------] [-]

 
 
 ----------------
 -	At 0.25 Microseconds per step (4M Steps/sec)
 -----------------------------------------------
   	  N	 	    0.5 N^2		7.527 N log(2)(N)
 ========== =============== =================
		100			 1.25ms			   1.25ms
	   1000			.125sec			  1/53sec	
	  10000			12.5sec			   1/4sec
	 100000			  21min			 3.125sec
	1000000			  35hrs			  37.5sec
	
	
	
struct Node
{
	std::string data;
	vector<Node*> children;
}
	
				George
				/ | \
			   /  |  \
		  eliza	 bet  anne
		   / \		 / | \
		  /   \     /  |  \
		wall  nut peg mar  owen
		

int countTree(count Node* t) //function to count the number of nodes in a tree
{
	if (t == nullptr)
		return 0;
	int total = 1;
	for (int k = 0; k != t->children.size(); k++)
		total += countTree(t->children[k])
	return total;
	
}

void printTree(const Node* t)
{
	if (t != nullptr)
	{
		cout << t->data << endl;
		for (int k = 0; k != t->children.size(); k++)
			printTree(t->children[k]);
	}
}


---------------------------
Templates

used to create functions that can be called with lots of different types of data

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

---------------------------
===========================
---------------------------
Vectors
---------------------------
Vectors are sequence containers representing arrays that can change in size.
Can be accessed using regularly offset pointers to their elements, just like arrays
Unlike arrays, the size can change dynamically



check out the vectors page

fucky cases with erase() - calling erase dereferences any iterators used to go through the vector
can be fixed by passing a modified value: v.erase(i--);
or by setting the iterator to the return of the function: i = v.erase(i);	




---------------------------


ostream is a base class of ofstream


------------------------------

Hash Tables & Binary Search Trees



A complete binary tree is a binary tree where all levels are filled, except possibly the bottom level, which is filled from left to right


A (max) heap is a complete binary tree in which the value at every note is >= all the values in that node's subtrees
A (min) heap is a complete binary tree in which the value at every node is <= all the values in that node's subtrees


Remove a node:

Delete the root
make the bottom rightmost item the new root
trickle down until it's in its proper place


A Binary Heap is a Complete Binary Tree. A binary heap is typically represented as array. The representation is done as:

    The root element will be at Arr[0].
    Below table shows indexes of other nodes for the ith node, i.e., Arr[i]:
    Arr[(i-1)/2] 	Returns the parent node
    Arr[(2*i)+1] 	Returns the left child node
    Arr[(2*i)+2] 	Returns the right child node

    The traversal method use to achieve Array representation is Level Order


	
	Finding things in <set>s = log(N)
	Finding things in <map>s = log(N)
	finding things in vectors = N, unless they're ordered in which case = log(N)
	




Load Factor = (# of items / # of buckets)
(average size of buckets)

incremental rehashing

BST With Balancing





set <set>
	multiset
	
map <map>
	multimap <----- BST (O(log N))
	
unordered_set
unordered_multiset
unordered_map
unordered_multimap



priority queue


unsorted vector
sorted vector

	
	
	
	



	
	