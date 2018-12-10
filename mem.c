#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>


int main(int argc, char * argv[]){
  key_t key;
  int shmid;
  char * str;
  int mode;

  //make the key
  key = ftok("mem", 'R');

  //allocate shared memory segment
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  //get pointer to segment
  str = shmat(shmid, (void *)0, 0);
  if(str[0]){
    printf("This is the segment: %s\n", str);
  }
  else{
    printf("Segment was just created!\n");
  }
  char input[200];
  printf("Type Change (Add to segment) OR Delete (Delete segment)\n");
  fgets(input, 200, stdin);
  if(!strcmp(input, "Change\n")){
    printf("Please enter new string to put into segment: \n" );
    fgets(input, 200, stdin);
    input[strlen(input)-1] = 0;
    strcpy(str, input);
    printf("Segment changed\n");
  }
  else if(!strcmp(input, "Delete\n")){
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Segment deleted\n");
  }
  return 0;
}
