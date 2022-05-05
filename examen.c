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

        struct timeval t_inicial;
        gettimeofday(&t_inicial,NULL);
        
        write(fildes[1], &t_inicial, sizeof(t_inicial));
        execlp(argv[1], argv[1],NULL);
    } else{
        //Proceso padre con espera de terminación del  proceso hijo 
        wait(NULL);
        struct timeval ti;
        read(fildes[0],&ti,sizeof(ti));
        
        double total_inicial = ti.tv_sec + ti.tv_usec*1e-6;
        printf("tiempo inicial es: %0.8f\n",total_inicial);
        
        struct timeval t_final;
        gettimeofday(&t_final,NULL);
        
        double total_final =  t_final.tv_sec + t_final.tv_usec*1e-6;
        printf("tiempo final es: %0.8f\n",total_final);
        
        double total = total_final - total_inicial;
        printf("El tiempo de ejecucion es : %0.8f\n",total);
    }
    close(fildes[0]);
    close(fildes[1]);
    return 0;

}
