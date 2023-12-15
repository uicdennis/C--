#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Kruskal算法

class UnionFind {
public:
    UnionFind():id(100) { for (int i=0; i<100; i++) id[i]=i; }
    ~UnionFind() {}

    int find(int x) {
        if (x != id[x])
            id[x] = find(id[x]);
        return id[x];
    }
    void unite(int x, int y) {
        int p = find(x);
        int q = find(y);
        if (p == q)
            return;
        id[p] = q;
    }
private:
    vector<int> id;
};

bool cmp(const vector<int>& a, const vector<int>& b) {
    return a[2] < b[2];
}

int main() {
    // vector<vector<int>> edges = {{1, 2, 100}, {2, 3, 200}, {3, 4, 300}, {4, 1, 150}, {1, 3, 500}};
    vector<vector<int>> edges = {{1, 2, 1}, {2, 3, 5}, {3, 4, 9}, {4, 5, 13}, {5, 6, 17}, {6, 1, 21}, {1, 4, 25}};
    sort(edges.begin(), edges.end(), cmp);

    UnionFind uf;
    int ans = 0;
    for (auto& e: edges) {
        int x = e[0], y = e[1], v = e[2];
        if (uf.find(x) != uf.find(y)) {
            uf.unite(x, y);
            ans += v;
            cout << x << "-" << y << endl;
        }
    }

    cout << ans << endl; // 输出最小生成树权重和450
}


// Prim算法
// int prim(vector<vector<int>>& g, vector<pair<int, int>>& city) {
//     int n = g.size();
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
//     vector<bool> visited(n);
//     int ans = 0;
//     q.push({0, 0}); // 从0点开始

//     while (!q.empty()) {
//         auto [dist, u] = q.top();
//         q.pop();

//         if (visited[u])
//             continue;

//         visited[u] = true;
//         ans += dist;

//         for (int v = 0; v < n; v++) {
//             // worng
//             // if (!visited[v] && g[u][v] != 0) {
//             //     q.push({g[u][v], v});
//             // }
//             // correct
//             if (!visited[v] && g[v][u] != 0) {
//                 q.push({g[v][u], v});
//             }
//         }
//     }
//     return ans;
// }

// int main() {
//    vector<vector<int>> g = {
//        {0, 100, 500, 0, 0},
//        {100, 0, 200, 0, 0},
//        {500, 200, 0, 0, 0},
//        {150, 0, 300, 0, 0},
//        {0, 0, 0, 0, 0}
//    };
//    vector<pair<int, int>> city(0);

//    cout << prim(g, city) << endl; // 输出450
// }