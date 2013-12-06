#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack * node = malloc(sizeof(Stack));
  node->list = NULL;
  return node;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */

void Stack_destroy(Stack * stack)
{
  if(stack == NULL)
    {
      return;
    }
  if(stack -> list == NULL)
    {
      free(stack);
      return;
    }
  ListNode * top = stack->list;
  stack->list = top->next;
  free(top);
  Stack_destroy(stack);
  return;
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if(stack == NULL || stack -> list == NULL)
    {
      return TRUE;
    }
  return FALSE;
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{

  ListNode * pop = stack -> list;
  int val = pop -> value;
  stack -> list = pop -> next;
  free(pop);
  return val;
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
  ListNode * push = malloc(sizeof(ListNode));

  push -> value = value;
  push -> next = stack -> list;
  stack -> list = push;
  return;
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */

void stackSort(int * array, int len)
{

  int printind = 0;
  Stack * stack = NULL;
  stack = Stack_create();
  int count = 1;
  ListNode * top;
  int val;

  Stack_push(stack, array[printind]);
  while(count < len)
    {
      top = stack -> list;
      if (array[count] < top->value)
	{
	  Stack_push(stack, array[count]);
	}
      else
	{
	  while ((array[count] > top -> value) && (stack->list != NULL))
	    {
	      val = Stack_pop(stack);
	      array[printind] = val;
	      printind++;
	    }
	  Stack_push(stack,array[count]);
	}
      count++;
    }

  while(stack->list != NULL)
    {
      val = Stack_pop(stack);
      array[printind] = val;
      printind++;
    }

  Stack_destroy(stack);

}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int isStackSortable(int * array, int len)
{
  int max = 0;
  int maxcomp = 0;
  int mincomp;
  int count;
  int maxindex;
  int left;
  int right;

  if(len < 3)
    {
      return TRUE;
    }

  for(count = 0; count < len; count++)
    {
      if(array[count] > max)
	{
	  max = array[count];
	  maxindex = count;
	}
    }
  mincomp = max;
  for(count = 0; count < maxindex; count++)
    {
      if(array[count] > maxcomp)
	{
	  maxcomp = array[count];
	}
    }
  for(count = maxindex+1;count < len;count++)
    {
      if(array[count] < mincomp)
	{
	  mincomp = array[count];
	}
    }

  if(maxcomp > mincomp)
    {
      return FALSE;
    }

  left = isStackSortable(array, maxindex);
  right = isStackSortable(&array[maxindex + 1],(len-maxindex-1));
  if((left == TRUE) && (right == TRUE))
    {
      return TRUE;
    }

    return FALSE;
}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [0..k-1] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */


void swap(int * a, int * b)
{
  int temp;
  temp = * a;
  * a = * b;
  *b = temp;
}

void permute(int * arr, int ind, int len)
{
  int i;
  int sortable;

  if(ind == len)
    {
      sortable = isStackSortable(arr, len);
      if(sortable == 1)
	{
	  TreeNode * tn = Tree_build(arr, len);
	  Tree_printShape(tn);
	  Tree_destroy(tn);
	}
      return;
    }

  for(i=ind;i<len;i++)
    {
      swap(&arr[i],&arr[ind]);
      permute(arr,ind+1,len);
      swap(&arr[i],&arr[ind]);
    }
}

void genShapes(int k)
{
  int values[k];
  int count;

  for(count = 0;count < k;count++)
    {
      values[count]=count;
    }
  permute(values,0,k);
}
