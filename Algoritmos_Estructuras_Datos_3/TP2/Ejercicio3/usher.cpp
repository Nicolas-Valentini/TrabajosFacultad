#include<iostream>
#include<vector>
#include <queue>
using namespace std;

using arista = pair<int, int>;
const int INF = 1e9;

// dijkstra (sacado de la práctica)
void dijkstra(const vector<vector<arista>>& G, vector<int>& d, vector<int>& p) {
    int n = G.size();
    d.assign(n, INF);
    p.assign(n, -1);
    d[0] = 0;
    priority_queue<arista, vector<arista>, greater<arista>> q;
    q.push({0, 0});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;
        for (auto edge : G[v]) {
            int to = edge.first;
            int len = edge.second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

int resolver(const vector<vector<arista>>& ady, int c){
    vector<int> distancias, padres;
    dijkstra(ady, distancias, padres);
    // Me quedo con el ciclo de menor peso
    int peso_ciclo_min = INF;
    for (int i = 1; i < ady.size(); i++){
        // Si apuntan al 0, forman un ciclo
        for (int j = 0; j < ady[i].size(); j++){
            if (ady[i][j].first == 0){
                // Si el peso del ciclo es menor al minimo, lo actualizo
                if (distancias[i] + ady[i][j].second < peso_ciclo_min){
                    peso_ciclo_min = distancias[i] + ady[i][j].second;
                }
            }
        }
    }
    
    int monedas = 0;
    int res = 0;
    while (true) {
        monedas += peso_ciclo_min;
        if (monedas >= c) {
            return res;
        }
        monedas--; 
        res++;
    }
}

int main(){
    int casos, capacidad, feligreses;
    vector<vector<arista>> G;
    cin >> casos;
    for (int caso = 0; caso < casos; caso++){
        cin >> capacidad >> feligreses;
        G = vector<vector<arista>>(feligreses+1, vector<arista>(0));

        int q;
        cin >> q;
        for (int i = 0; i < q; i++){
            int f;
            cin >> f;
            G[0].push_back({f, 0});
        }
        for (int i = 0; i < feligreses; i++){
            int reglas;
            cin >> reglas;
            for (int j = 0; j < reglas; j++){
                int monedas;
                int destino;
                cin >> monedas >> destino;
                G[i+1].push_back({destino, monedas});
            }
        }
        cout << resolver(G, capacidad) << endl;
    }
    return 0;
}