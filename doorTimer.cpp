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

/** include files **/
#include "doorTimer.h"      // class Door Timer
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Lueue
* Description: 
********************************************************************/
DoorTimer::DoorTimer( const string &name )
: Atomic( name )
, validCode( addInputPort( "validCode" ) )
, doorOpen( addOutputPort( "doorOpen" ) )
, preparationTime( 0, 0,15, 0 )

{
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &DoorTimer::initFunction()
{
	holdIn( passive, Time::Zero );
	ifopen = false ;
	ifsecond = false ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &DoorTimer::externalFunction( const ExternalMessage &msg )
{

	if ( state() == passive ) 
	{
		ifopen = true ;
		holdIn ( active, Time::Zero ) ;
	}
			

	else if ( ( state() == active ) && ( ifopen == false ) )
	{
		ifsecond = true ;
		holdIn ( active, Time::Zero ) ;
	} 

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &DoorTimer::internalFunction( const InternalMessage & )
{

	if ( ( ifopen == false) && ( state() == passive ) )
	{
		passivate();

	}
	
	
	
	if ( ( ifopen == true) && ( state() == active ) && ( ifsecond == false) )
	{
		ifopen = false ;
		holdIn ( active, preparationTime ) ;

	}
	
	else if ( ( ifopen == false) && ( state() == active ) && ( ifsecond == true) )
	{
		ifsecond = false ;
		holdIn ( active, preparationTime ) ;

	}
	
	
	else if ( ( ifopen == false) && ( state() == active ) )
	{
		ifopen = false ;
		ifsecond = false ;
		passivate();
	}

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &DoorTimer::outputFunction( const InternalMessage &msg )
{
	if ( ( state() == active ) && ( ifopen == true ) && ( ifsecond == false) )
	{
		sendOutput( msg.time(), doorOpen, true ) ;
		
	}

	if ( ( state() == active ) && ( ifopen == false ) && (ifsecond == false) )
	{
		sendOutput( msg.time(), doorOpen, false ) ;
	
	}
	
	
	return *this ;
}
