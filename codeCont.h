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

#ifndef __CODECONT_H
#define __CODECONT_H

#include <list>
#include "atomic.h"     // class Atomic

class CodeCont : public Atomic
{
public:
	CodeCont( const string &name = "CodeCont" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &input_code;
	const Port &open_request;
	const Port &emerg_open;
	Port &incre;
	Port &validCode;
	Port &emerg;
	Time preparationTime;
	bool ifvalid;
	bool ifemerg;
	bool ifincre;
	string passCode;
	
	


};	// class AlarmGen

// ** inline ** // 
inline
string CodeCont::className() const
{
	return "CodeCont" ;
}

#endif   //__CODECONT_H
