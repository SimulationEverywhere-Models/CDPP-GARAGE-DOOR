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

/** include files **/
#include "counter.h"      // class Counter
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Counter
* Description: 
********************************************************************/
Counter::Counter( const string &name )
: Atomic( name )
, incre( addInputPort( "incre" ) )
, unauth_attempt( addOutputPort( "unauth_attempt" ) )
, preparationTime( 0, 2, 0, 0 )
, initialTime( 0, 0, 0, 10 )

{
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Counter::initFunction()
{
	count = 0 ;

	holdIn( passive, Time::Zero ) ;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Counter::externalFunction( const ExternalMessage &msg )
{
	count = ++count ;

	if (count == 1)
	{
		initialTime = msg.time();
		holdIn ( passive, Time::Zero ) ;
	}
			

	if ( count == 3 )
	{
		Time elapsedTime = msg.time() - initialTime;
		if ( elapsedTime <= preparationTime )
		{
			count = 0;
			holdIn ( active, Time::Zero ) ;
		}
		else
		{
			elapsedTime = msg.time() - lastChange();
			if ( elapsedTime <= preparationTime )
			{
				initialTime = lastChange();
				count = 2;
				holdIn ( passive, Time::Zero ) ;
			}
			else
			{
				initialTime = msg.time();
				count = 1;
				holdIn ( passive, Time::Zero ) ;
			}
		}

	}
	
	
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Counter::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Counter::outputFunction( const InternalMessage &msg )
{
	if ( state() == active )
	{
		sendOutput( msg.time(), unauth_attempt, true ) ;
	
	}

	return *this ;
}
