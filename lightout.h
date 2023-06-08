/*******************************************************************
*
*  DESCRIPTION: Atomic Model Queue
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#ifndef __LIGHTOUT_H
#define __LIGHTOUT_H

#include <list>
#include "atomic.h"     // class Atomic

class LightOut : public Atomic
{
public:
	LightOut( const string &name = "LightOut" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &motion;
	const Port &light;
	Port &outlon;
	Time waitTime;
	Time preparationTime;
//	Time initialTime ;
//	bool ifmotion;
	bool iflight;
	bool ifsecond;


};	// class OutlightCont

// ** inline ** // 
inline
string LightOut::className() const
{
	return "LightOut" ;
}

#endif   //__OUTLIGHTCONT_H
