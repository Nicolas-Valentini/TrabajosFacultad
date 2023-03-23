#include "gtest-1.8.1/gtest.h"
#include "../src/aed2_simulacion.h"

aed2_Mapa crearMapa(Nat ancho, Nat alto, set<Coordenada> elevaciones,
                     map<Color, Coordenada> receptaculos,
                     set<Coordenada> rampas) {
	aed2_Mapa m(ancho, alto, elevaciones, receptaculos);

	for (Coordenada c : rampas) {
		m.agregarRampa(c);
	}
	return m;
}

class Simulacion_Test : public testing::Test {
protected:
	Coordenada posI, posI2, posI3, posI4, posI5, posI6, posI7, posPrevioObjeto;
	Coordenada posArr, posAb, posIzq, posDer, posI2ab, posI3arr, posI4izq, posI5der;
	Coordenada posAbAb, posIzqIzq, posDerDer, posArrArr, posArrArrIzq, posArrArrIzqAb;
	Coordenada posIbordeSupIzq, posIbordeInfDer;
	Coordenada posIAgenteSupIzq, posIAgenteSupArr, posIAgenteInfAb, posIAgenteInfDer;
	Coordenada e1, e2, e3, e4;
	Coordenada e3Arr, e3Ab, e3Izq, e1Der;
	Coordenada r1, r2, r3;
	Coordenada o1, o2, o3;
	Coordenada recep1, recep2, recep3;
	set<Coordenada> elevaciones1, elevaciones2, elevaciones3;
	set<Coordenada> rampas1;
	map<Color,Coordenada> receptaculos1;
	map<Color,Coordenada> objetos1, objetos2, objetos3, objetos4, objetos5;
	map<Color,Coordenada> objetos1movido, objetos1objetivo2cumplido, objetos1objetivosCumplidos;
	map<Color,Coordenada> objetos2arr, objetos2ab, objetos2der, objetos2izq;
	map<Color,Coordenada> objetosPegadosArr, objetosPegadosAb, objetosPegadosDer, objetosPegadosIzq;
	map<Color,Coordenada> objetosElevacionArr, objetosElevacionAb, objetosElevacionDer, objetosElevacionIzq;
	Objetivo objetivo1, objetivo2, objetivo3;
	aed2_Mapa m1, m2, m3;


	void SetUp() {
		
		posI = {4,5}; 
		posI2 = {7,1}; 
		posI3 = {7,3}; 
		posI4 = {6,2}; 
		posI5 = {8,2}; 
		posI6 = {3,2}; 
		posI7 = {1,0}; 
		posI2ab = {7,0}; 
		posI3arr = {7,4}; 
		posI4izq = {5,2}; 
		posI5der = {9,2}; 
		posPrevioObjeto = {7,6};
		posArr = {4,6};
		posAb = {4,4};
		posIzq = {3,5};
		posDer = {5,5};
		posIzqIzq = {2,5};
		posDerDer = {6,5};
		posAbAb = {4,3};
		posArrArr = {4,7};
		posArrArrIzq = {3,7};
		posArrArrIzqAb = {3,6};
		posIbordeSupIzq = {0,9};
		posIbordeInfDer = {9,0};
		posIAgenteSupIzq = {1,9};
		posIAgenteSupArr = {0,8};
		posIAgenteInfAb = {9,1};
		posIAgenteInfDer = {8,0};
		e1 = {3,0};
		e2 = {7,2};
		e3 = {3,7};
		e4 = {0,0};
		e1Der = {4,0};
		e3Arr = {3,8};
		e3Ab = {3,6};
		e3Izq = {2,7};
		r1 = {2,0};
		r2 = {3,1};
		r3 = {4,7};
		recep1 = {2,0};
		recep2 = {3,7};
		recep3 = {7,8};
		o1 = {7,7}; 
		o2 = {7,2}; 
		o3 = {5,7}; 
		elevaciones1 = {e1, e2, e3};
		elevaciones2 = {e1, e3}; 
		rampas1 = {r1, r2, r3};
		objetos1 = {{"Rojo", o1},
					{"Verde", o3}}; 
		objetos1movido = {{"Rojo", o1},
						  {"Verde", r3}};
		objetos1objetivo2cumplido = {{"Rojo", o1},
									 {"Verde", recep2}};
		objetos1objetivosCumplidos = {{"Rojo", recep3},
									  {"Verde", recep2}};
		objetos2 = {{"Rojo", o2}}; 
		objetos2arr = {{"Rojo", posI3}};
		objetos2ab = {{"Rojo", posI2}};
		objetos2der = {{"Rojo", posI5}};
		objetos2izq = {{"Rojo", posI4}};
		objetos3 = {{"Rojo", posIbordeSupIzq}}; 
		objetos4 = {{"Rojo", posIbordeInfDer}}; 
		objetos5 = {{"Rojo", recep1}};
		objetosElevacionArr = {{"Rojo", posI2}};
		objetosElevacionAb = {{"Rojo", posI3}};
		objetosElevacionDer = {{"Rojo", posI4}};
		objetosElevacionIzq = {{"Rojo", posI5}};
		objetosPegadosArr = {{"Rojo", posArr}, 
							 {"Verde", posArrArr}};
		objetosPegadosAb = {{"Rojo", posAb},
							{"Verde", posAbAb}};
		objetosPegadosDer = {{"Rojo", posDer},
							 {"Verde", posDerDer}};
		objetosPegadosIzq = {{"Rojo", posIzq},
							 {"Verde", posIzqIzq}};
		receptaculos1 = {{"Turquesa",recep1}, 
						{"Azul",recep2}, 
						{"Negro",recep3}};
		objetivo1 = Objetivo("Rojo", "Negro");
		objetivo2 = Objetivo("Verde", "Azul");
		objetivo3 = Objetivo("Rojo", "Turquesa");


		m1 = crearMapa(10, 10, elevaciones1, receptaculos1, rampas1);
		m2 = crearMapa(10, 10, elevaciones2, receptaculos1, rampas1);


	}

};

