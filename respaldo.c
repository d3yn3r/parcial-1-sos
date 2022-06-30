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


int main() { 
    
    while (1){
        int numero; 
        int binario[32];
        char control;
        int z,x,d,q,potencia=0,desplazamiento=0,pagina = 0,cont;
        printf("Ingrese dirección virtual: ");
        scanf("%s",&control);
        
        //tiempo inicial
        struct timeval t_inicial;
        gettimeofday(&t_inicial,NULL);
        double total_inicial = t_inicial.tv_sec + t_inicial.tv_usec*1e-6;
        
        if(control == 's'){
            break;
        }
        
        else if(control != 's'){
            numero = atoi(&control);
            for (int i = 0; i < 32; i++) {
                binario[i] = numero%2;
                numero = numero/2;
            }
        }
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
    }       
}