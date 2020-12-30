 void draw_cocktail_1GeV_v3(){
 //gROOT->Reset();
gStyle->SetOptStat(1111);
//gStyle->SetOptStat("e");
gStyle->SetPalette(1,0);
gStyle->SetOptTitle(0);
TPaveLabel pl, pl1;
TPaveText *pt;

 TH1F *hepem[9];
 TH1F *hepemMM[9];
 TH1F *hepemNcut[9];
 
 TFile *file[9];
 char name[200];
 TString s1="/lustre/nyx/hades/user/nrathod/jan2020/FAT3_FT/EPEM_SIM/";

 
 TString fname[]={
   "EpEm_FAT_output_PPim_p_pion",
   "EpEm_FAT_output_PPim_n_pion",
   "EpEm_FAT_output_PPim_eta_pi0",
   "EpEm_FAT_output_PPim_eta_3pion",
   "EpEm_FAT_output_PPim_3pions",
   "EpEm_FAT_output_Omega_Pi0_dalitz",
   "EpEm_FAT_output_Omega_dilepton",
   "EpEm_FAT_output_omega_pi0_dilepton",
   "EpEm_FAT_output_omega_photon",

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
 TH1F* hsumMM= new TH1F("sumMM","sumMM",100,0,2);
 TH1F* hsumNcut= new TH1F("sumNcut","sumNcut",100,0,1);
 
 const int n0=0;
 const int nb=9;

 for(int i=n0;i<nb;i++){
   file[i]=new TFile(s1+fname[i]+"_OA4deg_ID.root");
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

   hepem[i]->Scale(csec[i]);
   hepem[i]->GetSumw2()->Set(0);
   hepem[i]->SetMaximum(10000000e-6);

   hepemMM[i]->Scale(csec[i]);
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
     cout << hepem[i]->Integral("width") << endl;
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
