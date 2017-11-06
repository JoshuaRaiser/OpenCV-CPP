## Histograma
- Histogramas são a base para várias técnicas de processamento no domínio espacial.

- A sua manipulação pode ser utilizada para o realce de imagens, além de fornecer
estatísticas úteis da imagem, também são bastante úteis em outras aplicações de
processamento de imagens, como compressão e segmentação.

- São fáceis de serem calculados utilizando-se um aplicativo computacional, e eles
também podem ser calculados em implementações econômicas de hardware, sendo, dessa forma,
uma ferramenta popular para o processamento de imagens em tempo real.

> Funcionamento:

	- o histograma de uma imagem digital com níveis de intensidade no intervalo [0, 255]
	é uma função discreta H(Rk) = Nk, onde Rk é o k-ésimo valor de intensidade e Nk é o
	número de pixels da imagem com intensidade Rk.
  
	- costuma-se normalizar um histograma dividindo cada um desses componentes pelo número
	total de pixels da imagem, expresso pelo produto LC, onde, geralmente, L e C são as
	dimensões de linha e coluna da imagem.
  
	- dessa forma, um histograma normalizado é dado por P(Rk) = Rk/LC, para k = 0, 1, 2..., 255.
	De modo geral, P(Rk) é uma estimativa da probabilidade de ocorrência do nível de intensidade
	Rk em uma imagem.
  
	- a soma de todos os componentes de um histograma normalizado é igual a 1.

- Limiarização

Em virtude de suas propriedades intuitivas, a simplicidade de implementação e a velocidade
computacional, a limiarização de imagens tem uma posição central nas aplicações de segmentação
de uma imagem.

Definir um limite e transformar a imagem em preto e branco O processo de limiarização busca dividir
uma imagem em somente 1 bit de informação de cor, preto ou branco. Este processo busca separar a imagem
em duas categorias distintas e é muito utilizado como uma etapa inicial na tarefa de segmentação de imagem.
A limiarização traz como consequência a perda da maior parte dos detalhes da imagem.

Extrair objetos do fundo selecionando um limiar T, onde f(x,y) > T é chamado de ponto do objeto,
caso contrário, o ponto é chamado de ponto de fundo. A imagem segmentada, g(x,y), é dada pela
seguinte equação:

      se f(x,y)  > T então g(x,y) = 1,
	  se f(x,y) <= T então g(x,y) = 0

- Limiarização Global Simples

Utilizado para quando as distribuições de intensidade dos pixels de fundo e dos objetos são
suficientemente diferentes, é possível utilizar um único limiar (global) aplicável a toda a imagem.

Consiste o algoritmo em:

	1 - Selecionar uma estimativa inicial para o limiar global, T, normalmente a média de intensidade da imagem.
	2 - Segmentar a imagem usando T na equação:
		g(x,y) = 1, se f(x,y)  > T
		g(x,y) = 0, se f(x,y) <= T
	dando origem a dois grupos: G1, pixels de intensidade > T e G2, composto de pixels com valores <= T.
	3 - Calcular os valores de intensidade média de m1 e m2 para os pixels em G1 e G2.
	4 - Calcular um novo limiar: T = 1/2 * (m1+m2).
	5 - Repitir as etapas 2 a 4 até que a diferença entre os valores de T em iterações sucessivas seja
	menor que o parâmetro predefinido ΔT.
	6 - Aplicar o algoritmo de limiarização da imagem a partir do ultimo T encontrado.
	
## Segmentação por Borda
Os algoritmos de segmentação para imagens monocromáticas geralmente estão baseados em uma de duas categorias
básicas relacionadas às propriedades dos valores de intensidade: **descontinuidade e similaridade**.

A primeiro categoria, o pressuposto é que as **fronteiras** das regiões são **suficientemente diferentes** entre si
e em relação ao fundo das imagem para permitir a detecção de limite com base nas **descontinuidades** locais em intensidade.

A segmentação baseada nas **bordas** é a principal abordagem usada nesta categoria.

As abordagens da segmentação baseada na **região**, na segunda categoria, estão baseadas na divisão de **uma imagem em regiões**
que sejam semelhantes de acordo com um conjunto de critérios predefinidos.

