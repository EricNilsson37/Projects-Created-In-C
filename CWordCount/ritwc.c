#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define FALSE (0)
#define TRUE  (1)

int main() {
	int tot_chars = 0 ;	/* total characters */
	int tot_lines = 0 ;	/* total lines */
	int tot_words = 0 ;	/* total words */
	int c = getchar();
	int num_char = 0 ;// used to counts the number of chars before a space

	while( c != EOF){// will loop through the entire file given
	  
	  if(isspace(c) == 0){// will check to see if the char is not a space represented char
	    tot_chars +=1;
	    num_char +=1;
	  }
	  if(c== '\n'){//used to see if the char is a new line
	    tot_lines +=1;
	    tot_chars +=1;
	    if(num_char > 0){// if there was a space before or a newline before the next newline 
	      tot_words +=1;//it will not count that as a word since
	      num_char =0;//2 spaces is not a word
	    }}
	  if( isspace(c) != 0 && c != '\n'){// make sure to check that the char is a space character
	    tot_chars +=1;// that is not a newline char
	    if (num_char >0){// makes sure that the char before the call was an actual char
	      num_char =0;//and not another space type char
	    tot_words +=1;


	    
	    }}
	  c = getchar();// used to get the next char in the file}
	}
	  printf("%8d%8d%8d\n",tot_lines, tot_words, tot_chars);// prints the value seen in the original
	    //word count program
	return 0;
}
