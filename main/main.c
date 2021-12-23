#include <stdio.h>
#include <string.h>
#include <stdlib.h> // in order to allocate memory 

typedef struct  {
  char firstName[20];
  char lastName[20];
  int age;
}Person;

//This is an example to understand how the memory is updated.
void updatePerson(Person *person, char * dataRetreieved){ // with this we can access to the same location of memory and dont make a copy 
  strcpy(person->firstName,"data from dataRetreieved");
  strcpy(person->lastName,"data from dataRetreieved");
  person->age = 35;
}
void connectAndGetInfo(char *url,void(*DoWork)(char *dataRetreieved)){
  //connect to wireless
  //connect to end point
  //allocate memory 
  char *dataRetreieved=(char *)malloc(1024);
  //fill buffer with data : getRequest(&dataRetreived);
  //do work and geta person object 
  DoWork(dataRetreieved);
  //clean up memory and other resources
  free((void*)dataRetreieved);
}

void DoWork(char *dataRetreieved){
  Person person;
  updatePerson(&person,dataRetreieved);
  printf("person : %s %s is %d yeards old \n",personx.firstName, personx.lastName,personx.age);  
}

void app_main(void)
{


  connectAndGetInfo("https:getperson.com",DoWor);
}
 