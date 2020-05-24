// 为啥有人想做这题？？？

static const char EMPTY = '.';
static const char WALL  = '#';
static const char START = '@';
static const int  MAX_KEYS = 6;
static const char MIN_KEY = 'a';
static const char MAX_KEY = MIN_KEY + MAX_KEYS;
static const char MIN_LOCK = 'A';
static const char MAX_LOCK = MIN_LOCK + MAX_KEYS;
static const vector<pair<int, int>> DIRECTION_OFFSETS = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};

class Solution {
public:
    struct GridInfo {
        int m_numKeys = 0, m_startRow, m_startCol;
    };
    
    struct State {
        int m_row, m_col;
        int m_inventory; 
        int m_levelStatistic = 0;
        
        void addKey(char key) {
            m_inventory = (1 << (key - 'a')) | m_inventory;
        }

        bool hasKeyForLock(char lock) {
            char neededKey = 'a' + (lock - 'A');
            return (1 << (neededKey - 'a')) & m_inventory;
        }
    };

    int shortestPathAllKeys(vector<string>& p_grid) {
        auto lambda_hashCombine = [](int p_a, int p_b) -> size_t {
            static hash<int> hasher;
            size_t bHash = hasher(p_b);
            return hasher(p_a) + 0x9e3779b9 + (bHash << 6) + (bHash >> 2);
        };
        
        auto lambda_hashState = [lambda_hashCombine](const State &p_state) -> size_t {
            return lambda_hashCombine(p_state.m_row, lambda_hashCombine(p_state.m_col, p_state.m_inventory));
        };
        
        auto lambda_equalState = [](const State &p_a, const State &p_b) -> bool {
            return p_a.m_row == p_b.m_row && p_a.m_col == p_b.m_col && p_a.m_inventory == p_b.m_inventory;
        };
        
        auto lambda_computeGridInfo = [](const vector<string>& p_grid) -> GridInfo {
            GridInfo info;
            for (int row = 0; row < p_grid.size(); row++) {
                for (int col = 0; col < p_grid[0].size(); col++) {
                    char cell = p_grid[row][col];
                    if (cell == START) {
                        info.m_startRow = row;
                        info.m_startCol = col;
                    }
                    else if (cell >= MIN_KEY && cell <= MAX_KEY) {
                        info.m_numKeys++;
                    }
                }
            }
            return info;
        };
        
        auto lambda_computeFinalStateInvetory = [](int numKeysFoundInGrid) {
            int result = 0;
            for (int i = 0; i < numKeysFoundInGrid; i++) {
                result = result | (1 << i);
            }
            return result;
        };

        auto lambda_isFinal = [](const State &p_state, int finalStateInvetory) -> bool {
            return p_state.m_inventory == finalStateInvetory;
        };
        
        auto lambda_computeNeighbors = [](const vector<string> &p_grid, const State &p_state) -> vector<State> {
            vector<State> result;
            
            for (const pair<int, int> &directionOffset: DIRECTION_OFFSETS) {
                int newRow = p_state.m_row + directionOffset.first;
                int newCol = p_state.m_col + directionOffset.second;
                
                // Out of bounds - ignore
                if (newRow < 0 || newRow >= p_grid.size() || newCol < 0 || newCol >= p_grid[0].size()) continue;
                
                State newState {newRow, newCol, p_state.m_inventory, p_state.m_levelStatistic + 1};
                char cell = p_grid[newRow][newCol];
                
                if (cell == START ||
                    cell == EMPTY ||
                    (cell >= MIN_LOCK && cell <= MAX_LOCK && newState.hasKeyForLock(cell)))
                {
                    result.push_back(newState);
                }
                else if (cell >= MIN_KEY && cell <= MAX_KEY) {
                    newState.addKey(cell);
                    result.push_back(newState);
                }
            }
            return result;
        };
        
        GridInfo info = lambda_computeGridInfo(p_grid);
        int finalStateInventory = lambda_computeFinalStateInvetory(info.m_numKeys);
        
        State startingState = State{info.m_startRow, info.m_startCol, 0, 0};
        unordered_set<State, decltype(lambda_hashState), decltype(lambda_equalState)> visited {1, lambda_hashState, lambda_equalState};
        
        visited.insert(startingState);
        deque<State> toBeProcessed = {startingState};
        
        
        while (!toBeProcessed.empty()) {
            State current = toBeProcessed.front(); toBeProcessed.pop_front();
            if (lambda_isFinal(current, finalStateInventory)) return current.m_levelStatistic;
            
            for (const State &neighbor: lambda_computeNeighbors(p_grid, current)) {
                if (visited.find(neighbor) == visited.end()) {
                    toBeProcessed.push_back(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
        
        return -1;
    }
};
