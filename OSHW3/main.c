#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <sys/time.h>

int *input,*input2;
int *quick[2];
int ql[14]={0};
sem_t sem1[2], sem2[2], sem3[2], sem4[8],ans[15],sa;
struct timeval start[2], end[2];
int sec,usec;



int p[7];
int size;

int cmp( const void *a, const void *b) {
    return *((int*) a) - *((int*) b) ;
}

void quicksort1(){  //seperate input to q0 q1
    p[3]=input[(size-1+0)/2];
    
    int i;
    for (i=0; i!=size; i++) {
        if (input[i]<p[3]) {
            quick[0][ql[0]]=input[i];
            ql[0]++;
        }
        else{
            quick[1][ql[1]]=input[i];
            ql[1]++;
        }
    }
    for (i=0; i!=ql[0]; i++) {
        input[i]=quick[0][i];
    }
    for (i=ql[0]; i!=(ql[0]+ql[1]); i++) {
        input[i]=quick[1][i-ql[0]];
    }

    
    
    
   
    sem_post(&sem1[0]);
    sem_post(&sem1[1]);
    sem_post(&ans[0]);
    

}
void quicksort2(){  //seperate q0 to q2 q3
    
    sem_wait(&sem1[0]);
    p[1]=input[(ql[0]-1)/2];
    
    int i=0;
    for (i=0; i!=ql[0]; i++) {
        if (input[i]<p[1]) {
            quick[0][ql[2]]=input[i];
            ql[2]++;
        }
        else{
            quick[1][ql[3]]=input[i];
            ql[3]++;
        }
    }
    for (i=0; i!=ql[2]; i++) {
        input[i]=quick[0][i];
    }
    for (i=ql[2]; i!=(ql[2]+ql[3]); i++) {
        input[i]=quick[1][i-ql[2]];
    }

    
   
    
    sem_post(&sem2[0]);
    sem_post(&sem2[1]);
    sem_post(&ans[1]);

}

void quicksort3(){ //seperate q1 to q4 q5
    
    sem_wait(&sem1[1]);
    p[5]=input[(size-1+ql[0])/2];
    
    int i=0;
    for (i=ql[0]; i!=size; i++) {
        if (input[i]<p[5]) {
            quick[0][ql[4]]=input[i];
            ql[4]++;
        }
        else{
            quick[1][ql[5]]=input[i];
            ql[5]++;
        }
    }
    
    for (i=ql[0]; i!=ql[0]+ql[4]; i++) {
        input[i]=quick[0][i-ql[0]];
    }
    for (i=ql[0]+ql[4]; i!=(ql[0]+ql[4]+ql[5]); i++) {
        input[i]=quick[1][i-ql[4]-ql[0]];
    }
    
    
    
    
    sem_post(&sem3[0]);
    sem_post(&sem3[1]);
    sem_post(&ans[2]);
}


void quicksort4(){ //seperate q2 to q6 q7
    
    sem_wait(&sem2[0]);
    p[0]=input[(ql[2]-1)/2];
    
    int i=0;
    for (i=0; i!=ql[2]; i++) {
        if (input[i]<p[0]) {
            quick[0][ql[6]]=input[i];
            ql[6]++;
        }
        else{
            quick[1][ql[7]]=input[i];
            ql[7]++;
        }
    }
    

    for (i=0; i!=ql[6]; i++) {
        input[i]=quick[0][i];
    }
    for (i=ql[6]; i!=(ql[6]+ql[7]); i++) {
        input[i]=quick[1][i-ql[6]];
    }
    

    sem_post(&sem4[0]);
    sem_post(&sem4[1]);
    sem_post(&ans[3]);
}
void quicksort5(){ //seperate q3 to q8 q9
    sem_wait(&sem2[1]);
    p[2]=input[(ql[0]-1+ql[2])/2];
   
    int i=0;
    for (i=ql[2]; i!=ql[2]+ql[3]; i++) {
        if (input[i]<p[2]) {
            quick[0][ql[8]]=input[i];
            ql[8]++;
        }
        else{
            quick[1][ql[9]]=input[i];
            ql[9]++;
        }
    }
    for (i=ql[2]; i!=ql[2]+ql[8]; i++) {
        input[i]=quick[0][i-ql[2]];
    }
    for (i=ql[2]+ql[8]; i!=(ql[2]+ql[8]+ql[9]); i++) {
        input[i]=quick[1][i-ql[2]-ql[8]];
    }

   
    
    sem_post(&sem4[2]);
    sem_post(&sem4[3]);
    sem_post(&ans[4]);
}

