#ifndef PLAYER_H
#define PLAYER_H

#include "Side.h"
#include "Board.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <future>
#include <atomic>
#include <thread>

class AlarmClock;

class Player
{
public:
	
	Player(std::string name) : m_name(name) {}
//	Create a Player with the indicated name.
	
	std::string name() const {	return m_name;	}
//	Return the name of the player.
	
	virtual bool isInteractive() const { return false; }
//	Return false if the player is a computer player.Return true if the player is human.Most kinds of players will be computer players.
	
	virtual int chooseMove(const Board& b, Side s) const = 0;
//Every concrete class derived from this class must implement this function so that if the player were to be playing sides 
//and had to mak`e a move given board b, the function returns the move the player would choose.
//if no move is possible, return -1
	
	virtual ~Player() {}
//	Since this class is designed as a base class, it should have a virtual destructor.
private:
	std::string m_name;
};


class HumanPlayer : public Player
{
public:
	HumanPlayer(std::string name) : Player(name) {}
	
	bool isInteractive() const { return true; }

	int chooseMove(const Board& b, Side s) const;

private:

};

class BadPlayer : public Player
{
public:
	BadPlayer(std::string name) : Player(name) {}

	int chooseMove(const Board& b, Side s) const;

private:

};

class SmartPlayer : public Player
{
public:
	SmartPlayer(std::string name) : Player(name) {}

	int chooseMove(const Board& b, Side s) const;


	//heuristic: number of beans in my pot, minus the number the opponent has
	//minimax algorithm

private:
	void moveChoose(Board b, Side agent, AlarmClock& ac, int& value, int& besthole, int depth) const;
	
};

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

class AlarmClock
{
public:
	AlarmClock(int ms)
	{
		m_timedOut = false;
		m_isRunning = true;
		m_alarmClockFuture = std::async([=]() {
			for (int k = 0; k < ms && m_isRunning; k++)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (m_isRunning)
				m_timedOut = true;
		});
	}

	~AlarmClock()
	{
		m_isRunning = false;
		m_alarmClockFuture.get();
	}

	bool timedOut() const
	{
		return m_timedOut;
	}

	AlarmClock(const AlarmClock&) = delete;
	AlarmClock& operator=(const AlarmClock&) = delete;
private:
	std::atomic<bool> m_isRunning;
	std::atomic<bool> m_timedOut;
	std::future<void> m_alarmClockFuture;
};





#endif // !PLAYER_H