/*******************************************************************
*
*  DESCRIPTION: Atomic Model Queue
*
*  AUTHOR: Bengu Balya 
*
*  EMAIL: b_balya@hotmail.com
*
*  DATE: 20/10/2003
*
*******************************************************************/

#ifndef __DOORTIMER_H
#define __DOORTIMER_H

#include <list>
#include "atomic.h"     // class Atomic

class DoorTimer : public Atomic
{
public:
	DoorTimer( const string &name = "DoorTimer" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &validCode;
	Port &doorOpen;
	Time preparationTime;
//	Time initialTime;
	int count;
	bool ifopen;
	bool ifsecond;


};	// class DoorTimer

// ** inline ** // 
inline
string DoorTimer::className() const
{
	return "DoorTimer" ;
}

#endif   //__DOORTIMER_H
