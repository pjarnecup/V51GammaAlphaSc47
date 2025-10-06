// File: include / DetectorConstruction.hh
#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH


#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"


class G4LogicalVolume;


class DetectorConstruction : public G4VUserDetectorConstruction {
public:
	DetectorConstruction();
	~DetectorConstruction() override = default;


	G4VPhysicalVolume* Construct() override;


	static DetectorConstruction* Instance();
	G4LogicalVolume* GetTargetLV() const { return fTargetLV; }


private:
	void DefineMaterials();


private:
	static DetectorConstruction* fInstance; // singleton per process
	G4LogicalVolume* fTargetLV{ nullptr };
};


#endif