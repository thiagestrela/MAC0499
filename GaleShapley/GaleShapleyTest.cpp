#include <bits/stdc++.h>
#include "GaleShapley.h"
using namespace std;

void printMatch(vector<int> &match) {
    for (int i = 0; i < match.size(); i++) {
        if (i < match[i]) {
            cout << i << " <-> " << match[i] << "\n";
        }
    }
}

int main() {
    int nA, nB;
    int n;
    cin >> nA >> nB;
    n = nA + nB;
    vector<vector<int>> prefs(n, vector<int>());
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        while (v != -1) {
            prefs[i].push_back(v);
            cin >> v;
        }
    }
    vector<int> matchA = GaleShapley(prefs, nA, 0);
    cout << "Emparelhamento A-ótimo: \n";
    printMatch(matchA);
    vector<int> matchB = GaleShapley(prefs, nA, 1);
    cout << "Emparelhamento B-ótimo: \n";
    printMatch(matchB);
    return 0;
}
