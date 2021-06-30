#include <stdlib.h>
#include <stdio.h>

int main(){
  
  int TOTAL_DEGREES = 300;

  int cel;
  int i;
  printf("Fahrenheit-Celsius\n");

  for(i = 0; i <= TOTAL_DEGREES; i += 20){

    cel = (5.0*(i-32.0))/9;

    printf("    %-5d    ",i);
    printf("%-d\n", cel);

  }  

  return 0;

}
