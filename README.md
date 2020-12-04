# ProyectoED
  1. Presentación:
  
Proyecto del curso de Estructuras de Datos del Instituto Tecnológico de Costa Rica. Desarrollado por los siguientes estudiantes:
  * Pablo León Rodríguez. 
     Correo electrónico: pjleon.tec@gmail.com
  * Nallely González Zamora. 
     Correo electrónico: nallegonzs16@gmail.com
  * Josué Quesada Jiménez. 
     Correo electrónico: josucho.45@gmail.com
  * Mariluz Saborío Corea. 
     Correo electrónico: mariluzsabco@gmail.com

  2. Tipo de juego creado: 
Es un juego de 2D de laberintos estilo medieval, con cuatro personajes a elegir, los cuales son: una arquera, un mago, un hada sanadora y un bandido. El objetivo principal del juego es encontrar la llave necesaria para abrir el baúl en el tiempo establecido y lograr ganar ese nivel, además de desplazarse por los caminos correctos del laberinto recogiendo recompensas, sumando puntos, intentando encontrar las recompensas ocultas y evitando que los enemigos lo maten restando vidas al personaje y devolviéndolo al inicio del recorrido. Es un juego de dificultad baja de tipo arcade que pretende ofrecer una jugabilidad simple, no obstante, entretenida y envolvente para el jugador.

  3. Historia:
 En la Edad Media, se exparció un rumor de cuatro tesoros secretos escondidos en cuatro laberintos del Reino de Batsalú, pero esos tesoros eran resguardados por enemigos malvados que no deseaban que nadie lograra atravesar los laberintos, ni recoger sus recompenzas, ni mucho menos que alguien se llevara el tesoro. Después de que muchos intentaran buscar los tesoros y fracasaran en el intento, se decidió que sólo los más poderosos del Reino deberían iniciar la travesía, entonces, entre los elegidos se encontraban: Chachi la arquera valiente, Atlantes el mago invencible, Lucecita la sanadora de corazón puro y Josucho el enmascarado misterioso. Así que, Cada uno de estos poderosos guerreros debía decidir en cuál laberinto del Reino emprender su viaje en búsqueda del tesoro sin ser vencidos por los peligrosos enemigos.

  4. Principales estructuras de datos creadas:
 
En nuestro proyecto utilizamos diversas estructuras de datos con el fin de almacenar de manera ordenada una serie de valores. Las principales estructuras usadas fueron:
* Grafos: Son estructuras compuestas por vértices que contienen la información y aristas que los conectan. En el caso de este proyecto se utilizaron para creaar vértices en los lugares del mapa en los que se podía caminar y en esos lugares colocar recompenzas u otros.
* Matrices: Se utilizaron para crear los mapas con enteros dentro de ellas que representaban cada parte del mapa, para saber dónde podrían haber recompensas y para crear los grafos con la información de dónde podría caminar el personaje y los enemigos (se tomaban en cuenta las posiciones de la matriz con un entero específico).
* Vectores: Se utilizaron vectores para establecer la cantidad de recompensas en el mapa.
* Switch: Se utilizaron para definir qué rectángulo de imagen se pintaría en el mapa, ya que en un "switch" se pueden definir diferentes casos, en esta situación de acuerdo a los posibles números enteros que se encontraban en la matriz.
* Struct: Es una estructura en la que se definen variables y si es necesario los punteros que definan con cual otra estructura se conecta. En este caso se utilizaron para definir la estructura del grafo, sus aristas y vértices.

  5. Principales metódos con su respectiva función y sus parámetros si los requieren:
