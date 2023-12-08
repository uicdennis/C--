#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    //int parentCount;
    //int childCount;
    int value;
    vector<int> parents;
    vector<int> children;

public:
    Node() {}
    Node(int v):value(v) {}
    ~Node() {}

    void addParent(int p) { parents.push_back(p); }
    void addChild(int c) { children.push_back(c); }
    int parentsCount() { return parents.size(); }
    int childrenCount() { return children.size(); }
    int index() { return value; }
};

bool is_connected(vector<Node> vn, vector<int> v)
{
    vector<int> vp;
    vector<int> vc;

    for (int a:v) {
        vp = vn[a].parents;
        vc = vn[a].children;

        for (int b:vp) {

        }
    }
}

bool is_Biconnected(vector<Node> v, int n)
{
    vector<Node>::iterator it;
    int p_count=0, c_count=0;
    int i;
    vector<int> bridge(0);

    // [To Do]: 尚未得知如何判斷圖形是否斷掉!!
    // 移掉點(n)，查看原本連接的點是否還可以連著。
    // 點(n)的連接點
    if (v[n].parentsCount() || v[n].childrenCount()) {
        cout << n << ": ";
        for (int p:v[n].parents) {
            bridge.push_back(p);
        }
        for (int p:v[n].children) {
            bridge.push_back(p);
        }
        for (int p:bridge)
            cout << p;
        cout << endl << "-------" << endl;

        for (int a:bridge) {
            if (is_connected(bridge))
        }
    }

    // 掃描一遍，若有node n的連結，則將parent與child的次數減一，若原本有，之後變成0，則視為斷掉。
    // for (it=v.begin(); it!=v.end(); it++) {
    //     p_count = it->parentsCount();
    //     c_count = it->childrenCount();

    //     for (i=0; i<it->parents.size(); i++) {
    //         if (it->parents[i] == n)
    //             p_count--;
    //     }
    //     for (i=0; i<it->children.size(); i++) {
    //         if (it->children[i] == n)
    //             c_count--;
    //     }

    //     //若原本有，之後變成沒有 => 表示與n有連接??
    //     // if (it->parentsCount() && !p_count) {   // 移除是現在檢查的parent
    //     //     // 若移出的點(n)還有child
    //     //     if ((v[n].childrenCount()-1) || v[n].parentsCount())

    //     // }
    //     if (((it->parentsCount() && !p_count) && ((v[n].childrenCount()-1) || v[n].parentsCount())) ||
    //      ((it->childrenCount() && !c_count) && (v[n].childrenCount() || (v[n].parentsCount()-1))))
    //         return false;
    // }
    return true;
}

int main()
{
    vector<Node> list(0);
    int p, c;
    bool is_biconnected_graph=true;
    vector<int> break_node(0);
    vector<int> node_list(0);
    int count=0;

    for (int i=0; i<100; i++) {
        list.push_back(Node(i));
    }

    while (!cin.eof()) {    // Windows: Ctrl+Z to stop input, Linux: Ctrl+D
        p = -1;
        cin >> p >> c;

        if (p != -1) {
            count++;
            list[p].addChild(c);
            list[c].addParent(p);
        }
    }

    for (vector<Node>::iterator it=list.begin(); it!=list.end(); it++) {
        if (!is_Biconnected(list, it->index())) {
            is_biconnected_graph = false;
            break_node.push_back(it->index());
        }

        // if (it->parentsCount() && (it->childrenCount() > 1)) {
        //     break_node.push_back(it->index());
        // }
        // Debug
        // if (it->parentsCount()) {
        //     cout << "Node " << it->index() << " has " << it->parentsCount() << " parents.";
        // }
        // if (it->childrenCount()) {
        //     cout << "  --  Node " << it->index() << " has " << it->childrenCount() << " children.";
        // }
        // if (it->parentsCount() || it->childrenCount())
        //     cout << endl;
    }

    if (is_biconnected_graph) {
        cout << "true"; // << endl;
    } else {
        cout << "false" << endl;
        for (vector<int>::iterator it=break_node.begin(); it!=break_node.end(); it++) {
            if (it != break_node.end())
                cout << *it << " ";
            else
                cout << *it;
        }
        // No need endl??
        // cout << endl;
    }

    return 0;
}