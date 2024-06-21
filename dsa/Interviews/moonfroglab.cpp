// #include<bits/stdc++.h>
// using namespace std;

// bool isValidIP(string s) {
//     string substr = "";
//     int countOfPeriod = 0;
//     for(int i=0; i < s.size(); i++) {
//         if(s[i] == '.') {
//             countOfPeriod++;
//             if(countOfPeriod > 3) return false;
//             if (!checkSubstrValidity(substr)) {
//                 return false;
//             }
//             substr = "";
//         }
//         else {
//             substr += s[i];
//         }

//     }
//     // substr = ""

//     if(checkSubstrValidity(substr)) return true;
//     return false;


// }

// bool checkSubstrValidity(string s) {
//     if(s == "") return false;
//     string substr;
//     for(int i=0; i < s.size(); i++) {
//         if(int(s[i]) - int('0') >= 9) {
//            substr += s[i];

//         } else {
//             return false;
//         }
//     }

//     int d = stoi(substr);
//     string temp =
//     if(d >= 0 && d <= 255) return true;
//     return false;
// }

// int main() {
//     string s1 = "Hello how are";
//     string s2 = "10.1.1.1";
//     string s3 = "++.--.00.12"
//     string s4 = "12.13.0.256";
//     string s5 = "12.13. .256";
//     string s6 = "1.1.1.1."
//     string s7 = "1.1.1.1.1"
//     string s8 = "1.01.1.1.1"



//     string s5 = "";


//     cout << isValidIP(s1) << endl;
//     cout << isValidIP(s2) << endl;
// }


// #include<bits/stdc++.h>
// using namespace std;

// void dfs(vector<vector<string>> &grid, int x, int y, map<pair<int, int>, bool> &visited) {
//     int m = grid.size();
//     int n = grid[0].size();

//     if(x < 0 || x == m || y < 0 || y == n) return;
//     if(visited[{x,y}]) return;
//     if(grid[x][y] == "0") return;
//     visited[{x,y}] = true;
//     dfs(grid, x+1, y, visited);
//     dfs(grid, x, y+1, visited);
// }



// int maxIslands(vector<vector<string>> &grid) {
//     int m = grid.size();
//     if(m == 0) return 0;
//     int n = grid[0].size();

//     map<pair<int, int>, bool> visited;
//     int countOfIsland = 0;
//     for(int i=0; i < m; i++) {
//         for(int j = 0; j < n; j++) {
//             if(grid[i][j] == "1" && !visited[{i,j}]) {
//                 dfs(grid, i, j, visited);
//                 countOfIsland++;
//             }
//         }
//     }
//     return countOfIsland;
// }



// int main() {
//     vector<vector<string>> grid = {
//         {"1", "1", "1", "0", "0"},
//         {"1", "1", "0", "0", "0"},
//         {"0","0","1","1","0"},
//         {"0","0","1","1","1"},
//         };
//     cout << maxIslands(grid);
//     return 0;
// }


#include<bits/stdc++.h>
using namespace std;
int maxIslandAfterFlip = 0;
// void dfs(vector<vector<string>> &grid, int x, int y, map<pair<int, int>, bool> &visited) {
//     int m = grid.size();
//     int n = grid[0].size();

//     if(x < 0 || x == m || y < 0 || y == n) return;
//     if(visited[{x,y}]) return;
//     if(grid[x][y] == "0") return;
//     visited[{x,y}] = true;
//     dfs(grid, x+1, y, visited);
//     dfs(grid, x, y+1, visited);
// }



void dfs_oneFlip(vector<vector<string>> &grid, int x, int y, map<pair<int, int>, bool> &visited, bool isLastFlipped, int totalIslandSize) {
    int m = grid.size();
    int n = grid[0].size();

    if(x < 0 || x == m || y < 0 || y == n) return;
    if(visited[{x,y}]) return;
    visited[{x,y}] = true;
    if(grid[x][y] == "0") {
        if(isLastFlipped) return;

        dfs_oneFlip(grid, x+1, y, visited, true, totalIslandSize+1);
        dfs_oneFlip(grid, x, y+1, visited, true, totalIslandSize+1);
        visited[{x,y}] = false;

    } else {
        dfs_oneFlip(grid, x+1, y, visited, false, totalIslandSize+1);
        dfs_oneFlip(grid, x, y+1, visited, false, totalIslandSize+1);
    }


    maxIslandAfterFlip = max(maxIslandAfterFlip, totalIslandSize);
}

int maxIslands(vector<vector<string>> &grid) {
    int m = grid.size();
    if(m == 0) return 0;
    int n = grid[0].size();

    map<pair<int, int>, bool> visited;
    int countOfIsland = 0;
    for(int i=0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == "1" && !visited[{i,j}]) {
                int curSize = 0;
                dfs_oneFlip(grid, i, j, visited, false, curSize);
                countOfIsland++;
            }
        }
    }
    return countOfIsland;
}



int main() {
    vector<vector<string>> grid = {
        {"1", "1", "0", "0", "0"},
        {"1", "1", "1", "0", "0"},
        {"0", "0", "1", "0", "0"},
        {"0", "0", "1", "1", "1"},
        };
    cout << maxIslands(grid);
    cout << " " << maxIslandAfterFlip << endl;
    return 0;
}


