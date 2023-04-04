# Correr

Para ejecutar estos programas es necesario un interprete de Haskell. Se puede utilizar GHCi, para acceder al mismo se puede utilizar el comando 
```bash
ghci
```
Dentro de GHCi para cargar los archivos a utilizar
```bash
:load TP1
```
```bash 
:load TP2
```

## Para TP1 las funciones implementadas toman los parametros:

```bash
med :: Float -> Float -> Int -> Float
```
med i0 b n es la cantidad de infectados luego de n dı́as (es decir, In ), para un modelo con i0 infectados iniciales y tasa de infección b. Siguiendo la siguiente ecuacion 
```bash
It = It−1 + It−1 · b.
```

```bash
med :: Float -> Float -> Int -> Float
```
mld p i0 b n es la cantidad de infectados luego de n dı́as (es decir, In ), para un modelo con una población total de p personas, i0 infectados iniciales y tasa de infección b. Sigue la siguiente formula 

```bash
It = It−1 + It−1 · b · (St-1/P)
```

```bash
sir :: (Float, Float, Float) -> Float -> Float -> Int -> (Float, Float, Float)
```
sir (s0,i0,r0) b g n da una tupla con la cantidad de individuos sanos, infectados y recuperados luego de n dı́as, para un modelo con una población total de s0 individuos sanos, i0 individuos infectados y r0 individuos recuperados, y factores b y g.

```bash
maxsir :: (Float, Float, Float) -> Float -> Float -> Int -> Float
```
calcula la cantidad máxima de infectados en un perı́odo de tiempo (definido como la cantidad de infectados en el dı́a con mayor cantidad de infectados).



# Para TP2 las funciones implementadas toman los parametros:

Un divisor propio de un número natural n ∈ N es un divisor de n distinto de n. Llamemos s(n) a la suma de los divisores propios de n. Decimos que n es perfecto si n = s(n).

```bash
esPerfecto :: Int -> Bool 
```
Determina si un número es perfecto
```bash
sumaDeDivisoresPropios :: Int -> Int  
```
Calcula los divisores propios positivos y los suma.

La sucesión alı́cuota de un número n es una sucesión a1 , a2 , . . . tal que a1 = n, y cada elemento ai+1 (para i ≥ 1) es la suma de los divisores propios de ai.

Una lista de números distintos es un club (también definida como una lista de números sociables) si la suma de los divisores propios del k-ésimo entero coincide con el (k + 1)-ésimo entero y si la suma de divisores propios del último entero coincide con el valor del primer entero.
```bash
listaAlicuotaDeNDeLargo :: Int -> Int -> [Int] 
```
listaAlicuotaDeNDeLargo k n calcula los primeros k elementos de la lista alı́cuota de n 

```bash
sonSociables :: [Int] -> Bool
```
Determina si la lista especificada correspondea un club

Una manera de representar a los clubes es tomando el mı́nimo elemento que los genera. De esta manera se puede generar una lista de clubes de cierta longitud

```bash
minimosDeKClubesMenoresQue :: Int -> Int -> [Int]
```
Dada una longitud k y una cota c, devuelva una lista de elementos menores o iguales a c tales que sean el elemento mı́nimo de un club de largo k.

```bash
istaDeNClubesConNrosMenoresQue :: Int -> Int -> [[Int]]
```
listaDeNClubesConNrosMenoresQue n k devuelva una lista de todos los clubes con n miembros cuyos elementos son todos menores que k



