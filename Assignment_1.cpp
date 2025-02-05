#include <bits/stdc++.h>

using namespace std;


void printPuzzle(const vector<int>& puzzle) {
    for (int i = 0; i < 9; ++i) {
        cout << puzzle[i] << " ";
        if ((i + 1) % 3 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}



int findBlank(const vector<int>& puzzle) {
    for (int i = 0; i < 9; ++i) {
        if (puzzle[i] == 0) {
            return i;
        }
    }
    return -1; // Should not happen
}


vector<vector<int>> generateMoves(const vector<int>& puzzle) {
    vector<vector<int>> moves;
    int blankPos = findBlank(puzzle);
    int row = blankPos / 3;
    int col = blankPos % 3;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];

        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            vector<int> newPuzzle = puzzle;
            swap(newPuzzle[blankPos], newPuzzle[newRow * 3 + newCol]);
            moves.push_back(newPuzzle);
        }
    }
    return moves;
}


bool isGoal(const vector<int>& puzzle) {
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    return puzzle == goal;
}


bool dfs(vector<int> start, vector<int> goal, int maxDepth) {
    unordered_map<string, bool> visited; // Keep track of visited states
    vector<vector<int>> path;

    function<bool(vector<int>, int)> recursiveDfs = 
        [&](vector<int> current, int depth) {

        string stateStr;
        for (int x : current) stateStr += to_string(x);
        
        if (visited.count(stateStr)) return false; // Already visited
        visited[stateStr] = true;

        path.push_back(current);

        if (current == goal) {
            cout << "Goal reached!\n";
            for (const auto& p : path) {
                printPuzzle(p);
            }
            return true;
        }

        if (depth >= maxDepth) {
            path.pop_back(); // Backtrack
            return false;
        }

        vector<vector<int>> moves = generateMoves(current);
        for (const auto& move : moves) {
            if (recursiveDfs(move, depth + 1)) {
                return true;
            }
        }

        path.pop_back(); // Backtrack
        return false;
    };

    return recursiveDfs(start, 0);
}


int main() {
    vector<int> start = {1, 2, 3, 4, 0, 5, 7, 8, 6};  // Example start state.  0 is the blank.
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};  // Goal state
    int maxDepth = 25; // Set a maximum depth to prevent infinite search

    if (!dfs(start, goal, maxDepth)) {
        cout << "No solution found within the maximum depth.\n";
    }

    return 0;
}