void compararMapas(const aed2_Mapa &mapa1, const aed2_Mapa &mapa2) {
	for (int x = 0; x < 10; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			TipoCasillero c1 = mapa1.tipoCasillero(make_pair(x,y));
			TipoCasillero c2 = mapa2.tipoCasillero(make_pair(x,y));
			EXPECT_EQ(c1, c2);			
		}
	}
	EXPECT_EQ(mapa1.receptaculos(), mapa2.receptaculos());
}


TEST_F(Simulacion_Test, nuevo_mapa) {
	aed2_Mapa m(10, 10, elevaciones1, receptaculos1);

    EXPECT_EQ(m.ancho(), 10);
    EXPECT_EQ(m.alto(), 10);
    EXPECT_EQ(m.tipoCasillero(e1), ELEVACION);
    EXPECT_EQ(m.tipoCasillero(e2), ELEVACION);
    EXPECT_EQ(m.tipoCasillero(e3), ELEVACION);
    EXPECT_EQ(m.receptaculos(), receptaculos1);

    EXPECT_EQ(m.tipoCasillero(r1), PISO);
    m.agregarRampa(r1);
    EXPECT_EQ(m.tipoCasillero(r1), RAMPA);
    EXPECT_EQ(m.receptaculo("Turquesa"), r1);
    EXPECT_EQ(m.tipoCasillero(r2), PISO);
    m.agregarRampa(r2);
    EXPECT_EQ(m.tipoCasillero(r2), RAMPA);
    EXPECT_EQ(m.tipoCasillero(r3), PISO);
    m.agregarRampa(r3);
    EXPECT_EQ(m.tipoCasillero(r3), RAMPA);
}

TEST_F(Simulacion_Test, nueva_simulacion) {
	aed2_Simulacion s1(m1, objetos1, posI);

    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.agregarObjetivo(objetivo1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);

	s1.agregarObjetivo(objetivo2);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 2);
	EXPECT_EQ(s1.objetivosResueltos(), 0);

}

TEST_F(Simulacion_Test, mover_arriba) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posArr);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);
}

TEST_F(Simulacion_Test, mover_abajo) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ABAJO);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posAb);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);
}

TEST_F(Simulacion_Test, mover_derecha) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(DERECHA);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posDer);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);
}

TEST_F(Simulacion_Test, mover_izquierda) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(IZQUIERDA);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIzq);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);
}

TEST_F(Simulacion_Test, varios_movimientos) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posArr);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), posArrArr);
	EXPECT_EQ(s1.movimientos(), 2);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), posArrArrIzq);
	EXPECT_EQ(s1.movimientos(), 3);
	s1.mover(ABAJO);
	EXPECT_EQ(s1.posAgente(), posArrArrIzqAb);
	EXPECT_EQ(s1.movimientos(), 4);
}

TEST_F(Simulacion_Test, subir_rampa_arriba_y_bajar) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), r3);
	EXPECT_EQ(s1.movimientos(), 2);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), e3);
	EXPECT_EQ(s1.movimientos(), 3);
	s1.mover(DERECHA);
	s1.mover(ABAJO);
	s1.mover(ABAJO);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 6);
}

