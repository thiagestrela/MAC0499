#include <bits/stdc++.h>
using namespace std;

vector<int> GaleShapley(vector<vector<int>>&);

int main() {
    int V;
    scanf("%d", &V);
    vector<vector<int>> prefs(V, vector<int>());
    int x;
    for (int i = 0; i < V; i++) {
        do {
            scanf("%d", &x);
            if (x != -1) prefs[i].push_back(x);
        } while (x != -1);
    }
    vector<int> emp = GaleShapley(prefs);    
    printf("Emparelhamento A-ótimo:\n");
    for (int i = 0; i < V/2; i++) {
        if (emp[i] != -1)
            printf("%d %d\n", i, emp[i]);
    } 
    return 0;
}

vector<int> GaleShapley(vector<vector<int>> &prefs) {
   int V = (int)prefs.size();
   vector<queue<int>> lists(V);
   vector<int> emp(V, -1);
   for (int i = 0; i < V; i++) {
       for (int j : prefs[i]) {
           lists[i].push(j);
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
   for (int i = 0; i < V/2; i++) {
       free_verts.push(i);
   }
   
   int a, b;
   while (!free_verts.empty()) {
       a = free_verts.front(); free_verts.pop();
       b = lists[a].front(); lists[a].pop();
       cout << a << " " << b << endl;
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

