#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    int fildes[2];

    //fildes[0] - read
    //fildes[1] - write

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
        //execlp("/bin/ls","ls","-l",NULL);
        struct timeval t_inicial;
        gettimeofday(&t_inicial,NULL);
        printf("El tiempo incial es de : %lf\n",t_inicial.tv_usec);
   
        write(fildes[1], &t_inicial, sizeof(double));
    } else{
        //Proceso padre con espera de terminación del  proceso hijo 
        wait(NULL);
        struct timeval ti;
        read(fildes[0],&ti,sizeof(double));
        struct timeval t_final;
        gettimeofday(&t_final,NULL);
        printf("El tiempo final es de : %lf",t_final.tv_usec);

    }
    close(fildes[0]);
    close(fildes[1]);
    return 0;


}
