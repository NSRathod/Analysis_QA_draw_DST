void draw_cocktail_1GeV_V2(){
 //gROOT->Reset();
gStyle->SetOptStat(1111);
//gStyle->SetOptStat("e");
gStyle->SetPalette(1,0);
gStyle->SetOptTitle(0);
TPaveLabel pl, pl1;
TPaveText *pt;

 TH1F *hepem[9];
 
 TFile *file[9];
 char name[200];
 TString s1="/lustre/nyx/hades/user/nrathod/jan2020/FAT3_FT/EPEM_SIM/";
 
 TString fname[]={
   "EpEm_FAT_output_PPim_p_pion_OA4deg_ID.root",
   "EpEm_FAT_output_PPim_n_pion_OA4deg_ID.root",
   "EpEm_FAT_output_PPim_eta_pi0_OA4deg_ID.root",
   "EpEm_FAT_output_PPim_eta_3pion_OA4deg_ID.root",
   "EpEm_FAT_output_PPim_3pions_OA4deg_ID.root",
   "EpEm_FAT_output_Omega_Pi0_dalitz_OA4deg_ID.root",
   "EpEm_FAT_output_Omega_dilepton_OA4deg_ID.root",
   "EpEm_FAT_output_omega_pi0_dilepton_OA4deg_ID.root",
   "EpEm_FAT_output_omega_photon_OA4deg_ID.root",

 };

 TString chname[]={
   "p #pi^{-} #pi^{0} [#gamma e^{+}e^{-}]",
   "n #pi^{+} #pi^{-}",
   "n #eta #pi^{0} [#gamma e^{+}e^{-}]",
   "n #eta [#pi^{+} #pi^{-} #pi^{0} [#gamma e^{+}e^{-}]",
   "n #pi^{+} #pi^{-} #pi^{0} [#gamma e^{+}e^{-}]",
   "n #omega [#pi^{+} #pi^{-} #pi^{0} [#gamma e^{+}e^{-}]]",
   "n #omega [e^{+}e^{-}]",
   "n #omega [e^{+}e^{-} #pi^{0} [#gamma e^{+}e^{-}]]",
    "n #omega [#gamma #pi^{0} [#gamma e^{+}e^{-}]]"
 };


 
 float csec[]={
   7.6604e-8,
   9.83e-8,
   1.1740e-8,
   0.3108e-8,
   1.2885e-8,
   20.63e-10,
   1.43e-11,
   1.78e-12,
   1.91e-10  
 };


 TH1F* hsum= new TH1F("sum","sum",100,0,1);
 
 const int n0=0;
 const int nb=9;

 for(int i=n0;i<nb;i++){
   file[i]=new TFile(s1+fname[i]);
   file[i]->cd();
   hepem[i]=(TH1F*)file[i]->Get("sig_all");
   hepem[i]->Rebin(3);
   hepem[i]=(TH1F*)file[i]->Get("Inv_epem_N_region");

   hepemMM[i]=(TH1F*)file[i]->Get("MM_epem_more140");
 }
 
 for(int i=n0;i<nb;i++){
   //file[i]=new TFile(s1+fname[i]+"_OA4deg.root");
   //file[i]->cd();
   //hepem[i]=(TH1F*)file[i]->Get("sig_all");
   //hepem[i]->Rebin(2);

   hepem[i]->Scale(csec[i]);
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
