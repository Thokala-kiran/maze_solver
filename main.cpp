#include <bits/stdc++.h>

using namespace std;

struct Coordinate {
    int x, y;
    Coordinate(int a, int b) : x(a), y(b) {}
};

vector<pair<int, int>> neighbour(int k, int j, vector<vector<int>>& matrix) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    vector<pair<int, int>> neighbourvector;

    for (int i = 0; i < 4; i++) {
        int newdimx = k + dx[i];
        int newdimy = j + dy[i];
        
        if (newdimx >= 0 && newdimx < matrix.size() && newdimy >= 0 && newdimy < matrix[0].size()) {
            if (matrix[newdimx][newdimy] == 0) {
                neighbourvector.push_back(make_pair(newdimx, newdimy));
            }
        }
    }

    return neighbourvector;
}

void BFS(vector<vector<int>>& maze, int m, int n, vector<vector<int>>& level, vector<vector<Coordinate>>& parent) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    queue<Coordinate> q;

    visited[0][2] = true;
    level[0][2] = 0;

    parent[0][2].x=0;

    parent[0][2].y=0;
    q.push(Coordinate(0, 2));

    while (!q.empty()) {
        Coordinate curr = q.front();
        q.pop();
        int s = curr.x;
        int t = curr.y;

        vector<pair<int, int>> path = neighbour(s, t, maze);
        for (const auto& p : path) {
            int a = p.first;
            int b = p.second;
            
            if (!visited[a][b]) {
                visited[a][b] = true;
                level[a][b] = level[s][t] + 1;
                parent[a][b] = Coordinate(s, t);
                q.push(Coordinate(a, b));
            }
        }
    }
}

int main() {
    int rows = 5;
    int columns = 5;
    vector<vector<int>> maze(rows, vector<int>(columns));

    maze = {
        {1, 1, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1}
    };

    vector<vector<int>> level(rows, vector<int>(columns, -1));
    vector<vector<Coordinate>> parent(rows, vector<Coordinate>(columns, Coordinate(-1, -1)));

    BFS(maze, rows, columns, level, parent);

    // Print parent matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << "(" << parent[i][j].x << "," << parent[i][j].y << ") ";

        }
        cout << endl;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << level[i][j] << " ";
        }
        cout << endl;
    }
    

    return 0;
}