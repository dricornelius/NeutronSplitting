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

#include "NeutronSplittingProcess.hh"

#include "G4Track.hh"
#include "G4VParticleChange.hh"
#include <assert.h>
#include <vector>


// Initialise static data
G4int NeutronSplittingProcess::fNSecondaries = 0;
G4bool NeutronSplittingProcess::fActive = true;


NeutronSplittingProcess::NeutronSplittingProcess() {
    fNSplit = 2000;
    detector_construction = (DetectorConstruction*) (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
}


NeutronSplittingProcess::~NeutronSplittingProcess() {

}


G4VParticleChange* NeutronSplittingProcess::PostStepDoIt(const G4Track& track, const G4Step& step)
{
    G4VParticleChange* particleChange(0);

    if (!fActive) {
        particleChange = pRegProcess->PostStepDoIt(track, step);
        assert (0 != particleChange);

        fNSecondaries += particleChange->GetNumberOfSecondaries();

        return particleChange;
    }

    assert (fNSplit > 0);

    //G4cout << "Neutron created in " << track.GetVolume()->GetName() << G4endl;
    //detector_construction->neutron_source_volume = track.GetVolume()->GetName();

    G4int i(0);
    std::vector<G4Track*> secondaries;
    secondaries.reserve(fNSplit);

    for (i=0; i<fNSplit; i++) {
        particleChange = pRegProcess->PostStepDoIt(track, step);

        assert (0 != particleChange);
        particleChange->SetVerboseLevel(0);

        G4int j(0);

        for (j=0; j<particleChange->GetNumberOfSecondaries(); j++) {
//            secondaries.push_back(new G4Track(*(particleChange->GetSecondary(j))));
            G4Track* myTrack = new G4Track(*(particleChange->GetSecondary(j)));
           if (myTrack->GetKineticEnergy() > 10*keV) {;
                secondaries.push_back(myTrack);
            }
        }
    }

    particleChange->SetNumberOfSecondaries(secondaries.size());
    particleChange->SetSecondaryWeightByProcess(true);

    //G4double weight = track.GetWeight()/fNSplit;
    G4double weight = track.GetWeight()/secondaries.size();
    
    std::vector<G4Track*>::iterator iter = secondaries.begin();

    while (iter != secondaries.end()) {
        G4Track* myTrack = *iter;
        myTrack->SetWeight(weight);

        particleChange->AddSecondary(myTrack);
	delete *iter;
        iter++;
    }

    fNSecondaries += secondaries.size();
    //G4cout << fNSplit << " " << secondaries.size() << G4endl;

    return particleChange;
}

void NeutronSplittingProcess::SetNSplit(G4int nSplit)
{
    fNSplit = nSplit;
}

void NeutronSplittingProcess::SetIsActive(G4bool active)
{
    fActive = active;
}

G4bool NeutronSplittingProcess::GetIsActive()
{
    return fActive;class NeutronSplittingProcessMessenger;

}

G4int NeutronSplittingProcess::GetNSplit()
{
    return fNSplit;
}

G4int NeutronSplittingProcess::GetNSecondaries()
{
    return fNSecondaries;
}