void quicksort6(){ //seperate q4 to q10 q11
    sem_wait(&sem3[0]);
    p[4]=input[(ql[0]+ql[4]-1+ql[0])/2];
    int i=0;
    for (i=ql[0]; i!=ql[0]+ql[4]; i++) {
        if (input[i]<p[4]) {
            quick[0][ql[10]]=input[i];
            ql[10]++;
        }
        else{
            quick[1][ql[11]]=input[i];
            ql[11]++;
        }
    }
    for (i=ql[0]; i!=ql[0]+ql[10]; i++) {
        input[i]=quick[0][i-ql[0]];
    }
    for (i=ql[0]+ql[10]; i!=(ql[0]+ql[10]+ql[11]); i++) {
        input[i]=quick[1][i-ql[0]-ql[10]];
    }

   
    
    sem_post(&sem4[4]);
    sem_post(&sem4[5]);
    sem_post(&ans[5]);
}

void quicksort7(){ //seperate q5 to q12 q13
    sem_wait(&sem3[1]);
    p[6]=input[(size-1+ql[0]+ql[4])/2];
    
    int i=0;
    for (i=ql[0]+ql[4]; i!=size; i++) {
        if (input[i]<p[6]) {
            quick[0][ql[12]]=input[i];
            ql[12]++;
        }
        else{
            quick[1][ql[13]]=input[i];
            ql[13]++;
        }
    }

    for (i=ql[0]+ql[4]; i!=ql[0]+ql[4]+ql[12]; i++) {
        input[i]=quick[0][i-ql[0]-ql[4]];
    }
    for (i=ql[0]+ql[4]+ql[12]; i!=size; i++) {
        input[i]=quick[1][i-ql[0]-ql[4]-ql[12]];
    }
    
   
    
    sem_post(&sem4[6]);
    sem_post(&sem4[7]);
    sem_post(&ans[6]);
}

void merge1(){ //merge q6
    sem_wait(&sem4[0]);
    qsort(input, ql[6], sizeof(int), cmp);
    sem_post(&ans[7]);
}
void merge2(){ //merge q7
    sem_wait(&sem4[1]);
    qsort(input+ql[6], ql[7], sizeof(int), cmp);
    sem_post(&ans[8]);
}
void merge3(){ //merge q8
    sem_wait(&sem4[2]);
    qsort(input+ql[2], ql[8], sizeof(int), cmp);
    sem_post(&ans[9]);
}

void merge4(){ //merge q9
    sem_wait(&sem4[3]);
    qsort(input+(ql[2]+ql[8]), ql[9], sizeof(int), cmp);
    sem_post(&ans[10]);
}

void merge5(){ //merge q10
    sem_wait(&sem4[4]);
    qsort(input+ql[0], ql[10], sizeof(int), cmp);
    sem_post(&ans[11]);
}
void merge6(){ //merge q11
    sem_wait(&sem4[5]);
    qsort(input+(ql[0]+ql[10]), ql[11], sizeof(int), cmp);
    sem_post(&ans[12]);
}
void merge7(){ //merge q12
    sem_wait(&sem4[6]);
    qsort(input+(ql[0]+ql[4]), ql[12], sizeof(int), cmp);
    sem_post(&ans[13]);
}
void merge8(){ //merge q13
    sem_wait(&sem4[7]);
    qsort(input+(ql[0]+ql[4]+ql[12]), ql[13], sizeof(int), cmp);
    sem_post(&ans[14]);
}


void single(){ //single
    qsort(input2, size, sizeof(int), cmp);
    sem_post(&sa);
}

