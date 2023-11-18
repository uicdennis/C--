#include <iostream>
#include <stack>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

void test(string sA, string sB);
string post_to_in(string sA);
string in_to_post(string sA, bool reversed);

// 1. 字串與字元操作
void test(string sA, string sB)
{
    // 依序顯示字元
    for (int i=0; i < sA.size(); i++) {
        cout << sA[i];
    }
    
    cout << endl;
    cout << sB << endl;

    return;
}

// 2.字串與堆疊配合
void show_w_stack(string sA, string sB)
{
    // vector<char> vA;
    stack<char> stackA;
    int i;

    // 需要先指定vector大小，也就是sA的長度
    // vA.assign(sA.length(), '\0');
    // 拷貝字串至vetor
    // copy(sA.begin(), sA.end(), vA.begin());

    // 反向取用，並且將之退出堆疊
    // for (; !vA.empty(); vA.pop_back()) {
    //     c = vA.back();
    //     cout << c;
    // }

    vector<char>::iterator it;
    char c;

    for (i=0; i<sA.length(); i++) {
        stackA.push(sA[i]);
    }

    // 從堆疊取用，並且將之退出堆疊
    while (!stackA.empty()) {
        cout << stackA.top();
        stackA.pop();
    }

    cout << endl;
    cout << sB << endl;
}

// 3. 加入優先權
// 3.1 設定優先權table
// 3.2 運算員直接輸出
// 3.3 遇到堆疊裡的運算子優先權若較低，則將堆疊裡所有運算子輸出??
// 3.4 若字串已無需要處理，則輸出所有堆疊裡的東西
// 3.5 若考慮括號，則左括號進堆疊，又括號則pop堆疊至左括號，括號不輸出。
typedef struct tagOpPriority
{
    char op;
    int  prior;
} op_prior_t;

#define NUM_OP          6
op_prior_t op_table[NUM_OP] = {{'(', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}, {')', 1}};

int get_op_priority(char op)
{
    for (int i=0; i<NUM_OP; i++) {
        if (op == op_table[i].op) {
            return op_table[i].prior;
        }
    }

    return -1;  // no match
}

// 中序轉前序
string in_to_prefix(string sA)
{
    string s;

    // 反轉中序字串，然後再進行中序轉後序，然後再反轉輸出。
    reverse(sA.begin(), sA.end());
    s = in_to_post(sA, true);
    reverse(s.begin(), s.end());
    return s;
}

// 輸入後序sA, 回傳中序字串
string post_to_in(string sA)
{
    int i;
    stack<string> stackIn;
    string sInfix;
    string op1, op2, new_op;
    int prior=-1;

    // 需要取得兩個運算元後，結合運算子成一個新的運算元
    // stack須以string (運算元)作單位
    // 遇到運算子，輸出op2與op1與運算子成為新運算元再推入堆疊
    // 後序無括號
    for (i=0; i<sA.length(); i++) {
        switch (sA[i]) {
        case '+':   // 要比堆疊裡的運算子的優先權高(相等不行)，才能直接推入，
        case '-':
        case '*':
        case '/':
            if (!stackIn.empty()) {
                op2 = stackIn.top();
                stackIn.pop();
                op1 = stackIn.top();
                stackIn.pop();
                new_op = "(" + op1 + string(1, sA[i]) + op2 + ")";
                stackIn.push(new_op);
            }
            break;
        default:
            stackIn.push(string(1,sA[i]));
            break;
        }
    }

    sInfix = stackIn.top();
    stackIn.pop();

    cout << sInfix << endl;

    return sInfix;
}

string in_to_post(string sA, bool reversed=false)
{
    int i;
    stack<char> stackOp;
    string sPostfix;
    char op, c;
    int prior=-1;

    for (i=0; i<sA.length(); i++) {
        if (reversed) {
            if ((sA[i] == '('))
                sA[i] = ')';
            else if ((sA[i] == ')'))
                sA[i] = '(';
        }
        switch (sA[i]) {
        case '(':   // 無條件推入堆疊
            stackOp.push(sA[i]);
            break;
        case ')':   // pop to '('
            while (((c = stackOp.top()) != '(') && !stackOp.empty()) {
                sPostfix.append(string(1,c));
                stackOp.pop();
            }
            if (c == '(') stackOp.pop();
            break;
        case '+':   // 要比堆疊裡的運算子的優先權高(相等不行)，才能直接推入，
        case '-':
        case '*':
        case '/':
            while (!stackOp.empty()) {
                prior = get_op_priority(stackOp.top());
                if (prior != -1) {
                    if (get_op_priority(sA[i]) > prior) {
                        break;
                    } else {
                        sPostfix.append(string(1, stackOp.top()));
                        stackOp.pop();
                    }
                }
            }
            stackOp.push(sA[i]);
            break;
        default:
            sPostfix.append(string(1,sA[i]));
            break;
        }
    }

    while (!stackOp.empty()) {
        sPostfix.append(string(1, stackOp.top()));
        stackOp.pop();
    }

    // cout << sPostfix << endl;

    return sPostfix;
}

int main()
{
    string szA("a+b*d-c/d");
    // string szA("A+B*C");
    // string szA("(a+b)*(c+d)");
    string szB("abd*+cd/-");

    // show_w_stack(szA, szB);
    // cout << in_to_prefix(szA);

    string a("ab+");
    string b("+c*d");

    // cout << post_to_in(a) + b;
    cout << in_to_prefix(post_to_in(a) + b);

    return 0;
}