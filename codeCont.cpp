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
#include "codeCont.h"      // class CodeCont
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: AlarmGen
* Description: 
********************************************************************/
CodeCont::CodeCont( const string &name )
: Atomic( name )
, input_code( addInputPort( "input_code" ) )
, open_request( addInputPort( "open_request" ) )
, emerg_open( addInputPort( "emerg_open" ) )
, incre( addOutputPort( "incre" ) )
, validCode( addOutputPort( "validCode" ) )
, emerg( addOutputPort( "emerg" ) )
, preparationTime( 0, 0,15, 0 )

{
	passCode = "";
	if (MainSimulator::Instance().existsParameter( description(), "passcode" ) )
	{
		string code( MainSimulator::Instance().getParameter( description(), "passcode" ) );
		if (code != "")
		{
			passCode = code ;
		}
	}


}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &CodeCont::initFunction()
{
	holdIn( passive, Time::Zero );
	ifincre = false ;
	ifemerg = false ;
	ifvalid = false ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &CodeCont::externalFunction( const ExternalMessage &msg )
{

	if ( msg.port() == emerg_open )
	{
				ifemerg = true ;
	}
	
	
	else if ( msg.port() == open_request )
	{
			ifvalid = true ;

	}

	else if ( msg.port() == input_code ) 
	{
		int passCodeInt = 0 ;
		if ( passCode != "")
		{
			passCodeInt = str2Int(passCode);
		}
		int incomingcode = static_cast<int>(msg.value()) ;
		
		if ( incomingcode == passCodeInt)
		{
			ifvalid = true ;
		}
		else
		{
			ifincre = true;
		}
		
	}	
	
	holdIn( active, Time::Zero );

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &CodeCont::internalFunction( const InternalMessage & )
{

	ifincre = false ;
	ifemerg = false ;
	ifvalid = false ;
	passivate() ;
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &CodeCont::outputFunction( const InternalMessage &msg )
{
	if ( ifemerg == true ) 
	{
			sendOutput( msg.time(), emerg, true ) ;
			sendOutput( msg.time(), validCode, true ) ;
	}

	else if ( ifvalid == true ) 
			sendOutput( msg.time(), validCode, true ) ;


	else if ( ifincre == true ) 
			sendOutput( msg.time(), incre, true ) ;

	
	return *this ;
}
