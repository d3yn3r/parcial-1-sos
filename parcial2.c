/*                                  Sistemas operativos
            Parcial 2
            Profesor : Juan Felipe Muñoz Hernandez
            Integrantes : Juan Esteban Ochoa CC: 1.000.634.602
                          Deyner Elias Lopez Pineda CC: 1.216.728.753
*/
#include <stdio.h>
#include <conio.h>   
int main() 
{ 
    int z,x,numero,n2=0; 
    int binario[50]; 
    binario[0]=0; 
  
    printf("Introduce el decimal a convertir: " ); 
    scanf("%iu",&numero); 

    for (x=0;x<50;x++) { 
        binario[x]=numero%2; 
        numero=numero/2; 
    if(numero==0) 
    break; 
    } 

    for(z=x;z>=0;z--) { 
        printf("%d",binario[z]); 
    } 

    getch(); 
}
