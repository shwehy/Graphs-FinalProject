# DataFinalProject

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//We use DFS algorithm to check visited cells and backtracking it to geth the possible path
void DFS(int row, int col, vector<vector<char>> &maze, vector<pair<int, int>> &path, vector<vector<pair<int, int>>> &result) {


    path.push_back(make_pair(row, col)); //push rowNum and colNum to the path

    if (maze[row][col] == 'e') {
        result.push_back(path);  //If I reached the end push the result into the result vector
    }
    else {
        int directions[][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}}; //2D array of all 4 possible directions we can move

        for (int* d : directions) {
            int r = d[0] + row;
            int c = d[1] + col;

            //check whether any of the directions is allowed or not
            if (r >= 0 && c >= 0 && r < maze.size() && c < maze[r].size() && maze[r][c] != '0') {
                maze[row][col] = '0';
                DFS(r, c, maze, path, result);
                maze[row][col] = '1';
            }

        }
    }

    path.pop_back();
}


vector<vector<pair<int, int>>> getPaths(vector<vector<char>> maze) {
    vector<vector<pair<int, int>>> result;
    vector<pair<int, int>> path;
    //initialize start point at (0,0)
    int row = 0;
    int col = 0;
    DFS(row, col, maze, path, result);
    return result;
}

int main() {
    string matrix;
    cout << "Enter the matrix elements: \n";
    getline(cin, matrix);
    vector<vector<char>> maze;
    vector<char> row;
    
    //when the user enters space the program defines a new row and convert the string into 2d vector
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i] == ' ') {
            maze.push_back(row);
            row.clear();
        }
        else {
            row.push_back(matrix[i]);
        }
    }
    cout << "Possible Paths are: \n";

    maze.push_back(row);

    for (auto &path : getPaths(maze)) {
        cout << endl << '[';

        for (auto &cell : path) {
            cout << '(' << cell.first <<
                 "," << cell.second << ')';
        }

        cout << ']' << endl;
    }
}
