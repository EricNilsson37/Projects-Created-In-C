/* delete - binary tree with non-recursive delete operation

*/

#include <stdio.h>
#include <stdlib.h>

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
( DO NOT EDIT THIS FUNCTION ) 
************************************************************/
void push(struct treeNode *treePtr) {
  struct stackEntry *newNode;

  newNode = malloc(sizeof(struct stackEntry));

  newNode->treePtr = treePtr;
  newNode->next = stackHead;
  stackHead = newNode;
}

/********************************************************************
 pop - delete node at beginning of non-empty list and return its data
( DO NOT EDIT THIS FUNCTION )
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
      else { /* duplicate data value ignored */
         printf( "dup" );
      } 
   } 
} /* end function insertTreeNode */

/****************************************************************
 Delete - deletes a node in a binary tree
 
 COMPLETE THIS FUNCTION
 
 ***************************************************************/
void delete( struct treeNode **treePtr, struct treeNode** rootRef )
{ 
  struct treeNode *current = NULL;
  
  current = *treePtr;	// current is address of the parent's sub-tree pointer to the node to be deleted

  push(current->leftPtr);
  push(current->rightPtr);

  current->leftPtr = NULL;
  current->rightPtr = NULL;

  while(stackHead != NULL){
    if(find(stackHead->current)!= NULL){
    insertTreeNode(next, pop(stackHead));
  }
  }
}

/****************************************************************
 find - finds a node in a binary tree, assumes value is in tree
 ( DO NOT EDIT THIS FUNCTION )
 ***************************************************************/
struct treeNode* find( struct treeNode *treePtr, int value )
{ 
  if (treePtr->data == value) {
    return(treePtr);
  }
  if (treePtr->data > value) {
    return(find(treePtr->leftPtr, value));
  }
  if (treePtr->data < value) {
    return(find(treePtr->rightPtr, value));
  }
  return(NULL);
}

/****************************************************************
 inOrder - non-recursive inorder traversal of tree, prints value 
		of tree nodes in ascending order
( DO NOT EDIT THIS FUNCTION )
 ***************************************************************/
void inOrder( struct treeNode *treePtr )
{ 
   /* if tree is not empty then traverse */
   if ( treePtr != NULL ) { 
      inOrder( treePtr->leftPtr );
      printf( "%3d", treePtr->data );
      inOrder( treePtr->rightPtr );
   } /* end if */

} /* end function inOrder */

/****************************************************************
 preOrder - recursive preorder traversal of tree
 ( DO NOT EDIT THIS FUNCTION )
 ***************************************************************/
void preOrder( struct treeNode *treePtr )
{ 
   /* if tree is not empty then traverse */
   if ( treePtr != NULL ) { 
      printf( "%3d", treePtr->data );
      preOrder( treePtr->leftPtr );
      preOrder( treePtr->rightPtr );
   } /* end if */

} /* end function preOrder */

/* function main begins program execution */
int main()
{ 
   struct treeNode *rootPtr = NULL; 
   int i;
   struct treeNode *ptr = NULL; 

   printf("Inserting: ");
   insertTreeNode( &rootPtr, 8 );
   printf("%d ", 8);
   insertTreeNode( &rootPtr, 4 );
   printf("%d ", 4);
   insertTreeNode( &rootPtr, 12 );
   printf("%d ", 12);
   for ( i = 2; i <= 14; i=i+4 ) { 
      insertTreeNode( &rootPtr, i );
      printf("%d ", i);
   } /* end for */
   for ( i = 1; i <= 15; i=i+2 ) { 
      insertTreeNode( &rootPtr, i );
      printf("%d ", i);
   } /* end for */


   printf("\n\n");

   /* traverse the tree inOrder */
   printf( "The inOrder traversal is:\n" );
   inOrder( rootPtr );
   printf("\n\n");


   printf("Deleting left of 4 = 2\n");
   ptr = find(rootPtr, 4);
   delete(&(ptr->leftPtr), &rootPtr);
   /* traverse the tree inOrder */
   printf( "The inOrder traversal is:\n" );
   inOrder( rootPtr );
   printf("\n\n");

   printf("Deleting left of 14 = 13\n");
   ptr = find(rootPtr, 14);
   delete(&(ptr->leftPtr), &rootPtr);
   /* traverse the tree inOrder */
   printf( "The inOrder traversal is:\n" );
   inOrder( rootPtr );
   printf("\n\n");


   printf("Deleting right of 12 = 14\n");
   ptr = find(rootPtr, 12);
   delete(&(ptr->rightPtr), &rootPtr);

   /* traverse the tree inOrder */
   printf( "The inOrder traversal is:\n" );
   inOrder( rootPtr );
   printf("\n\n");

   return 0; /* indicates successful termination */

} /* end main */


