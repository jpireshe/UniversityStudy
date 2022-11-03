#include <stdio.h>
#include <stdlib.h>

typedef struct stack_node{

	int data;
	struct stack_node* next_node;	
	
}stack_node;


typedef struct stack{

	struct stack_node* top_node;
	
}stack;



void push( stack* the_stack, int the_value ){
	
	stack_node* insert_node = (stack_node*)malloc( sizeof(stack_node) );
	
	insert_node->data = the_value;
	insert_node->next_node = NULL;
	
	// Check if the list is empty
	if( the_stack->top_node == NULL ){
		
		// Set the head node equal to insert_node 
		the_stack->top_node = insert_node;
		
		// And return
		return;
	}
	
	// Now we just need to use a reference pointer and put them in front
	stack_node* reference = the_stack->top_node;
	
	// Set the top_node to the new node 
	the_stack->top_node = insert_node;
	
	// Set the new top_node's next to the reference 
	the_stack->top_node->next_node = reference;
	
}

// Print the Singly Linked List 
void print_stack( stack_node* top_node ){

	stack_node* curr_ptr = top_node;
  //fprintf (stdout, "Top to bottom\n");
	while( curr_ptr != NULL ){
		
		// Only print the value
		fprintf( stdout, "%d \n", curr_ptr->data );		

		// Iterate through the next node
		curr_ptr = curr_ptr->next_node;

	}
	fprintf( stdout, "\n" );

}	


// Free all the elements 
void destructor( stack_node* curr_ptr ){
	
	//Check if top is NULL
	if( curr_ptr == NULL )
		return;
	

	// Recursively call destructor on the next node  
	destructor( curr_ptr->next_node );
		
	// Free the current pointer 
	free( curr_ptr );
	
}


// Pop Front 
void pop( stack* the_stack ){

  
	// Check if the list is not empty
	if( the_stack->top_node == NULL )
		return;
	
	// Otherwise, move the node and free
	// Set a reference pointer to top_node
  stack_node* reference = the_stack->top_node;
	
	// Set the top_node to top_node's next_node;
	the_stack->top_node = the_stack->top_node->next_node;
	
	// Free the reference 
	free( reference );
	
}


void in_to_out(stack* in_stack, stack* out_stack){
  while(in_stack->top_node != NULL) {
    push(out_stack, in_stack->top_node->data);
    pop(in_stack);
  }
}

void pop_queue(stack* in_stack, stack* out_stack) {
  if (out_stack->top_node != NULL) {
    pop (out_stack);
  } else {
    in_to_out (in_stack, out_stack);
    pop (out_stack);
  }
}


int main( const int argc, const char* argv[] ){

	// Dynamically allocate a stack 
	stack* in_stack = (stack *)malloc( sizeof( stack ) );
  stack* out_stack = (stack *)malloc( sizeof( stack ) );
	
	// Set the top_node to NULL 
	in_stack->top_node = NULL;
  out_stack->top_node = NULL;

  push (in_stack, 10);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  push (in_stack, -13);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  push (in_stack, 25);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  pop_queue (in_stack, out_stack);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  push (in_stack, 35);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  pop_queue (in_stack, out_stack);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  push (in_stack, 45);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  pop_queue (in_stack, out_stack);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  pop_queue (in_stack, out_stack);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
  pop_queue (in_stack, out_stack);
  fprintf (stdout, "Instack: \n");
  print_stack( in_stack->top_node );
  fprintf (stdout, "Outstack: \n");
  print_stack( out_stack->top_node );
  
	
	// Step 11 - Call the destructor
	destructor( in_stack->top_node );
  destructor( out_stack->top_node );

	
	// Step 5 - Free the stack 
	free( in_stack );
  free( out_stack );
	
	return EXIT_SUCCESS;
}