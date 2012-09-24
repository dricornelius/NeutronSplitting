A (Photo) Neutron Splitting Process for GEANT4
======================================

Based on the Bremsstrahlung splitting process, this neutron splitting process aims apply the same technique to the variance reduction to photo-neutron calculations specifically.

Usage
-----

The process is constructed in the PhysicsList as per usual and added to gammas along with any other processes you have defined:

    #include "NeutronSplittingProcess.hh"
    ...
    void PhysicsList::ConstructProcess()
    {
        plist->ConstructProcess();
        theParticleIterator->reset();

        while ( (*theParticleIterator)()){

            G4ParticleDefinition* particle = theParticleIterator->value();

            G4ProcessManager* pmanager = particle->GetProcessManager();

            G4String particleName = particle->GetParticleName();

            if (particleName == "gamma"){
                G4GammaNuclearReaction* lowEGammaModel = new G4GammaNuclearReaction();
                lowEGammaModel->SetMaxEnergy(3.5*GeV);

                G4PhotoNuclearProcess* thePhotoNuclearProcess = new G4PhotoNuclearProcess();
                thePhotoNuclearProcess->RegisterMe(lowEGammaModel);

                NeutronSplittingProcess* neutronSplitting = new NeutronSplittingProcess();
                neutronSplitting->RegisterProcess(thePhotoNuclearProcess);
                pmanager->AddProcess(neutronSplitting, -1,-3, 3);
            }
        }
    }
    ...

Installation Note
-----------------

Just copy `NeutronSplittingProcess.cc` to your `src` directory, and `NeutronSplittingProcess.hh` to your `include` directory in your project.
