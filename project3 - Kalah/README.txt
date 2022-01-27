George Owen
README.txt

==================================
	0.	Prelude & Usage
---------------------------------------------------------------------------------------------------------------------------
	This project implements a working console-based version of Kalah, popularly known as Mancala. This game features an adversarial AI
	which uses the minimax algorithm to play optimally at every move. I originally created this project as part of UCLA's CS32 class. 
	Aside from the provided "AlarmClock" class, all of the code is original including the makefile.

	Usage:
		./kalah.exe
	Once in the game, play by inputting a hole number in the range 1-6.

	The game can also be played against two computers. The "SmartPlayer" class contains the smart AI, while the "BadPlayer" class moves
	randomly. To modify the game, change the Game "minigame" instantiation in Main.cpp to include one of the other instantiated players.
	Then run "make" to generate a new kalah.exe.


	The remainder of this file goes into detail on the creation of the project, as well as the pseudocode and algorithms.
---------------------------------------------------------------------------------------------------------------------------




==================================
	1	Design of Classes. 
---------------------------------------------------------------------------------------------------------------------------
	The first class I designed was Board. I decided to use two arrays (not dynamically allocated, but with a large maximum value) to
	represent the respective sides and holes of the board. Each location is a hole, with the value equal to the number of beans. 
	Board also contains a private variable that tracks the number of holes, but no other private helper functions.
	
	After Board came Player. I implemented most of the trivial functions purely in the base class, but isInteractive is partially
	virtual, with only the human player returning true. ChooseMove is the meat of this class, and I ended up implementing a helper
	function called moveChoose that chooses a move for SmartPlayer. This also necessitates the use of an AlarmClock class 
	(provided by Smallberg), which is implemented in Player.h
	
	For Game, I was able to implement the public member functions without declaring any additional helper functions or data structures.
	A Game contains a board and two players, and uses them to play the game.

	
==================================
	2	Design for SmartPlayer::chooseMove
---------------------------------------------------------------------------------------------------------------------------
	SmartPlayer loosely follows the pseudocode provided in the project spec, doing a depth-first search of as much of the game tree as
	possible within five seconds. The Heuristic I used to evaluate positions is: The number of beans in SOUTH's pot minus the number of
	beans in NORTH's pot. It recursively searches up to (depth) levels in the tree, which I've set to ten for the submitted files. When
	it reaches the end of a game, it determines who wins and sets the value of that state to either a very large or very small value.
	The pseudocode for the function can be found below


==================================
	3	Pseudocode for non-trivial algorithms.
---------------------------------------------------------------------------------------------------------------------------
	SmartPlayer::moveChoose
		Store the opposite side
		if the game is over
			hole = -1
			sweep beans to the pot
			if NORTH won, value = very low (-infinity)
			if SOUTH won, value = very high (+infinity)
			if it's a tie, value = 0
			return
		if the maximum depth is reached or time is up
			hole = -1
			value is south's beans - north's beans
			return
		for every hole on the board:
			if time is up, return
			make a copy of the board
			if there's beans in the hole
				make a complete move
				if it's the first hole being checked,
					this is the best hole
					value is south's beans - north's beans
				
				call moveChoose for the opponent
				
				if the value returned by the recursion is better for the player than the current value, make it the new value
	
	BadPlayer::ChooseMove
		if there's no beans in play, return
		continuously:
			choose a random number between 1 and the number of holes
			if there's beans in that hole, return that number as selection
		
	Board::Sow
		if the input is invalid, return false
		create a pointer to the side sowing began on's array
		
		if the hole is empty, return false
		
		beansToSow is the number of beans in the desired hole
		remove all beans from the hole
		
		while there are still beans to sow:
			if we're on the south side, increment up one hole
			if we're on the north side, decrement down one hole
			
			if we've reached the end of holes on the south side
				decrement one hole
				if the south player is sowing, add a bean to their pot
				swap to the north side
			if we've reached the end of holes on the north side
				increment one hole
				if the north player is sowing, add a bean to their pot
				swap to the south side
			
			if there's still beans to sow, add a bean to the current hole and decrement beansToSow
		set endside to the dummy pointer
		return true
					
	Game::Move
		figure out who's making the move
		running = true
		while running is true:
			check the status of the game using running (sets it to false if the game isn't over)
			if running is true
				sweep all the beans into the respective pots
				return false

			if the player is interactive, prompt them to select a hole
			have the player choose a move
			if the player isn't interactive, tell the user what the selection is
			
			sow the board based on the player's selection
			
			if the last bean landed in an empty hole on the player's side, and there's beans in the hole across
				move the beans in both holes to the pot (perform a capture)
			if the last bean landed in the player's pot,
				tell them they get an extra turn and display the board
				set running to true
		swap whose turn it is
		return true
				
	Game::Play
		initialize variables
		display the board
		continuously:
			make a move
			if move returns false, break
			if neither player is interactive, prompt the user to press ENTER to continue
		
		(the game is over when it breaks from the loop)
		check the status of the game
		display the end state
		print the winner

==================================
	4	Test Cases
---------------------------------------------------------------------------------------------------------------------------
A list of the test cases to thoroughly test the functions.


Board b(3, 2);
SmartPlayer smart("my teaching assistant <3");
BadPlayer dumb("Smallberg");
HumanPlayer user("George");

b.setBeans(SOUTH, 3, 0); //test setbeans

Game test(b, &dumb, &dumb); //possible to initialize a game with the same player as both players
Game g(b, &smart, &dumb);
---- //the game has been initialized
//	 2  2  2
// 0		 0
//   2  2  0

g.move() //smartplayer picks hole two, gets an extra turn, then picks hole one, gets another turn, then picks hole three

//	 2  2  2
// 0		 1 //tests the move function, and by extension sow
//   2  0  1
		||
	    \/

//	 2  2  2
// 0		 2 //tests extra turns
//   2  0  0
		||
		\/
		
//	 2  2  0
// 0		 5 //tests multiple extra turns, as well as captures
//   0  1  0

g.move() //dumbplayer chooses hole 2, gets another turn, then chooses hole one

//	 3  0  0
// 1		 5
//   0  1  0
		||
		\/

//	 0  0  0
// 2		 5  //the move function automatically calls g.status(), so at the point it detects that there are no possible moves and 
//   1  2  0	//ends the game
		||
		\/

//	 0  0  0
// 2		 8 //resulting board after dumbplayer chooses hole two
//   0  0  0

g.play() //the function responsible for the core loop of the game. Normally, it calls move() until the game has ended,
		 //but since we've already done that for it, all it will do is announce the winner of the game


		 
"The winner is my teaching assistant <3"
//you're the real winner here, buddy		 


