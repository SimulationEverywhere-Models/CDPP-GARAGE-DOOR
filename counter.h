/*******************************************************************
*
*  DESCRIPTION: Atomic Model Counter
*
*  AUTHOR: Bengu Balya 
*
*  EMAIL: b_balya@hotmail.com
*
*  DATE: 20/10/2003
*
*******************************************************************/

#ifndef __COUNTER_H
#define __COUNTER_H

#include <list>
#include "atomic.h"     // class Atomic
#include "message.h"    


class Counter : public Atomic
{
public:
	Counter( const string &name = "Counter" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &incre;
	Port &unauth_attempt;
	Time preparationTime;
	Time initialTime;
	int count;

};	// class Counter

// ** inline ** // 
inline
string Counter::className() const
{
	return "Counter" ;
}

#endif   //__COUNTER_H
