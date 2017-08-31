### Conceitos

Uma imagem pode ser definida como uma função bidimensional f(x,y), onde x e y são coordenadas espaciais (plano), e a amplitude de f em qualquer par de coordenadas (x, y) é chamado de intensidade ou nível de cinza de uma imagem naquele ponto.


### Algoritmos iniciais

*Escala de cinza* – Transformar a imagem colorida em escala de cinza

*Média* – a soma dos 3 canais de cor dividido por 3

*Brilho* – aplica peso de acordo com a percepção de brilho de cada cor, vermelho * 0.21 + verde * 0.72 + azul * 0.07

*Isolar Canal* – Retorna em escala de cinza somente um dos três canais de cor


### Operações lineares

> **Negativo**

– Inverter as cores da imagem

```
s = L - 1 - r
```

Esse tipo de processamento é particularmente adequado para realçar detalhes brancos ou cinza incorporados a regiões escuras de uma imagem, especialmente.

> **Função logarítmica (clareia a imagem)**

```
s = c log(1 + r), onde:
c = 255/log(256) ou c = 255/log(max(r) + 1)
```

Amenta o contraste em feições escuras.        
Essa transformação mapeia uma faixa estreita de baixos valores de intensidade de entrada em uma faixa mais ampla de níveis de saída.
O oposto se aplica aos valores mais altos de níveis de intensidade de entrada.
Utilizamos uma transformação desse tipo para expandir os valores de pixels mais escuros em uma imagem ao mesmo tempo em que comprimimos os valores de nível mais alto.
Este tipo de operador é aplicado em imagens que tem uma concentração maior nos pixels mais escuros, esticando esta faixa enquanto comprime a faixa mais clara.

> **Potência (escurece a imagem)**

s = cr^γ, sendo c e γ constantes positivas, γ define a curva de distribuição de pixels e c garante o intervalo de saída ser no mesmo intervalo da entrada.

```
c = 255/(255^γ) ou c = 255/(max(r)^γ)
```

Aumenta o contraste em feições claras (altos níveis de cinza da imagem).
Essa transformação mapeia uma faixa estreita de altos valores de intensidade de entrada em uma faixa mais ampla de níveis de saída.
        
O oposto se aplica aos valores mais baixos de níveis de intensidade de entrada. Utilizamos uma transformação desse tipo para expandir os valores de pixels mais claros em uma imagem ao mesmo tempo em que comprimimos os valores de nível mais baixo.
        
Este tipo de operador é aplicado em imagens que tem uma concentração maior nos pixels mais claros, esticando esta faixa enquanto comprime a faixa mais escura.
Diferente do log, onde a base somente muda a escala, o valor do expoente também modifica a curva de transformação dos pixels.


> **Função Linear por Partes**

Estas funções procuram aumentar o contraste de uma imagem de forma linear, diferentemente dos métodos anteriores.
Utilizaremos três formas diferentes de aplicação: *Limiarização, alargamento de contraste e janelamento*.

*Limiarização*

Definir um limite e transformar a imagem em preto e branco
O processo de limiarização busca dividir uma imagem em somente 1 bit de informação de cor, preto ou branco.
Este processo busca separar a imagem em duas categorias distintas e é muito utilizado como uma etapa inicial na tarefa de segmentação de imagem.
A limiarização traz como consequência a perda da maior parte dos detalhes da imagem

*Alargamento de contraste*

```
s = (r - min(r)) * 255 / (max(r) - min(r))
```

O alargamento de contraste busca aproveitar todo o espaço de intensidade possível para a imagem.
Ele procura o menor valor de intensidade de pixel na imagem e o define como 0, depois procura o maior valor de intensidade e o define como 255. Valores intermediários não sofrem alteração.
Este processo afeta imagens que não utilizam todo o espectro de intensidade possível.

*Janelamento*

O processo de janelamento utiliza a função a seguir:

```
s = 0, se r <= li
s = (r - li) * 255 / (ls - li), se li < r < ls
s = 255, se r >= ls
```

Sendo li e ls os limiares inferior e superior como constantes passadas através parâmetros da função.
O janelamento une os processos de alargamento e limiarização, com o objetivo de aumentar o contraste da imagem nos detalhes centrais, ignorando os limites superior e inferior de intensidade.
Este processo consegue trabalhar com imagens que já possuem os limites de intensidade presentes.
Diferente da limiarização, este processo consegue manter detalhes entre os limiares da função, inclusive aumentando seu contraste.


> **Filtros espaciais**

- O filtro espacial consiste em:
	- Uma vizinhança (normalmente um pequeno retângulo)
	- Uma operação predefinida realizada sobre os pixels da imagem incluídos na vizinhança.
	
A filtragem cria um novo pixel com coordenadas iguais às coordenadas do centro da vizinhança, e cujo valor é o resultado da operação de filtragem. Uma imagem processada (filtrada) é gerada à medida que o centro do filtro percorre cada pixel na imagem de entrada.

Usa-se uma matriz conhecida como máscara / kernel / janela / template.

> **Filtros de suavização**

Usados para borramento e redução de ruído.

*Mediana (algoritmo de suavização não linear)*

Substitui o valor de um pixel pela mediana dos valores de intensidade na vizinhança desse pixel (o valor original do pixel é incluído no cálculo da mediana). 
Proporcionam excelentes resultados na redução de ruído, com borramento consideravelmente menor do que filtros lineares de suavização de tamanho similar.
Os filtros de mediana são particularmente eficazes na presença de ruído impulsivo, também chamado de ruído sal e pimenta, em razão de sua aparência, como pontos brancos e pretos sobrepostos em uma imagem.

*Aguçamento*

Objetiva salientar transições de intensidade para o aumento da nitidez de uma imagem.


*Agradecimento especial à [wguilen (William Guilen)](https://github.com/wguilen).*
