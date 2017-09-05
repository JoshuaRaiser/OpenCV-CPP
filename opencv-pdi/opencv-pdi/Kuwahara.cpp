#include "stdafx.h"

#include <opencv2\opencv.hpp>

#include "Kuwahara.h"
#include "KuwaharaRegiao.h"
#include "PDI.h"

cv::Mat imagem;
int kernel, largura, altura, pad;

cv::Mat Kuwahara::filtroKuwahara(cv::Mat imagemBase, int tamanhoKernel)
{
	imagem = PDI::escalaCinza(imagemBase).clone();

	kernel = tamanhoKernel;
	pad = tamanhoKernel-1;
	
	cv::Mat tempImagem;
	tempImagem.create(imagem.size(), CV_8U);

	largura = tempImagem.cols; altura = tempImagem.rows;
	uchar *data = tempImagem.data;

	for (int x = 0; x<altura; x++) {
		for (int y = 0; y < largura; y++)
			//data[x*largura + y] = getRegioes(x,y).resultado();
			//tempImagem.at<uchar>(x, y) = getRegioes(y, x).resultado();
			tempImagem.at<uchar>(x, y) = getRegioes(x, y).resultado();
	}
	return tempImagem;
}

/*uchar Kuwahara::filtroKuwaharaRegiaoXY(int x, int y)
{
	return getRegioes(x, y).resultado();
}*/

KuwaharaRegiao Kuwahara::getRegioes(int x, int y) {
	KuwaharaRegiao regioes(kernel);

	uchar *data = imagem.data;

	// Atualiza data para cada região, os pixels fora dos limites da imagem são ignorados
	/*
	 1     1      1|2      2     2
	 1     1      1|2      2     2
	1|3   1|3   1|2|3|0   2|0   2|0
	 3     3      3|0      0     0
	 3     3      3|0      0     0
	*/

	//Area 1 (superior esquerda)
	for (int j = (x - pad >= 0) ? x - pad : 0; j >= 0 && j <= x && j < altura; j++){
		for (int i = ((y - pad >= 0) ? y - pad : 0); i >= 0 && i <= y && i < largura; i++) {
			regioes.atualizaData(1, data[(j*largura) + i]);
		}
	}

	//Area 2 (superior direita)
	for (int j = (x - pad >= 0) ? x - pad : 0; j <= x && j < altura; j++){
		for (int i = y; i <= y + pad && i < largura; i++) {
			regioes.atualizaData(2, data[(j*largura) + i]);
		}
	}

	//Area 3 (inferior esquerda)
	for (int j = x; j <= x + pad && j < altura; j++) {
		for (int i = ((y - pad >= 0) ? y - pad : 0); i <= y && i < largura; i++) {
			regioes.atualizaData(3, data[(j*largura) + i]);
		}
	} 

	//Area 0 (inferior direita)
	for (int j = x; j <= x + pad && j < altura; j++) {
		for (int i = y; i <= y + pad && i < largura; i++) {
			regioes.atualizaData(0, data[(j*largura) + i]);
		}
	}

	return regioes;
}
