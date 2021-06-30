// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include "linked_list_functions.h"
#include "unit_tests.h"

// Implement this function first to create an initialized linked list node.
// It must allocate space for the passed string in the one_word structure.
// It must copy the passed string into that structure and sets its word count to 1.
// Assume that the passed word points is not NULL and is not an empty string.
// The calling function is responsible for passing a valid string.
// This function returns a pointer to the allocated node.
struct node *create_node( char *word )
{
  struct word_entry entry;// word_entry struct for the node
  entry.unique_word = malloc(strlen(word) +1);
  strcpy(entry.unique_word, word);// copies a string pointer to a string pointer 
  entry.word_count = 1;
  struct node *first = malloc(sizeof (struct node));

  first->one_word = entry;//the value of the word_entry in node
  first->p_previous = NULL;// next node
  first->p_next = NULL;//previous node

  return first;
}

// Inserts a node at the beginning of the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Returns 0 for failure if either word test fails.
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the passed p_head and p_current members of p_list.
// p_head and p_current will always point to the newly added node.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
int add_node_at_head( struct linked_list *p_list, char *word )
{
  if(p_list == NULL || word == NULL || *word == '\0'){//checks to make sure that none of the values or pointers are null
    return 0;
  }

  struct node *current = create_node(word);
  
  current->p_next = p_list->p_head;// makes the currents node next node the node infront of it in the list

  if(p_list->p_head ==NULL){// if the head is empty the list is empty snd this is the first node
    p_list->p_tail = current;
  }
  else if(p_list->p_head !=NULL){//there is something already in the node
    p_list->p_head->p_previous = current;
  }

  p_list->p_head = current;//sets the current head of the list to the node
  p_list->p_current = current;//sets the current node in the list to the current node
  
  return 1;

  
}

// For the passed linked_list pointer free all of the nodes in the list.
// Be careful to free the space for the string before freeing the node itself.
// Also be careful to save a copy of the pointer to the next item in the list before
// freeing the node.
// Lastly, return the number of nodes freed (which could be zero if p_list indicates an empty list).
int clear_linked_list( struct linked_list *p_list )
{
  int count = 0;
  struct node *holder;
 
  while(p_list->p_current != NULL){// gets rid of all the nodes in list
    count +=1;

    holder = p_list->p_current->p_next; //holds the next current nodes 
    
    free(p_list->p_current->one_word.unique_word);
    p_list->p_current->one_word.unique_word = NULL;//sets the current nodes unique word to NULL
    free(p_list->p_current);
    p_list->p_current = NULL;//sets the node to NULL
    
    p_list->p_current = holder;//changes the current node to the nexts current node

  }

  free(holder);
  p_list->p_head = NULL;// sets the rest of the lists to NULL
  p_list->p_tail = NULL;
  
  return count;
}


// Inserts a node after the current pointer in the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Returns 0 for failure if either word test fails.
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the p_current member of p_list. p_current points to the newly added node.
// p_head is updated only if p_current is NULL (an empty list).
// p_tail is updated only if the new node is at the end of the list.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
// Hint: if this function is called with a p_current that is NULL (meaning the list is empty)
//       use the add_node_at_head function to create the new node.
int add_node_after_current( struct linked_list *p_list, char *word )
{
  //where the parameter arent ok
  if(p_list == NULL || word == NULL || *word == '\0'){
    return 0;
  }

  struct node *new_current = create_node(word);
  //if the node being added is the only node in the list
  if(p_list->p_current == NULL){
    add_node_at_head(p_list, word);
    return 1;
  }
  //links the new nodes to the nodes already in the list
  new_current->p_previous = p_list->p_current;
  new_current->p_next = p_list->p_current->p_next;

  //the new node being put in is the last node in the list now
  if(strcmp(p_list->p_current->one_word.unique_word, p_list->p_tail->one_word.unique_word) == 0){
    p_list->p_current->p_next = new_current;
    new_current->p_previous = p_list->p_current;
    p_list->p_tail = new_current;
    p_list->p_current = new_current;
    return 1;
  }
  // sets the nodes and p_list in every other scenario
  p_list->p_head->p_next = new_current;
  p_list->p_tail->p_previous = new_current;
  p_list->p_current = new_current;
  return 1;
}

// Searches the linked list for the passed word.
// NOTE -- this function REQUIRES that the linked list has been maintained in English language alphabetical order.
// Definition of match: every letter must match exactly including by case.
// e.g. "A" does NOT match "a". "a " does NOT match "a"
//
// If found it sets the current pointer to the matching node.
// If not found it returns a failure and sets the current pointer to the node just before the
// insertion point (by alphabetic order). Note the special case for a new word that goes at the
// beginning of the list. See the examples below.
//
// Hint: use strcmp to determine sorting order.
//
// If it is found the current pointer is set to the node containing the matching word.
// If it is found this function returns a 1 to indicate success.
//
// If it is not found the current pointer is set to the node just before the insertion point.
// If it is not found the function returns a 0 to indicate failure.
// e.g. the list contains the words "apple", "buy", "cat".
//      Searching for "baby" would set current to the node containing "apple".
//      Searching for "acid" would set current to NULL to indicate that "acid" belongs at the head.
//      searching for "zebra" would set current to the node containing "cat".
//
// Tests on p_list and word: p_list, p_list->head, and word must all not be NULL.
// In addition, word must not be an empty string.
// We must have a valid list with at least one node and we must a valid word to match.
// If any of these conditions are violated this function returns a -1 to indicate invalid input.
int find_word( struct linked_list *p_list, char *word )
{
  //checks to make sure all of the parameters are in order
  if(p_list == NULL || p_list->p_head == NULL || word == NULL || *word == '\0'){
    return -1;
  }

  struct node *holder = p_list->p_head;
  //checks the make sure the first word in the list matches the word
  if(strcmp(word, p_list->p_head->one_word.unique_word) == 0){
    p_list->p_current = p_list->p_head;
    return 1;
  }
  // the word will be in the list
  while(holder != NULL){

    p_list->p_current = holder;
    //checks to see if the words are equal
    if(strcmp(word, holder->one_word.unique_word)== 0){      
      return 1;
    }
    holder = holder->p_next;
  }
  //resests everything
  holder = p_list->p_head;

  //the word is not going to be in the list
  while(holder != NULL){
    p_list->p_current = holder;

    if(strcmp(word, holder->one_word.unique_word)< 0){
      // the word would go in  the front of the list
      if(strcmp(holder->one_word.unique_word, p_list->p_head->one_word.unique_word) ==0){
	p_list->p_current = NULL;
	return 0;
      }
      p_list->p_current = holder->p_previous;
      return 0;
    }
   
    holder = holder->p_next;
  }
  // the word is being put at the end of the list
  return 0;
}

