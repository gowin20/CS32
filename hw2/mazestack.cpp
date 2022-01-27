#include <stack>
#include <iostream>
using namespace std;


const int SOUTH = 1; //useless consts so I don't get confused
const int NORTH = -1;
const int EAST = 1;
const int WEST = -1;


class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};



// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;
	Coord start(sr, sc);
	Coord end(er, ec);
	
	coordStack.push(start);
	maze[start.r()][start.c()] = '#';

	while (!coordStack.empty())
	{
		Coord loc = coordStack.top();
		coordStack.pop();

		if ((loc.r() == end.r()) && (loc.c() == end.c()))
			return true;
		
		if (maze[loc.r() + SOUTH][loc.c()] == '.') //code puts all empty spaces around location onto the stack, and eventually checks them all, resulting in every accessible maze location being checked
		{
			Coord newloc(loc.r() + SOUTH, loc.c());
			maze[newloc.r()][newloc.c()] = '#';
			coordStack.push(newloc);
		}
		if (maze[loc.r()][loc.c() + WEST] == '.')
		{
			Coord newloc(loc.r(), loc.c() + WEST);
			maze[newloc.r()][newloc.c()] = '#';
			coordStack.push(newloc);
		}
		if (maze[loc.r() + NORTH][loc.c()] == '.')
		{
			Coord newloc(loc.r() + NORTH, loc.c());
			maze[newloc.r()][newloc.c()] = '#';
			coordStack.push(newloc);
		}
		if (maze[loc.r()][loc.c() + EAST] == '.')
		{
			Coord newloc(loc.r(), loc.c() + EAST);
			maze[newloc.r()][newloc.c()] = '#';
			coordStack.push(newloc);
		}
	}
	return false;
}

/*
Push the starting coordinate (sr,sc) onto the coordinate stack and
			update maze[sr][sc] to indicate that the algorithm has encountered
			it (i.e., set maze[sr][sc] to have a value other than '.').
		While the stack is not empty,
		{   Pop the top coordinate off the stack. This gives you the current
				(r,c) location that your algorithm is exploring.
			If the current (r,c) coordinate is equal to the ending coordinate,
				then we've solved the maze so return true!
			Check each place you can move from the current cell as follows:
				If you can move SOUTH and haven't encountered that cell yet,
					then push the coordinate (r+1,c) onto the stack and update
					maze[r+1][c] to indicate the algorithm has encountered it.
				If you can move WEST and haven't encountered that cell yet,
					then push the coordinate (r,c-1) onto the stack and update
					maze[r][c-1] to indicate the algorithm has encountered it.
				If you can move NORTH and haven't encountered that cell yet,
					then push the coordinate (r-1,c) onto the stack and update
					maze[r-1][c] to indicate the algorithm has encountered it.
				If you can move EAST and haven't encountered that cell yet,
					then push the coordinate (r,c+1) onto the stack and update
					maze[r][c+1] to indicate the algorithm has encountered it.
		}
		There was no solution, so return false
*/