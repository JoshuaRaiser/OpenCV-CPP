#pragma once
#include "stdafx.h"

#include "opencv2/opencv.hpp"
#include "Kuwahara.h"
#include <cmath>

class KuwaharaRegiao {

	int *Reg[4];
	int Tam[4];
	long Soma[4];
	double Var[4];
	int kernel;

public:

	KuwaharaRegiao(int _kernel) : kernel(_kernel) {
		for (int i = 0; i<4; i++) {
			Reg[i] = new int[kernel*kernel];
			Tam[i] = 0;
			Soma[i] = 0;
			Var[i] = 0.0;
		}
	}

	// Atualiza o valor do tamanho, da soma e região de determinada área
	void atualizaData(int area, int data) {
		Reg[area][Tam[area]] = data;
		Soma[area] += data;
		Tam[area]++;
	}

	// Calcula a variância de cada área
	double var(int area) {
		if (Tam[area] == 1) return 1.7e38; // Se esse for o único pixel dentro da região, então retorna o maximo do double
											// com esse número, a região nunca irá ser considerada em minVar(), por ser muito grande

		int somaArea = Soma[area];
		int tamanhoArea = (Tam[area] == 0 ? 1 : Tam[area]);

		int __mean = somaArea / tamanhoArea;

		double temp = 0;

		for (int i = 0; i<Tam[area]; i++) {
			temp += (Reg[area][i] - __mean) * (Reg[area][i] - __mean);
		}
		return sqrt(temp / (Tam[area] - 1));
	}

	// Calcula a variância das 4 regiões
	void calcVar() {
		for (int i = 0; i<4; i++) {
			Var[i] = var(i);
		}
	}

	// encontra a menor variancia entre as 4 regiões
	int menorVariancia() {
		calcVar();
		int aux = 0;
		double __var = Var[0];
		for (int i = 1; i < 4; i++)
		{
			if (__var > Var[i])
			{
				__var = Var[i];
				aux = i;
			}
		}
		return aux;
	}

	// retorna a media da região com menor variância
	uchar resultado() {
		int i = menorVariancia();
		return (double) (Soma[i] * 1.0) / Tam[i];
	}
};