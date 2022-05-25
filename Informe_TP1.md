# **Sistemas Embebidos**
## **Trabajo Práctico N° 1: Diagrama de Estado**
### **Integrantes:**

Villacampa Horta Augusto - 102602

## **Instalación y pasos previos**

En este trabajo se pretende aprender sobre la utilización de diagramas de estados y su codificación con la extensión de Yakindu.
Para esto se requiere:

-Poseer una placa de desarrollo EDU-CIAA

-Haber instalado la IDE Eclipse

-Haber instalado y licenciado la extensión de Yakindu para Eclipse

-Haber agregado la carpeta firmware_v3 que contiene todos los archivos necesarios

Teniendo todo esto es necesario configurar la IDE Eclipse para la placa de desarrollo, para poder compilar, cargar y depurar los programas.
En este paso es importante aclarar que se requieren varias herramientas y procedimientos para lograr que todo funcione correctamente ya que no existe un instalador que sirva de forma universal para todos los equipos. Esto lleva a que lo mas común sea encontrarse con muchos problemas y errores a lo largo de la instalación aún siguiendo el instructivo provisto. Además, a la hora de instalar la extensión de Yakindu fue necesario usar una versión antigua por problemas de compatibilidad.

Para probar que todo funcione se carga en la placa alguno de los programas de ejemplo con diagramas de estado que se encuentran en la carpeta de firmware_v3. En este punto se encontraron también algunos problemas. Lo primero es que la placa debe estar conectada siempre al mismo puerto, que previamente tuvo que ser configurado manualmente con Zadig, incluido en el launcher. Además se encontró un problema a la hora de cargar el programa en la placa por un error con libusb_open(). Para solucionarlo se tiene que usar el depurador para cargar el programa y luego reiniciar la placa cada vez que se carga un nuevo programa. Además el depurador también tuvo que ser configurado previamente para funcionar con esta placa específica y se le debe indicar cada vez el programa que debe cargar.

Habiendo verificado que se logra cargar programas en la placa se pueden probar y analizar los distintos ejemplos incluidos en firmware_v3 sobre Statecharts con Yakindu.

## **Ejemplos**

### **1) 1_toggle**
### **2) 2_blink**
### **3) 3_idleBlink**
### **4) 4_buttons**
### **5) 5_application**
