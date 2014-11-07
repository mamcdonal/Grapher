#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TFrame.h>
#include <TF2.h>
#include <TH2F.h>
#include <TPaveLabel.h>
#include <TStyle.h>

#include <TImage.h>

namespace dislin{
	#include "dislin.h"
}

namespace grapher {

void plot(const float *x, const float *y, int N){

	TCanvas *c1 = new TCanvas("c1","",2400,1800);

	c1->SetGrid();

	TGraph *gr = new TGraph(N,x,y);
	gr->SetLineColor(4);
	gr->SetTitle("a simple graph");
	gr->GetXaxis()->SetTitle("X title");
	gr->GetYaxis()->SetTitle("Y title");
	gr->Draw("ACP");

	c1->Print("test.eps");
//	c1->Print("test.root");
}

void imagesc(const float *x, const float *y, const float *z, const int NumRows, const int NumCols){

//	int binx;
//	int biny;
	const auto x_min = *std::min_element(x, x+NumCols);
	const auto x_max = *std::max_element(x, x+NumCols);
	const auto y_min = *std::min_element(y, y+NumRows);
	const auto y_max = *std::max_element(y, y+NumRows);

	TH2F h("h","",NumCols,x_min,x_max,NumRows,y_min,y_max);

	for (int i=0; i<NumRows; ++i) {
		for (int j=0; j<NumCols; ++j) {
//			binx = h.GetXaxis()->FindBin(x[j]);
//			biny = h.GetXaxis()->FindBin(y[i]);
//			h.SetBinContent(binx, biny, z[i*NumCols+j]);
			h.SetBinContent(j,i, z[i*NumCols+j]);
		}
	}

	TCanvas c("c","canvas",10,10,NumCols,NumRows);

	gStyle->SetOptStat(0);

	h.Draw("colz");

	h.GetXaxis()->SetTitle("Time(s)");
	h.GetYaxis()->SetTitle("Distance(m)");

	c.Update();

	c.Print("RootTest.eps");

	//	c.Print("testImage.root");

}

void imagesc2(const float *x, const float *y, const float *z, const int NumCols, const int NumRows){

	const auto NumEl = NumCols*NumRows;

	const auto Xmin = x[0];
	const auto Xmax = x[NumCols-1];
	const auto Xlen = (Xmax - Xmin);

	const auto Ymin = y[0];
	const auto Ymax = y[NumRows-1];
	const auto Ylen = (Ymax - Ymin);

	const auto Zmin = *std::min_element(z,z+NumEl);
	const auto Zmax = *std::max_element(z,z+NumEl);
	const auto Zlen = (Zmax - Zmin);

	const auto NumStepsXAxisLabels = 8;
	const auto NumStepsYAxisLabels = 8;
	const auto NumStepsCAxisLabels = 8;

	const auto Xstep = Xlen/NumStepsXAxisLabels;
	const auto Ystep = Ylen/NumStepsYAxisLabels;
	const auto Zstep = Zlen/NumStepsCAxisLabels;

	// set format to tiff and set filename
	dislin::metafl("EPS");
	dislin::setfil("DislinTest.eps");

	// set white background
	dislin::scrmod("REVERSE");

	//set pagesize
//	dislin::page(NumCols,NumRows);
	dislin::winsiz(NumCols,NumRows);

	// initialize DISLIN
	dislin::disini();

	// set font
	dislin::complx();

//	// set title
//	dislin::titlin("Test Image",4);

	// set axes labels
	dislin::name("Time(s)","X");
	dislin::name("Offset(m)","Y");
	dislin::name("Amplitude","Z");

	// set resolution
	dislin::autres(NumCols,NumRows);

	// draw axes
	dislin::graf3(Xmin,Xmax,Xmin,Xstep,Ymin,Ymax,Ymin,Ystep,Zmin,Zmax,Zmin,Zstep);

	float z_t[NumEl];

	for (int i=0; i<NumRows; ++i){
		for (int j=0; j<NumCols; ++j){
			z_t[i*NumCols+j] = z[j*NumRows+i];
		}
	}

	// draw image
	dislin::crvmat(z_t,NumRows,NumCols,1,1);

	// draw title
//	dislin::title();

	// write image and close program
	dislin::disfin();
}

} // grapher
