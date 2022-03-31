#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void print_evaloution(double *evaloution);

int main()
{
    double total = 0,coef = 1.0,coefs[1000],value;
    int powers[1000],coefs_index = 0,powers_index= 0,power_str_index = 0,coef_str_index = 0,coefval_index = 0,power_index = 0;
    char coef_str[1000], power_str[1000],current,value_str[100];


    
    FILE *fptr;/*opening file*/                 
    fptr  = fopen ("polynomial.txt", "r"); 
    
    if (fptr==NULL)/*to control is there a input file*/
    {
        printf("Please Upload the file...\n");
        return 0;
    }

    fscanf(fptr,"%c",&current);/*reading file char by char*/
    while(!feof(fptr))/*it continue to end of the file*/
    {
        while(current != 'x')/*while it see the x there is a part of coefficient*/
        {
            if(current == '-')/*if there is a minus we multiply with -1 coefficient*/
                coef *= -1;
            else if(current != '+')
                coef_str[coef_str_index++] = current;
            fscanf(fptr,"%c",&current);/*until end of file*/    
        }
        if(coef_str_index > 0)
            coefs[coefs_index++] = strtod(coef_str,NULL);
        else
            coefs[coefs_index++] = coef;
        fscanf(fptr,"%c",&current);
        if(current == '^')/*after see ^ we read the value until - or +*/
        {
            fscanf(fptr,"%c",&current);
            while(current <= 57 && current >= 48 && !feof(fptr))/*if it is in 0 to 9 we store*/
            {
                power_str[power_str_index++] = current;
                fscanf(fptr,"%c",&current);                 
            }
            powers[powers_index++] = atoi(power_str); 
        }
        else
            powers[powers_index++] = 1;
        for(int i = 0;i < coef_str_index;i++)
        {
            coef_str[i] = '\0';
        }
        for(int i = 0;i < power_str_index;i++)
            power_str[i] = '\0';
        coef_str_index = 0;/*we delete indexes for working properly everytime*/
        power_str_index = 0;
    }

    fclose(fptr);
    
    FILE *fptr_value;/*opening file*/                 
    fptr_value  = fopen ("values.txt", "r"); 
    
    if (fptr_value==NULL)/*to control is there a input file*/
    {
        printf("Please Upload the file...\n");
    }

    while(!feof(fptr_value))/*we calculate final value with multply coefficent and it's x value times component*/
    {   
        total = 0;
        fscanf(fptr_value,"%s",value_str);
        value = strtod(value_str,NULL);
        for(int i = 0;i < coefs_index;i++)
            total += pow(value,powers[i]) * coefs[i]; 
        print_evaloution(&total);
    }

    fclose(fptr_value);
}


void print_evaloution(double *evaloution)
{
    FILE *fptr;/*opening file*/                 
    fptr  = fopen ("evaluation.txt", "a"); 
    
    if (fptr==NULL)/*to control is there a input file*/
    {
        printf("There is a problem please try again...\n");
    }

    fprintf(fptr,"%.2lf\n",*evaloution);/*printing all the values with fprintf*/
    fclose(fptr);
}

