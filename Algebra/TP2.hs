--Ejercicio 1

--Calculos auxiliares
--Primero necesito una herramienta que calcule divisores.
--Esto lo hace simplemente probando 1 por 1 si tiene resto 0.
calculadoraDivisores :: Int -> Int-> [Int]
calculadoraDivisores n 0 = []
calculadoraDivisores n i 
 | (mod n i == 0) = i : calculadoraDivisores n (i-1)
 | otherwise = calculadoraDivisores n (i-1)
 
--Se llama a calculadoraDivisores a partir de div n 2 porque no puede haber divisores mayores que la mitad de un numero.
divisores:: Int->[Int]
divisores n = calculadoraDivisores n (div n 2)

--La funcion sumatoria simplemente saca la suma de todos los numeros dentro de una lista.  
sumatoria :: [Int] -> Int
sumatoria [] = 0
sumatoria (n:ns) = n + sumatoria ns 


--Ejercicio 1 A)
--sumaDeDivisoresPropios es la sumatoria de todos los divisores de un numero excepto si mismo.
sumaDeDivisoresPropios :: Int -> Int
sumaDeDivisoresPropios n = sumatoria (divisores n)

--Ejercicio 1 B) 
--Se define que un numero es perfecto si es igual a la sumaDeDivisoresPropios
esPerfecto :: Int -> Bool
esPerfecto n = (sumaDeDivisoresPropios n) == n



--Ejercicio 2

--Ejercicio 2 A) 

--Para armar la listaAlicuotaDeNDeLargo utilizo una funcion auxiliar que seria la misma a partir de un numero fijo i.
-- i indicaria la primera posicion. En donde se ubica el primer numero.
--pasada esa instancia se aplica la sumaDeDivisoresPropios de los numeros subsiguientes hasta llegar a que k sea 0.

listaAlicuotaDeNDeLargoDesde :: Int -> Int -> Int -> [Int]
listaAlicuotaDeNDeLargoDesde 0 _ n = []
listaAlicuotaDeNDeLargoDesde k i n 
 | (k == i) = n : listaAlicuotaDeNDeLargoDesde (k-1) i n 
 | otherwise = (sumaDeDivisoresPropios n) : (listaAlicuotaDeNDeLargoDesde (k-1) i (sumaDeDivisoresPropios n))
 
--Se llama a la funcion auxiliar con el i fijo siendo igual a k, para que en la primera posicion se ponga a N.
listaAlicuotaDeNDeLargo :: Int -> Int -> [Int]
listaAlicuotaDeNDeLargo k n = listaAlicuotaDeNDeLargoDesde k k n  

--Ejercicio 2 B)
--Para este ejercicio defino varias funciones auxiliares para cada una de las condiciones.
 
--Esta funcion se fija si para cualquier a(i+1) sea igual a la sumaDeDivisoresPropios de  a(i).
--Como caso base se toma una funcion de solo dos elementos. 
siguienteIgual :: [Int] -> Bool
siguienteIgual [n1,n2] = n2 == sumaDeDivisoresPropios n1
siguienteIgual (n:ns) = (head ns == sumaDeDivisoresPropios n) && siguienteIgual ns

--Esta funcion auxiliar se fija si un Int existe dentro de una lista
elementoDiferente :: Int -> [Int] -> Bool
elementoDiferente x [] = True
elementoDiferente x (n:ns)= x /= n && elementoDiferente x ns  

--Esta funcion auxiliar se asegura de que todos los elementos de la lista sean diferentes entre si.
todosDiferentes :: [Int] -> Bool
todosDiferentes [n] = True
todosDiferentes (n:ns) = elementoDiferente n ns && todosDiferentes ns 

--La funcion esta definida como aquella lista que tienen todos los elementos distintos.
--a(i+1)==a(i)
--El primer elemento es igual a la sumaDeDivisoresPropios del ultimo. 
--En caso de ser un unico elemento, tiene que cumplir que sea perfecto.
sonSociables :: [Int] -> Bool
sonSociables [n] = esPerfecto n
sonSociables (n:ns)= siguienteIgual (n:ns) && (n == sumaDeDivisoresPropios (last ns)) && todosDiferentes (n:ns)



--Ejercicio 3

--Funciones Auxiliares
--Defino aquellas funciones basicas para las funciones principales.
type Set a = [a]

--Si un elemento pertenece a un Set del mismo tipo
pertenece ::Eq a => a ->  Set a -> Bool 
pertenece _ [] = False 
pertenece x (y:ys) 
 | x == y = True
 | otherwise = pertenece x ys

--Agregar un elemento a un Set del mismo tipo.
agregar ::Eq a => a ->  Set a -> Set a
agregar x c 
 | pertenece x c = c
 | otherwise = x:c

--Determinar el elemento minimo de una lista. 
minimos :: [Int] -> Int 
minimos [n] = n
minimos (n:ns)
 | n <= head ns = minimos (n:(tail ns))
 | otherwise = minimos ns

--Fijarse si aquellos elementos de la lista son menores a los de un numero fijo
menores :: Int -> [Int] -> Bool
menores _ [] = True
menores n (x:xs) = (n > x) && menores n xs

--Ejercicio 3 A)

--El minimosDeKClubesMenoresQue se define como el elemento minimo que genera aquellas listas que sonSociables.
--La funcion se va fijando 1 por 1 hasta 0 para ver si son sociables. 
minimosDeKClubesMenoresQue :: Int -> Int -> [Int]
minimosDeKClubesMenoresQue k 0 = []
minimosDeKClubesMenoresQue k c 
 | (sonSociables lADNDL) = agregar (minimos lADNDL) (minimosDeKClubesMenoresQue k (c-1))
 | otherwise = minimosDeKClubesMenoresQue k (c-1)
 where lADNDL = listaAlicuotaDeNDeLargo k c  

--Ejercicio 3 B)
 
--Para evitar que listaDeNClubesConNrosMenoresQue se fije lista por lista, haciendo un proceso muy largo.
--Primero hago una funcion que devuelva una lista de las listaAlicuotaDeNDeLargo que hay en una lista normal.
--Como condicion tiene que todos los elementos de la lista tienen que ser menores a un numero fijo. 
listaDeLasPartes :: Int ->Int -> [Int] -> [[Int]]
listaDeLasPartes _ _ [] = []
listaDeLasPartes k i (n:ns) 
 | (menores i lADNDL)= agregar (lADNDL) (listaDeLasPartes k i ns)
 | otherwise = listaDeLasPartes k i ns
 where lADNDL = listaAlicuotaDeNDeLargo k n  
  
--listaDeNClubesConNrosMenoresQue se la puede entender como la lista de listas que se forman de aquel minimosDeKClubesMenoresQue con los mismos valores.
--Es importante la restriccion de menores en listaDeLasPartes porque por ejemplo con 5 13000 se obtiene 12496, sin embargo los miembros de ese club, no son menores a 13000.  
listaDeNClubesConNrosMenoresQue :: Int -> Int-> [[Int]]
listaDeNClubesConNrosMenoresQue n k = listaDeLasPartes n k (minimosDeKClubesMenoresQue n k) 





