#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <stack>
#include <string>
#include <tuple>

class Maze {
public:
    Maze(const std::string& filename) {
        loadFromFile(filename);
    }
    void print(const std::vector<std::tuple<int, int>>& path = {}) const {
        std::set<std::tuple<int, int>> pathSet;
        for (auto [r,c] : path) {
            pathSet.insert({r,c});
        }
        for (int r = 0; r < (int)grid.size(); ++r) {
            for(int c = 0; c < (int)grid[r].size(); ++c) {
                if(grid[r][c] == 1) {
                    std::cout << "1";
                } else if (pathSet.count({r,c})) {
                    std::cout << " ";
                } else {
                    std::cout << "0";
                }
            }
            std::cout << '\n';
        }
    }


    std::tuple<int, int> findStart() const {
        if(grid.empty() || grid[0].empty()) {
            return {-1,-1};
        }
        const int rows = static_cast<int>(grid.size());
        const int cols = static_cast<int>(grid[0].size());

        for (int j = 0; j < cols; ++j) {
            if (grid[0][j] == 0) {
                return {0,j};
            }
            if (grid[rows - 1][j] == 0) {
                return {rows - 1, j};
            }
        }
        for (int i = 1; i < rows - 1; ++i) {
            if (grid[i][0] == 0) {
                return {i,0};
            }
            if (grid[i][cols - 1] == 0) {
                return {i,cols - 1};
            }
        }
        return {-1,-1};

    }

    bool isOpen(int row, int col) const {
        int R = static_cast<int>(grid.size());
        int C = static_cast<int>(grid[0].size());
        return (row >= 0 && row < R && col >= 0 && col < C && grid[row][col] == 0);
    }

    bool isBoundary(int row, int col) const {
        int R = static_cast<int>(grid.size());
        int C = static_cast<int>(grid[0].size());
        return (row == 0 || row == R - 1 || col == 0 || col == C - 1);
    }

    std::vector<std::tuple<int, int>> findPath() const {
        auto [startingRow, startingCol] = findStart();
        if (startingRow == -1 || startingCol == -1) {
            return {};
        }
        const int R = static_cast<int>(grid.size());
        const int C = static_cast<int>(grid[0].size());
        std::vector<std::vector<bool>> explored(R, std::vector<bool>(C, false));

        std::stack<std::tuple<int, int>> stack;
        stack.push({startingRow, startingCol});
        explored[startingRow][startingCol] = true;

        const int moveRow[4] = {1,-1,0,0};
        const int moveCol[4] = {0,0,1,-1};

        while (!stack.empty()) {
            auto [currentRow, currentCol] = stack.top();

            if(isBoundary(currentRow, currentCol) && !(currentRow == startingRow && currentCol == startingCol)) {
                std::vector<std::tuple<int, int>> reversed;
                while(!stack.empty()) {
                    reversed.push_back(stack.top());
                    stack.pop();
                }
                std::vector<std::tuple<int, int>> path(reversed.rbegin(), reversed.rend());
                return path;
            }
            bool moved = false;
            for(int k = 0; k < 4; ++k) {
                int nextRow = currentRow + moveRow[k];
                int nextCol = currentCol + moveCol[k];
                if(isOpen(nextRow, nextCol) && !explored[nextRow][nextCol]) {
                    explored[nextRow][nextCol] = true;
                    stack.push({nextRow, nextCol});
                    moved = true;
                    break;
                }
            }
            if(!moved) {
                stack.pop();
            }
        }
        return {};
    }

    bool empty() const {
        return grid.empty() || grid[0].empty();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream input(filename);
        if (!input.is_open()) {
            std::cerr << "Failed to open file " << filename << std::endl;
            return;
        }

        std::string line;
        while(std::getline(input,line)) {
            std::vector<int> row;
            for (char c : line) {
                if (c == '0' || c == '1') {
                    row.push_back(c -'0');
                }
            }
            if(!row.empty()) {
                grid.push_back(row);
            }
        }
    }

private:
    std::vector<std::vector<int>> grid;


};



int main(int argc, char* argv[]) {
    std::string fileName;

    if (argc >= 2) {
        fileName = argv[1];
    }
    else {
        std::cout << "Enter a maze file name: ";
        std::cin >> fileName;
    }

    Maze maze(fileName);

    if(maze.empty()) {
        std::cout << "There is no maze!\n";
        return 1;
    }

    auto path = maze.findPath();

    if(path.empty()) {
        maze.print();
        std::cout << "No path found\n";
    } else {
        maze.print(path);
        for (auto [r, c] : path) std::cout << "(" << r << "," << c << ") ";
        std::cout << "\n";
    }
    return 0;
}


