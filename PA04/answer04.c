/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */
void printPartition(int * part, int length)
{
  int count; //Counting variable to print the entire array

  printf("= "); //prints leading equal sign once.
  for (count = 0; count < length - 1; count ++) //loop for printing all variable,s
    {
      printf("%d + ", part[count]); //prints variables and the + sign
    }
  printf("%d\n", part[length - 1]); //prints the last number in the array
}
void partition(int * part, int ind, int left)
{
  int val;  //counts the for loop to send value into the recursive fucntion
  if (left == 0) //if the sum is the number expected, then this triggars the print function
    {
      printPartition(part, ind);
      return;
    }
  for (val = 1; val <= left; val ++)  //for loop to recursively call the partition function in order to find sums
    {
      part[ind] = val; //places the value of val in the partition function
      partition(part, ind + 1, left - val);
    }
}

void partitionAll(int value)
{
  int * arr; //initalizes an array to store sum values
  arr = malloc(sizeof(int) * value); //allocates the max size the array can be
  printf("partitionAll %d\n", value);
  partition(arr, 0, value); //calls the partition fucntion
  free(arr); //frees the memory the array used.
  return;
  
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitioninc(int * part, int index, int left)
{
  int count = 0;

  if (left == 0)
    {
      printPartition(part, index);
    }

  for (count = 1; count <= left; count++) 
    {
      part[index] = count; //places counter value in the array

      if(index > 0) //loop for index greater than 1
	{ 
	  if(part[index - 1] < part[index]) //makes sure the next value is greater than the previous one.
	    {
	      partitioninc(part, index + 1, left - count);
	    }
	 
	}
    
      if (index == 0) //if count is 0, make sure it indexs to 1 in next recurstion
	{	  
	  partitioninc(part, index + 1, left - count);
	}
    }
}

void partitionIncreasing(int value)
{
  int * arr;
  arr = malloc(sizeof(int) * value);
  printf("partitionIncreasing %d\n", value);
  partitioninc(arr, 0, value);
  free(arr);
  return;
  

}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */
void partitiondec(int * part,int index,int left)
{
  int count = 0;

  if (left == 0)
    {
      printPartition(part, index);
    }

  for (count = 1; count <= left; count++)
    {
      part[index] = count;
     
      if(index > 0) //if the index is greater than zero, this starts the loop
	{ 
	  if(part[index - 1] > part[index]) //makes sure the next value in the array is less than the one being placed now.
	    {
	      partitiondec(part, index + 1, left - count);
	    }
	  
	}
      if (index == 0)
	{	  
	  partitiondec(part, index + 1, left - count);
	}
    }
}

void partitionDecreasing(int value)
{
  printf("partitionDecreasing %d\n", value);
  int * arr;
  arr = malloc(sizeof(int) * value);
  partitiondec(arr, 0, value);
  free(arr);
  return;

}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */
void partodd(int * part, int index, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(part, index);
      return;
    }
  for (val = 1; val <= left;val=val+2) //by adding 2 instead of 1, this makes it use odd values only.
    {
      part[index] = val;
      partodd(part, index + 1, left - val);
    }
}


void partitionOdd(int value)
{
  printf("partitionOdd %d\n", value);
  int * arr;
  arr = malloc(sizeof(int) * value);
  partodd(arr, 0, value);
  free(arr);
  return;
  
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void parteven(int * part, int index, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(part, index);
      return;
    }
  for (val = 2; val <= left;val=val+2)//By adding 2 to val instead of 1 and by starting this loop at 2 instead of 1, this now uses only even values to populate the array.
    {
      part[index] = val;
      parteven(part, index + 1, left - val);
    }
}
void partitionEven(int value)
{
  printf("partitionEven %d\n", value);
  int * arr;
  arr = malloc(sizeof(int) * value);
  parteven(arr, 0, value);
  free(arr);
  return;
}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */
void partevenodd(int * part, int index, int left)
{
  int val;
  if (left == 0)
    {
      printPartition(part, index);
      return;
    }
  for (val = 1; val <= left;val++)
    {
      if(val % 2 == 1)  //check if val is odd
	{
	  if(index % 2 ==0) //if val is odd, this make sure the index of the array is even.  
	    {
	      part[index] = val;
	      partevenodd(part, index + 1, left - val);
	    }
	  }
      if(val % 2 == 0) //checks if val is even
	{
	  if(index % 2 ==1) //if val is even, this make sure the index is an odd spot.
	    {
	      part[index] = val;
	      partevenodd(part, index + 1, left - val);
	    }
	}
    }
}


void partitionOddAndEven(int value)
{
  printf("partitionOddAndEven %d\n", value);
  int * arr;
  arr = malloc(sizeof(int) * value);
  partevenodd(arr, 0, value);
  free(arr);
  return;
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

int isprime(int value)
{
  int index;
  for(index = 2; index <= sqrt(value); index++) //index to check all possible 
    {
      if(value % index == 0) //checks for factors of the number
	{ 
	  return (0); //returns a false value if not a prime number
	}
    }
  return (1); //returns a true value if it is a prime number
}

void partprime(int * part, int ind, int left)
{
  int val;
  int prime;
  if (left == 0) 
    {
      printPartition(part, ind);
      return;
    }
  for (val = 2; val <= left; val ++) //starts checking loop.  starts at 2 because 1 is not a prime number, but passes isprime function
    {
      prime = isprime(val); //checks to see if the number is prime or not

      if(prime == 1) //if the number is prime, this enters the recursive call
	{
	  part[ind] = val;
	  partprime(part, ind + 1, left - val);
	}
    }
}


void partitionPrime(int value)
{
  printf("partitionPrime %d\n", value);
  int * arr;
  arr = malloc(sizeof(int) * value);
  partprime(arr, 0, value);
  free(arr);
}
