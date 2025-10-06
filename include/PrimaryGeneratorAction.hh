// File: include / PrimaryGeneratorAction.hh
#ifndef PRIMARY_GENERATOR_ACTION_HH
#define PRIMARY_GENERATOR_ACTION_HH


#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh" // for mm in member init
#include "globals.hh"


class G4ParticleGun;
class G4GenericMessenger;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
	PrimaryGeneratorAction();
	~PrimaryGeneratorAction() override;


	void GeneratePrimaries(G4Event* event) override;


private:
	void DefineCommands();


private:
	G4ParticleGun* fGun{ nullptr };
	G4GenericMessenger* fMessenger{ nullptr };
	G4double fEnergyMeV{ 30.0 }; // default
	G4ThreeVector fSourcePos{ 0,0,-2.0 * mm };
	G4ThreeVector fDir{ 0,0,1 };
};


#endif