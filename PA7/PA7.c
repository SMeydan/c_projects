#include <stdio.h>
#include <stdlib.h>

#define max 512

char Array[max][max];
void find_island(char Array[max][max]);/*Function to find*/
void find_terrain(char Array[max][max], int i, int k);

/*THE NUMBERS WHICH IS EQUAL TO L ASSIGN AS WATER*/

int main()
{
    int L, terrain;

    FILE *input, *output;/*File pointers to open and close files*/
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    fscanf(input, "%d", &L);/*first integer is L*/
    for (int x = 0; x < max; x++)
    {
        for (int y = 0; y < max; y++)
        {
            fscanf(input, "%d", &terrain);/*It fills the 512*512 matrix*/
            if (terrain <= L)/*If point has a level equal or under water level*/
                Array[x][y] = 'W';/*We fill the point as water*/

            else if (terrain > L)/*If point has a greater water level*/
                Array[x][y] = 'T';/*We fill the point as terrain*/
        }
    }

    find_island(Array);/*We send it to search algorithm*/
    int coordinate=1;
    for (int x = 0; x < max; x++)/*Search matrix for S which start point of island*/
    {
        for (int y = 0; y < max; y++)
        {
            if (Array[x][y] == 'S')
            {
                fprintf(output,"%d_coordinate%d %d_coordinate%d \n", x, coordinate, y, coordinate);/*It prints coordinates of islands*/
            	coordinate++;
            }
        }
    }
}
void find_island(char Array[max][max])
{

    int check = 0, i, k;

    for (i = 0; i < max; i++)/*Searchs matrix to find terrain or island points*/
    {
        for (k = 0; k < max; k++)
        {
            if (Array[i][k] == 'T')
            {
                find_terrain(Array, i, k);
                Array[i][k] = 'S';/*End of search and fill all the island point as water and fill the origin as S letter */
            }
        }
    }
}

void find_terrain(char Array[max][max], int i, int k)
{

    if (i - 1 >= 0)/*If search point is near the left side it stops */
    {
        if (Array[i - 1][k] == 'T')/*If the point is land*/
        {

            Array[i - 1][k] = 'W';/*It turns the water because of just write one point of island*/
            find_terrain(Array, i - 1, k);/*Search the left point*/
        }
    }

    if (i + 1 <= max - 1)/*If search point is near the right  side it stops */
    {
        if (Array[i + 1][k] == 'T')/*If the point is land*/
        {
            Array[i + 1][k] = 'W';/*It turns the water because of just write one point of island*/

            find_terrain(Array, i + 1, k);/*Search the right point*/
        }
    }
    if (k - 1 >= 0)/*If search point is near the up side it stops */
    {
        if (Array[i][k - 1] == 'T')/*If the point is land*/
        {
            Array[i][k - 1] = 'W';/*It turns the water because of just write one point of island*/

            find_terrain(Array, i, k - 1);/*Search the upper point*/
        }
    }

    if (k + 1 <= max - 1)/*If search point is near the down side it stops */
    {
        if (Array[i][k + 1] == 'T')/*If the point is land*/
        {
            Array[i][k + 1] = 'W';/*It turns the water because of just write one point of island*/

            find_terrain(Array, i, k + 1);/*Search the down point*/
        }
    }
}

/*FILE* input;
input = fopen("input.txt" , "w");
for(int i = 0; i <= 262144 ; i++)
{
    int randNum = rand() % 128;
    if(i == 262144)
        fprintf(input,"%d",randNum);
    else
        fprintf(input,"%d ",randNum);
}*/
/*This how to test my code ,I write a file with rand in main */
