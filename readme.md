# **Sistemas Embebidos**
## **Trabajo Pr�ctico N� 1: Diagrama de Estado**
### **Integrantes:**

Villacampa Horta Augusto - 102602

Strusberg Agustin Javier - 102809

## **Instalaci�n y pasos previos**

En este trabajo se pretende aprender sobre la utilizaci�n de diagramas de estados y su codificaci�n con la extensi�n de Yakindu.
Para esto se requiere:

-Poseer una placa de desarrollo EDU-CIAA

-Haber instalado la IDE Eclipse

-Haber instalado y licenciado la extensi�n de Yakindu para Eclipse

-Haber agregado la carpeta firmware_v3 que contiene todos los archivos necesarios

Teniendo todo esto es necesario configurar la IDE Eclipse para la placa de desarrollo, para poder compilar, cargar y depurar los programas.
En este paso es importante aclarar que se requieren varias herramientas y procedimientos para lograr que todo funcione correctamente ya queno existe un instalador que sirva de forma universal para todos los equipos. Esto lleva a que lo mas com�n sea encontrarse con muchos problemas y errores a lo largo de la instalaci�n a�n siguiendo el instructivo provisto. Adem�s, a la hora de instalar la extensi�n de Yakindu fue necesario usar una versi�n antigua por problemas de compatibilidad.

Para probar que todo funcione se carga en la placa alguno de los programas de ejemplo con diagramas de estado que se encuentran en la carpeta de firmware_v3. Para esto primero hay que generar los archivos necesarios a partir del diagrama de estados, usando el archivo .sgen. En este punto se encontraron tambi�n algunos problemas. Lo primero es que la placa debe estar conectada siempre al mismo puerto, que previamente tuvo que ser configurado manualmente con Zadig, incluido en el launcher. Adem�s se encontr� un problema a la hora de cargar el programa en la placa por un error con libusb_open(). Para solucionarlo se tiene que usar el depurador para cargar el programa y luego reiniciar la placa cada vez que se carga un nuevo programa. Adem�s el depurador tambi�n tuvo que ser configurado previamente para funcionar con esta placa espec�fica y se le debe indicar cada vez el programa que debe cargar.

Habiendo verificado que se logra cargar programas en la placa se pueden probar y analizar los distintos ejemplos incluidos en firmware_v3 sobre Statecharts con Yakindu.

## **Ejemplos**

### **1) 1_toggle**

En la siguiente figura se puede ver el diagrama de estados de este ejemplo:

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/f897da6e268a53f12ab5f560db75fdd0fcc3e73c/Statechart%201%20-%20Toggle/1_toggle/Statechart_toogle.png)

Este es el ejemplo m�s simple, en donde cada ciclo de la m�quina de estados dispara un evento que cambia el estado de un LED. Dada la alta frecuencia en la ejecuci�n de los ciclos de la m�quina no puede apreciarse este cambio, y se ve siempre al LED encendido. Para ver estos cambios lo que se puede hacer es entrar en modo depuraci�n con un breackpoint antes de hacer el cambio de estado en el LED, y realizar cada ciclo de la m�quina manualmente.

El c�digo principal del programa se encuentra en el archivo main.c, y es en este en donde se realizar�n las iteraciones de la m�quina de estados. Este archivo incluye Toggle.h, que tiene las definiciones de las funciones incluidas en Toggle.c. Estos 2 �ltimos archivos son los generados a partir del diagrama de estados, por lo que es importante reemplazarlos cada vez que se hagan cambios en el diagrama. Continuando con el archivo main.c, y dentro de la funci�n main propiamente dicha, lo primero que hace es inicializar la placa con boardConfig(), incluida en sapi_board.h. Luego configura la frecuencia del contador de tiempo en 1000 ticks por segundo con tickConfig(), de sapi_tick.c. Despu�s se usa tickCallbackSet(), tambi�n de sapi_tick.c para definir la rutina de interrupci�n a utilizar, en este caso es myTickHook(), definida m�s arriba en el c�digo, que solo activa un flag. Para terminar la configuraci�n se inicializa el vector de estados en cero y se limpian los eventos con toggle_init() y finalmente se entra en la m�quina de estados con toggle_enter(), ambas incluidas en Toggle.c.

Ahora se entra en la parte del loop del programa con un while(1). Dentro de este ciclo infinito lo primero que se hace es dormir al microcontrolador con \_\_WFI() a la espera de una interrupci�n, que en este caso se da por tiempo, 1000 veces por segundo. Cuando se detecta una interrupci�n primero se eval�a qu� flag se encuantra activo. En este caso solo puede ser el de tiempo, y cuando se valida que se trata de este flag se ejecuta la rutina deseada. En este caso lo primero es desactivar el flag, luego activar el evento correspondiente para la m�quina de estados con toggleIface_raise_evTick() y finalmente se corre un ciclo de la m�quina con toggle_runCycle(), que actuar� seg�n los eventos que se hayan activado. Terminado el ciclo el microcontrolador vuelve a dormir a la espera de la siguiente interrupci�n. Las �ltimas 2 funciones usadas se encuentran en Toggle.c.

Dentro de la funci�n que ejecuta un ciclo de la m�quina primero se limpian los eventos salientes (en este caso esta funci�n no hace nada) y luego se ejecuta un ciclo for que eval�a los elementos del vector de estados con un switch y act�a seg�n se programe cada uno. Finalmente limpia los eventos entrantes y termina el ciclo.