> Detecção de ponto, linha e borda

	- os três tipos de características de imagem são os pontos isolados, as linhas e as bordas.
  
	- os pixels de borda são pixels onde a intensidade da imagem muda de forma abrupta.
  
	- as bordas (ou segmentos de borda) são conjuntos de pixels de borda conexos.
  
	- uma linha pode ser vista como um segmento de borda em que a intensidade do fundo de cada lado da linha é muito superior
	ou muito inferior à intensidade dos pixels da linha, da mesma forma ocorre com um ponto isolado.
  
	
Os detectores são métodos desenvolvidos para detectar os pixels da borda.
	
- As derivadas de uma função digital são definidas em termos de diferenças, mas é preciso que qualquer aproximação utilizada
para uma primeira derivada:

    1 - seja zero nas áreas de intensidade constante.
    2 - seja diferente de zero no início de um degrau ou rampa de intensidade.
    3 - que seja diferente de zero em pontos ao longo de uma rampa de intensidade.
	
- Da mesma forma, é preciso que qualquer aproximação utilizada para uma derivada de segunda ordem:

    1 - seja zero nas áreas de intenidade constantes.
    2 - seja diferente de zero no início e no final de uma rampa ou degrau de intensidade.
    3 - seja diferente de zero ao longo das rampas de intensidade.
	
Este processo de aplicação de segunda derivada é aproximada para um espaço discreto, onde a menor mudança de pixel é um 1.
Todo esse processo acaba se resumindo a aplicação de um kernel, em que cada pixel, onde o peso do pixel central somado aos
seus vizinhos tem um resultado 0. Ito faz com que uma região onde todos os pixels são iguais traz um resultado igual a zero,
e pixels de intensidades diferentes tendem a um valor diferente de 0.
	
## Operadores Morfológicos
- A morfologia usada no contexto matemático como uma ferramenta para extrair componentes das imagens que são úteis na
representação e na descrição da forma de uma região, como fronteiras, esqueletos e o fecho convexo (convex hull).

- A linguagem da morfologia matemática é a teoria dos conjuntos. Por exemplo, o conjunto de todos os pixels brancos em uma
imagem binária é uma descrição morfológica completa da imagem.

- As operações são aplicadas sempre a partir de uma imagem binária (preto ou branco, 0 ou 255), o operador de erosão tende
a deteriorar a nossa área enquanto o de dilaração tende a aumenta-las.

- A abertura e o fechamento são a combinação desses dois operadores, sendo seu principal objetivo, utilizar as propriedades
do que for aplicado primeiro, e restaurar o melhor possível a imgem original com o segundo.

Estes processos são feitos aplicando um elemento estruturante na imagem original.

> Elementos estruturais (ES) 

	- seu formato interfere diretamente no resultado (imagem final), circulos tendem a gerar formas
	arredondadas enquanto quadrados tendem a gerar formas retas.
	- são pequenos conjuntos ou sub imagens usadas para examinar uma imagem buscando propriedades
	de interesse. Quando não importa se um lugar em um certo elemento estrutural é ou não um 
	membro do conjunto ES, essa localização é marcada com um "x" para indicar uma condição do tipo
	"não interessa".
	- além  de definir quais elementos são membros do ES, a origem de um elemento estruturante também
	deve ser especificada. As origens são indicadas por um ponto preto. Quando o ES é simétrico e nenhum
	ponto preto é mostrado, considera-se que a origem está no centro de simetria.
	- é necessário que os elementos	estruturantes sejam arranjos matriciais retangulares.
	
  Existem duas características principais que estão diretamente relacionadas aos elementos estruturantes:
	
  1) Forma: por exemplo, o elemento estruturante pode ser um circulo, uma linha, um quadrado, um anel etc.
	Escolhendo um elemento estruturante particular, estabelece-se uma maneira de diferenciar alguns objetos
	(ou parte de objetos) de outros, de acordo com sua forma ou orientação espacial.
	
  2) Tamanho: por exemplo, um elemento estruturante pode ser um quadrado 3x3 ou um 21x21. Definir o tamanho
	o elemento estruturante é semelhante à definição da escala de observação e é o critério para diferenciar
	objetos de imagem ou recursos de acordo com o tamanho.
	
> Erosão

	- diminui ou afina os objetos em uma imagem binária.
	- os detalhes menores do que o elemento estruturante da imagem são filtrados (removidos) da imagem.
	