TEST_F(Simulacion_Test, subir_rampa_abajo_y_bajar) {
	aed2_Simulacion s1(m1, objetos1, posI6);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI6);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ABAJO);
	EXPECT_EQ(s1.posAgente(), r2);
	EXPECT_EQ(s1.movimientos(), 1);
	s1.mover(ABAJO);
	s1.mover(IZQUIERDA);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), posI7);
	EXPECT_EQ(s1.movimientos(), 4);
}

TEST_F(Simulacion_Test, subir_rampa_derecha_y_bajar) {
	aed2_Simulacion s1(m1, objetos1, posI7);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI7);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(DERECHA);
	EXPECT_EQ(s1.posAgente(), r1);
	EXPECT_EQ(s1.movimientos(), 1);
	s1.mover(DERECHA);
	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), posI6);
	EXPECT_EQ(s1.movimientos(), 4);
}

TEST_F(Simulacion_Test, subir_rampa_izquierda_y_bajar) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(DERECHA);
	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), r3);
	EXPECT_EQ(s1.movimientos(), 4);
	s1.mover(DERECHA);
	s1.mover(ABAJO);
	s1.mover(ABAJO);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 8);
}

TEST_F(Simulacion_Test, caer_elevacion_piso_arriba) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), r3);
	EXPECT_EQ(s1.movimientos(), 2);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), e3);
	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), e3Arr);
	EXPECT_EQ(s1.movimientos(), 4);
}

TEST_F(Simulacion_Test, caer_elevacion_piso_abajo) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), r3);
	EXPECT_EQ(s1.movimientos(), 2);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), e3);
	s1.mover(ABAJO);
	EXPECT_EQ(s1.posAgente(), e3Ab);
	EXPECT_EQ(s1.movimientos(), 4);
}

TEST_F(Simulacion_Test, caer_elevacion_piso_derecha) {
	aed2_Simulacion s1(m1, objetos1, posI7);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI7);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(DERECHA);
	EXPECT_EQ(s1.posAgente(), r1);
	EXPECT_EQ(s1.movimientos(), 1);
	s1.mover(DERECHA);
	EXPECT_EQ(s1.posAgente(), e1);
	EXPECT_EQ(s1.movimientos(), 2);
	s1.mover(DERECHA);
	EXPECT_EQ(s1.posAgente(), e1Der);
	EXPECT_EQ(s1.movimientos(), 3);
}

TEST_F(Simulacion_Test, caer_elevacion_piso_izquierda) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), r3);
	EXPECT_EQ(s1.movimientos(), 2);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), e3);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), e3Izq);
	EXPECT_EQ(s1.movimientos(), 4);
}

TEST_F(Simulacion_Test, elevacion_bloquea_arriba) {
	aed2_Simulacion s1(m1, objetos1, posI2);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI2);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), posI2);
	EXPECT_EQ(s1.movimientos(), 1);
}

TEST_F(Simulacion_Test, elevacion_bloquea_abajo) {
	aed2_Simulacion s1(m1, objetos1, posI3);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI3);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ABAJO);
	EXPECT_EQ(s1.posAgente(), posI3);
	EXPECT_EQ(s1.movimientos(), 1);
}

TEST_F(Simulacion_Test, elevacion_bloquea_derecha) {
	aed2_Simulacion s1(m1, objetos1, posI4);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI4);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(DERECHA);
	EXPECT_EQ(s1.posAgente(), posI4);
	EXPECT_EQ(s1.movimientos(), 1);
}

TEST_F(Simulacion_Test, elevacion_bloquea_izquierda) {
	aed2_Simulacion s1(m1, objetos1, posI5);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI5);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), posI5);
	EXPECT_EQ(s1.movimientos(), 1);
}

TEST_F(Simulacion_Test, borde_bloquea_arriba) {
	aed2_Simulacion s1(m1, objetos1, posIbordeSupIzq);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIbordeSupIzq);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIbordeSupIzq);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);
}

TEST_F(Simulacion_Test, borde_bloquea_abajo) {
	aed2_Simulacion s1(m1, objetos1, posIbordeInfDer);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIbordeInfDer);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ABAJO);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIbordeInfDer);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);
}

TEST_F(Simulacion_Test, borde_bloquea_derecha) {
	aed2_Simulacion s1(m1, objetos1, posIbordeInfDer);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIbordeInfDer);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(DERECHA);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIbordeInfDer);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);
}

