#include "stdafx.h"
#include <opencv2\opencv.hpp>

using namespace cv;

Mat aplicaFiltro(Mat imagem, int indice, int cor)
{
	if (cor < 0 || indice < 0) return imagem;

	// percorre as linhas
	for (int x = 0; x < imagem.rows; x++)
	{
		// percorre as colunas
		for (int y = 0; y < imagem.cols; y++)
		{
			// obtem o pixel da posição x,y da imagem
			Vec3b pxlp = imagem.at<Vec3b>(x, y);

			// indice: 0 - azul, 1 - verde, 2 - vermelho
			pxlp[indice] = cor; // 0 - 255

								// joga o pixel alterado na imagem
			imagem.at<Vec3b>(x, y) = pxlp;
		}
	}
	return imagem;
}

Mat aplicaCinza(Mat imagem)
{
	for (int x = 0; x < imagem.rows; x++)
	{
		// percorre as colunas
		for (int y = 0; y < imagem.cols; y++)
		{
			// obtem o pixel da posição x,y da imagem
			Vec3b pxlp = imagem.at<Vec3b>(x, y);

			// aplica peso de acordo com a percepção de brilho de cada cor
			//int cinza = pxlp[2] * 0.21 + pxlp[1] * 0.72 + pxlp[0] * 0.07;

			// a soma dos 3 canais de cor dividido por 3
			int cinza = (pxlp[0] + pxlp[1] + pxlp[2]) / 3;

			// indice: 0 - azul, 1 - verde, 2 - vermelho
			pxlp[0] = cinza;
			pxlp[1] = cinza;
			pxlp[2] = cinza;

			// joga o pixel alterado na imagem
			imagem.at<Vec3b>(x, y) = pxlp;
		}
	}
	return imagem;
}

Mat aplicaPretoBranco(Mat imagem, int limiar)
{
	if (limiar < 0) return imagem;

	// aplica filtro cinza na imagem antes
	// de tratar ela para preto e branco
	imagem = aplicaCinza(imagem);
	for (int x = 0; x < imagem.rows; x++)
	{
		// percorre as colunas
		for (int y = 0; y < imagem.cols; y++)
		{
			// obtem o pixel da posição x,y da imagem
			Vec3b pxlp = imagem.at<Vec3b>(x, y);

			pxlp[0] = (limiar > pxlp[0]) ? 0 : 255;
			pxlp[1] = (limiar > pxlp[1]) ? 0 : 255;
			pxlp[2] = (limiar > pxlp[2]) ? 0 : 255;

			// joga o pixel alterado na imagem
			imagem.at<Vec3b>(x, y) = pxlp;
		}
	}
	return imagem;
}

int main()
{
	// lê a imagem
	Mat mat = imread("C:\\Users\\Joshua Raiser\\Downloads\\random-image.jpg");

	Mat imagem = aplicaCinza(mat);

	// mostra a imagem
	imshow("Random-Image", imagem);

	// aguarda um clique de tecla para encerrar a aplicação
	waitKey(0);

}
