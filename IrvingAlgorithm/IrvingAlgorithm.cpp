#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> IrvingPhase1(const vector<vector<int>>&);
vector<int> IrvingPhase2(const vector<vector<int>>&, const vector<vector<int>>&);
vector<int> Irving(const vector<vector<int>>&);

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
                printf("%d %d\n", i, match[i]);
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

vector<int> Irving(const vector<vector<int>>& prefs) {
    return IrvingPhase2(prefs, IrvingPhase1(prefs));
}

vector<vector<int>> IrvingPhase1(const vector<vector<int>>& prefs) {
    int n = prefs.size();
    vector<int> semi_engaged(n, -1);
    vector<vector<int>> Apos(n, vector<int>(n)), is_removed(n, vector<int>(n));
    queue<int> free_verts;
    vector<vector<int>> reduced_prefs(n, vector<int>());
    vector<deque<int>> lists(n, deque<int>());

    for (int i = 0; i < n; i++) {
        if (prefs[i].size() >= 1)
            free_verts.push(i);
    }

    int w;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)prefs[i].size(); j++) {
            w = prefs[i][j];
            is_removed[i][w] = false;
            Apos[i][w] = j;
        }
    }

    for (int i = 0; i < n; i++) {
        lists[i].assign(prefs[i].begin(), prefs[i].end());
    }

    while (!free_verts.empty()) {
        int v = free_verts.front(); free_verts.pop();
        int w;
        while (!lists[v].empty() and is_removed[v][lists[v].front()]) {
            lists[v].pop_front();
        }
        w = lists[v].front();
        if (int u = semi_engaged[w]; u != -1) {
            while (!lists[u].empty() and is_removed[u][lists[u].back()]) {
                lists[u].pop_back();    
            }
            if (!lists[u].empty()) {
                free_verts.push(u);
            }
        }
        semi_engaged[w] = v;
        while (lists[w].back() != v) {
            is_removed[w][lists[w].back()] = true;
            is_removed[lists[w].back()][w] = true;
            lists[w].pop_back();
        }
    }
    for (int i = 0; i < n; i++) {
        int w;
        for (int j = 0; j < (int)lists[i].size(); j++) {
            w = lists[i][j];
            if (!is_removed[i][w])
                reduced_prefs[i].push_back(w);
        }
    }

    return reduced_prefs; 
} 

void fix_node(const int u, vector<deque<int>>& lists, vector<int>& second, const vector<vector<int>>& is_removed) {
    while (!lists[u].empty() and is_removed[u][lists[u].back()]) {
        lists[u].pop_back();
    }
    while (!lists[u].empty() and is_removed[u][lists[u].front()]) {
        lists[u].pop_front();
    }
    if (lists[u].size() <= 1 or (lists[u].size() > 1 and second[u] == lists[u][1]))
        return;
    int s_idx = 1;
    while (is_removed[u][lists[u][s_idx]]) {
        s_idx++;
    }
    second[u] = lists[u][s_idx];
    assert(!is_removed[u][second[u]]);
}

void remove_rotation(vector<deque<int>>& lists, vector<int>& second, vector<pair<int,int>>& rotation, vector<vector<int>>& is_removed, bool& emptylist) {
    int n = rotation.size();
    cout << "Arestas removidas:" << endl;
    for (int i = 0; i < n; i++) {
        int y = rotation[i].second;
        int j = (i == 0 ? n - 1 : i - 1);
        int x = rotation[j].first;
        fix_node(y, lists, second, is_removed);
        while (!lists[y].empty() and lists[y].back() != x) {
            printf("(%d, %d)\n", y, lists[y].back());
            is_removed[y][lists[y].back()] = true;
            is_removed[lists[y].back()][y] = true;
            lists[y].pop_back();
        }
        if (lists[y].empty()) {
            emptylist = true; 
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        int y = rotation[i].second;
        fix_node(y, lists, second, is_removed);
        if (lists[y].empty()) {
            emptylist = true;
            return;
        }
    }
    rotation.clear();
}

vector<int> IrvingPhase2(const vector<vector<int>>& prefs, const vector<vector<int>>& reduced_prefs) {
    int n = prefs.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)prefs[i].size(); j++) {
            int w = prefs[i][j];
            if (reduced_prefs[i].empty() and reduced_prefs[w].empty())
                return {};
        }
    }
    bool is_matching = true;
    int u;
    for (int i = 0; i < n; i++) {
        if (prefs[i].size() > 1) {
            is_matching = false;
            u = i;
            break;
        }
    }
    if (is_matching) {
        vector<int> match(n, -1);
        for (int i = 0; i < n; i++) {
            if (!prefs[i].empty())
                match[i] = prefs[i].front();
        }   
        return match;
    }
    stack<int> st;
    vector<bool> in_stack(n, false);
    vector<pair<int,int>> rotation;
    bool emptylist = false;
    vector<deque<int>> lists(n, deque<int>());
    vector<vector<int>> is_removed(n, vector<int>(n));
    vector<int> second(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)reduced_prefs[i].size(); j++) {
            int w = reduced_prefs[i][j];
            is_removed[i][w] = false;
        }
        if (reduced_prefs[i].size() > 1)
            second[i] = reduced_prefs[i][1];
    }
    for (int i = 0; i < n; i++) {
        lists[i].assign(reduced_prefs[i].begin(), reduced_prefs[i].end());
    }
    while (u < n and !emptylist) {
        if (st.empty()) { 
            while (u < n) {
                cout << u << " " << lists[u].size() << endl;
                fix_node(u, lists, second, is_removed);
                if (lists[u].size() > 1) break;
                u++;
            } 
            if (u < n) { 
                st.push(u); in_stack[u] = true;
            }
        }
        else {
            int w = st.top(); 
            fix_node(w, lists, second, is_removed);
            assert(!is_removed[w][second[w]]);
            w = lists[second[w]].back(); 
            while (!in_stack[w]) {
                in_stack[w] = true;
                st.push(w);
                fix_node(w, lists, second, is_removed);
                w = lists[second[w]].back();
            }
            int w2 = st.top(); st.pop(); in_stack[w2] = false;
            rotation.push_back(make_pair(w2, lists[w2].front()));
            while (w2 != w) {
                w2 = st.top(); st.pop(); in_stack[w2] = false;
                rotation.push_back(make_pair(w2, lists[w2].front()));
            }
            reverse(rotation.begin(), rotation.end());
            printf("Rotação encontrada:\n");
            for (auto x : rotation) {
                printf("(%d, %d)\n", x.first, x.second);
            }
            remove_rotation(lists, second, rotation, is_removed, emptylist);
            assert(emptylist or rotation.empty());
        }
    }
    if (emptylist) return {};
    vector<int> match(n, -1);
    for (int i = 0; i < n; i++) {
        assert(lists[i].size() <= 1);
        if (lists[i].size() == 1)
            match[i] = lists[i].front();
    }
    return match;
}