TEST_F(Simulacion_Test, borde_bloquea_izquierda) {
	aed2_Simulacion s1(m1, objetos1, posIbordeSupIzq);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIbordeSupIzq);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(IZQUIERDA);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posIbordeSupIzq);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);
}

TEST_F(Simulacion_Test, empujar_objeto_arriba) {
	aed2_Simulacion s1(m2, objetos2, posI2);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posI2);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos2);

	s1.mover(ARRIBA);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), o2);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos2arr);
}

TEST_F(Simulacion_Test, empujar_objeto_abajo) {
	aed2_Simulacion s1(m2, objetos2, posI3);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posI3);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos2);

	s1.mover(ABAJO);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), o2);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos2ab);
}

TEST_F(Simulacion_Test, empujar_objeto_derecha) {
	aed2_Simulacion s1(m2, objetos2, posI4);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posI4);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos2);

	s1.mover(DERECHA);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), o2);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos2der);
}

TEST_F(Simulacion_Test, empujar_objeto_izquierda) {
aed2_Simulacion s1(m2, objetos2, posI5);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posI5);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos2);

	s1.mover(IZQUIERDA);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), o2);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos2izq);}

TEST_F(Simulacion_Test, dos_objetos_no_se_mueven_arriba) {
	aed2_Simulacion s1(m2, objetosPegadosArr, posI);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosPegadosArr);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosPegadosArr);
}

TEST_F(Simulacion_Test, dos_objetos_no_se_mueven_abajo) {
	aed2_Simulacion s1(m2, objetosPegadosAb, posI);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosPegadosAb);

	s1.mover(ABAJO);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosPegadosAb);
}

TEST_F(Simulacion_Test, dos_objetos_no_se_mueven_derecha) {
	aed2_Simulacion s1(m2, objetosPegadosDer, posI);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosPegadosDer);

	s1.mover(DERECHA);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosPegadosDer);
}

TEST_F(Simulacion_Test, dos_objetos_no_se_mueven_izquierda) {
	aed2_Simulacion s1(m2, objetosPegadosIzq, posI);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosPegadosIzq);

	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosPegadosIzq);
}

TEST_F(Simulacion_Test, objeto_no_sale_del_mundo_arriba) {
	aed2_Simulacion s1(m2, objetos3, posIAgenteSupArr);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posIAgenteSupArr);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos3);

	s1.mover(ARRIBA);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posIAgenteSupArr);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos3);
}

TEST_F(Simulacion_Test, objeto_no_sale_del_mundo_abajo) {
	aed2_Simulacion s1(m2, objetos4, posIAgenteInfAb);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posIAgenteInfAb);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos4);

	s1.mover(ABAJO);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posIAgenteInfAb);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos4);
}

TEST_F(Simulacion_Test, objeto_no_sale_del_mundo_derecha) {
	aed2_Simulacion s1(m2, objetos4, posIAgenteInfDer);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posIAgenteInfDer);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos4);

	s1.mover(DERECHA);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posIAgenteInfDer);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos4);
}

TEST_F(Simulacion_Test, objeto_no_sale_del_mundo_izquierda) {
	aed2_Simulacion s1(m2, objetos3, posIAgenteSupIzq);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posIAgenteSupIzq);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos3);

	s1.mover(IZQUIERDA);
    compararMapas(s1.mapa(), m2);
	EXPECT_EQ(s1.posAgente(), posIAgenteSupIzq);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos3);
}

TEST_F(Simulacion_Test, objeto_choca_elevacion_arriba_y_no_avanza) {
	aed2_Simulacion s1(m1, objetosElevacionArr, posI2ab);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI2ab);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosElevacionArr);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), posI2ab);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosElevacionArr);
}

TEST_F(Simulacion_Test, objeto_choca_elevacion_abajo_y_no_avanza) {
	aed2_Simulacion s1(m1, objetosElevacionAb, posI3arr);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI3arr);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosElevacionAb);

	s1.mover(ABAJO);
	EXPECT_EQ(s1.posAgente(), posI3arr);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosElevacionAb);
}

TEST_F(Simulacion_Test, objeto_choca_elevacion_derecha_y_no_avanza) {
	aed2_Simulacion s1(m1, objetosElevacionDer, posI4);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI4);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosElevacionDer);

	s1.mover(DERECHA);
	EXPECT_EQ(s1.posAgente(), posI4);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosElevacionDer);
}

TEST_F(Simulacion_Test, objeto_choca_elevacion_izquierda_y_no_avanza) {
	aed2_Simulacion s1(m1, objetosElevacionIzq, posI5der);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI5der);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosElevacionIzq);

	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), posI5der);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetosElevacionIzq);
}

