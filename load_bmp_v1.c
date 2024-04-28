//BITMAP LOADER BY TSW 2011. V1.0 Writing on VIDEO MEMORY
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Code for Borland Turbo C++ 3.0
//------------------------------------------------------
#include <graphics.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>   //LIBRERIAS
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <math.h>
 
informacion(); //subprograma cabecera
 
main()
{
//SUBPROGRAMA INFORMACION
 
    clrscr();
    cout << "BITMAP LOADER 1.0 BY TSWn";
 
    char *fil = "c:\nuevo1.bmp"; //aquí la ruta de tu archivo, no olvides poner DOBLE BARRA \ ,te recomiendo ponerlo en c: raiz el archivo.
    FILE *archivo;
    archivo = fopen(fil,"rb"); //binario
 
    if(archivo == NULL )
    printf("ERROR GRAVE !!! NO SE HA PODIDO ABRIR EL ARCHIVO!!!n");
    if (archivo)
        printf("ARCHIVO ABIERTO CON XITO !!!n");
 
cout << "Ruta de Archivo " << fil ;
cout << "n---------------------------------------n";
cout << "INFORMACIàN DE CABECERA ARCHIVO BMP n";
cout << "---------------------------------------n";
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
long tamano;
long offset;
long ancho;       //nombro variables
long alto;
int planos;
int bpp;
long compresion;
long tamanoBmpPixel;
long NumColores;
char tipo[1]; //Tipo BMP ( Microsoft,OS/2...)
 
tamano = 0;
offset = 0;
ancho = 0;       //inicializo variables para que no tomen valores extra¤os
alto= 0;
planos= 0;
bpp= 0;
compresion= 0;
tamanoBmpPixel= 0;
NumColores= 0;
 
 
fseek(archivo,0L,SEEK_SET); //Tipo de bmp
   fread(tipo,1,2,archivo);
   printf("þ     Tipo de BMP   = %s n",tipo);

 
fseek(archivo,2L,SEEK_SET); //---tama¤o archivo bmp
     fread(&tamano,1,4,archivo);
     printf("þ     Tama¤o de BMP = %lu Bytesn",tamano);
 
fseek(archivo,10L,SEEK_SET); //----offset archivo
     fread(&offset,1,4,archivo);
     printf("þ     Offset BMP    = %d (Datos im gen empiezan en este byte)n",offset);
 
 
fseek(archivo,18L,SEEK_SET); //----ancho archivo
    fread(&ancho,1,4,archivo); //guardo en &ancho, 1 registro de 4 bytes.
    printf("þ     Ancho de BMP  = %dn",ancho);
 
fseek(archivo,22L,SEEK_SET); //----alto bmp
    fread(&alto,1,4,archivo);
    printf("þ     Alto de BMP   = %dn",alto);
 
fseek(archivo,26L,SEEK_SET); //----numero de planos
    fread(&planos,1,2,archivo);
    printf("þ     Numero de planos BMP = %dn",planos);
 
fseek(archivo,28L,SEEK_SET); //----bit por pixel ( 256 colores 8 bit)
    fread(&bpp,1,2,archivo);
    printf("þ     Bit por pixel (BPP) = %dn",bpp);
 
fseek(archivo,30L,SEEK_SET); //----compresion archivo bmp
    fread(&compresion,1,2,archivo);
    printf("þ     ¨Existe compresi¢n? (0->NO) = %dn",compresion);
 
fseek(archivo,34L,SEEK_SET); //---cantidad en pixel
    fread(&tamanoBmpPixel,1,4,archivo);
    printf("þ     Tama¤o im gen %lu pixelesn",tamanoBmpPixel);
 
fseek(archivo,46L,SEEK_SET); //--- numero colores bmp
    fread(&NumColores,1,4,archivo);
    printf("þ     N£mero de colores de im gen %dn",NumColores);
 
cout << "n";
cout << "PULSE UNA TECLA PARA MOSTRAR EL BMP EN PANTALLA";
getch();
 
long  rojo,verde,azul,contador;
long  dato,cuenta_colores;
long  valorLetra;
int   valor;    //con INT SALE MAS COLOR original CHAR
int r,v,a,c;
r = 0; 
v = 0; 
a = 0; 
c = 0;
valor = 0;
valorLetra = 0;
cuenta_colores = 0;
contador =  0;
dato =  0;
 
    asm{
      mov ah,0
      mov al,13h
      int 10h
    }
 
 
    fseek(archivo,54L,SEEK_SET); //--- numero colores bmp ( Cargo Paleta Colores )
    do
    {
 
        outportb(0x3c8,cuenta_colores);
        fread(&valor,1,1,archivo);
           valorLetra = valor;
           azul = abs(valorLetra /4);   
           valorLetra = 0;
           a = azul;
 
        fread(&valor,1,1,archivo);
          valorLetra = valor;
          verde = abs(valorLetra/4 );
          valorLetra = 0;
          v = verde;
 
        fread(&valor,1,1,archivo);
           valorLetra = valor;
           rojo = abs(valorLetra/4 );
           valorLetra = 0;
           r = rojo;
 
        fread(&valor,1,1,archivo);
        valorLetra = 0;
        cuenta_colores = cuenta_colores + 1;
 
         outportb(0x3c9,r);
         outportb(0x3c9,v);
         outportb(0x3c9,a);
    }
    while(cuenta_colores <= 255);

    getch();
 
    do
    {
        fseek(archivo,1078L+contador,SEEK_SET);   //Aquí vuelvo a video memoria. Lo que quiero hacer es guardar esos datos en un array de 63779
        fread(&dato,1,1,archivo);                 //elementos y luego volcarlo a la video memoria, pero no se como hacerlo.
        pokeb(0xa000,contador,dato);              // Escribe en memoria de video
        contador = contador + 1 ;
    }
    while (contador <=63779);
 
    getch();
 
     asm{
        mov ah,0
        mov al,02h          //vuelvo a pantalla modo texto
        int 10h
    }
 
    return(0);
}