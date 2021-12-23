#include <stdio.h>
#include <string.h>

typedef struct  {
  char firstName[20];
  char lastName[20];
  int age;
}Person;

struct Person {
  char firstName[20];
  char lastName[20];
  int age;
};

//This is an example to understand how the memory is updated.
void updatePerson(Person *person){ // with this we can access to the same location of memory and dont make a copy 
  strcpy(person->firstName,"Bob");
  strcpy(person->lastName,"fisher");
  person->age = 35;
}
//
//void exclamIt(char *phrase){ // if you dont use * or [] it doent work
//  sprintf(phrase, "%s!",phrase);
//} // is the same use phrase[]

void app_main(void)
{
  Person person;
  //char phrase[20] = {"Hello world"};
  //exclamIt(phrase);

  struct Person personx;
  strcpy(personx.firstName,"Erick");
  strcpy(person.lastName,"fisher");
  personx.age = 35;
 
  updatePerson(&person);
  printf("person : %s %s is %d yeards old \n",personx.firstName, personx.lastName,personx.age);  
}
 