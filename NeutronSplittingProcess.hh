//////////////////////////////////////////////////////////////////////////
// License & Copyright
// ===================
// 
// Copyright 2012 Christopher M Poole
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////
// 
// This code is mostly based on the Bremsstrahlung splitting example
// described by Jane Tinslay.
//
//////////////////////////////////////////////////////////////////////////


#ifndef NeutronSplittingProcess_HH
#define NeutronSplittingProcess_HH 1

#include "G4WrapperProcess.hh"
//#include "DetectorConstruction.hh"

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
