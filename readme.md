# **Sistemas Embebidos**
## **Trabajo Práctico N° 1: Diagrama de Estado**
### **Integrantes:**

Villacampa Horta Augusto - 102602

Strusberg Agustin Javier - 102809

## **Instalación y pasos previos**

En este trabajo se pretende aprender sobre la utilización de diagramas de estados y su codificación con la extensión de Yakindu.
Para esto se requiere:

-Poseer una placa de desarrollo EDU-CIAA

-Haber instalado la IDE Eclipse

-Haber instalado y licenciado la extensión de Yakindu para Eclipse

-Haber agregado la carpeta firmware_v3 que contiene todos los archivos necesarios

Teniendo todo esto es necesario configurar la IDE Eclipse para la placa de desarrollo, para poder compilar, cargar y depurar los programas.
En este paso es importante aclarar que se requieren varias herramientas y procedimientos para lograr que todo funcione correctamente ya queno existe un instalador que sirva de forma universal para todos los equipos. Esto lleva a que lo mas común sea encontrarse con muchos problemas y errores a lo largo de la instalación aún siguiendo el instructivo provisto. Además, a la hora de instalar la extensión de Yakindu fue necesario usar una versión antigua por problemas de compatibilidad.

Para probar que todo funcione se carga en la placa alguno de los programas de ejemplo con diagramas de estado que se encuentran en la carpeta de firmware_v3. Para esto primero hay que generar los archivos necesarios a partir del diagrama de estados, usando el archivo .sgen. En este punto se encontraron también algunos problemas. Lo primero es que la placa debe estar conectada siempre al mismo puerto, que previamente tuvo que ser configurado manualmente con Zadig, incluido en el launcher. Además se encontró un problema a la hora de cargar el programa en la placa por un error con libusb_open(). Para solucionarlo se tiene que usar el depurador para cargar el programa y luego reiniciar la placa cada vez que se carga un nuevo programa. Además el depurador también tuvo que ser configurado previamente para funcionar con esta placa específica y se le debe indicar cada vez el programa que debe cargar.

Habiendo verificado que se logra cargar programas en la placa se pueden probar y analizar los distintos ejemplos incluidos en firmware_v3 sobre Statecharts con Yakindu.

## **Ejemplos**

### **1) 1_toggle**

En la siguiente figura se puede ver el diagrama de estados de este ejemplo:

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/f897da6e268a53f12ab5f560db75fdd0fcc3e73c/Statechart%201%20-%20Toggle/1_toggle/Statechart_toogle.png)

Este es el ejemplo más simple, en donde cada ciclo de la máquina de estados dispara un evento que cambia el estado de un LED. Dada la alta frecuencia en la ejecución de los ciclos de la máquina no puede apreciarse este cambio, y se ve siempre al LED encendido. Para ver estos cambios lo que se puede hacer es entrar en modo depuración con un breackpoint antes de hacer el cambio de estado en el LED, y realizar cada ciclo de la máquina manualmente.

El código principal del programa se encuentra en el archivo main.c, y es en este en donde se realizarán las iteraciones de la máquina de estados. Este archivo incluye Toggle.h, que tiene las definiciones de las funciones incluidas en Toggle.c. Estos 2 últimos archivos son los generados a partir del diagrama de estados, por lo que es importante reemplazarlos cada vez que se hagan cambios en el diagrama. Continuando con el archivo main.c, y dentro de la función main propiamente dicha, lo primero que hace es inicializar la placa con boardConfig(), incluida en sapi_board.h. Luego configura la frecuencia del contador de tiempo en 1000 ticks por segundo con tickConfig(), de sapi_tick.c. Después se usa tickCallbackSet(), también de sapi_tick.c para definir la rutina de interrupción a utilizar, en este caso es myTickHook(), definida más arriba en el código, que solo activa un flag. Para terminar la configuración se inicializa el vector de estados en cero y se limpian los eventos con toggle_init() y finalmente se entra en la máquina de estados con toggle_enter(), ambas incluidas en Toggle.c.

Ahora se entra en la parte del loop del programa con un while(1). Dentro de este ciclo infinito lo primero que se hace es dormir al microcontrolador con \_\_WFI() a la espera de una interrupción, que en este caso se da por tiempo, 1000 veces por segundo. Cuando se detecta una interrupción primero se evalúa qué flag se encuantra activo. En este caso solo puede ser el de tiempo, y cuando se valida que se trata de este flag se ejecuta la rutina deseada. En este caso lo primero es desactivar el flag, luego activar el evento correspondiente para la máquina de estados con toggleIface_raise_evTick() y finalmente se corre un ciclo de la máquina con toggle_runCycle(), que actuará según los eventos que se hayan activado. Terminado el ciclo el microcontrolador vuelve a dormir a la espera de la siguiente interrupción. Las últimas 2 funciones usadas se encuentran en Toggle.c.

Dentro de la función que ejecuta un ciclo de la máquina primero se limpian los eventos salientes (en este caso esta función no hace nada) y luego se ejecuta un ciclo for que evalúa los elementos del vector de estados con un switch y actúa según se programe cada uno. Finalmente limpia los eventos entrantes y termina el ciclo.

En esta máquina de estados lo que sucede en cada ciclo es que ante el evento evTick la máquina sale y entra al mismo estado, ejecutando la función opLED() cada vez que entra al estado. Esta función es la que se encarga de realizar el toggle.

### **2) 2_Myblink**

