#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include "grapher.h"

using namespace std;

int main() {

	const int NumRows = 600;

	const int NumCols = 800;

	const float Pi = M_PI;

	const float Xmax = 1;

	const float Ymax = 1;

	const float Xstep = Xmax/(NumCols-1);

	const float Ystep = Ymax/(NumRows-1);

	float x[NumCols];

	float y[NumRows];

	float z[NumRows][NumCols];

	for (int colNum=0; colNum<NumCols; ++colNum)
		x[colNum] = colNum*Xstep;

	for (int rowNum=0; rowNum<NumRows; ++rowNum)
		y[rowNum] = rowNum*Ystep;

	for (int rowNum = 0; rowNum<NumRows; ++rowNum)
		for (int colNum = 0; colNum<NumCols; ++colNum)
			z[rowNum][colNum] = sin(20*Pi*x[colNum])*sin(10*Pi*y[rowNum]);

	grapher::imagesc(x,y,(float*)z,NumRows,NumCols);

	return 0;
}
