#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 250/*Most size of text which includes string has 250 value */

int newick_recursive(char str[MAX],int i,FILE *ftpr,int counter,char letter);
/*This is the recursive function which parselaize the string and print out the output.txt */

int main()
{
    char str[MAX];/*This is the string which includes the text which is in the input.txt*/
    char letter;/*This is includes the char which is between two commas*/
    int counter = 0;/*It is for count ( and ) for printing it better*/
    int whereIs = 0;/*This is for follw the place where we are parselling it.*/

    FILE *fp;/*opening file in reading mode*/                 
    fp  = fopen ("input.txt", "r"); 
    
    FILE *fptr;/*opening file in writing mode*/                 
    fptr = fopen ("output.txt", "w"); 
    
    if (fp == NULL)/*to control is there a input file*/
        return 0;

    if(fgets(str,250,fp)!=NULL)/*If there is something in input.txt , fgets takes to text and puts in the str*/
    {
      puts(str);
    }
    str[strlen(str)+1] = '\0';/*It says this is the and of string*/

    newick_recursive(str,whereIs,fptr,counter,letter);

    fclose(fp);/*close the input.txt*/
    fclose(fptr);/*close the output.txt*/
}

int newick_recursive(char str[MAX],int i,FILE *ftpr,int counter,char letter)
{
    char sign='-';/*For the printing - opn output.txt*/

    if(str[i]!=EOF || str[i]!='\0' || i!=strlen(str))/*if it is end of file or end of string or it is greater than length of string it stops */	
    {
        if(counter==0 && i>strlen(str))/*if counter becomes zero it means it is end of string and i is greater than length it stops*/
        {
            return 0;
        }
        if(str[i] == '(')/*If there is ( we must add one more - sign*/
            {
            newick_recursive(str,i+1,ftpr,counter+1,letter);
            }
        else if(str[i] == ')')/*If there is ) we must add one less - sign*/
            {  
            newick_recursive(str,i+1,ftpr,counter-1,letter);
            }
        else if(str[i] == ','|| str[i]=='\0')/*If there is , or \0 just skip it*/
        {   	
          	newick_recursive(str,i+1,ftpr,counter,letter);      
        }
        else/*if there is a char*/
        {
            letter=str[i];/*save letter to char*/

            for(int x = 0; x < counter; x++)/*prints - as counters number because counter keeps () numbers*/
    		{
        	  fprintf(ftpr,"%c",sign);
    		}

    		fprintf(ftpr,"%c\n",letter);/*And prints letter and becomes new line*/
            newick_recursive(str,i+1,ftpr,counter,letter);
        }
   
    }
    return 0;
}





