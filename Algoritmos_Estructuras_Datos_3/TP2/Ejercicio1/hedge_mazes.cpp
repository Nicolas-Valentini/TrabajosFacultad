#include<iostream>
#include<vector>
using namespace std;

// detección de puentes (sacado de la práctica)
int dfs_puentes(const vector<vector<int>>& ady, int source, const vector<int>& time_in, const vector<int>& parents, vector<bool>& puente_con_parent) {
    int cantidad = 0;
    for (int u : ady[source]) {
        if (parents[u] == source) {
            cantidad += dfs_puentes(ady, u, time_in, parents, puente_con_parent);
        } else {
            if (time_in[source]>time_in[u] && parents[source]!=u) { //(source,u) es backedge que sube
                cantidad++;
            }
            if (time_in[source] < time_in[u]) { //(source,u) es backedge que viene de abajo 
                cantidad--;
            }
        }
    }
    if (cantidad==0 && parents[source]!=source) {
        puente_con_parent[source] = true;
    }
    return cantidad;
}

// dfs con timer y colores (sacado de la práctica)
void dfs_timer(const vector<vector<int>>& ady,const int source, int current_time, vector<int>& time_in, vector<int>& color, vector<int>& parents) {
    color[source] = 1;
    time_in[source] = current_time++;
    for (int u : ady[source]) {
        if (color[u]==0) {
            parents[u] = source;
            dfs_timer(ady, u, current_time, time_in, color, parents);
        }
    }
    color[source]=2;
}

// dfs normal que asigna "nivel" a los nodos del arbol
void dfs_niveles(const vector<vector<int>>& ady, int source, vector<int>& niveles, int nivel) {
    niveles[source] = nivel;
    for (int u : ady[source]) {
        if (niveles[u] == -1) {
            dfs_niveles(ady, u, niveles, nivel);
        }
    }
}

int main(){
    while (true){
        int R, C, Q;
        cin >> R >> C >> Q;
        if (R + C + Q == 0) break;

        // armo el grafo
        vector<vector<int>> G(R+1,vector<int>()); // de R+1 para usar indexar desde 1
        for(int i = 0; i < C; i++){ // cargo las aristas
            int A, B;
            cin >> A >> B;
            G[A].push_back(B);
            G[B].push_back(A);
        }

        // detecto puentes
        vector<int> tiempos(R+1, 0);
        vector<int> padres(R+1, -1);
        vector<int> colores(R+1, 0);
        padres[1] = 1;
        dfs_timer(G, 1, 0, tiempos, colores, padres);
        vector<bool> arista_puente(R+1, false);
        dfs_puentes(G, 1, tiempos, padres, arista_puente);

        // armo un grafo (G2) solo con las aristas puente 
        vector<vector<int>> G2(R+1, vector<int>());
        for(int i = 0; i < R+1; i++){
            if (arista_puente[i]){
                G2[padres[i]].push_back(i);
                G2[i].push_back(padres[i]);
            }
        }

        // le asigno un nivel a cada componente conexa de G2
        vector<int> niveles(R+1, -1);
        int nivel = 0;
        for (int i = 0; i < R+1; i++) {
            if (niveles[i] == -1) {
                dfs_niveles(G2, i, niveles, nivel);
                nivel++;
            }
        }

        // consultas
        for(int i = 0; i < Q; i++){
            int A, B; // habitaciones a consultar
            cin >> A >> B;
            if(niveles[A] == niveles[B]){
                cout << "Y" << endl;
            } else {
                cout << "N" << endl;
            }
        }
        cout << "-" << endl;
    }
    return 0;
}