//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
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
// HadrontherapyAnalysisManager.hh; May 2005
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy

#ifndef HADRONTHERAPYANALYSISMANAGER_HH
#define HADRONTHERAPYANALYSISMANAGER_HH 1

#include "globals.hh"

#ifdef ANALYSIS_USE ///< If we use analysis

#ifdef G4ANALYSIS_USE ///< If analysis is done via AIDA
#include <AIDA/AIDA.h>

namespace AIDA{
  class ITree;
  class IAnalysisFactory;
  class ITreeFactory;
}
#endif

#ifdef G4ANALYSIS_USE_ROOT ///< If analysis is done directly with ROOT
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TH1F.h"
#endif

/**
 * Messenger class for analysis-settings for HadronTherapyAnalysisManager 
 */
class HadrontherapyAnalysisFileMessenger;

/**
 * A class for connecting the simulation to an analysis package.
 */
class HadrontherapyAnalysisManager
{
private:
	/**
	 * Analysis manager is a singleton object (there is only one instance).
	 * The pointer to this object is available through the use of the method getInstance();
	 *
	 * @see getInstance
	 */
  HadrontherapyAnalysisManager();
  
public:
  ~HadrontherapyAnalysisManager();

  /**
   * Get the pointer to the analysis manager.
   */
  static HadrontherapyAnalysisManager* getInstance();

  /**
  * Book the histograms and ntuples in an AIDA or ROOT file.
  */
  void book();
  /**
   * Set name for the analysis file .root (used by macro)
   */
  void SetAnalysisFileName(G4String);
  
  /**
  * Fill the ntuple with the energy deposit in the phantom
  */
  void FillEnergyDeposit(G4int voxelXId, G4int voxelYId, G4int voxelZId,
                         G4double energyDeposit);

  void BraggPeak(G4int, G4double); ///< Fill 1D histogram with the Bragg peak in the phantom

  void SecondaryProtonEnergyDeposit(G4int slice, G4double energy);
  ///< Fill 1D histogram with the energy deposit of secondary protons

   void SecondaryNeutronEnergyDeposit(G4int slice, G4double energy);
  ///< Fill 1D histogram with the energy deposit of secondary neutrons

  void SecondaryAlphaEnergyDeposit(G4int slice, G4double energy);
  ///< Fill 1D histogram with the energy deposit of secondary alpha particles

  void SecondaryGammaEnergyDeposit(G4int slice, G4double energy);
  ///< Fill 1D histogram with the energy deposit of secondary gamma

  void SecondaryElectronEnergyDeposit(G4int slice, G4double energy);
  ///< Fill 1D histogram with the energy deposit of secondary electrons

  void SecondaryTritonEnergyDeposit(G4int slice, G4double energy);
  ///< Fill 1D histogram with the energy deposit of secondary tritons

  void SecondaryDeuteronEnergyDeposit(G4int slice, G4double energy);
  ///< Fill 1D histogram with the energy deposit of secondary deuterons

  void SecondaryPionEnergyDeposit(G4int slice, G4double energy);
  ///< Fill 1D histogram with the energy deposit of secondary pions

  void electronEnergyDistribution(G4double secondaryParticleKineticEnergy);
  ///< Energy distribution of secondary electrons originated in the phantom

  void gammaEnergyDistribution(G4double secondaryParticleKineticEnergy);
  ///< Energy distribution of secondary gamma originated in the phantom

  void deuteronEnergyDistribution(G4double secondaryParticleKineticEnergy);
  ///< Energy distribution of secondary deuterons originated in the phantom

  void tritonEnergyDistribution(G4double secondaryParticleKineticEnergy);
  ///< Energy distribution of secondary tritons originated in the phantom

  void alphaEnergyDistribution(G4double secondaryParticleKineticEnergy);
  ///< Energy distribution of secondary alpha originated in the phantom

  void heliumEnergy(G4double secondaryParticleKineticEnergy);
  ///< Energy distribution of the helium (He3 and alpha) particles after the phantom

  void hydrogenEnergy(G4double secondaryParticleKineticEnergy);
  ///< Energy distribution of the hydrogen (proton, d, t) particles after the phantom

  void fillFragmentTuple(G4int A, G4double Z, G4double energy, G4double posX, G4double posY, G4double posZ);
  ///< Energy ntuple

  void genericIonInformation(G4int, G4double, G4int, G4double);

  void ThintargetBeamDisp(G4double,G4double);

  void startNewEvent();
  ///< Tell the analysis manager that a new event is starting

  void setGeometryMetaData(G4double, G4double, G4double);
  ///< from the detector construction information about the geometry can be written as metadata

  void setBeamMetaData(G4double, G4double);
  ///< metadata about the beam can be written this way

  void finish();
  ///< Close the .hbk file with the histograms and the ntuples

void flush();

#ifdef G4ANALYSIS_USE_ROOT
private:
  TH1F *createHistogram1D(const TString name, const TString title, int bins, double xmin, double xmax) {
    TH1F *histo = new TH1F(name, title, bins, xmin, xmax);
    histo->SetLineWidth(2);
    return histo;
  }
#endif

private:
  static HadrontherapyAnalysisManager* instance;
  HadrontherapyAnalysisFileMessenger* fMess;
  G4String analysisFileName;
#ifdef G4ANALYSIS_USE
  AIDA::IAnalysisFactory* aFact;
  AIDA::ITree* theTree;
  AIDA::IHistogramFactory *histFact;
  AIDA::ITupleFactory *tupFact;
  AIDA::IHistogram1D *h1;
  AIDA::IHistogram1D *h2;
  AIDA::IHistogram1D *h3;
  AIDA::IHistogram1D *h4;
  AIDA::IHistogram1D *h5;
  AIDA::IHistogram1D *h6;
  AIDA::IHistogram1D *h7;
  AIDA::IHistogram1D *h8;
  AIDA::IHistogram1D *h9;
  AIDA::IHistogram1D *h10;
  AIDA::IHistogram1D *h11;
  AIDA::IHistogram1D *h12;
  AIDA::IHistogram1D *h13;
  AIDA::IHistogram1D *h14;
  AIDA::IHistogram1D *h15;
  AIDA::IHistogram1D *h16;
  AIDA::ITuple *ntuple;
  AIDA::ITuple *ionTuple;
  AIDA::ITuple *fragmentTuple;
#endif
#ifdef G4ANALYSIS_USE_ROOT
  TFile *theTFile;
  TH1F *histo1;
  TH1F *histo2;
  TH1F *histo3;
  TH1F *histo4;
  TH1F *histo5;
  TH1F *histo6;
  TH1F *histo7;
  TH1F *histo8;
  TH1F *histo9;
  TH1F *histo10;
  TH1F *histo11;
  TH1F *histo12;
  TH1F *histo13;
  TH1F *histo14;
  TH1F *histo15;
  TH1F *histo16;
  
  TNtuple *theROOTNtuple;
  TNtuple *theROOTIonTuple;
  TNtuple *fragmentNtuple; // fragments
  TNtuple *metaData;
#endif
  G4long eventCounter;      // Simulation metadata
  G4double detectorDistance;
  G4double phantomDepth;
  G4double beamEnergy;
  G4double energyError;
  G4double phantomCenterDistance;
};
#endif

#endif

