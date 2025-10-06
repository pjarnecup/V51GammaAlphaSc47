// File: include / RunAction.hh
#ifndef RUN_ACTION_HH
#define RUN_ACTION_HH


#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"


class RunAction : public G4UserRunAction {
public:
	RunAction();
	~RunAction() override = default;


	void BeginOfRunAction(const G4Run*) override;
	void EndOfRunAction(const G4Run*) override;


	void CountSc47();


private:
	G4Accumulable<G4long> fSc47Count;
};


#endif