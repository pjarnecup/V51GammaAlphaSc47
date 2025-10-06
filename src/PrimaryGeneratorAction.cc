// File: src / PrimaryGeneratorAction.cc
#include "PrimaryGeneratorAction.hh"


#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction() {
	fGun = new G4ParticleGun(1);
	fGun->SetParticleDefinition(G4Gamma::Gamma());
	fGun->SetParticlePosition(fSourcePos);
	fGun->SetParticleMomentumDirection(fDir);
	fGun->SetParticleEnergy(fEnergyMeV * MeV);
	DefineCommands();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fGun; delete fMessenger; }


void PrimaryGeneratorAction::DefineCommands() {
	fMessenger = new G4GenericMessenger(this, "/beam/", "Beam control");
	fMessenger->DeclareProperty("energy", fEnergyMeV, "Gamma energy in MeV");
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
	fGun->SetParticleEnergy(fEnergyMeV * MeV);
	fGun->GeneratePrimaryVertex(event);
}