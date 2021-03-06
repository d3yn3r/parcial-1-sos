/*                                  Sistemas operativos
            Parcial 1
            Profesor : Juan Felipe Muñoz Hernandez
            Integrantes : Juan Esteban Ochoa CC: 1.000.634.602
                          Deyner Elias Lopez Pineda CC: 1.216.728.753
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    int fildes[2];


    if (pipe(fildes) <0){
        perror("Error al crear la tubería\n");
        return (1);
    }
    pid_t pid;
    //Creamos nuevo proceso
    pid = fork();
    
    if (pid < 0){
        printf("¡Oh no!, falló el fork");
    } else if (pid ==0){    //Creación proceso hijo

        //Obtenemos el tiempo inicial
        struct timeval t_inicial;
        gettimeofday(&t_inicial,NULL);

        //Enviamos mediante una tuberia la estructura del tiempo inicial
        write(fildes[1], &t_inicial, sizeof(t_inicial));
        execlp(argv[1], argv[1],NULL);
    } else{
        //Proceso padre con espera de terminación del  proceso hijo 
        wait(NULL);

        //Recuperamos la estructura enviada mediante la tuberia
        struct timeval ti;
        read(fildes[0],&ti,sizeof(ti));

        //Calculamos el tiempo inicial
        double total_inicial = ti.tv_sec + ti.tv_usec*1e-6;
        printf("El tiempo inicial es: %0.8f segundos\n",total_inicial);

        //Obtenemos el tiempo final
        struct timeval t_final;
        gettimeofday(&t_final,NULL);
        //Calculamos el tiempo final
        double total_final =  t_final.tv_sec + t_final.tv_usec*1e-6;
        printf("El tiempo final es: %0.8f segundos\n",total_final);

        //Calculamos el tiempo total de ejecucion
        double total = total_final - total_inicial;
        printf("El tiempo de ejecucion es : %0.8f segundos\n",total);
    }
    //Cerramos la tuberia
    close(fildes[0]);
    close(fildes[1]);
    return 0;

}
