#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TRandom3.h"
#include "TFile.h"
#include "THnSparse.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include "AliESDEvent.h"
#include "AliESDInputHandler.h"
#include "AliAODEvent.h"
#include "AliAODInputHandler.h"
#include "AliMCEventHandler.h"
#include "AliMCEvent.h"
#include "AliMCParticle.h"
#include "AliCentrality.h"
#include "AliMultSelection.h"
#include "AliESDVZERO.h"
#include "AliESDpid.h"
#include "AliAODv0KineCuts.h"
#include "AliESDtrack.h"
#include "AliAnalysisTaskHFEBeautyMCTemplatesRun2.h"
#include "AliHFEpidTOF.h"
#include "AliHFEpid.h"
#include "AliHFEtools.h"
#include "AliHFEsignalCuts.h"
#include "AliHFEmcQA.h"
#include "AliAODMCParticle.h"
//#include "AliESDTrdTracklet.h"
//#include "AliTRDgeometry.h"
//#include "AliHFEcuts.h"
#include "AliHFEpid.h"
#include "AliHFEpidQAmanager.h"
#include "AliHFEtools.h"
#include "AliHFEVZEROEventPlane.h"
#include "AliEventplane.h"
#include <AliOADBContainer.h>


ClassImp(AliAnalysisTaskHFEBeautyMCTemplatesRun2)

//________________________________________________________________________
AliAnalysisTaskHFEBeautyMCTemplatesRun2::AliAnalysisTaskHFEBeautyMCTemplatesRun2()
  : AliAnalysisTaskSE(), fAOD(0), fOutputContainer(0), fSignalCuts(0), fExtraCuts(0), fAODArrayMCInfo(0), fCentrality(0), fDCACharm(0), fDCABeauty(0), fDCAConversion(0), fDCADalitz(0), fDCACharmNew(0), fDCABeautyNew(0), fDCAConversionNew(0), fDCADalitzNew(0), fDCADalitzCharm(0), fDCADalitzBeauty(0), fDCAConversionCharm(0), fDCAConversionBeauty(0), fAODV0Cuts(0), fBeautyMotherpT(0), fCharmMotherpT(0), fGroundStateBeautyMotherpT(0), fGroundStateCharmMotherpT(0), fRd(0), fDCACharm3050(0), fDCACharm3050IP(0), fDCACharm3050OOP(0), fDCACharmNew3050(0), fDCACharmNew3050IP(0), fDCACharmNew3050OOP(0), fDCABeautyHalfRAA(0), fDCABeautyHalfRAAIP(0), fDCABeautyHalfRAAOOP(0), fDCABeautyRAA(0), fDCABeautyRAAIP(0), fDCABeautyRAAOOP(0), fDCABeautyNewHalfRAA(0), fDCABeautyNewHalfRAAIP(0), fDCABeautyNewHalfRAAOOP(0), fDCABeautyNewRAA(0), fDCABeautyNewRAAIP(0), fDCABeautyNewRAAOOP(0), fDCAHadrons(0), fDCAWErrHadrons(0), fDCAHadronsFineBins(0), fDCAKaons(0), fDCAWErrKaons(0), fDCAKaonsFineBins(0), fDCAHadronsCorrected(0), fPionV0pTRNoCuts(0), fPionV0pTRWithCuts(0)
{
  
}

//________________________________________________________________________
AliAnalysisTaskHFEBeautyMCTemplatesRun2::AliAnalysisTaskHFEBeautyMCTemplatesRun2(const char *name)
  : AliAnalysisTaskSE(name), fAOD(0), fOutputContainer(0), fSignalCuts(0), fExtraCuts(0), fAODArrayMCInfo(0), fCentrality(0), fDCACharm(0), fDCABeauty(0), fDCAConversion(0), fDCADalitz(0), fDCACharmNew(0), fDCABeautyNew(0), fDCAConversionNew(0), fDCADalitzNew(0), fDCADalitzCharm(0), fDCADalitzBeauty(0), fDCAConversionCharm(0), fDCAConversionBeauty(0), fAODV0Cuts(0), fBeautyMotherpT(0), fCharmMotherpT(0), fGroundStateBeautyMotherpT(0), fGroundStateCharmMotherpT(0), fRd(0), fDCACharm3050(0), fDCACharm3050IP(0), fDCACharm3050OOP(0), fDCACharmNew3050(0), fDCACharmNew3050IP(0), fDCACharmNew3050OOP(0), fDCABeautyHalfRAA(0), fDCABeautyHalfRAAIP(0), fDCABeautyHalfRAAOOP(0), fDCABeautyRAA(0), fDCABeautyRAAIP(0), fDCABeautyRAAOOP(0), fDCABeautyNewHalfRAA(0), fDCABeautyNewHalfRAAIP(0), fDCABeautyNewHalfRAAOOP(0), fDCABeautyNewRAA(0), fDCABeautyNewRAAIP(0), fDCABeautyNewRAAOOP(0), fDCAHadrons(0), fDCAWErrHadrons(0), fDCAHadronsFineBins(0), fDCAKaons(0), fDCAWErrKaons(0), fDCAKaonsFineBins(0), fDCAHadronsCorrected(0), fPionV0pTRNoCuts(0), fPionV0pTRWithCuts(0)
{
  // Constructor
  // Define input and output slots here
  // Input slot #0 works with a TChain
   DefineInput(0, TChain::Class());
  // Output slot #0 writes into a TH1 container
  //DefineOutput(1, TObjArray::Class());
    DefineOutput(1, TList::Class());
    //    DefineOutput(2, TNtuple::Class());
    

}

AliAnalysisTaskHFEBeautyMCTemplatesRun2::~AliAnalysisTaskHFEBeautyMCTemplatesRun2()
{
}


