// File: src / DetectorConstruction.cc
#include "DetectorConstruction.hh"


#include "G4Box.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"


DetectorConstruction* DetectorConstruction::fInstance = nullptr;


DetectorConstruction::DetectorConstruction() { fInstance = this; }


DetectorConstruction* DetectorConstruction::Instance() { return fInstance; }


void DetectorConstruction::DefineMaterials() {
	auto* nist = G4NistManager::Instance();
	nist->FindOrBuildMaterial("G4_Galactic");


	// Pure 51V material
	const G4int Z = 23; // Vanadium
	auto* V51 = new G4Isotope("V51", Z, 51, 50.943961 * g / mole);
	auto* elV = new G4Element("Vanadium-51", "V-51", 1);
	elV->AddIsotope(V51, 100. * perCent);


	const G4double densityV = 6.11 * g / cm3; // bulk density
	auto* matV51 = new G4Material("V51", densityV, 1);
	matV51->AddElement(elV, 1.0);
}


G4VPhysicalVolume* DetectorConstruction::Construct() {
	DefineMaterials();
	auto* nist = G4NistManager::Instance();


	// World
	const G4double worldXY = 10 * cm;
	const G4double worldZ = 10 * cm;
	auto* solidWorld = new G4Box("World", worldXY / 2, worldXY / 2, worldZ / 2);
	auto* logicWorld = new G4LogicalVolume(solidWorld, nist->FindOrBuildMaterial("G4_Galactic"), "LV_World");
	auto* physWorld = new G4PVPlacement(nullptr, {}, logicWorld, "World", nullptr, false, 0, true);


	// Target: 1 cm tall (Y), 1 cm wide (X), 1 mm thick (Z)
	const G4double targetX = 1.0 * cm;
	const G4double targetY = 1.0 * cm;
	const G4double targetZ = 1.0 * mm;
	auto* solidTarget = new G4Box("Target", targetX / 2, targetY / 2, targetZ / 2);
	auto* matV51 = G4Material::GetMaterial("V51");
	fTargetLV = new G4LogicalVolume(solidTarget, matV51, "LV_Target");


	new G4PVPlacement(nullptr, { 0,0,0 }, fTargetLV, "Target", logicWorld, false, 0, true);


	// Visuals
	logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());
	auto* visT = new G4VisAttributes(G4Colour(0.1, 0.6, 0.9, 0.8));
	visT->SetForceSolid(true);
	fTargetLV->SetVisAttributes(visT);


	return physWorld;
}