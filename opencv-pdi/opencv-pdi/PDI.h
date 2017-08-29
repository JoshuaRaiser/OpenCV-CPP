#pragma once
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <cstdarg>

using Matriz = std::vector<std::vector<int>>;
using Pixel = cv::Vec3b;
using PixelEC = uchar;

class PDI
{
public:
	static cv::Mat escalaCinza(cv::Mat imagemColorida);
	static cv::Mat canal(cv::Mat imagemColorida, int canal);
	static cv::Mat negativo(cv::Mat imagemBase);
	static cv::Mat limiarizacao(cv::Mat imagemBase, int limiar);

	static cv::Mat logaritmo(cv::Mat imagemBase);
	static cv::Mat potencia(cv::Mat imagemBase, float gama);
	static cv::Mat alargamento(cv::Mat imagemBase);
	static cv::Mat janelamento(cv::Mat imagemBase, int li, int ls);

	static cv::Mat suavizacaoMedia(cv::Mat imagemBase, Matriz kernel);
	static cv::Mat suavizacaoMediana(cv::Mat imagemBase, int tamanhoKernel);

	static Matriz eeCustom(int tamX, int tamY, ...);

	static Matriz laplaciano();
	static Matriz laplacianoDiagonal();

	static Matriz kernelCompleto(int tamanho);
	static Matriz kernelPonderado5();

private:
	static int intensidadeMinima(cv::Mat imagemBase);
	static int intensidadeMaxima(cv::Mat imagemBase);
	static int somarKernel(Matriz kernel);

	static int compare(const void * a, const void * b);
};
