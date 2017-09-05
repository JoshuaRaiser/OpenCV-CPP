#pragma once
#include "stdafx.h"

#include <opencv2\opencv.hpp>
#include "KuwaharaRegiao.h"

class Kuwahara
{
public:
	static cv::Mat filtroKuwahara(cv::Mat imagemBase, int tamanhoKernel);

private:
	//static uchar filtroKuwaharaRegiaoXY(int x, int y);
	static KuwaharaRegiao getRegioes(int x, int y);
};