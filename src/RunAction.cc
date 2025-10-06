// File: src / RunAction.cc
#include "RunAction.hh"

#include "G4PhysicalConstants.hh"
#include "G4AccumulableManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>


RunAction::RunAction() : fSc47Count(0) {
	// Geant4 11.x API
	G4AccumulableManager::Instance()->Register(fSc47Count);
}


void RunAction::BeginOfRunAction(const G4Run*) {
	G4AccumulableManager::Instance()->Reset();
}


void RunAction::EndOfRunAction(const G4Run* run) {
	auto* mgr = G4AccumulableManager::Instance();
	mgr->Merge();


	const auto nEvents = run->GetNumberOfEvent();
	const auto nSc47 = fSc47Count.GetValue();
	const double yield = (nEvents > 0) ? static_cast<double>(nSc47) / nEvents : 0.0;


	// Print with plain ASCII quotes and no embedded multi-line string literals
	G4cout << G4endl;
	G4cout << "==== 51V(gamma,alpha)47Sc Summary ====" << G4endl;
	G4cout << " Events (gammas): " << nEvents << G4endl;
	G4cout << " 47Sc produced : " << nSc47 << G4endl;
	G4cout << " Yield/event : " << std::setprecision(6) << yield << G4endl;
	G4cout << "=====================================" << G4endl;

	const G4double densityV = 6.11 * g / cm3;
	const G4double thickness = 0.1 * cm;
	const G4double molarMass = 50.943961 * g / mole;
	const G4double nAtoms = (densityV * thickness * Avogadro) / molarMass;

	const G4double sigma = nSc47 / (nAtoms * nEvents);
	G4cout << "Cross section: " << (sigma / barn) * 1000 << " milibarns" << G4endl;

}


void RunAction::CountV50() { fV50Count += 1; }