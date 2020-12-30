 void draw_cocktail_1GeV(){
 //gROOT->Reset();
gStyle->SetOptStat(1111);
//gStyle->SetOptStat("e");
gStyle->SetPalette(1,0);
gStyle->SetOptTitle(0);
TPaveLabel pl, pl1;
TPaveText *pt;

 TH1F *hepem[13];
 
 TFile *file[13];
 char name[200];
 TString s1="/lustre/nyx/hades/user/nrathod/jan2020/FAT3_FT/EPEM_SIM/";
 
 TString fname[]={
   "EpEm_FAT_output_D0_DALITZ",
   "EpEm_FAT_output_D+_dalitz",
   "EpEm_FAT_output_D0_n",
   "EpEm_FAT_output_D0_p",
   "EpEm_FAT_output_Dplus",
   "EpEm_FAT_output_ETA_gg", //br=39.4% PDG
   "EpEm_FAT_output_ETA", //eta dalitz br=6.9e-3 PDG
   "EpEm_FAT_output_N1440",//dalitz
   "EpEm_FAT_output_N1520",//dalitz br=2.3e-5 - PWA- Federico PhD
   "EpEm_FAT_output_N1535",//dalitz br=3.5e-5 - PWA- Federico PhD 
   "EpEm_FAT_output_Pi0_gg", //br=98% PDG =1
   "EpEm_FAT_output_Pi0",//dalitz br=1.2% PDG
   "EpEm_FAT_output_RHO" //rho0->e+e- br=4.7e-5 PDG
 };

 TString chname[]={
   "#pi^{0} #Delta^{0}Dalitz",
   "#pi^{-} #Delta^{+}Dalitz",
   "#pi^{0} #Delta^{0}(n #pi^{0}Dalitz)",
   "#pi^{0}Dalitz #Delta^{0}(p #pi^{-})",
   "#pi^{-} #Delta^{+}(p #pi^{0}Dalitz)",
   "n #eta(#gamma#gamma)",
   "n #eta Dalitz", 
   "N1440 Dalitz",
   "N1520 Dalitz",
   "N1535 Dalitz",
   "n #pi^{0}(#gamma#gamma)", 
   "n #pi^{0} Dalitz ",
   "n #rho" 
 };


 
 float br[]={
   4.2e-5, 
   4.2e-5, 
   0.01174,//1*(1.174/100.),//?
   0.01174,
   0.01174,//1*(1.174/100.),//?
   0.394,//eta->gg PDG
   6.9e-3, //eta dalitz
   0,//N1440 ?
   2.3e-5,
   3.5e-5,
   1,
   0.012,
   4.7e-5 
 };

 float csec[]={
   1.,// Delta0 pi0:  1mb for proton target, 3.6 mb for CH2 target - from Federico -nothing closer has been found 
   0.876,//Delta+ pi-: 0.876mb Landolt-Bor. @p=1.024 GeV/c (Federico: 0.78mb for proton target, 2.8 mb for CH2 target) 
   1.,// Delta0 pi0:  1mb for proton target, 3.6 mb for CH2 target - from Federico -nothing closer has been found
   1.,// Delta0 pi0:  1mb for proton target, 3.6 mb for CH2 target - from Federico -nothing closer has been found
   0.876,//Delta+ pi-: 0.876mb Landolt-Bor. @p=1.024 GeV/c (Federico: 0.78mb for proton target, 2.8 mb for CH2 target) 
   0.52,//eta: 0.52mb Landolt-Bor. @p=1.046 GeV/c 
   0.52, //eta 
   0,//N1440 ?? 
   20.4,//N1520 (Federico PWA: 20.4 mb proton target, 72.4 mb for CH2 target)
   9.7,//N1535 (Federico PWA: 9.7 mb proton target, 34.4 mb for CH2 target)
   7.05, //pi0 n : 7.05 mb Landolt-Bor. @p=1.03 GeV/c
   7.05,//pi0 n : 7.05 mb Landolt-Bor. @p=1.03 GeV/c  
   0.489 //rho0 n : 0.489 mb interpolated from Landolt-Bor. @p=1.106(sigma=0.662mb) and 1.004(sigma=0.339mb) GeV/c
 };


 TH1F* hsum= new TH1F("sum","sum",100,0,1);
 
 const int n0=0;
 const int nb=13;

 for(int i=n0;i<nb;i++){
   file[i]=new TFile(s1+fname[i]+"_OA4deg.root");
   file[i]->cd();
   hepem[i]=(TH1F*)file[i]->Get("sig_all");
   hepem[i]->Rebin(3);
 }
 
 for(int i=n0;i<nb;i++){
   //file[i]=new TFile(s1+fname[i]+"_OA4deg.root");
   //file[i]->cd();
   //hepem[i]=(TH1F*)file[i]->Get("sig_all");
   //hepem[i]->Rebin(2);

   hepem[i]->Scale(csec[i]*br[i]/100000.);
   hepem[i]->GetSumw2()->Set(0);
   hepem[i]->SetLineColor(i+2);

   hepem[i]->SetMaximum(10000000e-6);

 }

 for(int i=n0;i<nb;i++)
 hsum->Add(hepem[i]);

 hsum->SetLineColor(1);
   
//#####################################################    
/*
 TCanvas *c0 = new TCanvas("invMass_epem","invMass_epem");
 c0->Divide(6,2);
 
 for(int i=n0;i<nb;i++){
   c0->cd(i+1);
   
   hepem[i]->Draw("same");
   
   }
*/
   TCanvas *c1 = new TCanvas("invMass_epem_sum","invMass_epem_sum");
   c1->SetLogy();
   hsum->Draw();
   for(int i=n0;i<nb;i++){
   c1->cd(i+1);

     if (i==5)continue;
     hepem[i]->Draw("samel");
   }
   

 
   TLegend *leg = new TLegend(0.17,0.65,0.48,0.88);
   //leg->SetHeader("The Legend Title","C");
   for(int i=n0;i<nb;i++){
     if (i==5)continue;
     leg->AddEntry(hepem[i],chname[i],"l");
   }
   leg->SetTextFont(132);
   leg->SetTextSize(0.06);
   leg->SetBorderSize(0);

   leg->Draw("same");
   

 

 
}
