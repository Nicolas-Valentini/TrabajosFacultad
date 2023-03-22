#include<iostream>
#include<vector>
#include<tuple>

using namespace std;

typedef tuple<int, int, int> Ecuacion;

bool fishburn(const vector<Ecuacion> &ecuaciones, const vector<int> &D, vector<int> &solucion){
    int a, b, c;
    int cant_ecuaciones = ecuaciones.size();
    
    bool changed = true;
    while (changed){
        changed = false;
        for (int i = 0; i < cant_ecuaciones; i++){
            a = get<0>(ecuaciones[i]);
            b = get<1>(ecuaciones[i]);
            c = get<2>(ecuaciones[i]);
            while (D[solucion[a]] > D[solucion[b]] + c){
                solucion[a]--;
                if (solucion[a] < 0) return false;
                changed = true;
            }
        }
    }

    return true;
}

int main(){
    int T, cant_ecuaciones, cant_variables, D_size;
    int a, b, c;
    vector<int> D, solucion;
    vector<Ecuacion> ecuaciones;
    cin >> T;
    for (int t = 0; t < T; t++){
        // Cargar datos
        cin >> cant_ecuaciones >> cant_variables >> D_size;
        ecuaciones.resize(cant_ecuaciones);
        solucion = vector<int>(cant_variables, D_size-1); // Los punteros empiezan apuntando al máximo de D
        D.resize(D_size);
        for (int i = 0; i < cant_ecuaciones; i++){
            cin >> a >> b >> c;
            ecuaciones[i] = make_tuple(a-1, b-1, c);
        }
        for (int i = 0; i < D_size; i++){
            cin >> D[i];
        }

        // Resolver
        if (fishburn(ecuaciones, D, solucion)){
            for (int i = 0; i < cant_variables; i++){
                cout << solucion[i]+1 << " ";
            }
            cout << endl;
        } else {
            cout << "insatisfactible" << endl;
        }
    }
    return 0;
}