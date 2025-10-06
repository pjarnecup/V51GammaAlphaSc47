// File: include / TrackingAction.hh
#ifndef TRACKING_ACTION_HH
#define TRACKING_ACTION_HH


#include "G4UserTrackingAction.hh"
#include "globals.hh"


class RunAction;
class G4LogicalVolume;


class TrackingAction : public G4UserTrackingAction {
public:
	explicit TrackingAction(RunAction* runAction);
	~TrackingAction() override = default;


	void PreUserTrackingAction(const G4Track* track) override;


private:
	RunAction* fRunAction{ nullptr };
	G4LogicalVolume* fTargetLV{ nullptr };
};


#endif