TEST_F(Simulacion_Test, agregar_objetivo_cumplido_automaticamente) {
	aed2_Simulacion s1(m1, objetos5, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos5);

	s1.agregarObjetivo(objetivo3);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos5);
}

TEST_F(Simulacion_Test, cumplir_objetivos) {
	aed2_Simulacion s1(m1, objetos1, posI);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posI);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.agregarObjetivo(objetivo1);
	s1.agregarObjetivo(objetivo2);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 2);

	s1.mover(DERECHA);
	s1.mover(DERECHA);
	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	s1.mover(IZQUIERDA);

	EXPECT_EQ(s1.posAgente(), o3);
	EXPECT_EQ(s1.movimientos(), 5);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 2);
	EXPECT_EQ(s1.posObjetos(), objetos1movido);

	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), r3);
	EXPECT_EQ(s1.movimientos(), 6);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 1);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivo2cumplido);

	s1.mover(DERECHA);
	s1.mover(DERECHA);
	s1.mover(ABAJO);
	s1.mover(DERECHA);
	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 10);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 1);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivo2cumplido);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), o1);
	EXPECT_EQ(s1.movimientos(), 11);
	EXPECT_EQ(s1.objetivosResueltos(), 2);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivosCumplidos);
}

TEST_F(Simulacion_Test, no_cumplir_objetivos_ya_resueltos) {
	aed2_Simulacion s1(m1, objetos1objetivo2cumplido, posPrevioObjeto);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivo2cumplido);

	s1.agregarObjetivo(objetivo1);

	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 1);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), o1);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivosCumplidos);

	s1.mover(DERECHA);
	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	s1.mover(IZQUIERDA);
	s1.mover(ABAJO);
	s1.mover(DERECHA);
	s1.mover(ABAJO);
	s1.mover(ABAJO);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 10);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivo2cumplido);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), o1);
	EXPECT_EQ(s1.movimientos(), 11);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivosCumplidos);

}


TEST_F(Simulacion_Test, objetivos_con_mismo_color_objeto) {
	aed2_Simulacion s1(m1, objetos1, posPrevioObjeto);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.agregarObjetivo(objetivo1);
	s1.agregarObjetivo(objetivo3);
	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 2);
	EXPECT_EQ(s1.posObjetos(), objetos1);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 1);

}

TEST_F(Simulacion_Test, cumplir_objetivo_mover_objeto_y_agregar_mismo_objetivo) {
	aed2_Simulacion s1(m1, objetos1objetivo2cumplido, posPrevioObjeto);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivo2cumplido);

	s1.agregarObjetivo(objetivo1);

	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 1);

	// cumple objetivo1
	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), o1);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivosCumplidos);

	// muevo objeto a posicion inicial
	s1.mover(DERECHA);
	s1.mover(ARRIBA);
	s1.mover(ARRIBA);
	s1.mover(IZQUIERDA);
	s1.mover(ABAJO);
	s1.mover(DERECHA);
	s1.mover(ABAJO);
	s1.mover(ABAJO);
	s1.mover(IZQUIERDA);
	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 10);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivo2cumplido);

	// agrego mismo objetivo que va a estar no resuelto
	s1.agregarObjetivo(objetivo1);

	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 10);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 1);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivo2cumplido);
}

TEST_F(Simulacion_Test, cumplir_objetivo_agregarlo_y_cumplir_automaticamente) {
	aed2_Simulacion s1(m1, objetos1objetivo2cumplido, posPrevioObjeto);
    compararMapas(s1.mapa(), m1);
	EXPECT_EQ(s1.posAgente(), posPrevioObjeto);
	EXPECT_EQ(s1.movimientos(), 0);
	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivo2cumplido);

	s1.agregarObjetivo(objetivo1);

	EXPECT_EQ(s1.objetivosResueltos(), 0);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 1);

	s1.mover(ARRIBA);
	EXPECT_EQ(s1.posAgente(), o1);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 1);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivosCumplidos);

	s1.agregarObjetivo(objetivo1);

	EXPECT_EQ(s1.posAgente(), o1);
	EXPECT_EQ(s1.movimientos(), 1);
	EXPECT_EQ(s1.objetivosResueltos(), 2);
	EXPECT_EQ(s1.objetivosDisponibles().size(), 0);
	EXPECT_EQ(s1.posObjetos(), objetos1objetivosCumplidos);
}