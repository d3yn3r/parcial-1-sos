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
    struct datos {
        int direc; int desp; int pag;
    };
    struct datos * grupo;
    grupo = (struct datos *) malloc(3* sizeof(struct datos));

    int contador_memoria = 0; 
    while (1){
        int numero; 
        int binario[32];
        char control;
        int z,x,d,q,potencia=0,desplazamiento=0,pagina = 0,cont;
        int hit = 0;
        printf("Ingrese dirección virtual: ");
        scanf("%s",&control);
        


        //tiempo inicial
        struct timeval t_inicial;
        gettimeofday(&t_inicial,NULL);
        double total_inicial = t_inicial.tv_sec + t_inicial.tv_usec*1e-6;
        


        if(control == 's'){
            printf("Good bye!");
            break;
        }
        
        else if(control != 's'){
            numero = atoi(&control);
            for (int i = 0; i < 32; i++) {
                binario[i] = numero%2;
                numero = numero/2;
            }
        }
        int direccion; 
        direccion = atoi(&control);
        int pertenecer = -1;
        for (int j = 0; j< 3;j++){
            printf("%d\n",grupo[j].direc);
            printf("%d\n",direccion);
            if (grupo[j].direc == direccion){
                pertenecer = j;
            }
        }
        printf("Pertenecer : %d\n",pertenecer);
        if (pertenecer != -1){
            printf("%d",hit);
            desplazamiento = grupo[pertenecer].desp;
            pagina = grupo[pertenecer].pag;
            hit = 1;

        }
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
            grupo[0].direc = direccion;
            grupo[0].desp = desplazamiento;
            grupo[0].pag = pagina;
            contador_memoria ++ ;
        }
        else if (contador_memoria <3) //Con espacio en memoria
        {
            grupo[contador_memoria].direc = direccion;
            grupo[contador_memoria].desp = desplazamiento;
            grupo[contador_memoria].pag = pagina;
            contador_memoria ++;
        }
        else        // Memoria llena 
        {
            int aleatorio rand() %3;
            grupo[aleatorio].direc = direccion;
            grupo[aleatorio].desp = desplazamiento;
            grupo[aleatorio].pag = pagina;
        }
        
        

        }
        //tiempo final
        struct timeval t_final;
        gettimeofday(&t_final,NULL);
        double total_final =  t_final.tv_sec + t_final.tv_usec*1e-6;
        
        double total = total_final - total_inicial;
        
        printf("Desplazamiento: ");
        printf("%d",desplazamiento);
        printf("\n");
        printf("Número de página: ");
        printf("%d",pagina);
        printf("\n");
        printf("Tiempo de traducción: ");
        printf("%0.8f",total);
        printf("\n");
        if (hit == 1){
            printf("TLB: Hit");
            printf("\n");
        }
        else{
            printf("TLB: Miss");
            printf("\n");

        }

    }       
}
