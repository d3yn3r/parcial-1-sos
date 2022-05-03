#include <stdio.h>
#include <unistd.h>
#include<sys/time.h>

int main(int argc, char *args[]){
    //descriptores de lectura y escritura
    int fildes[2];
    //Se crea tubería sin nombre
    if (pipe(fildes)<0){
        perror("Error al crear la tubería\n");
        return (1);
    }
    //Se crea proceso hijo
    if (fork()==0){
        //dato que se pone en la tubería
        int dato_entra= gettimeofday();
        write(fildes[1],&dato_entra,sizeof(int));
    }
    else{
        //Dato que sale de la tubería 
        int dato_sale;
        read(fildes[0], &dato_sale,sizeof(int));
        printf("Dato recibido por tubería: %d\n", dato_sale);
    }
    //Cerrar descriptores
    close(fildes[0]);
    close(fildes[1]);
    return 0;
}