#include "stdafx.h"

#include "opencv2/opencv.hpp"
#include "PDI.h"
#include "Kuwahara.h"

using namespace cv;

int main()
{
	/**
	 * Trabalho M1 - Pesquisar e implementar Filtro Kuwahara
	 * 
	 */

	Mat img = imread("C:\\Users\\Joshua Raiser\\Downloads\\2.jpg");
	imshow("Imagem Original", img);

	int kernel = 7;
	imshow("funciona desgraça :@", Kuwahara::filtroKuwahara(img, kernel));

	/* ... */
	waitKey();

    return 0;
}