* Inicializar:  
Función: Método que se encarga de cargar las imágenes necesarias, los sonidos, crear la ventana y todos los detalles necesarios para iniciar el juego.  
Parámetros: No recibe.  
* Pintar mapa:   
Función: Método que recorre la matriz para pintar cada sprite del mapa en pantalla según la posición que se necesita.  
Parámetros: Recibe el parámetro (SDL_rect personaje), que es un rectángulo del personaje que se utilizará.  
* Existe colisión arriba:  
Función: Su función es verificar si el personaje colisiona con una pared del muro del laberinto al subir. Permite la correcta movilidad del personaje.  
Parámetros: Recibe los parámetros (int posxPersonaje, int posyPersonaje), que son la posición en el eje x y en el eje y del personaje.  
* Existe colisión abajo:  
Función: Su función es verificar si el personaje colisiona con una pared del muro del laberinto al bajar. Permite la correcta movilidad del personaje.  
Parámetros:  Recibe los parámetros (int posxPersonaje, int posyPersonaje), que son la posición en el eje x y en el eje y del personaje.  
* Existe colisión izquierda:  
Función: Verifica si el personaje colisiona con una pared del muro del laberinto al moverse a la izquierda. Permite la correcta movilidad del personaje.    
Parámetros: Recibe los parámetros (int posxPersonaje, int posyPersonaje), que son la posición en el eje x y en el eje y del personaje.   
* Existe colisión derecha:  
Función: Verifica si el personaje colisiona con una pared del muro del laberinto al moverse a la derecha. Permite la correcta movilidad del personaje.  
Parámetros: Recibe los parámetros (int posxPersonaje, int posyPersonaje), que son la posición en el eje x y en el eje y del personaje.  
* Tiempo y Sprites:  
Función: Se encarga de generar el bucle del juego, llamando los demás métodos que se deben ejecutar hasta que el usuario cierre la aplicación.  
Parámetros: No recibe.  
  
  6. Análisis de resultados:	
  
* Objetivo: Crear sus propios personajes en sprites con una animación basica de movimiento en horizontal.  
  Condición: Completado.  
  Proceso: Cada uno diseñó su propio personaje y lo realizamos en sprites en la página Piskel.  
   
* Objetivo: Se debe pintar todo el laberinto, debe permitir movimientos en vertical y horizontal.  
  Condición: Completado.  
  Proceso: Se diseñó el mapa en el programa Tiled y luego se procedió a implementar cada sprite en una matriz en el código.     
   
* Objetivo: Crear las estructuras matriciales para cargar los sprites de las animaciones.  
  Condición: Completado.  
  Proceso: Existe una estructura dentro del programa encargada de multiplicar los valores del rectángulo de los personajes por 32 por cada segundo transcurrido.
  
* Objetivo: Crear las estructuras de listas para manejar la matriz de animación.  
  Condición: Completado.  
  Proceso: Se usaron estructuras de listas encargadas de controlar los valores del rectángulo por segundo transcurrido para dar la animación.  
   
* Objetivo: Se debe tener las estructruras para el manejo de pintado del laberinto.  
  Condición: Completado.  
  Proceso: Se creó un método que recorre la matriz para saber qué sprite del mapa debe pintar.  
   
* Objetivo: Se debe manejar la lista de las ubicaciones de las recompenzas.  
  Condición: Completado.
  Proceso: 
   
* Objetivo: Generar sonidos al morir el personaje y al cargar el personaje.  
  Condición: Completado.  
  Proceso: En el proceso en el cual el personaje pierde una vida se programó para que emita el sonido. Y en el inicializador del juego se programó el sonido que se emite al cargar el personaje.  
   
* Objetivo: Crear la historia del juego.  
  Condición: Completado.  
  Proceso: Se decidió entre los cuatro desarrolladores cuál sería la historia del juego, adecuada para el mapa y personajes diseñados.  
   
* Objetivo: Tener un manejo básico de vida dentro del juego, al menos tres vidas.  
  Condición: Completado.  
  Proceso: Se creó una función para mostrar en pantalla la cantidad de vidas restantes, además, hay una variable que define si ya se acabaron.  
   
* Objetivo: Se debe utilizar al menos matrices, arreglos, listas con apuntadores dinámicos, pueden ser simples, dobles, pilas o colas.  
  Condición: Completado.  
  Proceso: Para el desarrollo del juego se utilizaron las estructuras propuestas, por ejemplo, las matrices, listas y apuntadores dinámicos.  

* Objetivo: Se debe tener la animación de los cuatro personajes.  
  Condición: Completado.  
  Proceso: Se creó una estructura que puede controlar la animación del personaje que se mostrará en pantalla al jugar, la misma funciona para los cuatro personajes.  

* Objetivo: Cuando una recompensa es alcanzada se emite un sonido.  
  Condición: Completado.  
  Proceso: En la función que genera el mapa, se programó la interacción con las recompensas, y ahí se genera un sonido.  
   
* Objetivo: Al morir se emite un sonido.  
  Condición: Completado.  
  Proceso: En la función de colisión con el enemigo se programó que cuando el personaje pierde sus tres vidas se reproduce el sonido de muerte definitiva.  
  
*Objetivo:
   