Este programa es una modificacion del codigo buttons para hacer titilar a un led. Se modificó el statechart para que si se mantiene precionado el boton, el led parpadee en vez de mantenerse prendido. Esto se hizo modificando la función opLED, que se ejecuta siempre que se este en el estado "presionado". Al dejar de presionar el boton, se sale de este estado y el LED deja de titilar. En la siguiente figura se puede ver el Statechart en este caso:

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/6a17ae763e51efb54b4839195d13bad011812b2f/Statechart%202%20-%20Myblink/6_mi_prueba/Statechart_myblink.png)

En este caso la máquina comienza en el estado NO_OPRIMIDO. Cuando se presiona el pulsador se pasa al estado DEBOUNCE, se espera 100ms y luego se entra al estado VALIDACION. Si luego de ese tiempo el pulsador no está presionado se vuelve al estado inicial, de otra forma se sigue al estado PRESIONADO y se ejecutan las funciones correspondientes. Primero se ejecuta valueof() que devuelve el estado de los botones. Luego entra en un loop always que ejecuta opLED(). Esta función realiza un toggle del LED y espera 500ms. Luego vuelve a ejecutarse por estar en un ciclo always. La forma de salir es dejar de presionar el pulsador, que es el evento que lleva a la máquina al estado NO_OPRIMIDO nuevamente.

### **3) 3_idleBlink**
En la siguiente figura se muestra la máquina de estados de este ejemplo:

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/6a17ae763e51efb54b4839195d13bad011812b2f/Statechart%203%20-%20idleBlink/3_idleBlink/Statechart_idleblink.png)

En este caso la máquina comienza en el estado REPOSO, que ejecuta la función opLED(LED3, LED_OFF), es decir que apaga un LED si este estuviera encendido. Luego de 3000ms se dispara un evento que lleva a un estado anidado llamado TITILA, que comienza en el estado APAGADO y ejecuta la misma función de apagado del LED. Pasados 250ms se pasa al estado ENCENDIDO que enciende el LED, y vuelve al estado anterior luego de 500ms, apagando el LED. Esto sucede hasta que pasados 5000ms se sale del estado anidado y se apaga el LED.

### **4) 4_buttons**
En este proyecto se usa para leer el estado de los botones. Su diagrama de estados es el siguiente. 

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/6a17ae763e51efb54b4839195d13bad011812b2f/Statechart%204%20-%20buttons/4_buttons/Statechart_buttons.png)

Al iniciar, se espera en el estado NO_OPRIMIDO. Cuando se presiona un boton, se levanta el evento evTECXOprimido indicando de que hay un boton presionado, se mueve al estado DEBOUNCE y luego se espera un tiempo. Luego de ese tiempo se mueve al estado VALIDACIÓN para preguntar si sigue el mismo evento levantado. En caso de no haber un boton presionado, el evento evTECXNoOprimido estará en alto y se volvera al estado inicial. Si el evento evTECXOprimido sigue levantado se acepta que se presionó un boton, se mueve al estado OPRIMIDO y se cambia el estado del LED3 una vez. Luego se permanece en este estado hasta que no haya un boton presionado y se levante el evento evTECXNoOprimido, donde se vuelve al estado inicial.

### **5) 5_application**
En la siguiente figura se muestra la mÃ¡quina de estados de este ejemplo.

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/6a17ae763e51efb54b4839195d13bad011812b2f/Statechart%205%20-%20application/5_application/Statechart_aplication.png)

Esta es la mÃ¡quina de estados mÃ¡s compleja, ya que tiene 3 mÃ¡quinas que funcionan en paralelo. La primera comienza en el estado NO_OPRIMIDO, que no ejecuta nada. Lo mismo sucede con la segunda que empieza en el estado ESPERA, que tampoco ejecuta nada. La tercera comienza en REPOSO que ejecuta la funciÃ³n opLED() para apagar el LED. 

La Ãºnica manera de modificar los estados es oprimir un botÃ³n, que dispararÃ¡ un evento en la primera mÃ¡quina de estados llevÃ¡ndola al estado DEBOUNCE y luego VALIDACION, de la misma manera que en los ejemplos 2 y 4. Cuando llega al estado OPRIMIDO levanta el evento siTECXOK y luego guarda el estado de los pulsadores con valueof(). El evento siTECXOK sirve como disparador de un cambio de estado en la segunda mÃ¡quina. Este evento funciona en realidad como 4 eventos que se disparan por prioridad. En cada uno lo primero que se hace es evaluar el estado de los botones para saber cuÃ¡l se preiosnÃ³, con lo que solo ejecutarÃ¡ el cÃ³digo correspondiente al botÃ³n presionado.

En el caso de presionar TEC1 ejecuta la funciÃ³n opLED() 3 veces apagando los 3 LEDs, y luego levanta el evento siNoTitilarLED, para la tercera mÃ¡quina de estados. En caso de presionar TEC2 o TEC3 se ejecutarÃ¡ opLED() para encender LED1 o LED2 respectivamente. Si se presiona TEC4 se levanta el estado siTitilarLED para la tercera mÃ¡quina de estados. Luego de terminar cualquiera de estas ejecuciones la segunda mÃ¡quina de estados vuelve al estado ESPERAR.

La tercera mÃ¡quina de estados solo puede salir de RESPOSO ante el evento siTitilarLED, que lo lleva a un estado anidado llamado TITILA. Este estado anidado funciona igual que en el ejemplo 3, con la diferencia que la forma de salir es ante el evento siNoTitilarLED.

### **6) Proyecto nuestro**