En esta m�quina de estados lo que sucede en cada ciclo es que ante el evento evTick la m�quina sale y entra al mismo estado, ejecutando la funci�n opLED() cada vez que entra al estado. Esta funci�n es la que se encarga de realizar el toggle.

### **2) 2_Myblink**

Este programa es una modificacion del codigo buttons para hacer titilar a un led. Se modific� el statechart para que si se mantiene precionado el boton, el led parpadee en vez de mantenerse prendido. Esto se hizo modificando la funci�n opLED, que se ejecuta siempre que se este en el estado "presionado". Al dejar de presionar el boton, se sale de este estado y el LED deja de titilar. En la siguiente figura se puede ver el Statechart en este caso:

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/6a17ae763e51efb54b4839195d13bad011812b2f/Statechart%202%20-%20Myblink/6_mi_prueba/Statechart_myblink.png)

En este caso la m�quina comienza en el estado NO_OPRIMIDO. Cuando se presiona el pulsador se pasa al estado DEBOUNCE, se espera 100ms y luego se entra al estado VALIDACION. Si luego de ese tiempo el pulsador no est� presionado se vuelve al estado inicial, de otra forma se sigue al estado PRESIONADO y se ejecutan las funciones correspondientes. Primero se ejecuta valueof() que devuelve el estado de los botones. Luego entra en un loop always que ejecuta opLED(). Esta funci�n realiza un toggle del LED y espera 500ms. Luego vuelve a ejecutarse por estar en un ciclo always. La forma de salir es dejar de presionar el pulsador, que es el evento que lleva a la m�quina al estado NO_OPRIMIDO nuevamente.

### **3) 3_idleBlink**
En la siguiente figura se muestra la m�quina de estados de este ejemplo:

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/6a17ae763e51efb54b4839195d13bad011812b2f/Statechart%203%20-%20idleBlink/3_idleBlink/Statechart_idleblink.png)

En este caso la m�quina comienza en el estado REPOSO, que ejecuta la funci�n opLED(LED3, LED_OFF), es decir que apaga un LED si este estuviera encendido. Luego de 3000ms se dispara un evento que lleva a un estado anidado llamado TITILA, que comienza en el estado APAGADO y ejecuta la misma funci�n de apagado del LED. Pasados 250ms se pasa al estado ENCENDIDO que enciende el LED, y vuelve al estado anterior luego de 500ms, apagando el LED. Esto sucede hasta que pasados 5000ms se sale del estado anidado y se apaga el LED.

### **4) 4_buttons**
En este proyecto se usa para leer el estado de los botones. Su diagrama de estados es el siguiente. 

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/6a17ae763e51efb54b4839195d13bad011812b2f/Statechart%204%20-%20buttons/4_buttons/Statechart_buttons.png)

Al iniciar, se espera en el estado NO_OPRIMIDO. Cuando se presiona un boton, se levanta el evento evTECXOprimido indicando de que hay un boton presionado, se mueve al estado DEBOUNCE y luego se espera un tiempo. Luego de ese tiempo se mueve al estado VALIDACI�N para preguntar si sigue el mismo evento levantado. En caso de no haber un boton presionado, el evento evTECXNoOprimido estar� en alto y se volvera al estado inicial. Si el evento evTECXOprimido sigue levantado se acepta que se presion� un boton, se mueve al estado OPRIMIDO y se cambia el estado del LED3 una vez. Luego se permanece en este estado hasta que no haya un boton presionado y se levante el evento evTECXNoOprimido, donde se vuelve al estado inicial.

### **5) 5_application**
En la siguiente figura se muestra la máquina de estados de este ejemplo.

![Stetechart del Toggle](https://github.com/aguStrus/TP1---Sistemas-Embebidos/blob/6a17ae763e51efb54b4839195d13bad011812b2f/Statechart%205%20-%20application/5_application/Statechart_aplication.png)

Esta es la máquina de estados más compleja, ya que tiene 3 máquinas que funcionan en paralelo. La primera comienza en el estado NO_OPRIMIDO, que no ejecuta nada. Lo mismo sucede con la segunda que empieza en el estado ESPERA, que tampoco ejecuta nada. La tercera comienza en REPOSO que ejecuta la función opLED() para apagar el LED. 

La única manera de modificar los estados es oprimir un botón, que disparará un evento en la primera máquina de estados llevándola al estado DEBOUNCE y luego VALIDACION, de la misma manera que en los ejemplos 2 y 4. Cuando llega al estado OPRIMIDO levanta el evento siTECXOK y luego guarda el estado de los pulsadores con valueof(). El evento siTECXOK sirve como disparador de un cambio de estado en la segunda máquina. Este evento funciona en realidad como 4 eventos que se disparan por prioridad. En cada uno lo primero que se hace es evaluar el estado de los botones para saber cuál se preiosnó, con lo que solo ejecutará el código correspondiente al botón presionado.

En el caso de presionar TEC1 ejecuta la función opLED() 3 veces apagando los 3 LEDs, y luego levanta el evento siNoTitilarLED, para la tercera máquina de estados. En caso de presionar TEC2 o TEC3 se ejecutará opLED() para encender LED1 o LED2 respectivamente. Si se presiona TEC4 se levanta el estado siTitilarLED para la tercera máquina de estados. Luego de terminar cualquiera de estas ejecuciones la segunda máquina de estados vuelve al estado ESPERAR.

La tercera máquina de estados solo puede salir de RESPOSO ante el evento siTitilarLED, que lo lleva a un estado anidado llamado TITILA. Este estado anidado funciona igual que en el ejemplo 3, con la diferencia que la forma de salir es ante el evento siNoTitilarLED.

### **6) Proyecto nuestro**
