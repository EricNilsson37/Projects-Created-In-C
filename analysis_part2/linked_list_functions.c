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
	struct node *p_node = calloc( 1, sizeof( struct node ) ) ;	// create a node with everything set to 0
	int destination_size = strlen( word ) + 1 ;					// be sure to include space for the end of string terminator '\0'
	p_node->one_word.unique_word = malloc( destination_size ) ;
	strlcpy( p_node->one_word.unique_word, word, destination_size ) ;
	p_node->one_word.word_count = 1 ;
	
	return p_node ;
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
	int success = 0 ;		// set to failure by default
	
	if ( p_list && word && *word )	// is p_list and word both not NULL and is word a non-empty string?
	{
		success = 1 ;		// we have a valid word to add so we will succeed.

		struct node *p_node_new = create_node( word ) ;		// create a node with this word filled in.
		p_list->p_current = p_node_new ;					// In all cases the current points to the new node.
		
		// Now that we have the new node we need to insert it into the beginning of the linked list.
		// If there is already an item in the list make the new node point to what was the previous head.
		if ( p_list->p_head )
		{
			p_list->p_head->p_previous = p_node_new ;	// the former head's previous pointer must now point to the new head
			p_node_new->p_next = p_list->p_head ;		// the new head next pointer must point to the previous head.
		}
		else
			p_list->p_tail = p_node_new ;	// List was previously empty so make the tail also point to the only item in the list.

		p_list->p_head = p_node_new ;		// now set the new node to be the head
	}
	return success ;
}

// For the passed linked_list pointer free all of the nodes in the list.
// Be careful to free the space for the string before freeing the node itself.
// Also be careful to save a copy of the pointer to the next item in the list before
// freeing the node.
// Lastly, return the number of nodes freed (which could be zero if p_list indicates an empty list).
int clear_linked_list( struct linked_list *p_list )
{
	int nodes_cleared_count = 0 ;		// number of nodes removed from the linked list.
	
	if ( p_list )
	{
		struct node *p_work = p_list->p_head ;
		
		// walk through the list and free each node until we get to the end.
		while ( p_work )
		{
			free( p_work->one_word.unique_word ) ;		// free just the string
			struct node *p_next = p_work->p_next ;		// save our next pointer so we can free the current node
			free( p_work ) ;							// now free the current node
			p_work = p_next ;							// now point to the next node to be freed (if any)
			nodes_cleared_count++ ;
		}
	}
	// clear out all of the pointers since this is now an empty list.
	p_list->p_head = NULL ;
	p_list->p_tail = NULL ;
	p_list->p_current = NULL ;
	return nodes_cleared_count ;
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
	int success = 0 ;		// set to failure by default
	
	if ( p_list->p_current == NULL )
		success = add_node_at_head( p_list, word ) ;
	else
	{
		struct node *p_node_new = create_node( word ) ;		// create a node with this word filled in.

		struct node *p_previous = p_list->p_current ;	// create work pointers for previous and next.
		struct node *p_next = p_list->p_current->p_next ;
			
		p_node_new->p_next = p_next ;					// now set up new nodes prev and next
		p_node_new->p_previous = p_previous ;
			
		p_previous->p_next = p_node_new ;				// add the new node into the forward linked chain

		p_list->p_current = p_node_new ;				// update current pointer to the node we just added
		if ( p_next == NULL )				// now see if we are at the end of the list.
			p_list->p_tail = p_node_new ;
		else
			p_next->p_previous = p_node_new ;			// add the new node into the backward linked chain
		
		success = 1 ;
	}

	return success ;
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
	int success = -1 ;		// set to invalid input failure by default
	
	if ( p_list && p_list->p_head && word && *word )	// only do a search with a valid list and valid word
	{
		struct node *p_work = p_list->p_head ;	// set up work pointer
		
		while ( p_work )
		{
			int result = strcmp( p_work->one_word.unique_word, word ) ;	// store value returned by strcmp
			if ( result == 0 )					// we found a match
			{
				success = 1 ;
				p_list->p_current = p_work ;	// set current to the match we found
			}
			else if ( result > 0 )				// word was not found in the list
			{
				success = 0 ;					// indicate that the word is not in the list
				p_list->p_current = p_work->p_previous ;	// return a pointer to the previous node (which might be NULL)
			}
			if ( success < 0 )					// are we still searching?
				p_work = p_work->p_next ;		// now move to the next node in the list.
			else
				break ;							// exit the search loop.
		}
		if ( p_work == NULL )
		{
			p_list->p_current = p_list->p_tail ;	// we reached the end and did not find it so set current to the tail.
			success = 0 ;							// Indicate that the word is not in the list.
		}
	}
	
	return success ;
}