> Dilatação

	- aumenta ou engrossa os objetos em uma imagem binária.
	- a forma específica e a extensão desse espessamento são controlados pelo elemento estruturante.
	- uma de suas aplicações mais simples é a união de lacunas.
	
> Abertura

	- geralmente suaviza o contorno de um objeto, rompe os istmos e elimina as saliências finas.
	
> Fechamento

	- também tende a suavizar contornos, mas geralemente funde as descontinuidades estreitas e
	alonga os golfos finos, elimina pequenos buracos e preenche as lacunas em um contorno.

> Bordas

Não se pode encaixar o elemento estruturante nessas áreas, e com isso são é possível determinar seu resultado.
Existem duas soluções para este problema:

	- Não avaliar estes pixels, normalmente estas bordas são insignificantes para a totalidade da imagem e 
	podem ser desprezados para o resultado final.
	- Avaliar os pixels utilizando somente a parte do elemento estruturante que cabe na imagem. Isto é o mesmo
	que imaginar uma borda na imagem preenchida pelo elemento neutro da operação. Que é igual a branco para erosão
	e preto para a dilatação.	

## Detecção de Borda e Watershed

- Uma transição dos métodos de processamento de imagem cujas entradas e saídas são imagens para métodos em que as
entradas são imagens, mas as saídas são atributos extraídos dessas imagens. A segmentação é um passo importante.
- Produz resultados de segmentação mas estáveis.

> Segmentação

	- subdivide uma imagem em regiões ou objetos que a compõem. O nível de detalhe em que a subdivisão é realizada
	depdente do problema a ser resolvido. Ou seja, a segmentação deve parar quando os objetos ou as regiões de interesse
	de uma aplicação forem detectados.
	
Segmentação para imagens monocromáticas estão baseadas em uma de duas categorias: **descontinuidade e similaridade**

> Descontinuidade

	- o pressuposto é que as fronteiras das regiões são suficientemente diferentes entre si e em relação ao fundo
	da imagem para permitir a detecção de limite com base nas descontinuidades locais em intensidade.
	- tem como principal abordagem a segmentação baseada nas bordas

> Similaridade

	- baseia-se na divisão de uma imagem em regiões que sejam semelhantes de acordo com um connjunto de critérios predefinidos.
	- abordagem da segmentação baseada na região
	
> Watershed

Baseia-se na visualização de uma imagem em **três dimensões**: duas coordenadas espaciais versus intensidade.
Em uma interpretação, considera-se:

	1 - os pontos que pertencem a um mínimo regional.
	2 - pontos em que a gota d'água, se despejada na localização de algum desses pontos, cairia quase
	que com certeza em um mínimo simples
	3 - pontos em que a água tem a mesma probabilidade de cair em mais de um mínimo desses.

Para um **mínimo regional** específico, o conjunto de pontos que satisfaz a condição é chamado de bacia
hidrográfica, ou watershed desse mínimo. Os pontos que satisfazem a condição formam **linhas de crista** sobre
a superfície topográfica e são denominados linhas de divisão ou linhas de watershed.

O principal objetivo do algoritmo é encontrar as **linhas de watershed**.

A idéia é simples:

	- Suponha que um orifício seja perfurado em cada mínimo regional e que a topografia inteira seja inundada
	de baixo para cima, deixando a água subir pelos orifíciod a uma taxa uniforme.
  
	- Quando a água acumulada nas diversas watersheds está prestes a se juntar, uma barragem é construída para
	impedir a fusão. A inundação acabará por chegar a uma fase em que apenas os topos das barragens são visíveis
	acima da linha d'água.
  
	- Esses limites correspondem às linhas de divisão das watersheds, resultado desejado da segmentação.

A maneira mais simples de construir barragens separando os conjuntos de pontos binários é usar a dilatação morfológica.
A altura de todas as barragens geralmente é **estabelecida em 1, acrescido do valor máximo permitido** na imagem. Isso
evita que a água saia da barragem concluída conforme o nível de inundação aumenta. As barragens construídas por este processo,
que são as fronteiras da **segmentação** desejadas, são componentes conectados. Em oturas palavras, esse método elimina os problemas
de linhas de segmentação descontínuas.