/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "counter.h"    // class Counter
#include "doorTimer.h"  // class DoorTimer
#include "lightOut.h"  // class LightOut
#include "lightIn.h"  // class LightIn
#include "alarmGen.h"    // class AlarmGen
#include "codeCont.h"    // class CodeCont#include "queue.h"      // class Queue
#include "queue.h"    // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Counter>() , "Counter" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<DoorTimer>() , "DoorTimer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<LightOut>() , "LightOut" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<LightIn>() , "LightIn" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<AlarmGen>() , "AlarmGen" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CodeCont>() , "CodeCont" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
}
