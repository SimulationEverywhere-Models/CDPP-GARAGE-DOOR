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
#include "lightIn.h"      // class LightIn
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: LightIn
* Description: 
********************************************************************/
LightIn::LightIn( const string &name )
: Atomic( name )
, validCode( addInputPort( "validCode" ) )
, inlon( addOutputPort( "inlon" ) )
, waitTime( 0, 0, 0, 0 )
, preparationTime( 0, 5, 0, 0 )

{
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &LightIn::initFunction()
{
	ifsecond = false;
	holdIn( passive, Time::Zero );
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &LightIn::externalFunction( const ExternalMessage &msg )
{

	if ( state() == passive )
	{
		holdIn( active, Time::Zero ) ;
	}

	else
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
			ifsecond = true;
			holdIn( active, Time::Zero ) ;
		}
	}


	return *this ;

}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &LightIn::internalFunction( const InternalMessage & )
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
Model &LightIn::outputFunction( const InternalMessage &msg )
{
	if ( state() == active )
	{
		if ( waitTime == Time::Zero )
		{
			sendOutput( msg.time(), inlon, true );
		}
		else if ( ifsecond == false )
		{
			sendOutput( msg.time(), inlon, false );
		}
	}
	
	return *this ;
}
