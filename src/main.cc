// File: src / main.cc
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "FTFP_BERT.hh"
#include "QGSP_BIC.hh" //removeit
#include "G4EmExtraPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "Randomize.hh" // G4Random / CLHEP::HepRandom


#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"


#include <chrono>
#include <cstdlib>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif


static long MakeSeed() {
	if (const char* s = std::getenv("G4SEED")) {
		char* end = nullptr;
		long v = std::strtol(s, &end, 10);
		if (end && *end == '\0' && v > 0) return v;  // all digits, positive
	}
	auto now_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();
#ifdef _WIN32
	long pid = static_cast<long>(_getpid());
#else
	long pid = static_cast<long>(getpid());
#endif
	long seed = static_cast<long>((now_ns ^ (static_cast<long long>(pid) << 16)) & 0x7fffffffL);
	if (seed <= 0) seed = 1;
	return seed;
}


int main(int argc, char** argv) {
	// Randomize the seed for this run (override with env G4SEED)
	long seed = MakeSeed();
	G4Random::setTheSeed(seed);
	G4cout << "[RNG] Using seed: " << seed << G4endl;


	auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);


	runManager->SetUserInitialization(new DetectorConstruction());


	auto* physics = new FTFP_BERT; //FTFP_BERT
	physics->RegisterPhysics(new G4EmExtraPhysics()); // photonuclear
	physics->RegisterPhysics(new G4RadioactiveDecayPhysics()); // ion defs/decay
	runManager->SetUserInitialization(physics);


	runManager->SetUserInitialization(new ActionInitialization()); //hola


	G4UIExecutive* ui = (argc == 1) ? new G4UIExecutive(argc, argv) : nullptr;
	G4VisManager* visManager = nullptr;
	auto* UImanager = G4UImanager::GetUIpointer();


	if (ui) {
		visManager = new G4VisExecutive();
		visManager->Initialize();
		UImanager->ApplyCommand("/control/execute macros/init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	else {
		UImanager->ApplyCommand(G4String("/control/execute ") + argv[1]);
	}


	delete visManager;
	delete runManager;
	return 0;
}