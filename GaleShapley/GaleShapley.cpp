#include <bits/stdc++.h>
#include "GaleShapley.h"
using namespace std;

/* Esta função implementa o Algoritmo de Gale-Shapley.
 * Parâmetros:
 * prefs -> listas de preferências
 * nA -> número de elementos do conjunto A da bipartição (A, B).
 * orientation -> orientação do algoritmo. Se orientation = 0 (valor padrão)
 * a função executa a versão A-orientada. Se orientation = 1, a função executa
 * a versão B-orientada.
 * A função segue a convenção que A = {0, 1, ..., nA - 1} e B = {nA, ..., n},
 * onde n = prefs.size(). 
 * A saída match corresponde ao emparelhamento estável dado como saída.
 * o emparelhamento M que corresponde a match é aquele tal que para cada
 * vértice v: 
 * * match[v] = -1 <=> v não é coberto por M.
 * * match[v] != -1 <=> v é coberto por M e M(v) = match[v]. 
*/
vector<int> GaleShapley(const vector<vector<int>>& prefs, int nA, int orientation) {
   int V = (int)prefs.size();
   int nB = V - nA;
   //armazenará o emparelhamento estável que será devolvido.
   vector<int> match(V, -1); 
   vector<queue<int>> lists(V, queue<int>()); 
   
   int n = (orientation == 0 ? nA : nB);
   int offset = (orientation == 0 ? 0 : nA);
   for (int i = 0; i < n; i++) {
       int idx = offset + i;
       for (int j : prefs[idx]) {
           lists[idx].push(j);
       }
   } 
   vector<vector<int>> Apos(V, vector<int>(V, -1));
   int w;
   for (int i = 0; i < V; i++) {
       for (int j = 0; j < (int)prefs[i].size(); j++) {
           w = prefs[i][j];
           Apos[i][w] = j; 
       }
   }
   //Se a é adjacente a b, Apos[a][b] = a-posto de b. 
   
   queue<int> free_verts;
   for (int i = 0; i < n; i++) {
       int idx = offset + i;
       free_verts.push(idx);
   }
   
   int a, b;
   while (!free_verts.empty()) {
       a = free_verts.front(); free_verts.pop();
       b = lists[a].front(); lists[a].pop();
       //b não está comprometido com ninguém.
       if (match[b] == -1) {
           match[a] = b; match[b] = a;
       } //b prefere match[b] a a.
       else if (Apos[b][match[b]] < Apos[b][match[a]]) {
           if (!lists[a].empty()) free_verts.push(a);
       } //b prefere a a match[b].
       else {
           match[match[b]] = -1; //b rejeita match[b].
           if (!lists[match[b]].empty()) free_verts.push(match[b]);
           match[a] = b; match[b] = a; 
       }
   }
   return match;
}

