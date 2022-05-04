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
        printf("El tiempo incial es de : %ld segundos\n ",t_inicial.tv_sec);
   
        write(fildes[1], &t_inicial, sizeof(float));
        //execlp("/root/examen","examen","-l",NULL);
        execlp(argv[1], argv[1],NULL);
    } else{
        //Proceso padre con espera de terminación del  proceso hijo 
        wait(NULL);
        struct timeval ti;
        read(fildes[0],&ti,sizeof(float));
        struct timeval t_final;
        gettimeofday(&t_final,NULL);
        printf("El tiempo final es de : %ld segundos\n",t_final.tv_sec);

        float resultado_asaroso = (t_final.tv_sec - ti.tv_sec)+ 1e-9(t_final.tv_sec - ti.tv_sec);

        printf("El tiempo es : %ld\n",resultado_asaroso);


    }
    close(fildes[0]);
    close(fildes[1]);
    return 0;


}
