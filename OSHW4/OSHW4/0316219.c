#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <sys/time.h>

int *input;
int ql[14]={0};
int work=1;
sem_t sem1[2], sem2[2], sem3[2], sem4[8],ans[15],sa;
struct timeval start, end;
int sec,usec;
int p[7];
int size;



void quicksort1(){  //seperate input to q0 q1
    
    p[3]=input[0];
    int quick[2][1000000];
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
    
    
    
    
    
    //printf("[1]");
    sem_post(&sem1[0]);
    sem_post(&sem1[1]);
    //sem_post(&ans[0]);
    
    
}
void quicksort2(){  //seperate q0 to q2 q3
    sem_wait(&sem1[0]);
    p[1]=input[1];
    int quick[2][1000000];
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
    
    
    
    //printf("[2]");
    sem_post(&sem2[0]);
    sem_post(&sem2[1]);
    //sem_post(&ans[1]);
    
}

void quicksort3(){ //seperate q1 to q4 q5
    sem_wait(&sem1[1]);
    p[5]=input[ql[0]+1];
    int quick[2][1000000];
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
    
    
    
    //printf("[3]");
    sem_post(&sem3[0]);
    sem_post(&sem3[1]);
    //sem_post(&ans[2]);
    
}


void quicksort4(){ //seperate q2 to q6 q7
    sem_wait(&sem2[0]);
    p[0]=input[0];
    int quick[2][1000000];
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
    //printf("[4]");
    
    sem_post(&sem4[0]);
    sem_post(&sem4[1]);
    //sem_post(&ans[3]);
    
}
void quicksort5(){ //seperate q3 to q8 q9
    sem_wait(&sem2[1]);
    p[2]=input[ql[2]+2];
    int quick[2][1000000];
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
    
    
    //printf("[5]");
    sem_post(&sem4[2]);
    sem_post(&sem4[3]);
    //sem_post(&ans[4]);
}

void quicksort6(){ //seperate q4 to q10 q11
    sem_wait(&sem3[0]);
    p[4]=input[ql[0]+1];
    int quick[2][1000000];
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
    
    
    //printf("[6]");
    sem_post(&sem4[4]);
    sem_post(&sem4[5]);
    //sem_post(&ans[5]);
}

void quicksort7(){ //seperate q5 to q12 q13
    sem_wait(&sem3[1]);
    p[6]=input[ql[0]+ql[4]+1];
    int quick[2][1000000];
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
    
    
    //printf("[7]");
    sem_post(&sem4[6]);
    sem_post(&sem4[7]);
    //sem_post(&ans[6]);
}

void merge1(){ //merge q6
    sem_wait(&sem4[0]);
    int i=0;
    int j=0;
    int tmp;
    for (i=0; i<ql[6]; i++) {
        for (j=0; j<ql[6]-1; j++) {
            if (input[j]>input[j+1]) {
                tmp=input[j];
                input[j]=input[j+1];
                input[j+1]=tmp;
            }
        }
    }
    //printf("[8]%d %d",0,ql[6]);
    sem_post(&ans[7]);
    
}
void merge2(){ //merge q7
    sem_wait(&sem4[1]);
    int i=0;
    int j=0;
    int tmp;
    for (i=ql[6]; i<ql[6]+ql[7]; i++) {
        for (j=ql[6]; j<ql[6]+ql[7]-1; j++) {
            if (input[j]>input[j+1]) {
                tmp=input[j];
                input[j]=input[j+1];
                input[j+1]=tmp;
            }
        }
    }
    //printf("[9]%d %d",ql[6],ql[6]+ql[7]);
    sem_post(&ans[8]);
}
void merge3(){ //merge q8
    sem_wait(&sem4[2]);
    int i=0;
    int j=0;
    int tmp;
    for (i=ql[2]; i<ql[2]+ql[8]; i++) {
        for (j=ql[2]; j<ql[2]+ql[8]-1; j++) {
            if (input[j]>input[j+1]) {
                tmp=input[j];
                input[j]=input[j+1];
                input[j+1]=tmp;
            }
        }
    }
    //printf("[10]%d %d",ql[2],ql[2]+ql[8]);
    sem_post(&ans[9]);
}

void merge4(){ //merge q9
    sem_wait(&sem4[3]);
    int i=0;
    int j=0;
    int tmp;
    for (i=ql[2]+ql[8]; i<ql[0]; i++) {
        for (j=ql[2]+ql[8]; j<ql[0]-1; j++) {
            if (input[j]>input[j+1]) {
                tmp=input[j];
                input[j]=input[j+1];
                input[j+1]=tmp;
            }
        }
    }
    //printf("[11]%d %d",ql[2]+ql[8],ql[0]);
    sem_post(&ans[10]);
}