int main() {

    FILE *file,*out1,*out2;
    
    int i,j;
    int semid;
    char route[100];
    scanf("%s",route);
    pthread_t thread[16],sth;
    
    
    

    file=fopen(route, "r");
    if(!file){
        printf("no exist\n");
        return 0;
    }
    fscanf(file,"%d ",&size);
    input=(int*)malloc(sizeof(int)*size);
    input2=(int*)malloc(sizeof(int)*size);
    for (j=0; j!=2; j++) {
        quick[j]=(int*)malloc(sizeof(int)*size);
    }
    for (j=0; j!=size; j++) {
        fscanf(file,"%d ",&input[j]);
    }
    
    
    fclose(file);
    
    for (i=0; i!=size; i++) {
        input2[i]=input[i];
    }
    
    
    for (j=0; j!=2; j++) {
        semid=sem_init(&sem1[j], 0, 0);
        
        semid=sem_init(&sem2[j], 0, 0);
        
        semid=sem_init(&sem3[j], 0, 0);
        
    }
    
    for (j=0; j!=8; j++) {
        semid=sem_init(&sem4[j], 0, 0);
        
    }
    for (j=0; j!=15; j++) {
        semid=sem_init(&ans[j], 1, 0);
    }
    
    semid=sem_init(&sa, 1, 0);
    
    gettimeofday(&start[0], 0);
    pthread_create(&thread[1],NULL,(void *)quicksort1,NULL);
    pthread_create(&thread[2],NULL,(void *)quicksort2,NULL);
    pthread_create(&thread[3],NULL,(void *)quicksort3,NULL);
    pthread_create(&thread[4],NULL,(void *)quicksort4,NULL);
    pthread_create(&thread[5],NULL,(void *)quicksort5,NULL);
    pthread_create(&thread[6],NULL,(void *)quicksort6,NULL);
    pthread_create(&thread[7],NULL,(void *)quicksort7,NULL);
    pthread_create(&thread[8],NULL,(void *)merge1,NULL);
    pthread_create(&thread[9],NULL,(void *)merge2,NULL);
    pthread_create(&thread[10],NULL,(void *)merge3,NULL);
    pthread_create(&thread[11],NULL,(void *)merge4,NULL);
    pthread_create(&thread[12],NULL,(void *)merge5,NULL);
    pthread_create(&thread[13],NULL,(void *)merge6,NULL);
    pthread_create(&thread[14],NULL,(void *)merge7,NULL);
    pthread_create(&thread[15],NULL,(void *)merge8,NULL);

    
    
    sem_wait(&ans[0]);
    sem_wait(&ans[1]);
    sem_wait(&ans[2]);
    sem_wait(&ans[3]);
    sem_wait(&ans[4]);
    sem_wait(&ans[5]);
    sem_wait(&ans[6]);
    sem_wait(&ans[7]);
    sem_wait(&ans[8]);
    sem_wait(&ans[9]);
    sem_wait(&ans[10]);
    sem_wait(&ans[11]);
    sem_wait(&ans[12]);
    sem_wait(&ans[13]);
    sem_wait(&ans[14]);
    
   
    gettimeofday(&end[0], 0);
    sec = end[0].tv_sec - start[0].tv_sec;
    usec = end[0].tv_usec - start[0].tv_usec;
    printf("multi-thread/n");
    printf("Elapsed time: %f ms \n", (sec*1000+(usec/1000.0)));
    
    out1=fopen("output1.txt", "w");
    if(!out1){
        printf("no exist\n");
        return 0;
    }
    for (j=0; j!=size; j++) {
        fprintf(out1,"%d ",input[j]);
    }
    fclose(out1);
    
    
    gettimeofday(&start[1], 0);
    pthread_create(&sth,NULL,(void *)single,NULL);
    sem_wait(&sa);
    gettimeofday(&end[1], 0);
    sec = end[1].tv_sec - start[1].tv_sec;
    usec = end[1].tv_usec - start[1].tv_usec;
    printf("single thread/n");
    printf("Elapsed time: %f ms ", (sec*1000+(usec/1000.0)));
    
    out2=fopen("output2.txt", "w");
    if(!out2){
        printf("no exist\n");
        return 0;
    }
    for (j=0; j!=size; j++) {
        fprintf(out2,"%d ",input2[j]);
    }
    fclose(out2);

    
   
  
    
    
    

    return 0;
}



