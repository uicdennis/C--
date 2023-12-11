#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    int _count; // 頂點數量
    vector<vector<int>> adj; // 鄰接表
    int time; // DFS的發現時間
public:
    vector<int> break_point;
public:
    Graph(int vertices) : _count(vertices), adj(vertices), time(0), break_point(0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void articulationPointAndBridge(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<pair<int, int>>& bridges) {
        disc[u] = low[u] = ++time; // 初始化發現時間和最早祖先時間

        for (int v : adj[u]) {
            if (!disc[v]) {
                parent[v] = u;

                articulationPointAndBridge(v, disc, low, parent, bridges);

                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    // (u, v) 是一條橋
                    bridges.push_back({u, v});
                }
            } else if (v != parent[u]) {
                // 更新最早祖先時間
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    bool isBiconnected() {
        vector<int> disc(_count, 0); // 發現時間
        vector<int> low(_count, 0);  // 最早祖先時間
        vector<int> parent(_count, -1); // DFS樹中的父節點
        vector<pair<int, int>> bridges; // 存儲橋的列表
        vector<int> pt_setting(_count, 0);

        // 從每個未被訪問的節點開始DFS
        for (int i = 0; i < _count; ++i) {
            if (!disc[i]) {
                articulationPointAndBridge(i, disc, low, parent, bridges);
            }
        }

        for (pair<int, int> b:bridges) {
            // cout << b.first << "-" << b.second << " ";
            if (!pt_setting[b.second]) {
                if (adj[b.second].size() > 1) {
                    break_point.push_back(b.second);
                    pt_setting[b.second] = 1;
                }
            }
            if (!pt_setting[b.first]) {
                if (adj[b.first].size() > 1) {
                    break_point.push_back(b.first);
                    pt_setting[b.first] = 1;
                }
            }
        }
        // cout << endl;

        // 如果沒有割點且橋的數量等於或小於1，則圖是雙連通的
        return count(disc.begin(), disc.end(), 0) == 0 && bridges.size() <= 1;
    }

    void findArticulationPoints(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& isArticulation) {
        int children = 0; // 子節點計數

        disc[u] = low[u] = ++time; // 初始化發現時間和最早祖先時間

        for (int v : adj[u]) {
            if (!disc[v]) {
                children++;
                parent[v] = u;

                findArticulationPoints(v, disc, low, parent, isArticulation);

                low[u] = min(low[u], low[v]);

                // 檢查割點條件
                if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
                    isArticulation[u] = true;
                }
            } else if (v != parent[u]) {
                // 更新最早祖先時間
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    vector<int> getArticulationPoints() {
        vector<int> disc(_count, 0); // 發現時間
        vector<int> low(_count, 0);  // 最早祖先時間
        vector<int> parent(_count, -1); // DFS樹中的父節點
        vector<bool> isArticulation(_count, false); // 是否為割點

        // 從每個未被訪問的節點開始DFS
        for (int i = 0; i < _count; ++i) {
            if (!disc[i]) {
                findArticulationPoints(i, disc, low, parent, isArticulation);
            }
        }

        vector<int> articulationPoints;
        for (int i = 0; i < _count; ++i) {
            if (isArticulation[i]) {
                articulationPoints.push_back(i);
            }
        }

        return articulationPoints;
    }
};

int main()
{
    int p, c, count;
    vector<int> node_list(0);

    count = 0;
    while (!cin.eof()) {    // Windows: Ctrl+Z to stop input, Linux: Ctrl+D
        p = -1;
        cin >> p >> c;

        if (p != -1) {
            count++;
            node_list.push_back(p);
            node_list.push_back(c);
        }
    }

    Graph g(count);

    for (int i=0; i<count; i++) {
        g.addEdge(node_list[2*i], node_list[2*i+1]);
    }

    vector<int> articulationPoints = g.getArticulationPoints();

    if (!articulationPoints.size()) {
        cout << "true";
    } else {
        int i=0;

        sort(articulationPoints.begin(), articulationPoints.end());
        cout << "false" << endl;
        for (auto x : articulationPoints) {
            if (i++ != articulationPoints.size())
                cout << x << " ";
            else
                cout << x;
        }
        cout << endl;
    }

    // if (g.isBiconnected() && !g.break_point.size()) {
    //     cout << "true";
    // } else {
    //     int i=0;

    //     sort(g.break_point.begin(), g.break_point.end());
    //     cout << "false" << endl;
    //     // for (int i=g.break_point.size(); i>0; i--) {
    //     for (auto x : g.break_point) {
    //         if (i++ != g.break_point.size())
    //             cout << x << " ";
    //         else
    //             cout << x;
    //     }
    //     cout << endl;
    // }

    return 0;
}
