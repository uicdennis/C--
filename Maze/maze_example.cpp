#include <iostream>
#include <stack>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>

// 設定 TEST 為 1 啟動自動測試
// 此時須設定測試迷宮的大小，也就是 ROWS 及 COLS
// TEST_LOOP 則是設定每次測試幾個迷宮
#define TEST		1
#if TEST
    #define ROWS        6
    #define COLS        6
    #define TEST_LOOP   1
#else   // No TEST, force one shot
    #define TEST_LOOP   1
#endif

#define ROAD            0
#define WALL            1

using namespace std;

// 定義迷宮中的一個位置
struct Position {
    int row, col, dir;
    Position(int r, int c, int d=0) : row(r), col(c), dir(d) {}
};

typedef struct{
	int vert;
	int horiz;
}offsets;
offsets _move[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// 函數：深度優先搜索找尋迷宮的通路
bool findPath(vector<vector<int> >& maze, int startRow, int startCol, int exitRow, int exitCol) {
    int numRows = maze.size();
    int numCols = maze[0].size();
    bool found = false;
    
    stack<Position> s;
    vector<Position> path;
    s.push(Position(startRow, startCol));  // 從起點開始搜索
    vector<vector<int> > visited(numRows, vector<int>(numCols, 0));  // 創建一個狀態矩陣來記錄訪問狀態
    visited[startRow][startCol] = 1;

    path.push_back(Position(startRow, startCol));
    path.push_back(Position(startRow, startCol));

    while (!s.empty() && !found) {
        Position cur = s.top();
        s.pop();
        path.pop_back();

        int curRow = cur.row;
        int curCol = cur.col;
        int i=cur.dir;

#if TEST
        cout << "  ##  Current ==  " << "r = " << curRow << " c = " << curCol << " d = " << i << endl;	
#endif

        int newRow = curRow;
        int newCol = curCol;

        while ((i < 4) && !found) {
            newRow = curRow + _move[i].vert;
            newCol = curCol + _move[i].horiz;

			if ((newRow < 0) || (newCol < 0) || (newRow == numRows) || (newCol == numCols)) {
			    i++;
			    continue;
			}

#if TEST
            //cout << "    --> r = " << newRow << " c = " << newCol << " d = " << i << endl;	//
#endif
            if (newRow == (exitRow) &&
                newCol == (exitCol)) {
                found = true;
                path.push_back(Position(newRow, newCol));
			} else if (!maze[newRow][newCol] && !visited[newRow][newCol]) {
                // 可以移動到新位置
                s.push(Position(curRow, curCol));
#if TEST
				cout << "  --> Push " << newRow << "," << newCol << endl;
#endif
                visited[newRow][newCol] = 1;  // 標記為已訪問過
                path.push_back(Position(newRow, newCol));
                curRow = newRow;
                curCol = newCol;
                i = 0;
            } else {
                i++;
			}
        }

        if (i == 4) {
            // 如果無法前進，則退回上一步
            visited[curRow][curCol] = 2;  // 標記為已訪問過但無通路
        }
    }
    
    if (found) {
        // 找到出口，輸出通路
        cout << "Path Found:" << endl;
        cout << "  ----> s size = " << s.size() << endl;
        cout << "  ----> path size = " << path.size() << endl;
        
        vector<Position>::iterator it;
        
        for (it=path.begin(); it!=path.end();) {
        	cout << "(" << it->row << ", " << it->col << ")";
        	if (++it != path.end())
            	cout << " -> ";
		}
		cout << endl;
        //cout << "(" << exitRow << ", " << exitCol << ")" << endl;
        return true;
    }

    cout << "No Path Found." << endl;
    return false;
}

// 顯示迷宮長相
void show_maze(vector<vector<int> > m)
{
	vector<vector<int> >::iterator it_i;
	vector<int>::iterator it_j;
	for (it_i=m.begin(); it_i!=m.end(); it_i++) {
		for (it_j=it_i->begin(); it_j!=it_i->end(); it_j++) {
			cout << *it_j;
		}
		cout << endl;
	}
}

// 設定迷宮路徑
int f()
{
    int n = rand() & 0x03;  // 路徑:牆壁 <=> 3:1

    if (n)
        return ROAD;   // 路徑
    else
        return WALL;   // 牆壁
}

// 產生隨機迷宮
void random_maze(vector<vector<int> >& m, int rows, int cols)
{
    vector<int> test(rows*cols);
 
    generate(test.begin(), test.end(), f);
    int k=0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m[i][j] = test[k++];
        }
    }
    m[0][0] = 0;
    m[rows-1][cols-1] = 0;
}

int main()
{
    int numRows=ROWS, numCols=COLS;
    
#if !TEST	
    cout << "Enter the number of rows in the maze: ";
    cin >> numRows;
    cout << "Enter the number of columns in the maze: ";
    cin >> numCols;
#endif
	
    vector<vector<int> > maze(numRows, vector<int>(numCols, 0)); // 初始化為0，表示通路

#if !TEST	
    cout << "Enter the maze data (0 for path, 1 for obstacle):" << endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cin >> maze[i][j];
        }
    }
#endif
    
#if TEST
    srand(time(0));
#endif

    for (int l=0; l<TEST_LOOP; l++) {
#if TEST
        cout << "===================================================" << endl;
        cout << l << ". " << endl;
        random_maze(maze, numRows, numCols);
        show_maze(maze);	//
#endif

        int startRow=0, startCol=0, exitRow=numRows-1, exitCol=numCols-1;
#if !TEST	
    cout << "Enter the starting row and column: ";
    cin >> startRow >> startCol;
    cout << "Enter the exit row and column: ";
    cin >> exitRow >> exitCol;
#endif

        if (findPath(maze, startRow, startCol, exitRow, exitCol)) {
            cout << "Path Found!" << endl;
        } else {
            cout << "No Path Found." << endl;
        }
    }

    return 0;
}
