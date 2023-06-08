/*******************************************************************
*
*  DESCRIPTION: Atomic Model Queue
*
*  AUTHOR: Bengu Balya 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

/** include files **/
#include "lightOut.h"      // class OutlightCont
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Lueue
* Description: 
********************************************************************/
LightOut::LightOut( const string &name )
: Atomic( name )
, motion( addInputPort( "motion" ) )
, light( addInputPort( "light" ) )
, outlon( addOutputPort( "outlon" ) )
, waitTime( 0, 0, 0, 0 )
, preparationTime( 0, 2, 0, 0 )

{
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &LightOut::initFunction()
{
	iflight = false ;
	ifsecond = false;
//	waitTime = preparationTime ;
	holdIn( passive, Time::Zero );
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &LightOut::externalFunction( const ExternalMessage &msg )
{

	if ( msg.port() == light )
	{
		if ( msg.value() == true )
		{
			iflight = true;
			holdIn( passive, Time::Zero ) ;
		}
		else
		{
			iflight = false;
			holdIn( passive, Time::Zero ) ;
		}
	}

	else if ( msg.port() == motion )
	{
		if ( ( iflight == false ) && ( state() == passive ) )
		{
			holdIn( active, Time::Zero ) ;
		}
		else if ( ( iflight == false ) && ( state() == active ) )
		{

			Time timeLeft = msg.time() - lastChange() ;
			if ( timeLeft != preparationTime )
			{
				ifsecond = true ;
				waitTime = waitTime - timeLeft ;
				holdIn( active, Time::Zero ) ;
			}
			else
			{
				holdIn( active, Time::Zero ) ;
			}
		}
		else
		{
			holdIn( passive, Time::Zero ) ;
		}

	}

	return *this ;

}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &LightOut::internalFunction( const InternalMessage & )
{

	if ( state () == passive ) 

	{
		ifsecond = false;
		waitTime = Time::Zero;
		passivate();
	}
	else if ( waitTime == Time::Zero )
	{
		waitTime = preparationTime;
		holdIn( active, waitTime );
	}	
	else if ( ifsecond == true )
	{
		ifsecond = false;
		holdIn( active, waitTime );
	}
	else
	{
		waitTime = Time::Zero;
		passivate();
	}	
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &LightOut::outputFunction( const InternalMessage &msg )
{
	if ( state() == active )
	{
		if ( waitTime == Time::Zero )
		{
			sendOutput( msg.time(), outlon, true );
		}
		else if ( ifsecond == false )
		{
			sendOutput( msg.time(), outlon, false );
		}
	}
	// state passive
	else if ( ( iflight == true ) && ( waitTime != Time::Zero ) )
	{
		sendOutput( msg.time(), outlon, false );
	}
	
	return *this ;
}
