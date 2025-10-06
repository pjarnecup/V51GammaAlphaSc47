// File: src / ActionInitialization.cc
#include "ActionInitialization.hh"


#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "TrackingAction.hh"


void ActionInitialization::Build() const {
	auto* runAction = new RunAction();
	SetUserAction(runAction);
	SetUserAction(new PrimaryGeneratorAction());
	SetUserAction(new TrackingAction(runAction));
}


void ActionInitialization::BuildForMaster() const {
	SetUserAction(new RunAction());
}