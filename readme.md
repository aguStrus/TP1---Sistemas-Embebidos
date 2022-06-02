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

Ahora se entra en la parte del loop del programa con un while(1). Dentro de este ciclo infinito lo primero que se hace es dormir al microcontrolador con \_\_WFI() a la espera de una interrupción, que este caso se da por tiempo, 1000 veces por segundo. Cuando se detecta una interrupción primero se evalúa qué flag se encuantra activo. En este caso solo puede ser el de tiempo, y cuando se valida que se trata de este flag se ejecuta la rutina deseada. En este caso lo primero es desactivar el flag, luego activar el evento correspondiente para la máquina de estados con toggleIface_raise_evTick() y finalmente se corre un ciclo de la máquina con toggle_runCycle(), que actuará según los eventos que se hayan activado. Terminado el ciclo el microcontrolador vuelve a dormir a la espera de la siguiente interrupción. Las últimas 2 funciones usadas se encuentran en Toggle.c.

Dentro de la función que ejecuta un ciclo de la máquina primero se limpian los eventos salientes (en este caso esta función no hace nada) y luego se ejecuta un ciclo for que evalúa los elementos del vector de estados con un switch y actúa según se programe cada uno. Finalmente limpia los eventos entrantes y termina el ciclo.

### **2) 2_Myblink**

Este programa es una modificacion del codigo buttons para hacer titilar a un led. Se modificó el statechart para que si se mantiene precionado el boton, el led parpadee en vez de mantenerse prendido. Esto se hizo modificando la función opLED, que se ejecuta siempre que se este en el estado "presionado". Al dejar de presionar el boton, se sale de este estado y el LED deja de titilar.

### **3) 3_idleBlink**

### **4) 4_buttons**
HOLA
### **5) 5_application**
### **6) Proyecto nuestro**
