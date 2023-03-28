--Ejercicio 1

--La funcion med llama a la funcion auxiliar infectadosMed.
med :: Float -> Float -> Int -> Float
med i0 b n = infectadosMed i0 b n 

--Funcion auxiliar ejercicio 1.
--Defini la funcion como los infectados del dia anterior sumado b por el mismo numero.
--Como caso base defini que cuando haya pasado 0 dias, habria i0 infectados.
infectadosMed :: Float -> Float -> Int -> Float 
infectadosMed i0 _ 0 = i0
infectadosMed i0 b n = infectadosMed i0 b (n-1) + infectadosMed i0 b (n-1)* b 

--Ejercicio 2

--Llamo a la funcion auxiliar infectadosMld en el dia n.
mld :: Float ->  Float -> Float -> Int -> Float
mld p i0 b n = infectadosMld p i0 b n 

--Funcion auxiliar infectadosMld ejercicio 2.
--Esta funcion es similar a la anterior solo que en el ultimo termino se multiplica por los sanos en el dia anterior dividido la poblacion.
--Para eso llamo a la funcion auxiliar sanos en el dia anterior.  
--Como el ejercicio anterior, defini como caso base que a los 0 dias, existirian i0 infectados. 
infectadosMld :: Float ->  Float -> Float -> Int -> Float
infectadosMld _ i0 _ 0 = i0
infectadosMld p i0 b n = infectadosMld p i0 b (n-1) + infectadosMld p i0 b (n-1) *b*((sanosMld p i0 b (n-1))/p)  

--Funcion auxiliar Sanos ejercicio 2.
--Defino a la paoblacion sana como st=p-it
sanosMld :: Float-> Float-> Float-> Int-> Float
sanosMld p i0 b n = p - infectadosMld p i0 b n

--Ejercicio 3

{-Para este ejercicio decidi recomponer la tupla resultante de sir, con tres variables diferentes, las cuales estan relacionadas entre si
a traves de las ecuaciones dadas por el enunciado-}

sir :: (Float, Float, Float) -> Float -> Float -> Int -> (Float, Float, Float)
sir (s0, i0, r0) b g n = (st(s0,i0,r0) b g n ,it(s0, i0,r0) b g n ,rt(s0,i0,r0) b g n )

--Esta es la funcion auxiliar para St 

st :: (Float, Float, Float) -> Float-> Float -> Int -> Float
st (s0, i0,r0) _ _ 0 = s0
st (s0, i0,r0) b g n =st (s0,i0,i0) b g (n-1)- b*st (s0,i0,r0) b g (n-1)*it (s0,i0,r0) b g (n-1)

--Esta es la funcion auxiliar para It

it :: (Float, Float, Float)->Float->Float->Int->Float
it (s0, i0,r0) _ _ 0= i0
it (s0, i0,r0) b g n =it (s0,i0,r0) b g (n-1)+ b*it (s0,i0,r0) b g (n-1)*st (s0,i0,r0) b g (n-1)- g * it (s0,i0,r0) b g (n-1)

--Esta es la funcion auxiliar para Rt

rt :: (Float, Float, Float) -> Float-> Float-> Int-> Float
rt (s0,i0,r0) _ _ 0 = r0
rt (s0,i0,r0) b g n = rt(s0,i0,r0) b g (n-1)+ g*it(s0,i0,r0) b g (n-1)
      
--Ejercicio 4

--Se llama a la funcion auxiliar comparacionMaxsir que toma i y j como 0, y la compara hasta n.
--Esto se hace para que se puedan evaluar los valores desde el dia 0 hasta el n. 
maxsir :: (Float, Float, Float) -> Float-> Float -> Int -> Float
maxsir (s0,i0,r0) b g n = comparacionMaxsir (s0, i0,r0) b g 0 0 n

--Funcion auxiliar ejercicio 4

--Esta es una recursion creciente que sirve para encontrar un maximo.
--El caso base indica que cuando i sea mayor que n, se llame al it correspondiente a j.
--El objetivo de esta recusion es ir comparando el it que se tiene en j con i.
{-En caso de que j sea mayor que i, este tiene tiene chances de ser el maximo, asi que se evalua contra el proximo i.
En caso contrario significa que el i puede ser el maximo, entonces toma la posicion del j para ser comparado por el resto.-}
--De esta forma j va a ir cambiando su valor si y solo si i es mayor o igual a j y a todos los numeros anteriores.  
comparacionMaxsir:: (Float, Float, Float)->Float->Float->Int->Int->Int->Float
comparacionMaxsir (s0, i0,r0) b g i j n
 | (n<i) = it(s0, i0,r0) b g j
 | it(s0, i0,r0) b g j > it(s0, i0,r0) b g i = comparacionMaxsir(s0, i0,r0) b g (i+1) j n
 | otherwise = comparacionMaxsir (s0, i0,r0) b g (i+1) i n







