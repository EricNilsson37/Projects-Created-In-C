#include <stdlib.h>
#include <stdio.h>

int main(){

  int TOTAL_DEGREES = 300;

  double cel;
  int i;
  printf("Fahrenheit-Celsius\n");

  for(i = 0; i <= TOTAL_DEGREES; i += 20){

    cel = (5.0*(i-32.0))/9;

    printf("%6d",i);
    printf("%11.1f\n", cel);

  }

  return 0;

}
