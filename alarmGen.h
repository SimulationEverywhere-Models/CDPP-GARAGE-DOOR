/*******************************************************************
*
*  DESCRIPTION: Atomic Model AlarmGen
*
*  AUTHOR: Bengu Balya 
*
*  EMAIL: b_balya@hotmail.com
*
*  DATE: 20/10/2003
*
*******************************************************************/

#ifndef __ALARMGEN_H
#define __ALARMGEN_H

#include <list>
#include "atomic.h"     // class Atomic

class AlarmGen : public Atomic
{
public:
	AlarmGen( const string &name = "AlarmGen" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &unauth_attempt;
	const Port &emerg;
	const Port &alarm_reset;
	Port &minor_alarm;
	Port &major_alarm;
	Time preparationTime;
	bool ifminor;
	bool ifmajor;
	bool ifreset;
	
	


};	// class AlarmGen

// ** inline ** // 
inline
string AlarmGen::className() const
{
	return "AlarmGen" ;
}

#endif   //__ALARMGEN_H
