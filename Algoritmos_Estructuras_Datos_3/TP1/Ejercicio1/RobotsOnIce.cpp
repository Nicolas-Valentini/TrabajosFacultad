#include <iostream>
using namespace std;

pair<int, int> moves[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class RobotsOnIce {
    private:
        int m, n;
        int cells;
        int solved = 1;
        int acessible_cells;
        int quarters[4];
        int M[8][8];
        bool visited[8][8];
        pair<int, int> checkpoints[4];
        int solve_aux(int x, int y, int s);
        int count_islands(int s);
        void fill_island(int x, int y);
    public:
        int read_input();
        void solve();
};

int RobotsOnIce::read_input() {
    cin >> m >> n;
    if (m == n && m == 0){
        return 1;
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            M[i][j] = 0;
            visited[i][j] = false;
        }
    }
    cells = m * n;
    // read checkpoints
    int x, y, step;
    for (int i = 0; i < 3; i++) {
        cin >> x >> y;
        checkpoints[i] = {x, y};
        step = (i+1) * cells / 4;
        quarters[i] = step;
        M[x][y] = step;
    }
    checkpoints[3] = {0, 1};
    quarters[3] = cells;
    M[0][1] = cells;
    M[0][0] = 1;
    return 0;
}

void RobotsOnIce::solve() {
    cout << "Case " << solved << ": " << solve_aux(0, 0, 1) << endl;
    solved++;
}

void RobotsOnIce::fill_island(int x, int y){
    visited[x][y] = true;
    for (int i = 0; i < 4; i++){
        int new_x = x + moves[i].first;
        int new_y = y + moves[i].second;
        if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n && !visited[new_x][new_y]){
            fill_island(new_x, new_y);
        }
    }
}

int RobotsOnIce::count_islands(int s){
    int res = 0;
    // initialize visited matrix
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            visited[i][j] = (M[i][j] != 0);
        }
    }
    for (int i = 0; i < 4; i++){
        if (s < quarters[i]){
            visited[checkpoints[i].first][checkpoints[i].second] = false;
        }
    }
    // count islands
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (visited[i][j] == false){
                res++;
                fill_island(i, j);
            }
        }
    }
    return res;
}

int RobotsOnIce::solve_aux(int x, int y, int s) {
    if (x == 0 && y == 1) {
        return 1;
    }
    // check if the next step is 1/4, 1/2 or 3/4 of the total
    // also if the manhattan distance is greater than the
    // remaining steps, the robot can't reach the checkpoint
    bool is_quarter = false;
    for (int i = 0; i < 4; i++){
        if (s+1 == quarters[i]){
            is_quarter = true;
        }
        int dist;
        if (s < quarters[i]){
            dist = abs(x - checkpoints[i].first) + abs(y - checkpoints[i].second);
            if (dist > cells - s){
                return 0;
            }
            break;
        }
    }

    int islands = count_islands(s);
    if (islands > 1){
        return 0;
    }
    
    // i can move to a pos with 0 (not visited) only if the next 
    // step is not a quarter (then i must move to a checkpoint)
    // if its a quarter then i must check if it its value is s+1
    int res = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + moves[i].first;
        int ny = y + moves[i].second;
        if ((nx >= 0 && nx < m) && (ny >= 0 && ny < n)) {
            if (M[nx][ny] == 0 && !is_quarter){
                M[nx][ny] = s+1;
                res += solve_aux(nx, ny, s+1);
                M[nx][ny] = 0;
            } else {
                if (M[nx][ny] == s+1){
                    res += solve_aux(nx, ny, s+1);
                }
            }
        }
    }
    return res;
}

int main(){
    RobotsOnIce r;
    while(1){
        if (r.read_input() == 1){
            break;
        };
        r.solve();
    }
}
