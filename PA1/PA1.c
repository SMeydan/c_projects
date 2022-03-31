/*Time Complexity:My program takes the integers in the file one by one and compares them with all the remaining integers.
Since there is one-by-one comparison here, the implentation time increases as the file size increases and especially as the integers in the file increase. 
At the same time, the processing time is getting longer since it is forbidden to use arrays and it is necessary to open and read the file again and again. 
In other words,as the number of operations to be performed and the complexity of the operation increase,the time for the program to run and the file to be read increases.
*/

#include <stdio.h>
#include <stdlib.h>

int main () 
{
    int x,numberOfDigits,offset,y,size,done = 0;
    FILE *fp;                 
    fp  = fopen ("file.txt", "r+"); 
    
    if (fp==NULL)
    {
        printf("Uh la la!You forget file.Please upload it...\n");
        return 0;
    }

    fseek(fp,0,SEEK_END); 
    size = ftell(fp);  /* store size of file to check if reached end of file in while loop */
    fseek(fp,0,SEEK_SET);

    while(!done)  /* read until end of file */
    {
        fscanf(fp," %d",&x); /* read next integer */
        offset = ftell(fp); /* save offset of fp */
        while(!feof(fp)) /* iterate through next integers over file */
        {
            fscanf(fp," %d",&y);
            if(y == x) /* if it is equal to x print whitespace instead of every character of integer */
            {
                if(y < 0)
                {
                    numberOfDigits = 1;
                    y *= -1;
                }
                else
                    numberOfDigits = 0;
                while(y > 0)
                {
                    y /= 10;
                    numberOfDigits++;
                }
                fseek(fp,-numberOfDigits,SEEK_CUR);
                while(numberOfDigits > 0)
                {
                    fputs(" ",fp);
                    numberOfDigits--;
                }
                fseek(fp,-1,SEEK_CUR);
            }
        }

        if(offset == size) /* if offset is equal to size end loop or continue to next integer */
            done = 1;
        else
            fseek(fp,offset,SEEK_SET);
    }

    fclose(fp);
}

