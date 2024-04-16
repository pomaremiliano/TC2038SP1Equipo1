¿Qué tengo que hacer?

En equipos de máximo 3 personas, escribe un programa en C++ que lea 5 archivos de texto (de nombre fijo, no se piden al usuario) que contienen exclusivamente caracteres del 0 al 9, caracteres entre A y F y saltos de línea.

Los archivos de transmisión contienen caracteres de texto que representan el envío de datos de un dispositivo a otro.

    transmission1.txt
    transmission2.txt

Los archivos mcodex.txt representan código malicioso que se puede encontrar dentro de una transmisión.

    mcode1.txt
    mcode2.txt
    mcode3.txt

El programa debe analizar si el contenido de los archivos mcode1.txt, mcode2.txt y mcode3.txt están contenidos en los archivos transmission1.txt y transmission2.txt y desplegar un true o false si es que las secuencias de chars están contenidas o no. En caso de ser true, muestra true, seguido de exactamente un espacio, seguido de la posición en el archivo de transmissiónX.txt donde inicia el código de mcodeY.txt.

Suponiendo que el código malicioso tiene siempre código "espejeado" (palíndromos de chars), sería buena idea buscar este tipo de código en una transmisión. El programa después debe buscar si hay código "espejeado" dentro de los archivos de transmisión. (palíndromo a nivel chars, no meterse a nivel bits). El programa muestra en una sola línea dos enteros separados por un espacio correspondientes a la posición (iniciando en 1) en donde inicia y termina el código "espejeado" más largo (palíndromo) para cada archivo de transmisión. Puede asumirse que siempre se encontrará este tipo de código.

Finalmente el programa analiza qué tan similares son los archivos de transmisión, y debe mostrar la posición inicial y la posición final (iniciando en 1) del primer archivo en donde se encuentra el substring más largo común entre ambos archivos de transmisión.
Input

Nada, solamente deben existir los 5 archivos en la misma ruta donde se ejecuta el programa.
Output
Parte 1

    (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode1.txt.
    (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode2.txt.
    (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode3.txt.
    (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode1.txt.
    (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode2.txt.
    (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode3.txt.

Para cada caso true, muestra true, seguido de exactamente un espacio, seguido de la posición en el archivo de transmissiónX.txt donde inicia el código de mcodeY.txt.
Parte 2

    posiciónInicial posiciónFinal (para archivo de transmisión1)
    posiciónInicial posiciónFinal (para archivo de transmisión2)

Parte 3

    posiciónInicial posiciónFinal (de substring común más largo entre archivos de transmisión)

[Casos de Prueba](https://drive.google.com/drive/folders/1PiWn6hhoIb8Iu1MsnGhMyo34-2EjMf9h)

