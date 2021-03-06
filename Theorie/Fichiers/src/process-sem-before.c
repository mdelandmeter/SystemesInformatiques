/**************************************
 * process-sem-before.c
 *
 * Programme d'exemple de sémaphores
 * La fonction after ne peut s'exécuter
 * qu'après la fonction before
 **************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>


void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}


///AAA

sem_t *semaphore;

void before() {
  // do something
  for(int j=0;j<1000000;j++) {
  }
  printf("before done, pid=%d\n",(int) getpid());
  sem_post(semaphore);
}


int main (int argc, char *argv[])  {

  int err;

  semaphore=sem_open("lsinf1252",O_CREAT,S_IRUSR | S_IWUSR,0);
  if(semaphore==SEM_FAILED) {
    error(-1,"sem_open");
  }
  sleep(20);
  before();
  err=sem_close(semaphore);
  if(err!=0) {
      error(err,"sem_close");
  }
  return(EXIT_SUCCESS);
}
///BBB
