//{

//TGraph *MyGraph = new TGraph("/Users/Administrador/Desktop/dut_october/method1_251014_RUN000016c.txt");
//MyGraph->Draw("A*");
    
//}
TH1F *h1;
TH1F *h2;
TH1F *h3;
TH1F *h4;
TFile *f;
TNtuple *ntuple;


void method2_100x100_testbeam(){
   
    gROOT->Reset();
    TCanvas *c1 = new TCanvas("c1","c1",800,600);
    
    

    f = new TFile("basic.root","RECREATE");
    h1 = new TH1F("h1","Charge Collection Time",50,0.0,0.000002);
    h2 = new TH1F("h2","Collected Charge",100,0.0,0.1);
    h3 = new TH1F("h3","Standar Error Charge Collection Time",50,0.0,0.000002);
    h4 = new TH1F("h4","Standar Error Collected Charge",50,0.0,0.000002);
    ntuple = new TNtuple("ntuple","data from ascii file","event:time:hit:m:g:to:d:area");
    
    
    list_files();
    plot_histogram();
    
    
}


//6-2:  *dirname="/Users/Administrador/Documents/MAPS/XTB01/testbeams_data/SPSoctober/analysis_meth2_thr6-2/dut/text_files/"
//6-1:  *dirname="/Users/Administrador/Documents/MAPS/XTB01/testbeams_data/SPSoctober/analysis_method2_thr6-1/dut/waveform/"
//12-4: *dirname="/Users/Administrador/Documents/MAPS/XTB01/testbeams_data/SPSoctober/analysis_method2_thr12-4/dut/waveform/"

void list_files(const char *dirname="/Users/Administrador/Documents/MAPS/XTB01/testbeams_data/SPSoctober/analysis_method2_thr12-4/dut/waveform/", const char *ext=".txt")
{
    TSystemDirectory dir(dirname, dirname);
    TList *files = dir.GetListOfFiles();
    if (files) {
        TSystemFile *file;
        TString fname;
        string filename;
        TIter next(files);
        while ((file=(TSystemFile*)next())) {
            fname = file->GetName();
            if (!file->IsDirectory() && fname.EndsWith(ext)) {
                //cout << fname.Data() << endl;
                filename=dirname+fname;
                cout << filename << endl;
                fill_histogram(filename) ;
                
            }
        }
    }
}

//{
    
    
    //   example of macro to read data from an ascii file and
    //   create a root file with an histogram and an ntuple.
    

    

void fill_histogram(string filename){
 FILE *fp = fopen(filename.c_str(),"r");
    Float_t event,time,hit,m,g,to,d,area,errord,errorarea;
    Int_t ncols;
    Int_t nlines = 0;
    while (1) {
 
        ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %*f %*f %*f %f %f",&event,&time,&hit,&m,&g,&to,&d,&area,&errord,&errorarea);
        if (ncols < 0) break;
        //if (nlines < 5) printf("event=%8f, time=%8f, hit=%1f\n, a=%8f, b=%8f, c=%8f, d=%8f, area=%8f\n",event,time,hit,a,b,c,d,area);
        if (hit == 1)
        printf("event=%1f, time=%1f, hit=%1f, m=%8f, g=%8f, to=%8f, d=%8f, area=%8f, errc=%8f, errarea=%8f\n",event,time,hit,m,g,to,d,area,errord,errorarea);
 
        if (hit !=0){
        
        h1->Fill(d);
        h2->Fill(area);
        h3->Fill(errord);
        h4->Fill(errorarea);
        }
    ntuple->Fill(event,time,hit,m,g,to,d,area,errord,errorarea);
    nlines++;
    }
 fclose(fp);

 
 }

void plot_histogram(){
    
    //if() printf(" found %d points\n",nlines);
    h1->SetFillStyle(1001);
    h1->SetXTitle("Time [s]");
    h1->SetYTitle("Number of Entries");
    h2->SetFillStyle(1001);
    h2->SetXTitle("Collected charge [V]");
    h2->SetYTitle("Number of Entries");
    h3->SetFillStyle(1001);
    h3->SetXTitle("Time [s]");
    h3->SetYTitle("Number of Entries");
    h2->SetFillStyle(1001);
    h2->SetFillColor(kYellow);
    h4->SetXTitle("Error Collected charge [A.U]");
    h4->SetYTitle("Number of Entries");
    h2->Draw();
}
/*
    fp = fopen("/Users/Administrador/Desktop/dut_october/method2_m100_testbeam/method2_251014_RUN000017c_try.txt","r");
    while (1) {
        ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %*f %*f %*f %f %f",&event,&time,&hit,&m,&g,&to,&d,&area,&errord,&errorarea);
        if (ncols < 0) break;
        //if (nlines < 5) printf("event=%8f, time=%8f, hit=%1f\n, a=%8f, b=%8f, c=%8f, d=%8f, area=%8f\n",event,time,hit,a,b,c,d,area);
        if (hit == 1)
            printf("event=%1f, time=%1f, hit=%1f, m=%8f, g=%8f, to=%8f, d=%8f, area=%8f, errc=%8f, errarea=%8f\n",event,time,hit,m,g,to,d,area,errord,errorarea);

        
        if (hit != 0){
            h1->Fill(d);
            h2->Fill(area);
            h3->Fill(errord);
            h4->Fill(errorarea);
        }
        ntuple->Fill(event,time,hit,m,g,to,d,area,errord,errorarea);
        nlines++;
    }
    fclose(fp);
    
    fp = fopen("/Users/Administrador/Desktop/dut_october/method2_m100_testbeam/method2_251014_RUN000018c.txt","r");
    while (1) {
        ncols = fscanf(fp,"%f %f %f %f %f %f %f %f %*f %*f %*f %f %f",&event,&time,&hit,&m,&g,&to,&d,&area,&errord,&errorarea);
        if (ncols < 0) break;
        //if (nlines < 5) printf("event=%8f, time=%8f, hit=%1f\n, a=%8f, b=%8f, c=%8f, d=%8f, area=%8f\n",event,time,hit,a,b,c,d,area);
        if (hit == 1)
            printf("event=%1f, time=%1f, hit=%1f, m=%8f, g=%8f, to=%8f, d=%8f, area=%8f, errc=%8f, errarea=%8f\n",event,time,hit,m,g,to,d,area,errord,errorarea);

        
        if (area != 0){
            h1->Fill(d);
            h2->Fill(area);
            h3->Fill(errord);
            h4->Fill(errorarea);
        }
        ntuple->Fill(event,time,hit,m,g,to,d,area,errord,errorarea);
        nlines++;
    }
    fclose(fp);
    
    
 
    

//h2->Draw();
    //h1->SaveAs("/Users/Administrador/Desktop/dut_october/method1_m100_testbeam/time.png");
    //h1->Save("/Users/Administrador/Desktop/dut_october/method1_m100_testbeam/rms.png");
    //h1->Save("/Users/Administrador/Desktop/dut_october/method1_m100_testbeam/rms.C");
    //h2->Save("/Users/Administrador/Desktop/dut_october/method1_m100_testbeam/area.pdf");
    //h2->Save("/Users/Administrador/Desktop/dut_october/method1_m100_testbeam/area.png");
    //h2->Save("/Users/Administrador/Desktop/dut_october/method1_m100_testbeam/area.C");
    
    
    
    //f->Write();
}
 */
