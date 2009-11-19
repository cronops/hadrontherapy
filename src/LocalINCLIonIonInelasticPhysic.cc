//
// ********************************************************************
// * License and Disclaimer                                           *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// LocalINCLIonIonInelasticPhysic.cc
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy
//
// In this class the models for ion-ion interactions at intermediate energies (0 - 1 GeV per nucleon)
// can be activate. This class can be used alternatively to the "binary_ion" physics list
//
// The usefullness of this class is that you can explicitally see the total inelastic sections
// activated and the models called. Moreover you can choose to activate for ions (from deuteron
// to heavier nucleus) three different and exclusive models: the Binary Light Ion cascade, the QMD
// and The Wilson.

// For hadrotherapy pouposes, where distributions of produced fragments is importante we strongly
// suggest to use Binary or QMD. The Binary model is the default and at moment, you can swith beetween models decommenting
// the line of code and recompiling

#include "LocalINCLIonIonInelasticPhysic.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

// Total cross section for inelastic processes
#include "G4TripathiCrossSection.hh"
#include "G4TripathiLightCrossSection.hh"
#include "G4IonsShenCrossSection.hh"

#include "G4DeuteronInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"
#include "G4AlphaInelasticProcess.hh"
#include "G4LEDeuteronInelastic.hh"
#include "G4LETritonInelastic.hh"
#include "G4LEAlphaInelastic.hh"
#include "G4BinaryLightIonReaction.hh"
#include "G4InclAblaLightIonInterface.hh"
#include "G4QMDReaction.hh"
#include "G4WilsonAbrasionModel.hh"
#include "G4IonInelasticProcess.hh"
#include "G4GeneralSpaceNNCrossSection.hh"

/////////////////////////////////////////////////////////////////////////////
LocalINCLIonIonInelasticPhysic::LocalINCLIonIonInelasticPhysic(const G4String& name): 
  G4VPhysicsConstructor(name)
{
  G4cout << G4endl 
	 << "A local inelastic model is activated for all ions" 
	 << G4endl;
}

/////////////////////////////////////////////////////////////////////////////
LocalINCLIonIonInelasticPhysic::~LocalINCLIonIonInelasticPhysic()
{}

/////////////////////////////////////////////////////////////////////////////
void LocalINCLIonIonInelasticPhysic::ConstructProcess()
{
  G4ParticleDefinition* particle = 0;
  G4ProcessManager* processManager = 0;

  // ****************************************************************
  // ***                Ion-Ion models definition                 ***
  // ****************************************************************
  G4QMDReaction* JQMDmodel = new G4QMDReaction();
  JQMDmodel -> SetMinEnergy(0*MeV);
  JQMDmodel -> SetMaxEnergy(10*GeV);

  G4BinaryLightIonReaction* lightBinary = new G4BinaryLightIonReaction();
  lightBinary -> SetMinEnergy(0*MeV);
  lightBinary -> SetMaxEnergy(10*GeV);  

  G4WilsonAbrasionModel* WilsonModel = new G4WilsonAbrasionModel();
  WilsonModel -> SetUseAblation(true);
  WilsonModel -> SetMinEnergy(0*MeV);
  WilsonModel -> SetMaxEnergy(10 *GeV);

//  G4InclAblaLightIonInterface* INCLIonModel = new G4InclAblaLightIonInterface();

  G4TripathiCrossSection* TripatiCrossSections = new G4TripathiCrossSection;
  G4TripathiCrossSection* TripatiLightCrossSections = new G4TripathiCrossSection;
  G4IonsShenCrossSection* ShenCrossSections = new G4IonsShenCrossSection;

  // ****************
  // *** Deuteron ***
  // ****************
  G4DeuteronInelasticProcess* deuteronInelasticProcess = new G4DeuteronInelasticProcess;

  deuteronInelasticProcess -> AddDataSet(ShenCrossSections);
  deuteronInelasticProcess -> AddDataSet(TripatiCrossSections);
  deuteronInelasticProcess -> AddDataSet(TripatiLightCrossSections);

  //deuteronInelasticProcess -> RegisterMe(INCLIonModel);
  //deuteronInelasticProcess -> RegisterMe(lightBinary);
  deuteronInelasticProcess -> RegisterMe(JQMDmodel);
  //deuteronInelasticProcess -> RegisterMe(WilsonModel);

  particle = G4Deuteron::Deuteron();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(deuteronInelasticProcess);

  // **************
  // *** Triton ***
  // **************
  G4TritonInelasticProcess* tritonInelasticProcess = new G4TritonInelasticProcess;

  tritonInelasticProcess -> AddDataSet(ShenCrossSections);
  tritonInelasticProcess -> AddDataSet(TripatiCrossSections);
  tritonInelasticProcess -> AddDataSet(TripatiLightCrossSections);

  //tritonInelasticProcess -> RegisterMe(INCLIonModel);
  //tritonInelasticProcess -> RegisterMe(lightBinary);
  tritonInelasticProcess -> RegisterMe(JQMDmodel);
  //tritonInelasticProcess -> RegisterMe(WilsonModel);
  
  particle = G4Triton::Triton();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(tritonInelasticProcess);
 
  // *************
  // *** He3   ***
  // *************
  /*
  G4He3InelasticProcess* he3InelasticProcess = new G4He3InelasticProcess;
  
  he3InelasticProcess -> AddDataSet(ShenCrossSections);
  he3InelasticProcess -> AddDataSet(TripatiCrossSections);
  he3InelasticProcess -> AddDataSet(TripatiLightCrossSections);

  he3InelasticProcess -> RegisterMe(INCLIonModel);

  particle = G4He3::He3();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(he3InelasticProcess);           
  */
  // *************
  // *** Alpha ***
  // *************
  G4AlphaInelasticProcess* alphaInelasticProcess = new G4AlphaInelasticProcess;
  
  alphaInelasticProcess -> AddDataSet(ShenCrossSections);
  alphaInelasticProcess -> AddDataSet(TripatiCrossSections);
  alphaInelasticProcess -> AddDataSet(TripatiLightCrossSections);

  //alphaInelasticProcess -> RegisterMe(INCLIonModel);
  //alphaInelasticProcess -> RegisterMe(lightBinary);
 alphaInelasticProcess -> RegisterMe(JQMDmodel);
 //alphaInelasticProcess -> RegisterMe(WilsonModel);

  particle = G4Alpha::Alpha();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(alphaInelasticProcess);           

  // *******************
  // *** Generic Ion ***
  // *******************
  G4IonInelasticProcess* genericIonInelasticProcess = new G4IonInelasticProcess();

  genericIonInelasticProcess -> AddDataSet(ShenCrossSections);
  genericIonInelasticProcess -> AddDataSet(TripatiCrossSections);
  genericIonInelasticProcess -> AddDataSet(TripatiLightCrossSections);

  //genericIonInelasticProcess -> RegisterMe(lightBinary);
  genericIonInelasticProcess -> RegisterMe(JQMDmodel);
  //genericIonInelasticProcess -> RegisterMe(WilsonModel);
  
  particle = G4GenericIon::GenericIon();
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(genericIonInelasticProcess);
}



