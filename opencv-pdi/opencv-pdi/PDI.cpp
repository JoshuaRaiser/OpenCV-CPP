#include "stdafx.h"
#include "PDI.h"
#include <algorithm>
#include <cmath>

cv::Mat PDI::escalaCinza(cv::Mat imagemColorida) {
	cv::Mat aux = imagemColorida.clone();

	/*for (int x = 0; x < aux.rows; x++) {
	for (int y = 0; y < aux.cols; y++) {
	Pixel pixel = aux.at<Pixel>(x, y);
	int cinza = pixel[2] * 0.21 + pixel[1] * 0.72 + pixel[0] * 0.07;

	pixel[2] = cinza;
	pixel[1] = cinza;
	pixel[0] = cinza;

	aux.at<Pixel>(x, y) = pixel;
	}
	}*/

	cv::cvtColor(imagemColorida, aux, CV_BGR2GRAY);

	return aux;
}

cv::Mat PDI::limiarizacao(cv::Mat imagemBase, int limiar) {
	cv::Mat aux = imagemBase.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);
			PixelEC cPixel;

			if (pixel <= limiar)
				cPixel = 0;
			else
				cPixel = 255;

			aux.at<PixelEC>(x, y) = cPixel;
		}
	}

	return aux;
}

cv::Mat PDI::negativo(cv::Mat imagemBase) {
	cv::Mat aux = imagemBase.clone();

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);
			PixelEC negativo = 255 - pixel;
			aux.at<PixelEC>(x, y) = negativo;
		}
	}

	return aux;
}

cv::Mat PDI::canal(cv::Mat imagemColorida, int canal) {
	cv::Mat aux = escalaCinza(imagemColorida);

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {

			Pixel pixel = imagemColorida.at<Pixel>(x, y);
			PixelEC pCanal = pixel[canal];


			aux.at<PixelEC>(x, y) = pCanal;
		}
	}

	return aux;
}

cv::Mat PDI::logaritmo(cv::Mat imagemBase) {
	cv::Mat aux = imagemBase.clone();

	float c = 255 / (log(intensidadeMaxima(imagemBase)));

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);

			PixelEC pLog = c * log(1 + pixel);

			aux.at<PixelEC>(x, y) = pLog;
		}
	}

	return aux;
}

cv::Mat PDI::potencia(cv::Mat imagemBase, float gama) {
	cv::Mat aux = imagemBase.clone();

	float c = 255 / pow(intensidadeMaxima(imagemBase), gama);

	for (int x = 0; x < aux.rows; x++) {
		for (int y = 0; y < aux.cols; y++) {
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);

			PixelEC pExp = c * pow(pixel, gama);

			aux.at<PixelEC>(x, y) = pExp;
		}
	}

	return aux;
}

cv::Mat PDI::alargamento(cv::Mat imagemBase) {
	cv::Mat aux = imagemBase.clone();

	int minI = intensidadeMinima(imagemBase);
	int maxI = intensidadeMaxima(imagemBase);
	float escala = maxI - minI;

	for (int x = 0; x < imagemBase.rows; x++) {
		for (int y = 0; y < imagemBase.cols; y++) {
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);
			PixelEC novoPixel = (pixel - minI) * (255 / escala);

			aux.at<PixelEC>(x, y) = novoPixel;
		}
	}

	return aux;
}

cv::Mat PDI::janelamento(cv::Mat imagemBase, int li, int ls) {
	cv::Mat aux = imagemBase.clone();

	float escala = ls - li;

	for (int x = 0; x < imagemBase.rows; x++) {
		for (int y = 0; y < imagemBase.cols; y++) {
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);
			PixelEC novoPixel = pixel;

			if (pixel <= li)
				novoPixel = 0;
			else if (pixel >= ls)
				novoPixel = 255;
			else
				novoPixel = (pixel - li) * (255 / escala);

			aux.at<PixelEC>(x, y) = novoPixel;
		}
	}

	return aux;
}

