
#include "pa03.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Read a file of integers.
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of integers (one
 * per line)
 * 
 * numberOfIntegers: pointer to store the number of integers in the
 * file. You need to update the value stored at the address which is
 * the pointer's value
 *
 * Returns:
 *
 * a array of integers from the file, or NULL if *any* error is
 * encountered.
 *
 * You do NOT know how many integers are in the file until you have
 * read it. Once you know how many integers there are, you can modify
 * the "numberOfIntegers" variable. (Note that this is a pointer, not
 * an integer) You must allocate memory to store the integers.
 * 
 * Once memory is allocated to store the integers, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek".
 * 
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read integeres is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 *
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 *
 * int * ptr = (int *) malloc(sizeof(int) * size);
 *
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 *
 * The allocated memory will be released in pa03.c. You do not need to
 * worry about releasing memory.
 *
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of integers in the file.  For example, if
 * you write this
 *
 * int array[10000];
 * 
 *
 */

int * readIntegers(const char * filename, int * numberOfIntegers)
{
  FILE * input; //Holds file array while searching for length
  int placeholder; //placeholder for value compare when finding length and putting values in new array
  int count2 = 0; //Keeps track of array index when inserting values
  int * array; //array to store the contents of the opened file

  input = fopen(filename, "r"); //initializes contact with file to be read
  if (input == NULL) //Gives error if there is a problem connecting with the file
    {
      return NULL;
    }

  while(fscanf(input, "%d", &placeholder) != EOF) //Scans the file to get the length in order to produce an adaquete array length
   {
     * numberOfIntegers = *numberOfIntegers + 1; //Index of length of array in file
   }
  array = malloc((* numberOfIntegers) * sizeof(int)); //Allocates memory for the array to be made

  fseek(input, 0 , SEEK_SET); //resets pointer of file back to index 0

  while(count2 < * numberOfIntegers) //places elements of file into new array
    {
      fscanf(input, "%d", &placeholder);
      array[count2]=placeholder;
      count2++;
    }
  fclose(input); //closes communications with the file

  return array; //returns the values in the array
}

/**
 * Sort an (ascending) array of integers
 *
 * Arguments:
 * arr    The array to search
 * length Number of elements in the array
 *
 * Uses "quicksort" to sort "arr".  Use the first element of the array
 * as the pivot.  
 *
 * Your solution MUST use recursive function (or functions)
 * 
 * quicksort works in the following way: 
 * 
 * find an element in the array (this element is called the
 * pivot). 
 *
 * rearrange the array's elements into two parts: the part smaller
 * than this pivot and the part greater than this pivot; make the pivot
 * the element between these two parts
 * 
 * sort the first and the second parts separately by repeating the 
 * procedure described above
 * 
 * You will receive no point if you use any other sorting algorithm.
 * You cannot use selection sort, merge sort, or bubble sort.
 * 
 * Some students are fascinated by the name of bubble sort.  In
 * reality, bubble sort is rarely used because it is slow.  It is a
 * mystery why some students (or even professors) like bubble sort.
 * Other than the funny name, bubble sort has nothing special and is
 * inefficient, in both asymptotic complexity and the amount of data
 * movement.  There are many algorithms much better than bubble sort.
 * You would not lose anything if you do not know (or forget) bubble
 * sort.
 *
 */

void swapfunc(int arr[], int x, int y) //swaps the values when needed for sorting
{
  int temp;
  temp=arr[x];
  arr[x]=arr[y];
  arr[y]=temp;
}


int split(int * arr,int under, int over) //divides the array into smaller chuncks in order to sort more quickly
  {
    int left;
    int right;
    int index;
    left = under;
    index = arr[under];
    right = over;

    while(left < right)
      {
	while(arr[right] > index)
	  {
	    right = right - 1;
	  }
	while(arr[left] <= index)
	  {
	    left = left + 1;
	  }

	if(left  < right)
	  {
	    swapfunc(arr,left,right);
	  }
      }
    arr[under] = arr[right];
    arr[right] = index;

    return(right);
  }

void Sort1(int * arr, int pivot, int last) //recursive file in order to use the quicksort function
{
  int temp;
  if (pivot<last)
    {
      temp=split(arr,pivot,last);
      Sort1(arr,pivot,temp-1);
      Sort1(arr,temp+1,last); 
    }
}
void sort(int * arr, int length)
{
  Sort1(arr, 0 , length-1);//Calls the recursive function in order to quicksort
}

/**
 * Use binary search to find 'key' in a sorted array of integers
 *
 * Arguments:
 * 
 * arr The array to search. Must be sorted ascending.  You do not need
 *        to check. This array is from the result of your sort
 *        function. Make sure your sort function is correct before you
 *        start writing this function.
 *
 * length Number of elements in the array
 * key    Value to search for in arr
 *
 * Returns:
 * The index of 'key', or -1 if key is not found.
 *
 * Since the array is sorted, you can quickly discard many elements by
 * comparing the key and the element at the center of the array. If
 * the key is the same as this element, you have found the index.  If
 * the key is greater than this element, you can discard the first
 * half of the array.  If the key is smaller, you can discard the
 * second half of the array.  Now you have only half of the array to
 * search.  Continue this procedure until either you find the index or
 * it is impossible to find a match.
 * 
 * Your solution MUST use recursive function (or functions)
 *
 * Don't forget that arrays are 'zero-indexed'. Also, you must
 * use a binary search to pass this question.
 * 
 * You will receive no point if you do the following because it is not
 * binary search.  This is called linear search because it checks
 * every element.
 *
 * int ind;
 * for (ind = 0; ind < length; ind ++)
 * {
 *    if (arr[ind] == key)
 *    {
 *       return ind;
 *    }
 * }
 * return -1;
 */
int helper(int * arr, int lowerbound, int upperbound, int key)
{
  if(lowerbound > upperbound) //returns -1 if the key is not found in the array
    {
      return -1;
    }

  int indexvar = (lowerbound + upperbound)/2; //divides the array in half to make searching quickly

  if (arr[indexvar] == key) //returns pointer if the key is found
    {
      return indexvar;
    }
  if (arr[indexvar] > key) //searches lower half if key is less than value at pointer
    {
      return(helper(arr, lowerbound, indexvar - 1, key));
    }
  if (arr[indexvar] < key) //searches upper half if key is greater than value at pointer
    {
      return(helper(arr, indexvar+1, upperbound,key));
    }
  return -1;
}

int search(int * arr, int length, int key)
{
  return helper(arr,0,length,key); //Calls recursive function to find key
}


