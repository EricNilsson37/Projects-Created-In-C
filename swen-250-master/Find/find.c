/*
 * Implementation of functions that find values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h>
 *****
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "find.h"

#define NOT_FOUND (-1)	// integer indicator for not found.

/*
 * Return the index of the first occurrence of <ch> in <string>,
 * or (-1) if the <ch> is not in <string>.
 */
int find_ch_index(char string[], char ch) {
  int x;
  // will loop through all the indexs of the strinf until it finds the char
  // if it doesnt find the char it just exits the loop and returns -1
  for(x = 0; x < sizeof(string); x ++){
    if(string[x] == ch){
      return x;
    }
  }
  return -1;
}

/*
 * Return a pointer to the first occurrence of <ch> in <string>,
 * or NULL if the <ch> is not in <string>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_ch_ptr(char *string, char ch) {

  //will go though every char in the pointer by chaing where the pointer looks
  // if it finds the char and where the pointer points at it will return
  // that location else it returns null if it exits the loop
  for(string; *string != '\0'; string ++){

    if(*string == ch){
      return string;
    }
  }
  return NULL;
}

/*
 * Return the index of the first occurrence of any character in <stop>
 * in the given <string>, or (-1) if the <string> contains no character
 * in <stop>.
 */
int find_any_index(char string[], char stop[]) {
  int x;
  int y;
  //will go through the string one char at a time by index and
  // then call another forloop by index of all the chars in stop
  // if the char that it's checking against all the chars of stop
  // matches it will return that index or if it exits the loop -1
  for(x = 0; string[x] != '\0'; x++){
    for(y = 0; stop[y] != '\0'; y++){
      if(string[x] == stop[y]){
       	return x;
      }
    }
  }
  return NOT_FOUND;
}

/*
 * Return a pointer to the first occurrence of any character in <stop>
 * in the given <string> or NULL if the <string> contains no characters
 * in <stop>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_any_ptr(char *string, char* stop) {

  int count = 0;
  //will loop through each point by calling the pointer location and then
  // moving through where the pointer points and checks the char at each of those spots
  // it it doesnt find a match it will reset the location of the second pointer
  //a and keep doing this until it goes through all memory locations of the first pointer
  for(string; *string != '\0'; string++){
    for(stop; *stop != '\0'; stop++){
      count ++;
      if(*string == *stop){
	return string;
      }
    }
      stop = stop - count;
      count =0;
    
  }
  return NULL;
}

/*
 * Return a pointer to the first character of the first occurrence of
 * <substr> in the given <string> or NULL if <substr> is not a substring
 * of <string>.
 * Note: An empty <substr> ("") matches *any* <string> at the <string>'s
 * start.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_substr(char *string, char* substr) {
  char *finder = find_ch_ptr(string, *substr);
  // checks to see if the substring is empty
  if(*substr == '\0'){
    return string; 
  }
  // checks to see if substring first char is even in
  // the string 
  if(finder == NULL){
    return NULL;
  }
  // will make string equal the finder and tehn loop through both the
  // string and substring and they should match since finder is the pointer
  // to the first char in the substr
  string = finder;
  for(substr; *substr != '\0'; substr++){
    if(*string != *substr){
      return NULL;
    }
    string ++;
	
  }
  return finder;
}
