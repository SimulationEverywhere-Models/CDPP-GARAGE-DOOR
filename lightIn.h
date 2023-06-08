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

#ifndef __LIGHTIN_H
#define __LIGHTIN_H

#include <list>
#include "atomic.h"     // class Atomic

class LightIn : public Atomic
{
public:
	LightIn( const string &name = "LightIn" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &validCode;
	Port &inlon;
	Time waitTime;
	Time preparationTime;
	bool ifsecond;


};	// class OutlightCont

// ** inline ** // 
inline
string LightIn::className() const
{
	return "LightIn" ;
}

#endif   //__LIGHTIN_H
