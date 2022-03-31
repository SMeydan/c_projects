#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double cost(char *objectName);/*it is the recursive function*/
char *remove_white_spaces(char *str);/*it is for remove white spaces*/
int is_double(char *buffer);/*it is control the user input is only number or complex something*/


int main()
{
    double total = 0;
    char objectName[100];/*it is used for the name of definig object*/
    size_t buffer_size = 100;/*and it's maximum size is 100*/
    char *o = objectName;

    printf("Define the object\n");
    scanf(" %[^\n]s",objectName);

    total = cost(objectName);

    printf("Total cost of %s: %.2lf",objectName,total);/*it prints the total value*/
}


char *remove_white_spaces(char *str)
{
	int i = 0, j = 0;
	while (str[i])
	{
		if (str[i] != ' ')/*if strings have smt it saved into str if have white space just jump*/
		  str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}


int is_double(char *buffer)
{
    int i = 0;
    char c = buffer[i];

    while(c != '\0')/*it is control char is it double or not*/
    {
        if(!((c - 48 >= 0 && c - 48 <= 9) || c == '.'))/*they are number which is in ascii code*/
            return 0;
        c = buffer[i++];        
    }

    return 1;
} 


double cost(char * objectName)
{
    double total_cost = 0.0;
    char buffer[100];
    char *b = buffer;
    int currentQuantity = 1,currentBufferIndex = 0;
    char currentBuffer[100];
    char currentObjectName[100];
    size_t bufferSize = 100;
    printf("What is %s?\n",objectName);
    scanf(" %[^\n]s",buffer);/*we get the user input*/
    char *buffer2 = remove_white_spaces(buffer);/*and remove the white spaces*/
    if(!is_double(buffer2))/*we control is it only number or not*/
    {
        for(int i = 0;i < strlen(buffer2) + 1;i++)/*and split char by char*/
        {
            if(buffer2[i] - 48 >= 0 && buffer2[i] - 48 <= 9)/*if it is a number we save the number to currentbuffer*/
                currentBuffer[currentBufferIndex++] = buffer2[i];

            else if(buffer2[i] == '*')/*if there is * then we use numbers in currnt buffer with atoi function*/
            {
                currentQuantity = atoi(currentBuffer);
                for(int j = 0;j < currentBufferIndex;j++)
                    currentBuffer[j] = '\0';
                currentBufferIndex = 0;
            }
            else if(buffer2[i] == '+' || buffer2[i] == '\0')/*if it is end of string or + we find name of object parts and */
            {                                               /*save it into current and search new object with recursive*/
                strcpy(currentObjectName,currentBuffer);
                for(int j = 0;j < currentBufferIndex;j++)
                    currentBuffer[j] = '\0';
                currentBufferIndex = 0;
                total_cost +=currentQuantity*cost(currentObjectName);
            }

            else/*if it is a letter it is also save int to current buffer*/
            {
                currentBuffer[currentBufferIndex++] = buffer2[i];
            }
        }
    }
    else/*if there is only number we just send the value*/
    {
        total_cost = strtod(buffer2,NULL);
    }
    return total_cost;/*and return the cost for print*/

}
