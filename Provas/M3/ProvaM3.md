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

## Crescimento de Região.

- É um procedimento que **agrupa os pixels** ou as sub-regiões em regiões maiores com base em critérios predefinidos para o crescimento.

- A abordagem básica é começar com um conjunto de pontos “**semente**” e, a partir deles, fazer as **regiões crescerem** anexando a cada
semente aqueles pixels vizinhos que têm propriedades predefinidas semelhantes às das sementes (como os intervalos específicos de intensidade ou cor).

- A **seleção de um conjunto** de um ou mais pontos de partida muitas vezes pode ser baseada na natureza do problema. Quando uma **informação de prioridade**
não estiver diponível, o procedirmento é calcular em cada pixel o mesmo conjunto de propriedades que, em última análise, será utilizadas para **designar
os pixels das regiões** durante o processo de crescimento.

- Se o resultado **mostrar conjuntos de valores**, os pixels cujas propriedades os deixam perto do **centroid desses aglomerados** podem ser usados como sementes.

- A seleção dos **critérios de similaridade** depende não só do problema em questão, mas também do tipo de dados da imagem disponível.

> Quando as imagens são monocromáticas, a análise de região deve ser realizada com um conjunto de indicadores baseados nos níveis de intensidade e nas propriedades
espaciais (como os momentos ou textura).

- O crescimento deve parar quando **não houver mais píxels** satisfazendo os critérios de **inclusão** na região referida. Critérios como os valores de **intensidade**,
textura e cor são de natureza loval e não levam em conta o "histórico" da região crescida.

> Consiste o algoritmo em:

	1 - Encontrar todos os componentes conectados em S(x, y) e erodir cada componente conectado a um pixel; 
	2 - Rotular todos os pixels encontrados como número 1. Todos os outros pixels em S recebem 0.
	3 - Formar uma imagem fQ que, em um par de coordenadas (x, y), deixe fQ(x, y) = 1 se a imagem de entrada
	satisfaz a propriedade determinada, Q, nessas coordenadas; caso contrário, deixe fQ(x, y) = 0.
	4 - Digamos que g é uma imagem formada anexando a cada semente em S todos os pontos rotulados com o número 1
	em fQ que estão 8-conectados a essa semente.
	5 - Rotular cada componente conectado em g com uma diferente etiqueta de região (por exemplo, 1, 2, 3, ...).
	Esta é a imagem segmentada obtida pelo crescimento de região.

## Labelling

- É usada em visão computacional para detectar regiões conectadas em imagens digitais binárias.

> Algoritmo de Rotulação: Um omponente por vez

Método rápido e muito simples. Baseia-se em métodos de cruzamento de gráficos na teoria dos grafos. Uma vez que o primeiro pixel de um componente conectado é
encontrado, todos os pixels conectados desse componente conectado são retulados antes de passar para o próximo pixel na imagem.

Para fazer isso, é formada uma lista vinculada que manterá os índices dos pixels que estão conectados entre si. O método de definição da lista vinculada espefifica
o uso de uma primeira pesquisa de profundidade ou largura. O tipo mais simples de uma última fila de saída, implementada como uma lista ligada separadamente, resultará
em uma primeira estratégia de busca em profundidade.

- O algoritmo é dado da seguinte forma:

	1 - Comece a partir do primeiro pixel na imagem. Configure o rótulo atual para 1.
	2 - Se esse pixel for um pixel de primeiro plano e ainda não estiver rotulado, dê 
	o rótulo atual e adicione-o como o primeiro elemento em uma fila. Se for um pixel
	de fundo ou já foi rotulado, repita para o próximo pixel na imagem.
	3 - Destaque um elemento da fila e veja seus vizinhos (com base em qualquer tipo 
	de conectividade). Se um vizinho é um pixel de primeiro plano e ainda não está rotulado,
	dê o rótulo atual e adicione-o à fila. Repita até que não hava mais elementos na fila.
	4 - Vá para o próximo pixel na imagem e incremente o rótulo atual em 1.
	
> Two-Pass Algorithm: Algoritmo de duas passagens

De simples implementação, o algoritmo de duas passagens itera duas vezes através dos pixels da imagem.

- A primeira passagem para atribuir etiquetas temporárias e equivalências de registro. A segunda passagem
serve para substituir cada etiqueta temporária pelo menor rótulo de sua classe de equivalência.

As verificações de conectividade são realizadas verificando os rótulos dos pixels vizinhos (elementos vizinhos
cujos **rótulos** ainda não foram atribuídos são **ignorados**), ou seja, o **Nordeste**, o **Norte**, o **Noroeste**
e o **Oeste** do pixel atual (assumindo que sejam 8-conectividade). A 4-conectividade usa apenas vizinhos Norte e Oeste do pixel atual.

- Assumindo 4-conectividade, as condições para verificar são:

```
O pixel para a esquerda (Oeste) tem o mesmo valor que o pixel atual?
	Sim - Estamos na mesma região. Atribua o mesmo rótulo ao pixel atual.
	Não - Verifique a próxima condição.

Os dois pixels para o Norte e Oeste do pixel atual têm o mesmo valor que o pixel atual mas não mesmo rótulo?
	Sim - Sabemos que os pixels Norte e Oeste pertencem à mesma região e devem ser fundidos.
	Atribua o pixel atual o mínimo das etiquetas Norte e Oeste e registre seu relacionamento de equivalência.
	Não - Verifique a próxima condição.

O pixel à esquerda (Oeste) tem um valor diferente e o do Norte o mesmo valor que o pixel atual?
	Sim - Atribua a etiqueta do pixel Norte ao pixel atual.
	Não - Verifique a próxima condição.

Os vizinhos do pixel Norte e do Oeste têm valore de pixel diferentes dos pixels atuais?
	Sim - Crie um novo ID de etiqueta e atribua-o ao pixel atual.
```

O algoritmo trabalha aplicando estes testes para cada pixel na imagem que pertence à um objeto (pixel branco).
Trabalha com uma estrutura do mesmo tamanho da imagem que armazena cada rótulo, quando um pixel é rotulado, o
rótulo definido pelas condições acima é aplicado nesta estrutura.

Além dos vetores de rótulos, temos um vetor de equivalências, no início cada rótulo é equivalente a ele mesmo,
o que muda quando élocalizado um pixel que faz fronteira pixels de dois rótulos diferentes.
