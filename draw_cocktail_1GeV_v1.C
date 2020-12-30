 void draw_cocktail_1GeV_v1(){
 //gROOT->Reset();
gStyle->SetOptStat(1111);
//gStyle->SetOptStat("e");
gStyle->SetPalette(1,0);
gStyle->SetOptTitle(0);
TPaveLabel pl, pl1;
TPaveText *pt;

 TH1F *hepem[13];
 TH1F *hepemMM[13];
 TH1F *hepemNcut[13];
 
 TFile *file[13];
 char name[200];
 TString s1="/lustre/nyx/hades/user/nrathod/jan2020/FAT3_FT/EPEM_SIM/";
 
 TString fname[]={
   "EpEm_FAT_output_D0_dalitz",
   "EpEm_FAT_output_D+_dalitz",
   "EpEm_FAT_output_D0_n",
   "EpEm_FAT_output_D0_p",
   "EpEm_FAT_output_Dplus",
   "EpEm_FAT_output_ETA", //eta dalitz br=6.9e-3 PDG
   "EpEm_FAT_output_N1440",//dalitz
   "EpEm_FAT_output_N1520",//dalitz br=2.3e-5 - PWA- Federico PhD
   "EpEm_FAT_output_N1535",//dalitz br=3.5e-5 - PWA- Federico PhD 
   "EpEm_FAT_output_Pi0",//dalitz br=1.2% PDG
   "EpEm_FAT_output_RHO" //rho0->e+e- br=4.7e-5 PDG
 };

 //**********************************


  TString chname[]={
   "#pi^{0} #Delta^{0}#rightarrow #pi^{0}ne^{+}e^{-}",
   "#pi^{-} #Delta^{+}#rightarrow #pi^{-}pe^{+}e^{-}",
   "#pi^{0} #Delta^{0}#rightarrow #pi^{0}n#pi^{0}#rightarrow #pi^{0}n#gamma e^{+}e^{-}",
   "#pi^{0} #Delta^{0}#rightarrow #pi^{0}p#pi^{-}#rightarrow #gamma e^{+}e^{-}#pi^{-}p",
   "#pi^{-} #Delta^{+}#rightarrow #pi^{-}p pi^{0}#rightarrow #pi^{-}p#gamma e^{+}e^{-}",
   "n #eta #rightarrow n#gamma e^{+}e^{-}", 
   "N1440 Dalitz",
   "N1520 Dalitz",
   "N1535 Dalitz",
   //"n #eta(#gamma#gamma)",
   //"n #pi^{0}(#gamma#gamma)", 
   "n #pi^{0} #rightarrow n#gamma e^{+}e^{-}",
   "n #rho#rightarrow ne^{+}e^{-}" 
 };


 
 float br[]={
   4.2e-5, 
   4.2e-5, 
   0.01174,//1*(1.174/100.),//?
   0.01174,
   0.01174,//1*(1.174/100.),//?
   6.9e-3, //eta dalitz
   0,//N1440 ?
   2.3e-5,
   3.5e-5,
   0.01174,
   4.72e-5 
 };

 float csec[]={
   1.,// Delta0 pi0:  1mb for proton target, 3.6 mb for CH2 target - from Federico -nothing closer has been found 
   0.876,//Delta+ pi-: 0.876mb Landolt-Bor. @p=1.024 GeV/c (Federico: 0.78mb for proton target, 2.8 mb for CH2 target) 
   1.*(1./3.),// Delta0 pi0:  1mb for proton target, 3.6 mb for CH2 target - from Federico -nothing closer has been found
   1.*(2./3.),// Delta0 pi0:  1mb for proton target, 3.6 mb for CH2 target - from Federico -nothing closer has been found
   0.876*(2./3.),//Delta+ pi-: 0.876mb Landolt-Bor. @p=1.024 GeV/c (Federico: 0.78mb for proton target, 2.8 mb for CH2 target) 
   1.25, //eta 
   0,//N1440 ?? 
   20.4,//N1520 (Federico PWA: 20.4 mb proton target, 72.4 mb for CH2 target)
   9.7,//N1535 (Federico PWA: 9.7 mb proton target, 34.4 mb for CH2 target)
   7.05,//pi0 n : 7.05 mb Landolt-Bor. @p=1.03 GeV/c  
   1.7//=0.489 +off shell effects
   //0.489 //rho0 n : 0.489 mb interpolated from Landolt-Bor. @p=1.106(sigma=0.662mb) and 1.004(sigma=0.339mb) GeV/c
 };



 TH1F* hsum= new TH1F("sum","sum",100,0,1);
 TH1F* hsumMM= new TH1F("sumMM","sumMM",100,0,2);
 TH1F* hsumNcut= new TH1F("sumNcut","sumNcut",100,0,1);
 
 const int n0=0;
 const int nb=11;

 for(int i=n0;i<nb;i++){
   file[i]=new TFile(s1+fname[i]+"_OA4deg.root");
   file[i]->cd();
   //hepem[i]=(TH1F*)file[i]->Get("sig_all");
   //hepemNcut[i]=(TH1F*)file[i]->Get("Inv_epem_N_region");
   //hepem[i]=(TH1F*)file[i]->Get("Inv_epem_N_region_more140");
   hepem[i]=(TH1F*)file[i]->Get("Inv_epem_N_region");
   
   hepemMM[i]=(TH1F*)file[i]->Get("MM_epem_more140");
   //hepemMM[i]=(TH1F*)file[i]->Get("MM_epem_all");
								 
   
   hepem[i]->Rebin(3);
   hepemMM[i]->Rebin(3);
   //hepemNcut[i]->Rebin(3);

 }
 
 for(int i=n0;i<nb;i++){
   //file[i]=new TFile(s1+fname[i]+"_OA4deg.root");
   //file[i]->cd();
   //hepem[i]=(TH1F*)file[i]->Get("sig_all");
   //hepem[i]->Rebin(2);

   hepem[i]->Scale(csec[i]*br[i]/100000.);
   hepem[i]->GetSumw2()->Set(0);
   hepem[i]->SetMaximum(10000000e-6);

   hepemMM[i]->Scale(csec[i]*br[i]/100000.);
   hepemMM[i]->GetSumw2()->Set(0);
   hepemMM[i]->SetMaximum(10000000e-6);
   
   //hepemNcut[i]->Scale(csec[i]*br[i]/100000.);
   //hepemNcut[i]->GetSumw2()->Set(0);
   //hepemNcut[i]->SetLineColor(i+2);
   //hepemNcut[i]->SetMaximum(10000000e-6);
   hepem[i]->SetLineWidth(2);
   hepemMM[i]->SetLineWidth(2);


   if(i<9){
     hepem[i]->SetLineColor(i+2);
     hepemMM[i]->SetLineColor(i+2);
     //hepemNcut[i]->SetLineColor(i+2);

   }
   if (i==3 || i==4 || i>=8){
     hepem[i]->SetLineStyle(7);
     hepemMM[i]->SetLineStyle(7);
     //hepemNcut[i]->SetLineStyle(7);

     if(i==3){
       hepem[i]->SetLineColor(7);
       hepemMM[i]->SetLineColor(7);
       //hepemNcut[i]->SetLineColor(7);

     }
     if(i==4){
       hepem[i]->SetLineColor(6);
       hepemMM[i]->SetLineColor(6);
       //hepemNcut[i]->SetLineColor(6);

     }
     if(i==8){
       hepem[i]->SetLineColor(1);
       hepemMM[i]->SetLineColor(1);
       //hepemNcut[i]->SetLineColor(1);

     }
     if(i==9){
       hepem[i]->SetLineColor(2);
       hepemMM[i]->SetLineColor(2);
       //hepemNcut[i]->SetLineColor(2);

     }
     if(i==10){
       hepem[i]->SetLineColor(4);
       hepemMM[i]->SetLineColor(4);
       //hepemNcut[i]->SetLineColor(4);

     }
   }

   
 }

 for(int i=n0;i<nb;i++){
   hsum->Add(hepem[i]);
   hsumMM->Add(hepemMM[i]);
 //hsumNcut->Add(hepemNcut[i]);
 }

 hsum->SetLineColor(1);
 hsumMM->SetLineColor(1);
 //hsumNcut->SetLineColor(1);

 
 //#####################################################    

   TLegend *leg = new TLegend(0.17,0.65,0.48,0.88);
   //leg->SetHeader("The Legend Title","C");
   for(int i=n0;i<nb;i++){
     //if (i==7)continue;
     leg->AddEntry(hepem[i],chname[i],"l");
   }
   leg->SetTextFont(132);
   leg->SetTextSize(0.06);
   leg->SetBorderSize(0);



  
 TCanvas *c1 = new TCanvas("epem_invM","epem_invM");
   c1->SetLogy();
   hsum->Draw();
   for(int i=n0;i<nb;i++){
   c1->cd(i+1);

   //if (i==7)continue;
     hepem[i]->Draw("same");
   }
   leg->Draw("same");
   

   TCanvas *c2 = new TCanvas("epemMM","epemMM");
   c2->SetLogy();
   hsumMM->Draw();
   for(int i=n0;i<nb;i++){
     c2->cd(i+1);

     //if (i==7)continue;
     hepemMM[i]->Draw("same");
   }
   /*
   TCanvas *c3 = new TCanvas("epem_invM_Ncut","epem_invM_Ncut");
   c3->SetLogy();
   hsumNcut->Draw();
   for(int i=n0;i<nb;i++){
     c3->cd(i+1);

     if (i==5)continue;
          hepemNcut[i]->Draw("samel");
   }

   */

/*
 TCanvas *c0 = new TCanvas("invMass_epem","invMass_epem");
 c0->Divide(6,2);
 
 for(int i=n0;i<nb;i++){
   c0->cd(i+1);
   
   hepem[i]->Draw("same");
   
   }
*/
 

 
}
