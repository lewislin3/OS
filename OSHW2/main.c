#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>


int main() {
    int input;
    int cnt;
//  uint32_t  array[800][800];
    uint32_t  sum = 0;
    int i,j,k,l;
    uint32_t num=0;
    int shmid,shmarray;
    uint32_t * shm,* shma;
    int pid[16];
    int sec,usec;
    struct timeval start[16], end[16];
    
    //input number and create a matrix
    scanf("%d",&input);
    shmarray=shmget(IPC_PRIVATE, sizeof(unsigned int)*input*input, SHM_W|SHM_R|IPC_CREAT);
    if (shmarray<0) {
        perror("share memory array error");
        exit(0);
    }

    shma=shmat(shmarray, 0, 0);
    
    for(i=0; i!=input; i++){
        for(j=0; j!=input; j++){
            shma[i*input+j]=num;
            num++;
        }
    }
    shmdt(shma) ;
    
    shmid=shmget(IPC_PRIVATE, sizeof(unsigned int)*input*input, SHM_W|SHM_R|IPC_CREAT);
    
    if (shmid<0) {
        perror("share memory error");
        exit(0);
    }
    
   
    ///////////
    //2+ process
    for (cnt=1; cnt!=17; cnt++) {
        printf("Multiplying matrices using %d process\n",cnt);
        shm=shmat(shmid, 0, 0);
        shma=shmat(shmarray, 0, 0);
        for (int i=0; i!=input*input; i++) {
            shm[i]=0;
        }
        gettimeofday(&start[cnt-1], 0);
        sum=0;
        
        
        //fork child
        pid[0]=fork();
        if (pid[0]<0) {
            perror("fork error");
            exit(0);
        }
        for (l=1; l!=cnt; l++) {
            
            for (i=0; i!=l; i++) {
                if (pid[i]==0) {
                    break;
                }
            }
            if (i==l) {
                pid[l]=fork();
            }
            if (pid[l]<0) {
                perror("fork error");
                exit(0);
            }
        }
        
        
        
        for (l=0; l!=cnt; l++) {
            if (pid[l]==0) {
                //printf("child%d\n",l);
                if (l!=cnt-1) {
                    for (i=(input/(cnt))*l ;i!=(input/(cnt))*(l+1); i++) {
                        for (j=0; j!=input; j++) {
                            for (k=0; k!=input; k++) {
                                //printf("[%d][%d]*[%d][%d]\n",i,k,k,j);
                                shm[i*input+j]=shm[i*input+j]+shma[i*input+k]*shma[k*input+j];
                            }
                        }
                    }
                }
                else{
                    for (i=(input/(cnt))*l ;i!=input; i++) {
                        for (j=0; j!=input; j++) {
                            for (k=0; k!=input; k++) {
                                //printf("[%d][%d]*[%d][%d]\n",i,k,k,j);
                                shm[i*input+j]=shm[i*input+j]+shma[i*input+k]*shma[k*input+j];
                                
                            }
                        }
                    }
                }
                exit(0);
            }
            else{
                for (i=0; i!=cnt; i++) {
                    wait(NULL);
                }
            }
        }
        
        
        
        
        sum=0;
        for (l=0; l!=input*input; l++) {
            //printf("%d\n",shm[l]);
            sum=sum+shm[l];
        }
        shmdt(shm) ;
        shmdt(shma) ;
        gettimeofday(&end[cnt-1], 0);
        sec = end[cnt-1].tv_sec - start[cnt-1].tv_sec;
        usec = end[cnt-1].tv_usec - start[cnt-1].tv_usec;
        printf("Elapsed time: %f s ", (sec*1000+(usec/1000.0))/1000);
        printf("Check: %u\n",sum);
        

        
    }
    
    
    shmctl(shmid, IPC_RMID, NULL) ;
    shmctl(shmarray, IPC_RMID, NULL) ;
    return 0;
    
}
