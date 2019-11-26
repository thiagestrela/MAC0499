# MAC0499 - Trabalho de formatura supervisionado

Este repositório contém o código do trabalho de formatura supervisionado de Thiago Estrela Montenegro, disponível em
https://linux.ime.usp.br/~thiagestrela/mac0499/

## Implementações

Todas as implementações descritas abaixos foram feitas utilizando a linguagem C++17.

### Algoritmo de Gale-Shapley

O código GaleShapley/GaleShapley.cpp contém a função GaleShapley que implementa o clássico Algoritmo de Gale-Shapley que, dado um grafo de preferências bipartido, devolve um emparelhamento estável. A implementação consome tempo proporcional ao número de arestas do grafo de preferências dado como entrada. O código está documentado.

### Algoritmo de Irving

O código IrvingAlgorithm/IrvingAlgorithm.cpp contém a função IrvingAlgorithm que implementa o Algoritmo de Irving que, dado um grafo de preferências, devolve um emparelhamento estável. A implementaçào consome tempo proporcional ao número de arestas do grafo de preferências. O código está documentado.

## Compilando

Para compilar, basta executar na pasta correspondente:
```
make
```
