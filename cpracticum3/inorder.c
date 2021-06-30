/*
* Inorder - Implement a non-recursive inorder traversal
*		of a sorted binary tree
*
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

struct treeNode { 
   int data; 			/* tree node value */
   struct treeNode *leftPtr;  /* pointer to left subtree */
   struct treeNode *rightPtr; /* pointer to right subtree */
}; 

struct stackEntry {
  struct treeNode *treePtr;  /* list value */
  struct stackEntry *next;   /* pointer to next entry in list */
};

struct stackEntry *stackHead = NULL;    /* pointer to head of stack */


/************************************************************
 push - add new node at beginning of list
 
************************************************************/
void push(struct treeNode *treePtr) {
  struct stackEntry *newNode;

  newNode = malloc(sizeof(struct stackEntry)); // need to free up the space used for the node
  
  newNode->treePtr = treePtr;
  newNode->next = stackHead;
  stackHead = newNode;
}

/********************************************************************
 pop - delete node at beginning of non-empty list and return its data

 *******************************************************************/
struct treeNode *pop() {
  struct stackEntry *current;
  struct treeNode *val;

  current = stackHead;
  stackHead = current->next;
  val = current->treePtr;
  if (val != NULL) {
    free(current);
  }

  return(val);
}


/****************************************************************
 insertTreeNode - inserts a tree node into a sorted binary tree
( DO NOT EDIT THIS FUNCTION )
 ***************************************************************/
void insertTreeNode( struct treeNode **treePtr, int value )
{ 
   if ( *treePtr == NULL ) {   
      *treePtr = malloc( sizeof( struct treeNode ) );
      ( *treePtr )->data = value;
      ( *treePtr )->leftPtr = NULL;
      ( *treePtr )->rightPtr = NULL;
   } 
   else { /* tree is not empty */
      /* data to insert is less than data in current node */
      if ( value < ( *treePtr )->data ) {
         insertTreeNode( &( ( *treePtr )->leftPtr ), value );
      } 
      /* data to insert is greater than data in current node */
      else if ( value > ( *treePtr )->data ) {
         insertTreeNode( &( ( *treePtr )->rightPtr ), value );
      } 
      else { /* duplicate data values ignored */
         printf( "dup" );
      } 
   } 
} 

/****************************************************************
 inOrder - non-recursive inorder traversal of tree, prints value 
		of tree nodes in ascending order
 ***************************************************************/

void inOrder( struct treeNode *treePtr )
{ 

  if(treePtr == NULL){ // checks to make sure that the treePtr is not empty
    return;
  }
  
  struct treeNode *current;
  char done = FALSE; 
  
  stackHead = NULL;

  current = treePtr;

  while( done == FALSE ){
    while( current->rightPtr != NULL){     
      push( current );
      current = current->leftPtr;          
    }
    printf(" %d ", current->data);

    while( current->leftPtr == NULL ){
	if( stackHead == NULL ){
	  done = TRUE;
	  printf("\n");
	  break;
	}
	else {
    
	  current = pop( );
	  
	}
    }
    current = current->rightPtr;
  }    
    
} 

/**************************************************************************
 main - function main begins program execution - no command line parameters 
***************************************************************************/
int main()
{ 
   struct treeNode *rootPtr = NULL;

   printf("\n\nThe inOrder traversal for an empty tree:\n");
   printf("Should be blank\n\n");
   inOrder( rootPtr );
   
   /* root node only */
   insertTreeNode( &rootPtr, 20 );
   printf("\n\nThe inOrder traversal for a tree with one node:\n");
   printf("Should be 20 \n\n");
   inOrder( rootPtr );

   /* insert sample values in the tree */
   rootPtr = NULL;
   insertTreeNode( &rootPtr, 8 );
   insertTreeNode( &rootPtr, 12);
   insertTreeNode( &rootPtr, 10);
   insertTreeNode( &rootPtr, 4);
   insertTreeNode( &rootPtr, 6);
   insertTreeNode( &rootPtr, 2);
   printf( "\n\nThe inOrder traversal for the sample tree:\n" );
   printf("Should be 2 4 6 8 10 12 \n\n");
   inOrder( rootPtr );

   /* unbalanced - left */
   rootPtr = NULL;
   insertTreeNode( &rootPtr, 10);
   insertTreeNode( &rootPtr, 8);
   insertTreeNode( &rootPtr, 6);
   printf("\n\nThe inorder traversal for unbalanced left\n");
   printf("Should be 6 8 10 \n\n");
   inOrder( rootPtr );
   

   /* unbalanced - right */
   rootPtr = NULL;
   insertTreeNode( &rootPtr, 6);
   insertTreeNode( &rootPtr, 8);
   insertTreeNode( &rootPtr, 10);
   printf("\n\nThe inorder traversal for unbalanced right\n");
   printf("Should be 6 8 10 \n\n");
   inOrder( rootPtr );
 


   return 0; 

} /* end main */
