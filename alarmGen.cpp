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

/** include files **/
#include "alarmGen.h"      // class AlarmGen
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: AlarmGen
* Description: 
********************************************************************/
AlarmGen::AlarmGen( const string &name )
: Atomic( name )
, unauth_attempt( addInputPort( "unauth_attempt" ) )
, emerg( addInputPort( "emerg" ) )
, alarm_reset( addInputPort( "alarm_reset" ) )
, minor_alarm( addOutputPort( "minor_alarm" ) )
, major_alarm( addOutputPort( "major_alarm" ) )
, preparationTime( 0, 0,15, 0 )

{
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &AlarmGen::initFunction()
{
	holdIn( passive, Time::Zero );
	ifminor = false ;
	ifmajor = false ;
	ifreset = false ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &AlarmGen::externalFunction( const ExternalMessage &msg )
{

	if ( ( msg.port() == alarm_reset ) && ( msg.value() == true ) )
	{
			ifreset = true ;

	}
	
	
	if ( ( msg.port() == unauth_attempt ) && ( msg.value() == true ) )
	{
		ifminor = true ;
	}
			

	if ( ( msg.port() == emerg ) && ( msg.value() == true ) )
	{
		ifmajor = true ;

	}

	holdIn( active, Time::Zero );

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &AlarmGen::internalFunction( const InternalMessage & )
{

	ifminor = false ;
	ifmajor = false ;
	ifreset = false ;
	passivate() ;
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &AlarmGen::outputFunction( const InternalMessage &msg )
{
	if ( ifreset == true ) 
	{
			sendOutput( msg.time(), minor_alarm, false ) ;
			sendOutput( msg.time(), major_alarm, false ) ;
	}

	else if ( ifmajor == true ) 
	{
		sendOutput( msg.time(), major_alarm, true ) ;

	}

	else if ( ifminor == true ) 
	{
		sendOutput( msg.time(), minor_alarm, true ) ;

	}
	
	
	
	return *this ;
}
