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
int main() { 
    
    while (1){
        int numero; 
        char binario;
        char control;
        int c,n,k;

        scanf("%s",&control); 
        if(control == 's'){
            break;
        }
        
        else if(control != 's'){
            numero = atoi(&control);
            for (c=15;c>=0;c--){
	            k = numero>>c;
	            if (k&1){
	               printf("1");
	            }
		        else {
    	            printf("0");
		        }
	        }
        }
    }       
}
