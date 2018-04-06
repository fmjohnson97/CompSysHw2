#include <stdio.h> 
#include <stdbool.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <semaphore.h> 
#include <unistd.h> 
#include <errno.h>

int total_keys; 

sem_t employeeKeys;
sem_t switchWorker;

break_time(){
    sleep(1);
}


working_window(){// this is the time the coders code
    printf("employees are coding in office\n");
    sleep(1);
}

clean_office(){//this is time the cleaners clean
    printf("cleaners are cleaning office\n");
    sleep(1);
}

void employee(){

    int keys;
    
    while(true){ 
    /*synchronization schemes*/
        wait(&switchWorker); // grabs a key if no cleaners
        wait(&employeeKeys); //grabs 1 of n keys
        
        working_window(); //works
        signal(&employeeKeys);  //gives up key
         
        while(true){     
          sem_getvalue(&employeeKeys,&keys);  
         
          if(keys==total_keys){ // all N workers left for break
              signal(&switchWorker); //swtich workers
              break;
           }  
        }
    /*synchronization schemes*/    
    
        break_time();
    }

}

void cleaner(){

    while(true){
    /*synchronization schemes*/
    wait(&switchWorker);
    
    clean_office();
    /*synchronization schemes*/
     signal(&switchWorker);
    
    break_time();
  
    }
}


int main(int argc, char ** argv){
 
   int e,c,i;
   printf("please enter the amount of employees: \n");
   scanf("%d",&e);
   
   total_keys=e;
   
    sem_init(&employeeKeys,0,e);
    sem_init(&switchWorker,0,1);
     
    pthread_t c_tid;
    pthread_t e_tid[e]; 
    pthread_attr_t attr;
    pthread_attr_init(&attr);
  
    pthread_create(&c_tid,&attr,(void*)cleaner,NULL);
    
    for(i=0;i<e;i++){
        pthread_create(&e_tid[i],&attr,(void*)employee,NULL);
    }
    
    pthread_join(c_tid,NULL);
    
    for(i=0;i<e;i++){
        pthread_join(e_tid[i],NULL);
    }
}