void merge5(){ //merge q10
    sem_wait(&sem4[4]);
    int i=0;
    int j=0;
    int tmp;
    for (i=ql[0]; i<ql[0]+ql[10]; i++) {
        for (j=ql[0]; j<ql[0]+ql[10]-1; j++) {
            if (input[j]>input[j+1]) {
                tmp=input[j];
                input[j]=input[j+1];
                input[j+1]=tmp;
            }
        }
    }
    //printf("[12]%d %d",ql[0],ql[0]+ql[10]);
    sem_post(&ans[11]);
}
void merge6(){ //merge q11
    sem_wait(&sem4[5]);
    int i=0;
    int j=0;
    int tmp;
    for (i=ql[0]+ql[10]; i<ql[0]+ql[4]; i++) {
        for (j=ql[0]+ql[10]; j<ql[0]+ql[4]-1; j++) {
            if (input[j]>input[j+1]) {
                tmp=input[j];
                input[j]=input[j+1];
                input[j+1]=tmp;
            }
        }
    }
    //printf("[13]%d %d",ql[0]+ql[10],ql[0]+ql[4]);
    sem_post(&ans[12]);
}
void merge7(){ //merge q12
    sem_wait(&sem4[6]);
    int i=0;
    int j=0;
    int tmp;
    for (i=ql[0]+ql[4]; i<ql[0]+ql[4]+ql[12]; i++) {
        for (j=ql[0]+ql[4]; j<ql[0]+ql[4]+ql[12]-1; j++) {
            if (input[j]>input[j+1]) {
                tmp=input[j];
                input[j]=input[j+1];
                input[j+1]=tmp;
            }
        }
    }
    //printf("[14]%d %d",ql[0]+ql[4],ql[0]+ql[4]+ql[12]);
    sem_post(&ans[13]);
}
void merge8(){ //merge q13
    sem_wait(&sem4[7]);
    int i=0;
    int j=0;
    int tmp;
    for (i=ql[0]+ql[4]+ql[12]; i<size; i++) {
        for (j=ql[0]+ql[4]+ql[12]; j<size-1; j++) {
            if (input[j]>input[j+1]) {
                tmp=input[j];
                input[j]=input[j+1];
                input[j+1]=tmp;
            }
        }
    }
    //printf("[15]%d %d",ql[0]+ql[4]+ql[12],size);
    sem_post(&ans[14]);
}



void choose(){
    int w;//there isn't any accel??
    while (work<=15) {
        sem_wait(&sa);
        w=work;
        work++;
        sem_post(&sa);
        if (w==1) {
            quicksort1();
        }
        if (w==2) {
            quicksort2();
        }
        if (w==3) {
            quicksort3();
        }
        if (w==4) {
            quicksort4();
        }
        if (w==5) {
            quicksort5();
        }
        if (w==6) {
            quicksort6();
        }
        if (w==7) {
            quicksort7();
        }
        if (w==8) {
            merge1();
        }
        if (w==9) {
            merge2();
        }
        if (w==10) {
            merge3();
        }
        if (w==11) {
            merge4();
        }
        if (w==12) {
            merge5();
        }
        if (w==13) {
            merge6();
        }
        if (w==14) {
            merge7();
        }
        if (w==15) {
            merge8();
        }
    }
}

int main() {
    
    FILE *file,*out1;
    
    int i,j;
    int times;
    char file_name[30]="output_x.txt";
    pthread_t thread[8];
    
    
    
    //read file
    file=fopen("input.txt", "r");
    if(!file){
        printf("no exist\n");
        return 0;
    }
    fscanf(file,"%d ",&size);
    input=(int*)malloc(sizeof(int)*size*10);
    
    fclose(file);
    for (j=0; j!=2; j++) {
        sem_init(&sem1[j], 0, 0);
        sem_init(&sem2[j], 0, 0);
        sem_init(&sem3[j], 0, 0);
        //printf("a\n");
    }
    for (j=0; j!=8; j++) {
        sem_init(&sem4[j], 0, 0);
    }
    for (j=0; j!=15; j++) {
        sem_init(&ans[j], 1, 0);
    }
    sem_init(&sa,0,1);
    
    
    
    
    
    for (times=1; times<=8; times++) {
        //////////////////////////// initialize
        
        work=1;
        
        for (i=0; i!=14; i++) {
            ql[i]=0;
        }
        
        file=fopen("input.txt", "r");
        if(!file){
            printf("no exist\n");
            return 0;
        }
        fscanf(file,"%d ",&size);
        for (j=0; j!=size; j++) {
            fscanf(file,"%d ",&input[j]);
        }
        
        fclose(file);
        /////////////////////////////////////////
        
        
        gettimeofday(&start, 0);
        
        for (i=0; i<times; i++) {
            pthread_create(&thread[i],NULL,(void *)choose,NULL);
            
        }
        
        
        
        sem_wait(&ans[7]);
        sem_wait(&ans[8]);
        sem_wait(&ans[9]);
        sem_wait(&ans[10]);
        sem_wait(&ans[11]);
        sem_wait(&ans[12]);
        sem_wait(&ans[13]);
        sem_wait(&ans[14]);
        
        gettimeofday(&end, 0);
        
        for(i=0;i<times;i++){
            pthread_cancel(thread[i]);
        }
        
        sec = end.tv_sec - start.tv_sec;
        usec = end.tv_usec - start.tv_usec;
        printf("n=%d\n",times);
        printf("Elapsed time: %f ms \n", (sec*1000+(usec/1000.0)));
        file_name[7]=times+'0';
        out1=fopen(file_name, "w");
        if(!out1){
            printf("no exist\n");
            return 0;
        }
        for (j=0; j!=size; j++) {
            fprintf(out1,"%d ",input[j]);
        }
        fclose(out1);
        for (j=0; j!=2; j++) {
            sem_init(&sem1[j], 0, 0);
            sem_init(&sem2[j], 0, 0);
            sem_init(&sem3[j], 0, 0);
            //printf("a\n");
        }
        for (j=0; j!=8; j++) {
            sem_init(&sem4[j], 0, 0);
        }
        for (j=0; j!=15; j++) {
            sem_init(&ans[j], 1, 0);
        }
        sem_init(&sa,0,1);
        
    }
    
    
    
    
    
    
    
    
    return 0;
}






