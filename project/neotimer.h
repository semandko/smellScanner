#ifndef _NEOTIMER_H
#define _NEOTIMER_H

#define NEOTIMER_INDEFINITE -1
#define NEOTIMER_UNLIMITED -1


#include <Arduino.h>

class Neotimer
{
	public:
	
	Neotimer();
	Neotimer(unsigned long t);
	~Neotimer();

	void init();            
	bool done();         
	bool repeat(int times);
	bool repeat(int times, unsigned long t);
	bool repeat();
	void repeatReset();
	bool isWaiting();		
	bool isStarted();		
	void start();			
	unsigned long stop();	
	unsigned long getEllapsed();	
	void restart();
	void reset();           
	void set(unsigned long t);
	unsigned long get();
	bool isDebounce(bool signal);
	int repetitions = NEOTIMER_UNLIMITED;

	private:

	struct stMYTIMER_
	{
		unsigned long time;
		unsigned long last;
		bool isDone;
		bool isStarted;
	};

	struct stMYTIMER_ timer_;
	bool isWaiting_;
};

//Default constructor
Neotimer::Neotimer()
{
	this->timer_.time = 1000; //Default 1 second interval if not specified
}

Neotimer::Neotimer(unsigned long t)
{
  this->timer_.time = t;
}

//Default destructor
Neotimer::~Neotimer()
{

}

//Initializations
void Neotimer::init()
{
  this->isWaiting_ = false;
}

/*
 * Repeats a timer x times
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat(10)){
 * 	  do something 10 times, every second (default)
 * }
 */
bool Neotimer::repeat(int times)
{
	if(times != NEOTIMER_UNLIMITED)
	{
		// First repeat
		if(this->repetitions == NEOTIMER_UNLIMITED)
		{
			this->repetitions = times;
		}
		// Stop
		if(this->repetitions == 0)
		{
			return false;
		}

		if(this->repeat())
		{
			this->repetitions--;
			return true;
		}
		return false;
	}
	return this->repeat();
}

/*
 * Repeats a timer x times with a defined period
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat(10,5000)){
 * 	  do something 10 times, every 5 seconds
 * }
 */
bool Neotimer::repeat(int times, unsigned long t)
{
	this->timer_.time = t;
	return this->repeat(times);
}

/*
 * Repeats a timer indefinetely
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat()){
 * 	  do something indefinetely, every second (default)
 * }
 */
bool Neotimer::repeat()
{
  if(this->done())
  {
    this->reset();
    return true;
  }
	if(!this->timer_.isStarted)
	{
		this->timer_.last = millis();
		this->timer_.isStarted = true;
    this->isWaiting_ = true;
  }
  return false;
}

void Neotimer::repeatReset()
{
	this->repetitions = -1;
}

/*
 * Checks if timer has finished
 * Returns true if it finished
 */
bool Neotimer::done()
{
  if(!this->_timer.isStarted) return false;
  
  if( (millis()-(this->timer_.last)) >= this->timer_.time)
  {
    this->timer_.isDone = true;
    this->isWaiting_ = false;
    return true;
  }
  return false;
}

/*
 * Sets a timer preset
 */
void Neotimer::set(unsigned long t)
{
  this->timer_.time = t;
}

/*
 * Gets the timer preset
 */
unsigned long Neotimer::get()
{
	return this->timer_.time;
}

/*
 * Returns the debounced value of signal
 * This is very useful to avoid "bouncing"
 * of electromechanical signals
 */
bool Neotimer::isDebounce(bool signal)
{
	if(this->done() && signal)
	{
		this->start();
		return true;
	}
	return false;
}

/*
 * Resets a timer
 */
void Neotimer::reset()
{
  this->stop();
  this->timer_.last = millis();
  this->timer_.isDone = false;
}

/*
 * Start a timer
 */
void Neotimer::start()
{
	this->reset();
	this->timer_.isStarted = true;
	this->isWaiting_ = true;
}

/*
 * Stops a timer
 */
unsigned long Neotimer::stop()
{
  this->timer_.isStarted = false;
  this->isWaiting_ = false;
  return this->getEllapsed();
}

/*
 * Gets ellapsed time
 */
unsigned long Neotimer::getEllapsed()
{
  return millis()-(this->timer_.last);
}

/*
 * Continues a stopped timer
 */
void Neotimer::restart()
{
	if(!this->done())
	{
		this->timer_.isStarted = true;
		this->isWaiting_ = true;
	}
}

/*
 * Indicates if the timer is active
 * but has not yet finished.
 */
boolean Neotimer::waiting()
{
  return (this->timer_.isStarted && !this->done()) ? true : false;
}

boolean Neotimer::started()
{
	return this->timer_.isStarted;
}

#endif