cv::Mat PDI::suavizacaoMedia(cv::Mat imagemBase, Matriz kernel) {
	cv::Mat aux = imagemBase.clone();
	int somaKernel = somarKernel(kernel);
	int desl = kernel.size() / 2;

	for (int x = desl; x < aux.rows - desl; x++) {
		for (int y = desl; y < aux.cols - desl; y++) {
			float soma = 0;
			for (int i = x - desl; i <= x + desl; i++) {
				for (int j = y - desl; j <= y + desl; j++) {
					PixelEC pixel = imagemBase.at<PixelEC>(i, j);
					soma += pixel * kernel[i - x + desl][j - y + desl];
				}
			}
			soma = soma / somaKernel;
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);
			pixel = soma;
			aux.at<PixelEC>(x, y) = pixel;
		}
	}
	return aux;
}

cv::Mat PDI::suavizacaoMediana(cv::Mat imagemBase, int tamanhoKernel) {
	cv::Mat aux = imagemBase.clone();
	int desl = tamanhoKernel / 2;
	for (int x = desl; x < aux.rows - desl; x++) {
		for (int y = desl; y < aux.cols - desl; y++) {
			PixelEC *vet = new PixelEC[tamanhoKernel * tamanhoKernel];
			for (int i = x - desl; i <= x + desl; i++) {
				for (int j = y - desl; j <= y + desl; j++) {
					PixelEC pixel = imagemBase.at<PixelEC>(i, j);
					vet[(i - x + desl) * tamanhoKernel + (j - y + desl)] = pixel;
				}
			}
			qsort(vet, tamanhoKernel * tamanhoKernel, sizeof(PixelEC), compare);
			PixelEC mediana = vet[(tamanhoKernel * tamanhoKernel) / 2];
			delete[] vet;
			aux.at<PixelEC>(x, y) = mediana;
		}
	}
	return aux;
}


//////////////////////
//FUNÇÕES AUXILIARES//
//////////////////////


int PDI::compare(const void * a, const void * b)
{
	return (*(uchar*)a - *(uchar*)b);
}

Matriz PDI::eeCustom(int tamX, int tamY, ...) {
	Matriz retorno;

	va_list args;
	va_start(args, tamY);

	for (int i = 0; i < tamX; i++) {
		std::vector<int> aux;
		for (int j = 0; j < tamY; j++) {
			aux.push_back(va_arg(args, int));
		}
		retorno.push_back(aux);
	}
	va_end(args);

	return retorno;
}

Matriz PDI::laplaciano() {
	return eeCustom(3, 3,
		0, -1, 0,
		-1, 4, -1,
		0, -1, 0);
}

Matriz PDI::laplacianoDiagonal() {
	return eeCustom(3, 3,
		-1, -1, -1,
		-1, 8, -1,
		-1, -1, -1);
}

Matriz PDI::kernelPonderado5() {
	return eeCustom(5, 5,
		1, 4, 6, 4, 1,
		4, 16, 24, 16, 4,
		6, 24, 36, 24, 6,
		4, 16, 24, 16, 4,
		1, 4, 6, 4, 1);
}

Matriz PDI::kernelCompleto(int tamanho) {
	Matriz retorno;

	for (int i = 0; i < tamanho; i++) {
		std::vector<int> aux;
		for (int j = 0; j < tamanho; j++) {
			aux.push_back(1);
		}
		retorno.push_back(aux);
	}

	return retorno;
}

int PDI::intensidadeMaxima(cv::Mat imagemBase) {
	int maximo = 0;
	for (int x = 0; x < imagemBase.rows; x++) {
		for (int y = 0; y < imagemBase.cols; y++) {
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);
			if (pixel > maximo) {
				maximo = pixel;
			}
		}
	}

	return maximo;
}

int PDI::intensidadeMinima(cv::Mat imagemBase) {
	int minimo = 255;
	for (int x = 0; x < imagemBase.rows; x++) {
		for (int y = 0; y < imagemBase.cols; y++) {
			PixelEC pixel = imagemBase.at<PixelEC>(x, y);
			if (pixel < minimo) {
				minimo = pixel;
			}
		}
	}

	return minimo;
}

int PDI::somarKernel(Matriz kernel) {
	int soma = 0;
	for (std::vector<int> linha : kernel) {
		for (int elemento : linha) {
			soma += elemento;
		}
	}
	return soma;
}
