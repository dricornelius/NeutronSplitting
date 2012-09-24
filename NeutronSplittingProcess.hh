#ifndef NeutronSplittingProcess_HH
#define NeutronSplittingProcess_HH 1

#include "G4WrapperProcess.hh"
#include "DetectorConstruction.hh"

class NeutronSplittingProcess : public G4WrapperProcess {

public:

  NeutronSplittingProcess();

  virtual ~NeutronSplittingProcess();

  // Override PostStepDoIt  method
  G4VParticleChange* PostStepDoIt(const G4Track& track, const G4Step& step);

  // Modifiers
   void SetNSplit(G4int);
  static void SetIsActive(G4bool);

  // Accessors
  static G4bool GetIsActive();
   G4int GetNSplit();
  static G4int GetNSecondaries();


private:

  // Data members
//  static G4int fNSplit;
   G4int fNSplit;
  static G4int fNSecondaries;
  static G4bool fActive;

public:
  DetectorConstruction* detector_construction;
};

#endif
