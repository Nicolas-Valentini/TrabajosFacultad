#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Costo = unsigned long int;
using Arista = pair<size_t,size_t>;

//Estructura Union-Find.
//Proporciona dos funciones: Unite y Find
struct UF {
    //vectores internos
    //  p: Vector con los parents
    //  s: Vector con tamaños
    vector<int> p, s;
    
    //Constructor
    UF(int n): p(n, -1), s(n, 1) {}
    
    //unite: Hace la unión y devuelve el tamaño del resultante
    int unite(int v, int w) {
        v = find(v); w = find(w);
        if(v == w) return s[v];
        if(s[v] < s[w]) swap(v, w);
        p[w] = v; //El árbol de mayor tamaño queda como padre
        return s[v] += s[w];
    }
    
    //find: Devuelve el parent
    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]); //Recursión para path compression
    }
};

int main() {
    int t;
    cin >> t;

    for (int a = 0; a < t; a++) {
        size_t n,m;
        cin >> n >> m;

        UF componentes(n + 1);                //Para indexar desde 1
        vector<pair<Costo, Arista>> valores(m);

        //Lectura del vector de aristas
        for (int j = 0; j < m; j++) {
            size_t v, w;
            Costo c;
            cin >> v >> w >> c;
            valores[j] = {c, {v, w}};
        }

        //Ordenamiento de las aristas por peso
        sort(valores.begin(), valores.end(), greater<pair<Costo, Arista>>());

        vector<Costo> minimasPorComponente(n + 1, -1);
        vector<vector<pair<Costo, Costo>>> conexionesEntreComponentes(n + 1, vector<pair<Costo, Costo>>(n + 1, {-1, 0}));
        vector<vector<pair<Costo, int>>> listasDeAdyacencia(n + 1);

        for (int j = 0; j < m; j++) {
            listasDeAdyacencia[valores[j].second.first].push_back({valores[j].first, valores[j].second.second});
            listasDeAdyacencia[valores[j].second.second].push_back({valores[j].first, valores[j].second.first});
        }

        int total = 0;

        //Recorre las aristas ordenadas y se queda con aquellas que unan
        //dos vértices de componentes conexas distintas, uniéndolas
        for (int b = 0; b < m; b++) {
            Costo c = valores[b].first;
            Arista e = valores[b].second;

            size_t i = e.first;
            size_t j = e.second;

            int compI = componentes.find(i);
            int compJ = componentes.find(j);

            if (compI != compJ) {
                if (componentes.s[compI] > 1 && componentes.s[compJ] > 1) { // Uniendo dos componentes con mas de un nodo
                    int comp = componentes.s[compI] >= componentes.s[compJ] ? compI : compJ;

                    for (int k = 1; k <= n; k++) {
                        int compK = componentes.find(k);

                        if (compK != compI && compK != compJ) {
                            pair<Costo, Costo> conexionActual = conexionesEntreComponentes[comp][compK];
                            Costo conexionNuevaMin = min(conexionesEntreComponentes[compI][compK].first, conexionesEntreComponentes[compJ][compK].first);
                            Costo conexionNuevaMax = max(conexionesEntreComponentes[compI][compK].second, conexionesEntreComponentes[compJ][compK].second);
                            conexionesEntreComponentes[comp][compK] = { min(conexionActual.first, conexionNuevaMin), max(conexionActual.second, conexionNuevaMax) };
                            conexionesEntreComponentes[compK][comp] = conexionesEntreComponentes[comp][compK];
                        }
                    }

                    minimasPorComponente[comp] = min(min(minimasPorComponente[compI], minimasPorComponente[compJ]), min(conexionesEntreComponentes[compI][compJ].first, c));
                } else if (componentes.s[compI] > 1 || componentes.s[compJ] > 1) { // Uniendo nodo a componente con mas de un nodo
                    int comp = componentes.s[compI] > 1 ? compI : compJ;
                    int nodo = componentes.s[compI] > 1 ? j : i;

                    for (int k = 0; k < listasDeAdyacencia[nodo].size(); k++) {
                        Costo cK = listasDeAdyacencia[nodo][k].first;
                        int compK = componentes.find(listasDeAdyacencia[nodo][k].second);

                        if (compK != comp) {
                            pair<Costo, Costo> conexionActual = conexionesEntreComponentes[comp][compK];
                            conexionesEntreComponentes[comp][compK] = { min(cK, conexionActual.first), max(cK, conexionActual.second) };
                            conexionesEntreComponentes[compK][comp] = conexionesEntreComponentes[comp][compK];
                        } else {
                            minimasPorComponente[comp] = min(minimasPorComponente[comp], cK);
                        }
                    }
                } else { // Uniendo dos nodos
                    for (int k = 0; k < listasDeAdyacencia[i].size(); k++) {
                        Costo cK = listasDeAdyacencia[i][k].first;
                        int compK = componentes.find(listasDeAdyacencia[i][k].second);

                        pair<Costo, Costo> conexionActual = conexionesEntreComponentes[i][compK];
                        conexionesEntreComponentes[i][compK] = { min(cK, conexionActual.first), max(cK, conexionActual.second) };
                        conexionesEntreComponentes[compK][i] = conexionesEntreComponentes[i][compK];
                    }
                    for (int k = 0; k < listasDeAdyacencia[j].size(); k++) {
                        Costo cK = listasDeAdyacencia[j][k].first;
                        int compK = componentes.find(listasDeAdyacencia[j][k].second);

                        pair<Costo, Costo> conexionActual = conexionesEntreComponentes[j][compK];
                        conexionesEntreComponentes[j][compK] = { min(cK, conexionActual.first), max(cK, conexionActual.second) };
                        conexionesEntreComponentes[compK][j] = conexionesEntreComponentes[j][compK];
                    }

                    for (int k = 1; k <= n; k++) {
                        int compK = componentes.find(k);

                        if (compK != compI && compK != compJ) {
                            pair<Costo, Costo> conexionActual = conexionesEntreComponentes[i][compK];
                            Costo conexionNuevaMin = min(conexionesEntreComponentes[compI][compK].first, conexionesEntreComponentes[compJ][compK].first);
                            Costo conexionNuevaMax = max(conexionesEntreComponentes[compI][compK].second, conexionesEntreComponentes[compJ][compK].second);
                            conexionesEntreComponentes[compI][compK] = { min(conexionActual.first, conexionNuevaMin), max(conexionActual.second, conexionNuevaMax) };
                            conexionesEntreComponentes[compK][compI] = conexionesEntreComponentes[compI][compK];
                        }
                    }

                    minimasPorComponente[i] = c;
                }

                componentes.unite(i, j);

                Costo maxExterna = 0;
                int nodos = 0;

                int comp = componentes.find(i);

                for (int k = 1; k <= n; k++) {
                    int compK = componentes.find(k);

                    if (compK == comp) {
                        nodos++;
                    } else {
                        Costo aristaMaximaExterna = conexionesEntreComponentes[comp][compK].second;
                        if (aristaMaximaExterna + 1 == 0) {
                            aristaMaximaExterna = 0;
                        }
                        maxExterna = max(maxExterna, aristaMaximaExterna);
                    }
                }

                if (maxExterna < minimasPorComponente[comp]) {
                    total += nodos;
                }
            }
        }

        cout << total << endl;
    }

    return 0;
}
