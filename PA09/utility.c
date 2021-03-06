#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pa09.h"

//create a leaf node
HuffNode * NodeCreate(int data)
{
  HuffNode * base = malloc(sizeof(HuffNode));
  base -> value = data;
  base -> right = NULL;
  base -> left = NULL;

  return base;
}

//Push function to push the new node to the top of the stack
Stack * Push(Stack *st, HuffNode * tree)
{
  Stack * topnode = malloc(sizeof(Stack));
  topnode-> node = tree;
  topnode -> next = st;
  return topnode;
}

//Pops the stack to get rid of accounted for branches
Stack * Pop(Stack * st)
{
  if (st == NULL)
    {
      return NULL;
    }
  Stack * base = st->next;
  free(st);
  return base;
}

HuffNode * TreeCreate(FILE *fh)
{
  Stack * st = NULL; //Creates empty stack

  int byte; //holds value of the byte in the header
  int val; //holds value if the byte is 1
  int end = 0; //Terminates the loops when this is zero
  HuffNode * root = NULL; //Creates a Node for the roots to be stored in.
 
  while(end != 1) //Runs the loop until end is 1
    {
      byte = fgetc(fh); //grabs the next byte of the header
      if (byte == '1') //If byte is a leaf node, grabs the next bte and creates a leaf node for it.  Pops the stack.
      {
	val = fgetc(fh);
	HuffNode * t = NodeCreate(val);
	st = Push(st,t);
      }
      else //creates intermediate nodes if the byte is not 1.  Pops the stack and pushes the stack.  Also ends the loop if we are at the end of the header.
	{
	  HuffNode * A = st -> node;
	  st = Pop(st);
	  if(st == NULL)
	    {
	      end = 1;
	      root =  A;
	    }
	  else
	    {
	      HuffNode * B = st -> node;
	      st = Pop(st);
	      HuffNode * mid = malloc(sizeof(HuffNode));
	      mid -> value = 0;
	      mid -> right = A;
	      mid -> left = B;
	      st = Push(st, mid);
	    }
	}
    }
    return root;
}

void HuffPrintToFile(HuffNode * base, FILE * savefile)
{
    // Base case: empty subtree
    if (base == NULL)
      {
	return;
      }

    // Recursive case: post-order traversal

    // Visit left
    fprintf(savefile, "Left\n");
    HuffPrintToFile(base->left, savefile);
    fprintf(savefile, "Back\n");
   
    // Visit right
    fprintf(savefile, "Right\n");
    HuffPrintToFile(base->right, savefile);
    fprintf(savefile, "Back\n");
   
    // Visit node itself (only if leaf)
    if (base->left == NULL && base->right == NULL)
      {
	fprintf(savefile, "Leaf: %c\n", base->value);
      }
}

void TreeDelete(HuffNode *base)
{
  if (base == NULL) //finds the leaf nodes.
    {
      return;
    }

  TreeDelete(base -> left); //deletes left side of tree
  TreeDelete(base -> right); //deletes right side of tree
  free(base); //frees the base of the tree
  return;
}

HuffNode * bitCreate(FILE * fh)
{
  char mask1[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01}; //Masks so that there is only one bit in the command byte.  
  char mask2[8] = {0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00}; //Masks everything before the command bit
  char mask3[8] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF}; //Masks everything after the command bit of the NEXT byte
  int shift1[8] = {1,2,3,4,5,6,7,8}; //Shifts the first byte to the beginning of a new bte
  int shift2[8] = {7,6,5,4,3,2,1,0}; //Shifts the second bte to the end of the new byte.
  int counter = 0; //counts where in the byte I am
  char end = 0; //flags when the loop should end
  char data = 0; //Holds the data that is combined from the two seperate bytes
  char wholebyte = 0;
  char command = 0;
  Stack * st = NULL;
  HuffNode * tn = NULL;
  HuffNode * base = NULL;
  unsigned char temp1 = 0;
  unsigned char temp2 = 0;

  wholebyte = fgetc(fh); //Gets the first byte of the program

  while (end == 0) //runs while we are not at the end of the data.
    {
      if (counter == 8) //if we are at the end of the byte, grabs the next byte and resets the counter
        {
          wholebyte = fgetc(fh);
          counter = 0;
        }
      
      command = wholebyte & mask1[counter]; //Masks the byte to get the bit of interst
      if (command != 0) //If bit is not zero (1), this find the char after the bit.
        {
          temp1 = wholebyte & mask2[counter];
          wholebyte = fgetc(fh);
          temp2 = wholebyte & mask3[counter];

          temp1 = temp1 << shift1[counter];
          temp2 = temp2 >> shift2[counter];
          data = temp1 | temp2;

          tn = NodeCreate(data);
          st = Push(st, tn);
          counter++;
        }
      
      else // if the command bit is zero, this pops the nodes in the correct order
        {
          HuffNode *A = st->node;
          st = Pop(st);
          if (st == NULL) //If we are at the end of the header, this ends the loop
            {
              end = 1;
              base = A;
            }

          else //this pops and pushes the stack to make the tree correctly.
            {
              HuffNode * B = st->node;
              st = Pop(st);
              HuffNode * mid = malloc(sizeof(HuffNode));
              mid->value = 0;
              mid->right = A;
              mid->left = B;
              st = Push(st, mid);
              counter++;
            }
        }
    }

  return base; //returns the base of the tree.
}
