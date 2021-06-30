/***
 * Functions for the DMV customer scheduling and service application.
 * Implementation file.
 ***/

#include <stdlib.h>
#include "dmv_schedule.h"

/*
 * Actual definition of the line array of service lines.
 */
struct service_line line[NLINES] ;

/*
 * Initialize the service lines so that (a) line[0] has priority 'A'
 * through line[2] having priority 'C' and (b) there are no customers
 * in any line.
 * NOTES: As usual, an empty list is signified by a NULL pointer.
 */
void init_service_lines() {

  //sets the priority of each line and makes it so it has no customers head
  //becasue if there is no head there is no line
  line[0].priority = 'A';
  line[0].head_of_line = NULL;
  line[1].priority = 'B';
  line[1].head_of_line = NULL;
  line[2].priority = 'C';
  line[2].head_of_line = NULL;
  
}

/*
 * Return the next ticket number.
 * 	The first customer gets ticket number 1.
 *	The number increases by 1 on each call.
 * Local (static) int ticket holds the current ticket value.
 */
static int ticket = 1 ;
int next_ticket() {

  //will hold the current ticket then add one to the count for the next customer
  //and then return the holder int for what the ticket was
  int holder = ticket;

  ticket +=1;
  return holder;
}

/*
 * A new customer arrives with the given <priority> and
 * <ticket_number>. The customer is placed at the end of
 * the appropriate service line.
 */
void new_customer(char priority, int ticket_number) {

  
  struct customer* new_guy = malloc(sizeof(struct customer));
  struct customer* current_customer = malloc(sizeof(struct customer));
  int line_num;

  new_guy->ticket_number = ticket_number;
  new_guy->next_customer = NULL;

  //finds out which line it is
  if( priority == 'A'){
    line_num = 0;
  }
  else if(priority == 'B'){
    line_num = 1;
  }
  else{
    line_num = 2;
  }

  // will add it at the head
  if(line[line_num].head_of_line == NULL){
    line[line_num].head_of_line = new_guy;
  }

  else{
    // will go through and find wher the end is and add it at the end
      current_customer = line[line_num].head_of_line;
      
      while(current_customer->next_customer != NULL){
	current_customer = current_customer->next_customer;
      }
      current_customer->next_customer = new_guy;
    }
  
  
}

/*
 * Return the ticket number of the first customer in the
 * line for <priority> after removing the customer from the
 * associated service_line.
 *
 * Return NO_CUSTOMER if there are no customers in the indicated line.
 */
int serve_customer(char priority) {

  int ticket;
  int line_num;
  //finds out which line it is                                                             
  if( priority == 'A'){
    line_num = 0;
  }
  else if(priority == 'B'){
    line_num = 1;
  }
  else{
    line_num = 2;
  }

  // there is no customer
  if(line[line_num].head_of_line == NULL){
    return NO_CUSTOMER;
  }
  //remove the customer at the head and then replace the next customer with the current
  else{
    ticket = line[line_num].head_of_line->ticket_number;
    line[line_num].head_of_line = line[line_num].head_of_line->next_customer;
    
  }

  return ticket;
}

/*
 * Return the ticket number of the first customer in the highest
 * priority line that has customers after removing the customer
 * from the line. 'A' is highest priority and 'C' is lowest.
 *
 * Return NO_CUSTOMER if there are no customers in any of the lines.
 *
 * Example: if there are 0 customers in the 'A' line, 3 customers in the 'B'
 *          line and 2 customers in the 'C' line, then the first customer in
 *          the 'B' line would be removed and his/her ticket number returned.
 */
int serve_highest_priority_customer() {
  int ticket;
  int line_num;
  //will find go to the first priority list and return the head customer if there is one
  if(line[0].head_of_line != NULL){
    ticket = serve_customer('A');
    return ticket;
  }
  else if(line[1].head_of_line != NULL){
    ticket = serve_customer('B');
    return ticket;
  }
  else if(line[2].head_of_line != NULL){
    ticket = serve_customer('C');
    return ticket;
  }
  // there are no customer in any list
  else{
    return NO_CUSTOMER; 
  }

}

/*
 * Return the number of customers in the service line for <priority>
 */
int customer_count(char priority) {
  int count = 0;
  int line_holder;
  struct customer* current_customer = malloc(sizeof(struct customer));

  //will set which line to go down
  if(priority == 'A'){
    line_holder = 0;
  }
  else if(priority == 'B'){
    line_holder = 1;
  }
  else{
    line_holder = 2;
  }
  //checks to see if there is a customer in the line
  if(line[line_holder].head_of_line == NULL){
    return count;
  }
  else{
    current_customer = line[line_holder].head_of_line;
    count +=1;
    //will loop through how many customers there are in the list
    while(current_customer->next_customer != NULL){
      count +=1;
      current_customer = current_customer->next_customer;
    }
    return count;
  }
}

/*
 * Return the number of customers in all service lines.
 */
int customer_count_all() {
  int all_count = 0;

  all_count += customer_count('A');
  all_count += customer_count('B');
  all_count += customer_count('C');

  return all_count;
}
