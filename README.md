# Universidad del Valle de Guatemala <br />Sistemas Operativos <br /> Adrian Fulladolsa - 21592


## Laboratorio 1
Descripción: en este laboratorio se realizarán ejercicios para reforzar los conceptos de llamadas de
sistema e introducir de manera práctica el concepto de proceso. Estos ejercicios requerirán programación
en C. Se explicarán algunas instrucciones y métodos de trabajo usados con C, pero se recomienda
profundizar e investigar sobre el lenguaje puesto que lo seguiremos usando durante el curso.

<details><summary>Ejercicio 1</summary>
    <ul>

<li><details> <summary>A</summary>
         Al ejecutar el programa compilado:   <code>ej1A</code>  se obtiene lo siguiente:
 
        Hello World!
        31522
</details></li>
    <li><details> <summary>B</summary>
       El ejecutar el programa compilado: <code>ej1B</code> se obtiene lo siguiente:
        
        31524
        Hello World!
        31525
        Hello World!
        31524
</details></li>
    <li><details> <summary>C</summary>
    <ul>
    <li>Compile el primer programa y ejecútelo varias veces. Responda: ¿por qué aparecen números diferentes cada vez? 

<details><summary>R/ </summary>
    
    Cada ejecución del programa ej1A crea un nuevo proceso al cual el Sistema Operativo le asigna un PID único. 
</details>        
</li>
    <li>
    Proceda a compilar el segundo programa y ejecútelo una vez. ¿Por qué aparecen dos números distintos a pesar de que estamos ejecutando un único programa?

<details><summary>R/ </summary>

    Al ejecutar el segundo programa se obtienen un total de tres números, en mi caso el primero y el tercero son el mismo número mientras que el segundo es distinto. 

    Esto se debe al uso de la función fork() la cual crea un proceso hijo el cual ejecuta de manera concurrente la instrucción siguiente al llamado de la función.

    Dado esto, podemos entender que uno de los números es el PID del proceso padre y el otro número es el PID del proceso hijo.
    
</details></li>
    <li>¿Por qué el primer y el segundo números son iguales?

<details><summary>R/ </summary>
    
    En mi caso, el primer y el tercer número son iguales y el segundo es distinto.
    Este comportamiento se debe a la ejecución concurrente del proceso padre y el proceso hijo.

    El primer número mostrado por la función printf del else muestra el PID del proceso padre.

    El segundo número mostrado por la función printf ejecutada bajo la función execl es ejecutada dentro del proceso hijo por lo que tiene un PID con un número mayor al del proceso padre.

    Por último, el tercer número mostrado es el retorno al proceso padre para que dentro de este se ejecute el execl que nos muestra el primer PID.
</details></li>
    <li>En la terminal, ejecute el comando top (que despliega el top de procesos en cuanto a consumo de CPU) y note cuál es el primer proceso en la lista (con identificador 1). ¿Para qué sirve este proceso?
<details><summary>R/ </summary>

    El proceso con el PID 1 corresponde al proceso systemd, este proceso el el encargado de manejar el sistema y los servicios de Linux. Sus funciones incluyen las de manejar los procesos del usuario y el bootstrap del espacio de usuario.
</details></li>
    </ul>
    </details>
</details>


<details><summary>Ejercicio 2</summary>
    <ul>
    <li><details> <summary>A</summary>
    </details></li>
    <li><details> <summary>B</summary>
    </details></li>
    <li><details> <summary>C</summary>
    </details></li>
    <li><details> <summary>D</summary>
    </details></li>
</ul></details>



<details><summary>Ejercicio 3</summary>
    <ul>
    <li><details> <summary>A</summary>
    </details></li>
    <li><details> <summary>B</summary>
    </details></li>
    <li><details> <summary>C</summary>
    </details></li>
    <li><details> <summary>D</summary>
    </details></li>
    <li><details> <summary>E</summary>
    </details></li>
    <li><details> <summary>F</summary>
    </details></li>
    <li><details> <summary>E</summary>
    </details></li>
    <li><details> <summary>G</summary>
    </details></li>
    <li><details> <summary>H</summary>
    </details></li>
</ul></details>
