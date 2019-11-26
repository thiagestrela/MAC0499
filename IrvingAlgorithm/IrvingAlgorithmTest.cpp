#include "IrvingAlgorithm.h"
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

int main() { 
    printf("Algoritmo de Irving ---------------\n");
    int V;
    cin >> V;
    vector<vector<int>> prefs(V, vector<int>());
    
    int x;
    for (int i = 0; i < V; i++) {
        do {
            scanf("%d", &x);
            if (x != -1) prefs[i].push_back(x);
        } while (x != -1);
    }
    vector<int> match = Irving(prefs);
    if (match.empty()) {
        printf("Instância sem solução\n");
    }
    else {
        printf("Emparelhamento estável encontrado:\n");
        for (int i = 0; i < V; i++) {
            if (match[i] != -1 and match[i] > i) {
                printf("%d <-> %d\n", i, match[i]);
            }
        }
    }
    prefs = IrvingPhase1(prefs);
    for (int i = 0; i < V; i++) {
        printf("%d:", i);
        for (int j = 0; j < (int)prefs[i].size(); j++) {
            printf(" %d", prefs[i][j]);
        }
        printf("\n");
    }
    return 0;
}
