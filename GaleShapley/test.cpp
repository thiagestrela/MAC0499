#include <bits/stdc++.h>
using namespace std;

vector<int> GaleShapley(const vector<vector<int>>&, int, int, int);

int main() {
    int nA, nB;
    scanf("%d %d", &nA, &nB);
    int V = nA + nB;
    vector<vector<int>> prefs(V, vector<int>());

    int x;
    for (int i = 0; i < V; i++) {
        do {
            scanf("%d", &x);
            if (x != -1) prefs[i].push_back(x);
        } while (x != -1);
    }

    vector<int> Aopt, Bopt;
    Aopt = GaleShapley(prefs, nA, nB, 0);
    Bopt = GaleShapley(prefs, nA, nB, 1);

    printf("Emparelhamento A-ótimo:\n");
    for (int i = 0; i < nA; i++) {
        if (Aopt[i] != -1)
            printf("%d %d\n", i, Aopt[i]);
    }
    printf("Emparelhamento B-ótimo:\n");
    for (int i = 0; i < nA; i++) {
        if (Bopt[i] != -1)
            printf("%d %d\n", i, Bopt[i]);
    }
    return 0;
}

vector<int> GaleShapley(const vector<vector<int>>& prefs, int nA, int nB, int orientation) {
   int V = nA + nB;
   vector<int> emp(V, -1);
   vector<queue<int>> lists(V, queue<int>());

   int n = (orientation == 0 ? nA : nB);
   int offset = (orientation == 0 ? 0 : nB);
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
   
   queue<int> free_verts;
   for (int i = 0; i < n; i++) {
       int idx = offset + i;
       free_verts.push(idx);
   }
   
   int a, b;
   while (!free_verts.empty()) {
       a = free_verts.front(); free_verts.pop();
       b = lists[a].front(); lists[a].pop();
       if (emp[b] == -1) {
           emp[a] = b; emp[b] = a;
       }
       else if (Apos[b][emp[b]] < Apos[b][emp[a]]) {
           if (!lists[a].empty()) free_verts.push(a);
       }
       else {
           emp[emp[b]] = -1;
           if (!lists[emp[b]].empty()) free_verts.push(emp[b]);
           emp[a] = b; emp[b] = a;
       }
   }
   return emp;
}

