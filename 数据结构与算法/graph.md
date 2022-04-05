# 图
## 图的分类
1. 无向图
2. 有向图
3. 网
## 图的存储结构
### 邻接矩阵 无向图/有向图/网
用一维数组存储节点信息，用二维数组存储边的信息  
适用边数相较节点数较多的情况
### 邻接表 无向图/有向图/网
用一维数组存储节点信息，用单链表存储结点的邻接点（出度）信息  
适用边数相较节点数较少的情况  
对节点操作方便，但对边操作不方便
### 十字链表 有向图
用一维数组存储节点信息，用两个单链表存储节点的邻接点（入度和出度）信息
### 临界多重表

### 边集数组
由两个一维数组构成，一个存储顶点信息，一个存储边的信息  
适合对边依次进行处理
## 图的遍历
### 深度优先
### 广度优先
## 最小生成树
### Prim 算法
### 
## 最短路径算法
## 拓扑排序
## 关键路径

## leetcode
[841. 钥匙和房间](https://leetcode-cn.com/problems/keys-and-rooms/)  
dfs
```cpp
void dfs(vector<vector<int>>& rooms, vector<int>& visited, int i) {
    visited[i] = 1;
    for (int j = 0; j < rooms[i].size(); j++) {
        if (visited[rooms[i][j]] == 0) {// 没有被访问 {
            dfs(rooms, visited, rooms[i][j]);
        }
    }
}
bool canVisitAllRooms(vector<vector<int>>& rooms) {
    vector<int> visited(rooms.size(), 0); // 记录每个房间是否被访问过
    visited[0] = 1;
    for (int i = 0; i < rooms[0].size(); i++) {
        if (visited[rooms[0][i]] == 0) {// 没有被访问 {
            dfs(rooms, visited, rooms[0][i]);
        }
    }
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == 0) {
            return false;
        }
    }
    return true;
}
```
bfs
```cpp
bool canVisitAllRooms(vector<vector<int>>& rooms) {
    vector<int> visited(rooms.size(), 0); // 记录每个房间是否被访问过
    queue<int> que;
    que.push(0);
    
    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            int index = que.front(); // 待访问
            visited[index] = 1;
            for (int j = 0; j < rooms[index].size(); j++) {
                if (visited[rooms[index][j]] == 0) {
                    que.push(rooms[index][j]);
                }
            }
            que.pop();
        }
    }
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == 0) {
            return false;
        }
    }
    return true;
}
```

[剑指 Offer 12. 矩阵中的路径](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof/)  
dfs
```cpp
bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int k) {
    if (i < 0 || i >= board.size() || j < 0 || j >= board[i].size() || board[i][j] != word[k]) return false;
    if (k == word.size() - 1) return true;
    board[i][j] = '\0';
    bool res = dfs(board, word, i, j - 1, k + 1) || dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i - 1, j, k + 1) || dfs(board, word, i + 1, j, k + 1);
    board[i][j] = word[k];
    return res;
}
bool exist(vector<vector<char>>& board, string word) {
    int m = board.size();
    int n = board[0].size();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0]) {
                if (dfs(board, word, i, j, 0)) return true;
            }
        }
    }

    return false;
}
```

## 模拟
[463. 岛屿的周长](https://leetcode-cn.com/problems/island-perimeter/)  

只需比较每个岛屿的左边和上边是不是岛屿
```cpp
int islandPerimeter(vector<vector<int>>& grid) {
    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j]) {
                int left = (i - 1 < 0 ? 0 : grid[i - 1][j]);
                int top = (j - 1 < 0 ? 0 : grid[i][j - 1]);
                count += 4 - 2 * (left + top);
            }
        }
    } 
    return count;
}
```