// src/TrackingAction.cc
#include "TrackingAction.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"

#include "G4Track.hh"
#include "G4Ions.hh"
#include "G4VProcess.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"  // for mm in debug print

TrackingAction::TrackingAction(RunAction* runAction) : fRunAction(runAction) {
    fTargetLV = DetectorConstruction::Instance()
        ? DetectorConstruction::Instance()->GetTargetLV()
        : nullptr;
}

void TrackingAction::PreUserTrackingAction(const G4Track* track) {
    if (!fRunAction || !fTargetLV) return;
    if (track->GetParentID() == 0) return;  // skip primaries

    const auto* def = track->GetParticleDefinition();
    const auto* ion = dynamic_cast<const G4Ions*>(def);
    if (!ion) return;

    const bool isSc47 =
        (ion->GetAtomicNumber() == 21 && ion->GetAtomicMass() == 47);
    if (!isSc47) return;

    const auto* startLV = track->GetLogicalVolumeAtVertex();
    if (startLV != fTargetLV) return;  // only count produced in target

    const auto* creator = track->GetCreatorProcess();
    if (creator) {
        const auto& name = creator->GetProcessName();
        // Only count if made by photonuclear interaction (names can vary)
        if (name != "photonNuclear" && name != "PhotonInelastic") return;
    }

    fRunAction->CountSc47();
}