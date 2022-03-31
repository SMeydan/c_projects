/*Bubble sort begins the least number in first index and continue until list finishs.
Selection sort begins one full unordered array and empty array it founds the least number and
place into empty array first index then it contiue .
Quick sort divides numbers big and small and replace it with this way,it is faster than other sorts in general.
Merge sort is pretty long compared with other ones.
Heap sort is begins the biggest number and replace the last element of array, then it continues with all numbers
Insertion sort is good effiency with small numbers
At worst situation On^2
I use bubble sort for the sorting arrays nd I am just writing it most efficient way. 
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100/*Maksimum size of array*/ 

int is_include(int x,int numbers[SIZE],int size);/*For controlling repating numbers*/
int write(int numbers[SIZE],int repetition[SIZE],int current);/*it writes file which is output.txt in given format*/
int sort_array(int numbers[SIZE],int repetition[SIZE],int current);/*to sort all of the numbers- I use bubble sort*/
void swap(int *arr, int *arr1);/*For swaping arrays to ascending order*/

int main () 
{
    int x,current = 0,file_station;/*the input which comes input,the location where the cursor,to control output.txt */
    int numbers[SIZE],repetition[SIZE];/*arrays for numbers and repetition counts*/
    
    FILE *fp;/*opening file*/                 
    fp  = fopen ("input.txt", "r"); 
    
    if (fp==NULL)/*to control is there a input file*/
    {
        printf("Please Upload the file...");
        return 0;
    }

    while(!feof(fp)) 
    {
            fscanf(fp," %d",&x);/*read the numbers*/
            int index=is_include(x,numbers,current);
            
            if(index != -1)/*Index is -1 when x does not in array*/ 
            {
               repetition[index]=repetition[index]+1;/*add one to repetition number*/ 
            }
            
            else/*If the number is new we save in number array and we begin to count repetition number*/
            {
                numbers[current] = x; 
                repetition[current]=1;    
                current++;    
            }
    }
    file_station=write(numbers,repetition,current);/*control the output.txt*/
    if(file_station==0)
    {
        return 0;
    }
    fclose(fp);/*close the fp*/

}


int is_include(int x,int numbers[SIZE],int current) 
{
    int i;/*It is controlling the array for is there any number has the same value with x*/
    for(i = 0;i < current;i++)
        if(numbers[i] == x)
            return i;
    return -1;
}

int write(int numbers[SIZE],int repetition[SIZE],int current)
{
    FILE *fp1;/*opening file for writing*/                 
    fp1 = fopen ("output.txt", "w");
    if(fp1==NULL)/*If there is a problem file says it is null and we can see the error message*/
    {
        printf("You gotta some problem...\n");
        return 0;
    }

    int i;/*before display numbers and it's repetition numbers we just sort the arrays for ascending order */
    sort_array(numbers,repetition,current);   

    for(i=0;i<current;i++)/*we print arrays one by one with given output format*/
    {
     fprintf(fp1,"%d:%d \n",numbers[i],repetition[i]);
    }
    fclose(fp1);/*close the file*/
}

int sort_array(int numbers[SIZE],int repetition[SIZE],int current)
{
    int i=0,j=0,temp;/*For sorting I am using the bubble sort*/

   for (i = 0; i < current-1; i++)       
       for (j = 0; j < current-i-1; j++)
           if (repetition[j] > repetition[j+1])
           {
               swap(&repetition[j],&repetition[j+1]);  
               swap(&numbers[j],&numbers[j+1]);   
           }
           else if(repetition[j] == repetition[j+1])/*if they are equal bigger numbers comes last*/
            {
              if(numbers[j] > numbers[j+1])
              { 
               swap(&numbers[j],&numbers[j+1]);  
              }
            }                 
}

void swap(int *arr, int *arr1)
{
    int temp = *arr;/*Just swap and change their adresses for order*/
    *arr = *arr1;
    *arr1 = temp;
}
