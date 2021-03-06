/*                                  Sistemas operativos
            Parcial 2
            Profesor : Juan Felipe Muñoz Hernandez
            Integrantes : Juan Esteban Ochoa CC: 1.000.634.602
                          Deyner Elias Lopez Pineda CC: 1.216.728.753
*/
#include <stdio.h>
#include <conio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

int main() {
    //Definimos la estructura que va a ingresar al espacio de memoria
    struct datos {
        long direc; long desp; long pag;
    };
    struct datos * grupo;
    grupo = (struct datos *) malloc(5* sizeof(struct datos));

    int contador_memoria = 0; 
    while (1){
        //variables
        long numero; 
        long binario[32];
        char control[32];
        long z,x,d,q,potencia=0,desplazamiento=0,pagina = 0,cont;
        long hit = 0;
        
        //lectura de direccion
        printf("Ingrese dirección virtual: ");
        scanf("%s",control);
        
        //calculo del tiempo inicial
        struct timeval t_inicial;
        gettimeofday(&t_inicial,NULL);
        double total_inicial = t_inicial.tv_sec + t_inicial.tv_usec*1e-6;
        
        //control de salida
        if(strcmp(control,"s")==0){
            printf("Good bye!");
            break;
        }
        
        //conversion de decimal a binario
        else if(strcmp(control,"s")!=0){
            numero = atol(control);
            for (int i = 0; i < 32; i++) {
                binario[i] = numero%2;
                numero = numero/2;
            }
        }
        
        //verificacion de direccion cargada en espacio de memoria
        long direccion; 
        direccion = atol(control);
        long pertenecer = -1;
        for (int j = 0; j< 5;j++){

            if (grupo[j].direc == direccion){
                pertenecer = j;
            }
        }

        if (pertenecer != -1){
            desplazamiento = grupo[pertenecer].desp;
            pagina = grupo[pertenecer].pag;
            hit = 1;

        }
        
        //En caso de no estar cargada en memoria, se procede a realizar la traducción
        else{
            //Desplazamiento
            for(z=0;z<12;z++) { 
                d = binario[z];
                if(d==1){
                    potencia = pow(2,z);
                    desplazamiento = desplazamiento + potencia;
                }
            }
            //paginación
            for (int i = 12; i < 32; i++) {
                int exponente = i - 12;
                int valor = binario[i];
                if(valor == 1){
                    potencia = pow(2,exponente);
                    pagina = pagina + potencia;
                }
            }

            if (contador_memoria == 0){ // Primera vez ingresando datos
                struct datos ingreso = {direccion,desplazamiento, pagina};
                contador_memoria ++ ;
                grupo[0] = ingreso;
            }
            else if (contador_memoria <5) //Con espacio en memoria
            {
                struct datos ingreso = {direccion,desplazamiento, pagina};
                grupo[contador_memoria] = ingreso;
                contador_memoria ++;
            }
            else// Memoria llena
            // la politica de reemplazo aleatoria
            {
                int aleatorio = rand() %5;
                struct datos ingreso = {direccion,desplazamiento, pagina};
                grupo[aleatorio] = ingreso;
            }
        
        }
        
        //calculo del tiempo final y el tiempo de ejecucion
        struct timeval t_final;
        gettimeofday(&t_final,NULL);
        double total_final =  t_final.tv_sec + t_final.tv_usec*1e-6;
        double total = total_final - total_inicial;
        
        //impresion de datos por pantalla
        printf("Desplazamiento: ");
        printf("%ld\n",desplazamiento);

        printf("Número de página: ");
        printf("%ld\n",pagina);

        printf("Tiempo de traducción: ");
        printf("%0.8f Segundos\n",total);

        if (hit == 1){
            printf("TLB: Hit\n");
        }
        else{
            printf("TLB: Miss\n");
        }
    }       
}