//________________________________________________________________________
void AliAnalysisTaskHFEBeautyMCTemplatesRun2::UserCreateOutputObjects()
{
  // Set up HFE objects:
  fSignalCuts = new AliHFEsignalCuts("HFEsignalCuts", "HFE MC Signal definition");
  fExtraCuts = new AliHFEextraCuts("hfeExtraCuts","HFE Extra Cuts");
  fAODV0Cuts = new AliAODv0KineCuts();

  // Create histograms
  // Called once
    Double_t ptbinningX[19] = {0., 0.1, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 2., 2.5, 3., 4., 6., 8., 10., 12., 16., 20.}; // Apr 2018 binning
    
    fCentrality = new TH1D(Form("fCentrality"),Form("fCentrality"), 20, 0., 100.);
    //fSourceGenerator = new TH2D(Form("fSourceGenerator"),Form("fSourceGenerator"), 10, -0.5, 9.5, 20, -1.5, 18.5);
    fDCACharm = new TH2D(Form("fDCACharm"),Form("fDCACharm"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCACharm3050 = new TH2D(Form("fDCACharm3050"),Form("fDCACharm3050"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCACharm3050IP = new TH2D(Form("fDCACharm3050IP"),Form("fDCACharm3050IP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCACharm3050OOP = new TH2D(Form("fDCACharm3050OOP"),Form("fDCACharm3050OOP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeauty = new TH2D(Form("fDCABeauty"),Form("fDCABeauty"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyHalfRAA = new TH2D(Form("fDCABeautyHalfRAA"),Form("fDCABeautyHalfRAA"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyHalfRAAIP = new TH2D(Form("fDCABeautyHalfRAAIP"),Form("fDCABeautyHalfRAAIP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyHalfRAAOOP = new TH2D(Form("fDCABeautyHalfRAAOOP"),Form("fDCABeautyHalfRAAOOP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyRAA = new TH2D(Form("fDCABeautyRAA"),Form("fDCABeautyRAA"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyRAAIP = new TH2D(Form("fDCABeautyRAAIP"),Form("fDCABeautyRAAIP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyRAAOOP = new TH2D(Form("fDCABeautyRAAOOP"),Form("fDCABeautyRAAOOP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCAConversion = new TH2D(Form("fDCAConversion"),Form("fDCAConversion"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCADalitz = new TH2D(Form("fDCADalitz"),Form("fDCADalitz"), 18, ptbinningX, 400, -0.2, 0.2);

    fDCACharmNew = new TH2D(Form("fDCACharmNew"),Form("fDCACharmNew"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCACharmNew3050 = new TH2D(Form("fDCACharmNew3050"),Form("fDCACharmNew3050"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCACharmNew3050IP = new TH2D(Form("fDCACharmNew3050IP"),Form("fDCACharmNew3050IP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCACharmNew3050OOP = new TH2D(Form("fDCACharmNew3050OOP"),Form("fDCACharmNew3050OOP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyNew = new TH2D(Form("fDCABeautyNew"),Form("fDCABeautyNew"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyNewHalfRAA = new TH2D(Form("fDCABeautyNewHalfRAA"),Form("fDCABeautyNewHalfRAA"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyNewHalfRAAIP = new TH2D(Form("fDCABeautyNewHalfRAAIP"),Form("fDCABeautyNewHalfRAAIP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyNewHalfRAAOOP = new TH2D(Form("fDCABeautyNewHalfRAAOOP"),Form("fDCABeautyNewHalfRAAOOP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyNewRAA = new TH2D(Form("fDCABeautyNewRAA"),Form("fDCABeautyNewRAA"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyNewRAAIP = new TH2D(Form("fDCABeautyNewRAAIP"),Form("fDCABeautyNewRAAIP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCABeautyNewRAAOOP = new TH2D(Form("fDCABeautyNewRAAOOP"),Form("fDCABeautyNewRAAOOP"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCAConversionNew = new TH2D(Form("fDCAConversionNew"),Form("fDCAConversionNew"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCADalitzNew = new TH2D(Form("fDCADalitzNew"),Form("fDCADalitzNew"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCADalitzCharm = new TH2D(Form("fDCADalitzCharm"),Form("fDCADalitzCharm"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCADalitzBeauty = new TH2D(Form("fDCADalitzBeauty"),Form("fDCADalitzBeauty"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCAConversionCharm = new TH2D(Form("fDCAConversionCharm"),Form("fDCAConversionCharm"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCAConversionBeauty = new TH2D(Form("fDCAConversionBeauty"),Form("fDCAConversionBeauty"), 18, ptbinningX, 400, -0.2, 0.2);

    fDCAHadrons = new TH2D(Form("fDCAHadrons"),Form("fDCAHadrons"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCAWErrHadrons = new TH3D(Form("fDCAWErrHadrons"),Form("fDCAWErrHadrons"), 80, 0., 10., 400, -0.2, 0.2, 100, 0.0, 0.01);
    fDCAHadronsFineBins = new TH3D(Form("fDCAHadronsFineBins"),Form("fDCAHadronsFineBins"), 80, 0., 10., 400, -0.2, 0.2, 10, 0., 100.);
    fDCAKaons = new TH2D(Form("fDCAKaons"),Form("fDCAKaons"), 18, ptbinningX, 400, -0.2, 0.2);
    fDCAWErrKaons = new TH3D(Form("fDCAWErrKaons"),Form("fDCAWErrKaons"), 80, 0., 10., 400, -0.2, 0.2, 100, 0.0, 0.01);
    fDCAKaonsFineBins = new TH3D(Form("fDCAKaonsFineBins"),Form("fDCAKaonsFineBins"), 80, 0., 10., 400, -0.2, 0.2, 10, 0., 100.);
    fDCAHadronsCorrected = new TH2D(Form("fDCAHadronsCorrected"),Form("fDCAHadronsCorrected"), 18, ptbinningX, 400, -0.2, 0.2);
    

    fBeautyMotherpT = new TH1D(Form("fBeautyMotherpT"),Form("fBeautyMotherpT"), 40, 0., 20.);
    fCharmMotherpT = new TH1D(Form("fCharmMotherpT"),Form("fCharmMotherpT"), 40, 0., 20.);
    fGroundStateBeautyMotherpT = new TH1D(Form("fGroundStateBeautyMotherpT"),Form("fGroundStateBeautyMotherpT"), 40, 0., 20.);
    fGroundStateCharmMotherpT = new TH1D(Form("fGroundStateCharmMotherpT"),Form("fGroundStateCharmMotherpT"), 40, 0., 20.);

    fPionV0pTRNoCuts = new TH3D(Form("fPionV0pTRNoCuts"),Form("fPionV0pTRNoCuts"), 40, 0., 10., 80, 0., 20., 10, 0., 100.);
    fPionV0pTRWithCuts = new TH3D(Form("fPionV0pTRWithCuts"),Form("fPionV0pTRWithCuts"), 40, 0., 10., 80, 0., 20., 10, 0., 100.);

    fRd = new TRandom3(0);
    
    fOutputContainer = new TObjArray(1);
    fOutputContainer->SetName(GetName());
    fOutputContainer->SetOwner();
    fOutputContainer->Add(fCentrality);
    fOutputContainer->Add(fDCACharm);
    fOutputContainer->Add(fDCACharm3050);
    fOutputContainer->Add(fDCACharm3050IP);
    fOutputContainer->Add(fDCACharm3050OOP);
    fOutputContainer->Add(fDCABeauty);
    fOutputContainer->Add(fDCABeautyHalfRAA);
    fOutputContainer->Add(fDCABeautyHalfRAAIP);
    fOutputContainer->Add(fDCABeautyHalfRAAOOP);
    fOutputContainer->Add(fDCABeautyRAA);
    fOutputContainer->Add(fDCABeautyRAAIP);
    fOutputContainer->Add(fDCABeautyRAAOOP);
    fOutputContainer->Add(fDCAConversion);
    fOutputContainer->Add(fDCADalitz);
    fOutputContainer->Add(fDCACharmNew);
    fOutputContainer->Add(fDCACharmNew3050);
    fOutputContainer->Add(fDCACharmNew3050IP);
    fOutputContainer->Add(fDCACharmNew3050OOP);
    fOutputContainer->Add(fDCABeautyNew);
    fOutputContainer->Add(fDCABeautyNewHalfRAA);
    fOutputContainer->Add(fDCABeautyNewHalfRAAIP);
    fOutputContainer->Add(fDCABeautyNewHalfRAAOOP);
    fOutputContainer->Add(fDCABeautyNewRAA);
    fOutputContainer->Add(fDCABeautyNewRAAIP);
    fOutputContainer->Add(fDCABeautyNewRAAOOP);
    fOutputContainer->Add(fDCAConversionNew);
    fOutputContainer->Add(fDCADalitzNew);
    fOutputContainer->Add(fDCADalitzCharm);
    fOutputContainer->Add(fDCADalitzBeauty);
    fOutputContainer->Add(fDCAConversionCharm);
    fOutputContainer->Add(fDCAConversionBeauty);
    fOutputContainer->Add(fBeautyMotherpT);
    fOutputContainer->Add(fCharmMotherpT);
    fOutputContainer->Add(fGroundStateBeautyMotherpT);
    fOutputContainer->Add(fGroundStateCharmMotherpT);
    fOutputContainer->Add(fDCAHadrons);
    fOutputContainer->Add(fDCAWErrHadrons);
    fOutputContainer->Add(fDCAHadronsFineBins);
    fOutputContainer->Add(fDCAKaons);
    fOutputContainer->Add(fDCAWErrKaons);
    fOutputContainer->Add(fDCAKaonsFineBins);
    fOutputContainer->Add(fDCAHadronsCorrected);
    fOutputContainer->Add(fPionV0pTRNoCuts);
    fOutputContainer->Add(fPionV0pTRWithCuts);

    PostData(1, fOutputContainer);
    
}

Int_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::FindSource(AliMCParticle * mcple, AliMCEvent* fMCEvent, Double_t &motherPt, Double_t &GroundStateMotherPt)
{
  motherPt = 0.;
  GroundStateMotherPt = 0.; // Just for safety
  Bool_t HasPhotonAncestor = kFALSE;
  Bool_t HasJPsiAncestor = kFALSE;
  Bool_t HasStrangeAncestor = kFALSE;
  Bool_t HasCharmedAncestor = kFALSE;
  AliMCParticle * mother;
  Int_t pdgCode = 0;
  mother=mcple;
  while(mother!=0)
  {
    pdgCode = TMath::Abs(mother->PdgCode());
    motherPt = mother->Pt();
    if(pdgCode%10==1)
      GroundStateMotherPt = mother->Pt();
    if(pdgCode == 22) HasPhotonAncestor = kTRUE;
    if(pdgCode == 443) HasJPsiAncestor = kTRUE;
    if((pdgCode >= 300 && pdgCode <= 399) || (pdgCode >= 3000 && pdgCode <= 3999)) HasStrangeAncestor = kTRUE;
    if((pdgCode >= 400 && pdgCode <= 499) || (pdgCode >= 4000 && pdgCode <= 4999)) HasCharmedAncestor = kTRUE;
    if(mother->GetMother() > 0)
      if(TMath::Abs(((AliMCParticle*) fMCEvent->GetTrack(mother->GetMother()))->PdgCode())<10) break;
    if(mother->GetMother() > 0)
        mother =  (AliMCParticle*) fMCEvent->GetTrack(mother->GetMother());
    else mother = 0x0;
  }
  if(HasJPsiAncestor) return 4;
  if(pdgCode == 5 || (pdgCode >= 500 && pdgCode <= 599) || (pdgCode >= 5000 && pdgCode <= 5999)) return 1; // Beauty
  if(pdgCode == 4 || (pdgCode >= 400 && pdgCode <= 499) || (pdgCode >= 4000 && pdgCode <= 4999)) return 0; // Charm
  if(HasPhotonAncestor) return 2; // Conversion but not from charm, beauty or strangeness
  if(true) return 3; // Dalitz !HasStrangeAncestor - 
        
  return 7;
}

Int_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::MotherPDG(AliMCParticle * mcple, AliMCEvent* fMCEvent)
{
  AliMCParticle * mother = (AliMCParticle*) fMCEvent->GetTrack(mcple->GetMother());
  if(mother)
    return mother->PdgCode();
  else
    return 0;
}

void AliAnalysisTaskHFEBeautyMCTemplatesRun2::PrintHierarchy(AliMCParticle * mcple, AliMCEvent* fMCEvent)
{
  AliMCParticle * mother;
  Int_t pdgCode = 0;
  mother=mcple;
  //std::cout << "Decay chain: " ;
  while(mother!=0)
  {
    pdgCode = mother->PdgCode();
    //std::cout << pdgCode << " " ;
    mother =  (AliMCParticle*) fMCEvent->GetTrack(mother->GetMother());
  }
  //mother =  (AliMCParticle*) fMCEvent->GetTrack((mcple->Particle())->GetFirstMother());
  //std::cout << std::endl;
  
}


Bool_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::PassesTrackCuts(AliAODTrack *track)
{
    if(TMath::Abs(track->Eta())>0.8) return kFALSE;
    ULong_t status = track->GetStatus();
    // Basic tracking
    if(!((status & AliVTrack::kITSrefit) && (status & AliVTrack::kTPCrefit))) return kFALSE;
    // ITS tracking
    if(!(track->HasPointOnITSLayer(0) && track->HasPointOnITSLayer(1) && track->GetITSNcls()>=4)) return kFALSE;
    Int_t nclustersITS(track->GetITSclusters(NULL)),
          nclustersTPC(track->GetTPCNcls()),
          nclustersTPCall(track->GetTPCClusterMap().CountBits()),
          nclustersTPCshared(0);
    UChar_t nfindableTPC = track->GetTPCNclsF();
    Double_t FoundOverFindable = (nfindableTPC ? static_cast<Float_t>(nclustersTPC)/static_cast<Float_t>(nfindableTPC) : 0);
    // TPC Quality
    if(!(track->GetTPCNcls()>=110 && track->GetTPCsignalN()>=80 && FoundOverFindable>0.6 && track->GetTPCchi2()/Double_t(nclustersTPC)<4.)) return kFALSE;
    // ITS Quality
    if(track->GetITSchi2()/double(track->GetITSNcls()) > 10.) return kFALSE; 
      UChar_t ITSShared = track->GetITSSharedClusterMap();
      Int_t nSharedITS = 0;
      for(int i=0;i<6;i++)
          if((ITSShared >> i) & 1)
              nSharedITS++;
    if(nSharedITS > 3) return kFALSE; 
    // TOF quality
    //if(!((status & AliVTrack::kTOFpid))) return kFALSE; // Does not work for run2 data!
    return kTRUE;
}

Bool_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::PassesMinimalTrackCuts(AliAODTrack *track)
{
    if(TMath::Abs(track->Eta())>0.8) return kFALSE;
    ULong_t status = track->GetStatus();
    // Basic tracking
    if(!((status & AliVTrack::kITSrefit) && (status & AliVTrack::kTPCrefit))) return kFALSE;
    return kTRUE;
}

Bool_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::PassesITSTrackCuts(AliAODTrack *track)
{
    if(TMath::Abs(track->Eta())>0.8) return kFALSE;
    ULong_t status = track->GetStatus();
    // Basic tracking
    if(!((status & AliVTrack::kITSrefit) && (status & AliVTrack::kTPCrefit))) return kFALSE;
    // ITS tracking
    if(!(track->HasPointOnITSLayer(0) && track->HasPointOnITSLayer(1) && track->GetITSNcls()>=4)) return kFALSE;
    Int_t nclustersITS(track->GetITSclusters(NULL)),
          nclustersTPC(track->GetTPCNcls()),
          nclustersTPCall(track->GetTPCClusterMap().CountBits()),
          nclustersTPCshared(0);
    // ITS Quality
    if(track->GetITSchi2()/double(track->GetITSNcls()) > 10.) return kFALSE; 
      UChar_t ITSShared = track->GetITSSharedClusterMap();
      Int_t nSharedITS = 0;
      for(int i=0;i<6;i++)
          if((ITSShared >> i) & 1)
              nSharedITS++;
    if(nSharedITS > 3) return kFALSE; 
    return kTRUE;
}

Bool_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::PassesElectronPID(AliAODTrack *track, AliPIDResponse *pid)
{
    if(pid->NumberOfSigmasTPC(track, AliPID::kElectron) >3. || pid->NumberOfSigmasTPC(track, AliPID::kElectron) <-0.5) return kFALSE;
    if(TMath::Abs(pid->NumberOfSigmasTOF(track, AliPID::kElectron))>3.) return kFALSE;
    return kTRUE;
}

Bool_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::PassesPionPID(AliAODTrack *track, AliPIDResponse *pid)
{
  //std::cout << "TPC pion: " << pid->NumberOfSigmasTPC(track, AliPID::kPion) << " TOF: " << pid->NumberOfSigmasTOF(track, AliPID::kPion) << " electron: " << pid->NumberOfSigmasTOF(track, AliPID::kElectron)  << std::endl;
    if(pid->NumberOfSigmasTPC(track, AliPID::kPion) > 3. || pid->NumberOfSigmasTPC(track, AliPID::kPion) < -1.) return kFALSE;
    if(TMath::Abs(pid->NumberOfSigmasTOF(track, AliPID::kPion))>3.) return kFALSE; // Should be basically same as electron
    return kTRUE;
}

Bool_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::PassesKaonPID(AliAODTrack *track, AliPIDResponse *pid)
{
    if(pid->NumberOfSigmasTPC(track, AliPID::kKaon) >3. || pid->NumberOfSigmasTPC(track, AliPID::kKaon) <-3.) return kFALSE;
    if(TMath::Abs(pid->NumberOfSigmasTOF(track, AliPID::kKaon))>2.) return kFALSE;
    return kTRUE;
}


Bool_t AliAnalysisTaskHFEBeautyMCTemplatesRun2::IsAddedSignal(AliMCParticle * mcple)
{
  if(mcple->GetGeneratorIndex()>0)
    return kTRUE;
  else
    return kFALSE;
}



//_____________________________________________________________________________
void AliAnalysisTaskHFEBeautyMCTemplatesRun2::UserExec(Option_t *)
{
  //
  // Called for each event
    //
    

    //AliESDInputHandler *esdH = dynamic_cast<AliESDInputHandler*> (AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
    //AliAODInputHandler *aodH = dynamic_cast<AliAODInputHandler*> (AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
    fAOD = dynamic_cast<AliAODEvent*>(InputEvent());

    if (!fAOD)
    {
	printf("ERROR: Could not get AODInputHandler \n");
    }
    else fAOD = dynamic_cast<AliAODEvent*>(InputEvent());


    Process(fAOD);


    // Post output data.
    //PostData(1, fOutput);
    //PostData(1, fOutputContainer);
    //    PostData(2, rec);
    //    PostData(2, treeoutput);
}

//________________________________________________________________________
void AliAnalysisTaskHFEBeautyMCTemplatesRun2::Process(AliAODEvent *const aodEvent)
{
  // Main loop
  // Called for each event
  //if(!(((AliInputEventHandler*)(AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler()))->IsEventSelected() & (AliVEvent::kCentral | AliVEvent::kSemiCentral | AliVEvent::kMB))) //return;
  if (!aodEvent) {
    Printf("ERROR: aodEvent not available");
    return;
  }
  AliInputEventHandler* handler = dynamic_cast<AliInputEventHandler*>( AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
  if(!(handler)) printf("AOD inputhandler not available \n");

  fAODArrayMCInfo = dynamic_cast<TClonesArray *>(aodEvent->FindListObject(AliAODMCParticle::StdBranchName())); // This is needed by the GetSignalSource function

  AliMCEvent* fMCEvent=0;
  fMCEvent = handler->MCEvent();
  if(!fMCEvent)
    return;

  AliPIDResponse *pid = NULL;
  if(handler){
    pid = handler->GetPIDResponse();
  } else {
    AliError("No Handler");
  }
  if(!pid){
    AliError("No PID response");
    return;
  }
  fExtraCuts->SetRecEventInfo(aodEvent);
  fSignalCuts->SetMCAODInfo(fAODArrayMCInfo);
  
  Float_t centrality = -1.;
  Float_t fV0Cent = -999.;
  Float_t fV0CentCalib = -999.;

  //AliCentrality *hicent = aodEvent->GetCentrality();
  //centrality = hicent->GetCentralityPercentile("V0M");
  AliMultSelection *MultSelection = 0x0;
  MultSelection = (AliMultSelection*)aodEvent->FindListObject("MultSelection");
  if(!MultSelection){
    AliWarning("AliMultSelection object not found!");
  }else{
    fV0Cent = MultSelection->GetMultiplicityPercentile("V0M", false);
    fV0CentCalib = MultSelection->GetMultiplicityPercentile("V0M", true);
    centrality = fV0CentCalib;
  }
  
  const AliAODVertex *vertex = aodEvent->GetPrimaryVertex();
  const AliAODVertex *vertexSPD = aodEvent->GetPrimaryVertexSPD();
  Double_t vcov[6];
  vertex->GetCovMatrix(vcov);
  Double_t vtx[3];
  Double_t vtxSPD[3];
  vertex->GetXYZ(vtx);
  vertexSPD->GetXYZ(vtxSPD);

  bool analyzeEvent=(centrality>=0.0 && centrality<=90.0 && TMath::Sqrt(vcov[5]) < 0.25 && TMath::Abs(vtx[2])<10. && TMath::Abs(vtx[2] - vtxSPD[2]) < 0.5);
  //hfetrackCuts->SetRecEvent(aodEvent);

  int nTracks = aodEvent->GetNumberOfTracks();
  int nMCPles = fMCEvent->GetNumberOfTracks(); // Actually return # of MC particles, not tracks, it seems (fMCParticles)
  int nMCPrimaries = fMCEvent->GetNumberOfPrimaries();
  fCentrality->Fill(centrality);
  AliMCParticle * mcple;
  AliMCParticle * mother;
  AliAODv0 * v0;
  AliAODTrack* V0Daughter[2];
  Int_t V0MotherPdg, V0Daughter1Pdg, V0Daughter2Pdg;
  Double_t MotherPt=0., GSMotherPt=0.;
  int pdgCode=0;
  AliAODTrack *track = 0x0;
  double radius =0., recoRadius=0.;
  Double_t dcaErr, dcaxyD;
  Double_t pt = 0., pTEdgeOfBin=0.;
  Double_t fieldConfiguration = TMath::Sign(1.,aodEvent->GetMagneticField());
  Double_t IP=0., IPUncorr, CorrBeautyRAA, CorrBeautyHalfRAA, BasicBeautyCorrection, CorrCharm3050, IPCorrection, OOPCorrection, BeautyIPCorrection, BeautyOOPCorrection;
  Double_t rndm = 0.;
  Int_t Source, SourceNew;
  Double_t CorrGaussWidth=0.;
  
  if(analyzeEvent)
  {
    for(int i=0;i<nTracks;i++)
    {
      track = dynamic_cast<AliAODTrack *>(aodEvent->GetTrack(i));
      pt = track->Pt();
      if(!PassesTrackCuts(track)) continue;
      mcple = (AliMCParticle *)(fAODArrayMCInfo->At(TMath::Abs(track->GetLabel())));
      pdgCode = mcple->PdgCode(); // wrong code for now! need mc code
      radius = TMath::Sqrt(mcple->Xv()*mcple->Xv()+mcple->Yv()*mcple->Yv());
      // static_cast<Int_t>(fSignalCuts->GetSignalSource(mcple))
      // FindSource(mcple, fMCEvent, MotherPt, GSMotherPt)
      if(TMath::Abs(pdgCode) == 11)
      {
        rndm = fRd->Rndm();
        Source = static_cast<Int_t>(fSignalCuts->GetSignalSource(mcple)); // Only call this once
        SourceNew = FindSource(mcple, fMCEvent, MotherPt, GSMotherPt); // This also fills the motherPt
        fExtraCuts->GetHFEImpactParameters((AliVTrack *)track,dcaxyD,dcaErr);
        dcaErr =  dcaxyD / dcaErr; // because dcaerr is actually the dca significance
        CorrGaussWidth = TMath::Sqrt((1. + 0.085)*(1. + 0.085)-1.);
        IP = dcaxyD*track->Charge()*fieldConfiguration+fRd->Gaus(0., CorrGaussWidth*dcaErr); // 0.458 corresponds to a 10% width change
        if(Source == 0)
        {
           // Just to fill the motherpT
          pTEdgeOfBin = fDCABeauty->GetXaxis()->GetBinLowEdge(fDCABeauty->GetXaxis()->FindBin(pt));
          //CorrCharm3050 = 15.8864*(TMath::Exp(-1.16759*MotherPt)+0.00498538*TMath::Exp(-0.357565*MotherPt))/(MotherPt*(2.09819*TMath::Exp(-MotherPt*0.739794)+0.0396785*TMath::Exp(-MotherPt*0.169834))) / (15.8864*(TMath::Exp(-1.16759*pTEdgeOfBin)+0.00498538*TMath::Exp(-0.357565*pTEdgeOfBin))/(pTEdgeOfBin*(2.09819*TMath::Exp(-pTEdgeOfBin*0.739794)+0.0396785*TMath::Exp(-pTEdgeOfBin*0.169834)))); // 11h
          CorrCharm3050 = 15.1975*(TMath::Exp(-1.16759*MotherPt)+0.00498538*TMath::Exp(-0.357565*MotherPt))/(1.63014*TMath::Gaus(MotherPt,-0.556635, 2.17658) + 1.48821 * TMath::Exp(-TMath::Sqrt(MotherPt)*1.14519)) / (15.1975*(TMath::Exp(-1.16759*pTEdgeOfBin)+0.00498538*TMath::Exp(-0.357565*pTEdgeOfBin))/(1.63014*TMath::Gaus(pTEdgeOfBin,-0.556635, 2.17658) + 1.48821 * TMath::Exp(-TMath::Sqrt(pTEdgeOfBin)*1.14519)));
          //CorrCharm3050 = 1410.16*(TMath::Exp(-1.16759*MotherPt)+0.00498538*TMath::Exp(-0.357565*MotherPt))/(TMath::Exp(-MotherPt*0.11023)+234.578*TMath::Exp(-MotherPt*0.439153)) // old (10h)
          //      /(1410.16*(TMath::Exp(-1.16759*pTEdgeOfBin)+0.00498538*TMath::Exp(-0.357565*pTEdgeOfBin))/(TMath::Exp(-pTEdgeOfBin*0.11023)+234.578*TMath::Exp(-pTEdgeOfBin*0.439153)));
          IPCorrection = ((MotherPt*TMath::Exp(-0.3*MotherPt)/6.)*0.8*4/3.14159+1) / ((pTEdgeOfBin*TMath::Exp(-0.3*pTEdgeOfBin)/6.)*0.8*4/3.14159+1);
          OOPCorrection = (1-(MotherPt*TMath::Exp(-0.3*MotherPt)/6.)*0.8*4/3.14159) / (1-(pTEdgeOfBin*TMath::Exp(-0.3*pTEdgeOfBin)/6.)*0.8*4/3.14159);
          fDCACharm->Fill(pt, IP);
          if(rndm < CorrCharm3050) fDCACharm3050->Fill(pt, IP);
          if(rndm < CorrCharm3050*IPCorrection) fDCACharm3050IP->Fill(pt, IP);
          if(rndm < CorrCharm3050*OOPCorrection) fDCACharm3050OOP->Fill(pt, IP);
        }
        if(Source == 1)
        {
          fDCABeauty->Fill(pt, IP);
          //BasicBeautyCorrection = (0.940489/(1.+TMath::Power((MotherPt-0.860907)/4.84045,2.))+0.230487*TMath::Gaus(MotherPt,8.47677,4.75503)); // 11h
          BasicBeautyCorrection = (0.88686*TMath::Power(MotherPt,0.430499)*TMath::Exp(-MotherPt*0.133517)+-3.87792e-08*TMath::Power(MotherPt,8.05593)*TMath::Exp(-MotherPt*0.472494));
          CorrBeautyHalfRAA = 1.05*BasicBeautyCorrection*(1.+(0.5/(1. + TMath::Exp((MotherPt-7.)*0.7)) + 0.5 + (MotherPt-15.)/300.))/2.;
          BeautyIPCorrection = CorrBeautyHalfRAA * ((0.014*MotherPt*MotherPt*TMath::Exp(-2*MotherPt/6.))*0.8*4/3.14159+1)*0.95;
          BeautyOOPCorrection = CorrBeautyHalfRAA * (-(0.014*MotherPt*MotherPt*TMath::Exp(-2*MotherPt/6.))*0.8*4/3.14159+1)*1.05;
          if(rndm < CorrBeautyHalfRAA) fDCABeautyHalfRAA->Fill(pt, IP);
          if(rndm < BeautyIPCorrection) fDCABeautyHalfRAAIP->Fill(pt, IP);
          if(rndm < BeautyOOPCorrection) fDCABeautyHalfRAAOOP->Fill(pt, IP);
          CorrBeautyRAA = 1.1*BasicBeautyCorrection*(0.5/(1. + TMath::Exp((MotherPt-7.)*0.7)) + 0.5 + (MotherPt-15.)/300.);
          BeautyIPCorrection = CorrBeautyRAA * ((0.014*MotherPt*MotherPt*TMath::Exp(-2*MotherPt/6.))*0.8*4/3.14159+1)*0.95;
          BeautyOOPCorrection = CorrBeautyRAA * (-(0.014*MotherPt*MotherPt*TMath::Exp(-2*MotherPt/6.))*0.8*4/3.14159+1)*1.05;
          if(rndm < CorrBeautyRAA) fDCABeautyRAA->Fill(pt, IP);
          if(rndm < BeautyIPCorrection) fDCABeautyRAAIP->Fill(pt, IP);
          if(rndm < BeautyOOPCorrection) fDCABeautyRAAOOP->Fill(pt, IP);
        }
        if(Source == 2 && !IsAddedSignal(mcple))
          fDCAConversion->Fill(pt, IP);
        if(Source == 3 && !IsAddedSignal(mcple))
          fDCADalitz->Fill(pt, IP);
        if(SourceNew == 0)
        {
          pTEdgeOfBin = fDCABeauty->GetXaxis()->GetBinLowEdge(fDCABeauty->GetXaxis()->FindBin(pt));
          //CorrCharm3050 = 15.8864*(TMath::Exp(-1.16759*MotherPt)+0.00498538*TMath::Exp(-0.357565*MotherPt))/(MotherPt*(2.09819*TMath::Exp(-MotherPt*0.739794)+0.0396785*TMath::Exp(-MotherPt*0.169834))) / (15.8864*(TMath::Exp(-1.16759*pTEdgeOfBin)+0.00498538*TMath::Exp(-0.357565*pTEdgeOfBin))/(pTEdgeOfBin*(2.09819*TMath::Exp(-pTEdgeOfBin*0.739794)+0.0396785*TMath::Exp(-pTEdgeOfBin*0.169834))));
          CorrCharm3050 = 15.1975*(TMath::Exp(-1.16759*MotherPt)+0.00498538*TMath::Exp(-0.357565*MotherPt))/(1.63014*TMath::Gaus(MotherPt,-0.556635, 2.17658) + 1.48821 * TMath::Exp(-TMath::Sqrt(MotherPt)*1.14519)) / (15.1975*(TMath::Exp(-1.16759*pTEdgeOfBin)+0.00498538*TMath::Exp(-0.357565*pTEdgeOfBin))/(1.63014*TMath::Gaus(pTEdgeOfBin,-0.556635, 2.17658) + 1.48821 * TMath::Exp(-TMath::Sqrt(pTEdgeOfBin)*1.14519)));
          //1410.16*(TMath::Exp(-1.16759*MotherPt)+0.00498538*TMath::Exp(-0.357565*MotherPt))/(TMath::Exp(-MotherPt*0.11023)+234.578*TMath::Exp(-MotherPt*0.439153)) // old
          //      /(1410.16*(TMath::Exp(-1.16759*pTEdgeOfBin)+0.00498538*TMath::Exp(-0.357565*pTEdgeOfBin))/(TMath::Exp(-pTEdgeOfBin*0.11023)+234.578*TMath::Exp(-pTEdgeOfBin*0.439153)));
          IPCorrection = ((MotherPt*TMath::Exp(-0.3*MotherPt)/6.)*0.8*4/3.14159+1) / ((pTEdgeOfBin*TMath::Exp(-0.3*pTEdgeOfBin)/6.)*0.8*4/3.14159+1);
          OOPCorrection = (1-(MotherPt*TMath::Exp(-0.3*MotherPt)/6.)*0.8*4/3.14159) / (1-(pTEdgeOfBin*TMath::Exp(-0.3*pTEdgeOfBin)/6.)*0.8*4/3.14159);
          fDCACharmNew->Fill(pt, IP);
          if(rndm < CorrCharm3050) fDCACharmNew3050->Fill(pt, IP);
          if(rndm < CorrCharm3050*IPCorrection) fDCACharmNew3050IP->Fill(pt, IP);
          if(rndm < CorrCharm3050*OOPCorrection) fDCACharmNew3050OOP->Fill(pt, IP);
        }
        if(SourceNew == 1)
        {
          fDCABeautyNew->Fill(pt, IP);
          //BasicBeautyCorrection = (0.940489/(1.+TMath::Power((MotherPt-0.860907)/4.84045,2.))+0.230487*TMath::Gaus(MotherPt,8.47677,4.75503)); // 11h
          BasicBeautyCorrection = (0.88686*TMath::Power(MotherPt,0.430499)*TMath::Exp(-MotherPt*0.133517)+-3.87792e-08*TMath::Power(MotherPt,8.05593)*TMath::Exp(-MotherPt*0.472494));
          CorrBeautyHalfRAA = 1.05*BasicBeautyCorrection*(1.+(0.5/(1. + TMath::Exp((MotherPt-7.)*0.7)) + 0.5 + (MotherPt-15.)/300.))/2.;
          BeautyIPCorrection = CorrBeautyHalfRAA * ((0.014*MotherPt*MotherPt*TMath::Exp(-2*MotherPt/6.))*0.8*4/3.14159+1)*0.95;
          BeautyOOPCorrection = CorrBeautyHalfRAA * (-(0.014*MotherPt*MotherPt*TMath::Exp(-2*MotherPt/6.))*0.8*4/3.14159+1)*1.05;
          if(rndm < CorrBeautyHalfRAA) fDCABeautyNewHalfRAA->Fill(pt, IP);
          if(rndm < BeautyIPCorrection) fDCABeautyNewHalfRAAIP->Fill(pt, IP);
          if(rndm < BeautyOOPCorrection) fDCABeautyNewHalfRAAOOP->Fill(pt, IP);
          CorrBeautyRAA = 1.1*BasicBeautyCorrection*(0.5/(1. + TMath::Exp((MotherPt-7.)*0.7)) + 0.5 + (MotherPt-15.)/300.);
          BeautyIPCorrection = CorrBeautyRAA * ((0.014*MotherPt*MotherPt*TMath::Exp(-2*MotherPt/6.))*0.8*4/3.14159+1)*0.95;
          BeautyOOPCorrection = CorrBeautyRAA * (-(0.014*MotherPt*MotherPt*TMath::Exp(-2*MotherPt/6.))*0.8*4/3.14159+1)*1.05;
          if(rndm < CorrBeautyRAA) fDCABeautyNewRAA->Fill(pt, IP);
          if(rndm < BeautyIPCorrection) fDCABeautyNewRAAIP->Fill(pt, IP);
          if(rndm < BeautyOOPCorrection) fDCABeautyNewRAAOOP->Fill(pt, IP);
        }
        if(SourceNew == 2 && !IsAddedSignal(mcple))
          fDCAConversionNew->Fill(pt, IP);
        if(SourceNew == 3 && !IsAddedSignal(mcple))
          fDCADalitzNew->Fill(pt, IP);

        if(SourceNew == 0)
        {
          fCharmMotherpT->Fill(MotherPt);
          fGroundStateCharmMotherpT->Fill(GSMotherPt);
        }
        if(SourceNew == 1)
        {
          fBeautyMotherpT->Fill(MotherPt);
          fGroundStateBeautyMotherpT->Fill(GSMotherPt);
        }

        if(Source != 1 && SourceNew==1)
        {
          if(MotherPDG(mcple, fMCEvent) == 22)
            fDCAConversionBeauty->Fill(pt, IP);
          else
            fDCADalitzBeauty->Fill(pt, IP);
        }
        if(Source != 0 && SourceNew==0)
        {
          //PrintHierarchy(mcple, fMCEvent);
          if(MotherPDG(mcple, fMCEvent) == 22)
            fDCAConversionCharm->Fill(pt, IP);
          else
            fDCADalitzCharm->Fill(pt, IP);
        }
      }

      // Now fill primary hadron plots
      if(!IsAddedSignal(mcple) && (PassesPionPID(track, pid) || PassesKaonPID(track, pid)) && track->Pt() > 0.5)
      {
        fExtraCuts->GetHFEImpactParameters((AliVTrack *)track,dcaxyD,dcaErr);  // DCA only calculated for electrons otherwise
        dcaErr =  dcaxyD / dcaErr; // because dcaerr is actually the dca significance
        CorrGaussWidth = TMath::Sqrt((1. + 0.085)*(1. + 0.085)-1.);
        IP = dcaxyD*track->Charge()*fieldConfiguration+fRd->Gaus(0., CorrGaussWidth*dcaErr); // 0.458 corresponds to a 10% width change
        IPUncorr = dcaxyD*track->Charge()*fieldConfiguration;
        fDCAHadrons->Fill(pt, dcaxyD*track->Charge()*fieldConfiguration); // dcaxyD*track->Charge()*fieldConfiguration , for now leav factors out to check on center changes etc.
        
        if(PassesPionPID(track, pid))
          {
            if(centrality>=20.0 && centrality<=50.0) fDCAHadrons->Fill(track->Pt(), IPUncorr);
            if(centrality>=20.0 && centrality<=50.0) fDCAWErrHadrons->Fill(track->Pt(), IPUncorr, dcaErr);
            fDCAHadronsFineBins->Fill(track->Pt(), IPUncorr, centrality);
            if(centrality>=20.0 && centrality<=50.0) fDCAHadronsCorrected->Fill(pt, IP); // for comparison
          }
          if(PassesKaonPID(track, pid))
          {
            if(centrality>=20.0 && centrality<=50.0) fDCAKaons->Fill(track->Pt(), IPUncorr);
            if(centrality>=20.0 && centrality<=50.0) fDCAWErrKaons->Fill(track->Pt(), IPUncorr, dcaErr);
            fDCAKaonsFineBins->Fill(track->Pt(), IPUncorr, centrality);
          }
      }
      /*if(!IsAddedSignal(mcple) && TMath::Abs(dcaxyD*track->Charge()*fieldConfiguration)<0.0001)
      {
        if(fMCEvent->GetTrack(mcple->GetMother()))
          std::cout << "IP is " << dcaxyD*track->Charge()*fieldConfiguration << " pdg: " << pdgCode << " mother pdg: " << ((AliMCParticle*) fMCEvent->GetTrack(mcple->GetMother()))->PdgCode() << " radius: " << radius << std::endl;
        else
          std::cout << "IP is " << dcaxyD*track->Charge()*fieldConfiguration << " pdg: " << pdgCode << " no mother" << " radius: " << radius << std::endl;
      }*/
    }
    // Now fill V0 plots
    fAODV0Cuts->SetEvent(aodEvent);
    for(int i= 0;i<aodEvent->GetNumberOfV0s();i++)
    {
      //
      v0 = aodEvent->GetV0(i);
      //if(!PassesTrackCuts(track));
      if(fAODV0Cuts->ProcessV0(v0, V0MotherPdg, V0Daughter1Pdg, V0Daughter2Pdg))
      {
        recoRadius = v0->RadiusSecVtx();
        if(TMath::Abs(V0MotherPdg)==310 && recoRadius>0.5)
        {
          V0Daughter[0] = dynamic_cast<AliAODTrack *> (v0->GetSecondaryVtx()->GetDaughter(0)); // This is how to get the daughter particles in AODs, apparently
          V0Daughter[1] = dynamic_cast<AliAODTrack *> (v0->GetSecondaryVtx()->GetDaughter(1));
          if(PassesMinimalTrackCuts(V0Daughter[0])) fPionV0pTRNoCuts->Fill(V0Daughter[0]->Pt(), recoRadius, centrality);
          if(PassesMinimalTrackCuts(V0Daughter[1])) fPionV0pTRNoCuts->Fill(V0Daughter[1]->Pt(), recoRadius, centrality);
          if(PassesITSTrackCuts(V0Daughter[0])) fPionV0pTRWithCuts->Fill(V0Daughter[0]->Pt(), recoRadius, centrality);
          if(PassesITSTrackCuts(V0Daughter[1])) fPionV0pTRWithCuts->Fill(V0Daughter[1]->Pt(), recoRadius, centrality);
        }
      }
    }
  }

  PostData(1, fOutputContainer);
}

//________________________________________________________________________
void AliAnalysisTaskHFEBeautyMCTemplatesRun2::Terminate(const Option_t *)
{
//   treeoutput->Write();

}
