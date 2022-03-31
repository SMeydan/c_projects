#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    OR,AND,NOT,FLIPFLOP
} GATETYPE;/*enum for describing gate types*/

typedef struct INPUT
{
    int val;
    char* name;
    struct INPUT* next;
} INPUT;/*struct for input.txt*/

typedef struct GATE
{
    char* name;
    int type;
    INPUT* input1;
    INPUT* input2;
    struct GATE* gateIn1;
    struct GATE* gateIn2;
    int memory; 
    struct GATE* next;
} GATE;/*struct for circuit.txt */


void clearBuffer(char *buffer,int currentSize)
{
    for(int i = 0;i < currentSize;i++)
        buffer[i] = '\0';
}/*to clear buffer , we equal all the indexes zero*/


void clearLineEnding(FILE *fp)
{
	int c;
	while((c = getc(fp)) == '\n' || c == '\r')
		;
	if(c != EOF)
		ungetc(c, fp);
}/*It is cleaning end of line like /n and /r*/


int readLine(char* buffer,FILE* fp)
{
    char c;
    int cur = 0;
    while((c = getc(fp)) != '\n' && c != EOF && c != '\r'  && cur < 1024)
        buffer[cur++] = c;
    clearLineEnding(fp);
    return cur;
}/*it is reading line 1024 char and cleans and then sent it to lin end clear */


int evaluate(GATE* gate)
{
    int val1,val2;
    if(gate->input1 == NULL)
        val1 = evaluate(gate->gateIn1);
    else
        val1 = gate->input1->val;
    if(gate->type == NOT)
        return !val1;
    /*If gate type is NOT , we inverse the value of integer*/    
    if(gate->type == FLIPFLOP)
    {
        if(gate->memory && val1)
        {
            gate->memory = 0;
            return 0;
        }
        else if(!val1 && !gate->memory)
        {
            gate->memory = 0;
            return 0;
        }
        else
        {
            gate->memory = 1;
            return 1;
        }
    }/*If gate type is flipflop  we send result of flipflop to memory and calculate result  */
    
    if(gate->input2 == NULL)
        val2 = evaluate(gate->gateIn2);
    else
        val2 = gate->input2->val;
    
    if(gate->type == AND)
        return val1 && val2;
    /*If the gate type is and we return value1 and value2*/    
    if(gate->type == OR)
        return val1 || val2;
    /*If the gate type is and we return value1 or value2*/    
}


void addGate(GATE* head,GATE* new)
{
    GATE *copy = head;

    if(copy == NULL)
    {
        head = new;
        return;
    }
    while(copy->next != NULL)
        copy = copy->next;
    
    copy->next = new;
}/*add new node to linked for circuit.txt*/

void addInput(INPUT* head,INPUT* new)
{
    INPUT *copy =head;

    if(copy == NULL)
    {
        head = new;
        return;
    }

    while(copy->next != NULL)
        copy = copy->next;
    copy->next = new;
}/*add new node to linked for input.txt*/

INPUT* findInput(INPUT* head,char* name)
{
    INPUT* h = head;

    while(h != NULL)
    {
        if(strcmp(h->name,name) == 0)
            return h;
        h = h->next;
    }

    return NULL;
}/*if there is a input which is named h->name we return h to read*/

GATE* findGate(GATE* head,char* name)
{
    GATE* h = head;

    while(h != NULL)
    {
        if(strcmp(h->name,name) == 0)
            return h;
        h = h->next;
    }

    return NULL;
}/*if there is a gate which is named h->name we return h to read*/

GATE* newGate(char *name)
{
    GATE* new = (GATE*)malloc(sizeof(GATE));
    new->name = (char*)malloc(20 * sizeof(char));
    strcpy(new->name,name);
    new->next = NULL;
    new->gateIn1 = NULL;
    new->gateIn2 = NULL;
    new->input1 = NULL;
    new->input2 = NULL;
    return new;
}/*create a dynamic struct to gate and its name */

INPUT* newInput(char *name)
{
    INPUT* new = (INPUT*)malloc(sizeof(INPUT));
    new->name = (char*)malloc(20);
    strcpy(new->name,name);
    new->next = NULL;
    return new;
}/*create a dynamic struct to gate and its name */


void freeNamesGate(GATE* head)
{
    while (head != NULL)
    {
        free(head->name);
        head = head->next;
    }
    
}/*It get free the memory*/


void freeNamesInput(INPUT* head)
{
    while (head != NULL)
    {
        free(head->name);
        head = head->next;
    }
    
}/*It get free the memory*/

int main()
{
    int inputNum = 0,gateNum = 0,bufferIndex = 0,inputIndex = 0,gateIndex = 0,bufferSize;
    char buffer[1024],*token;
    GATE* gateHead = NULL;
    INPUT* inputHead = NULL;
    FILE* circuitFile = fopen("circuit.txt","r");
    FILE* inputFile = fopen("input.txt","r");
    char c;
    int flag = 0;
    /*it opens circuit and input file*/

    clearBuffer(buffer,1024);
    bufferSize = readLine(buffer,circuitFile);/*read the line and */
    token = strtok(buffer," ");/*seperate the string using white spaces */
    token = strtok(NULL," ");
    while(token != NULL)
    {
        if(inputHead == NULL)
            inputHead = newInput(token);
        else
            addInput(inputHead,newInput(token));
        token = strtok(NULL," ");
    }

    while(!feof(circuitFile))/*it is reading the end of file*/
    {
        flag = 0;
        clearBuffer(buffer,1024);/*clears the buffer*/
        bufferSize = readLine(buffer,circuitFile);/*read the line*/
        token = strtok(buffer," ");
        GATE* new = newGate(token);
        if(gateHead == NULL)
            gateHead = new;
        else/*it find type of the gate*/
            addGate(gateHead,new);
        if(strcmp("AND",token) == 0)
            new->type = AND;
        if(strcmp("OR",token) == 0)
            new->type = OR;
        if(strcmp("NOT",token) == 0)
            new->type = NOT;
        if(strcmp("FLIPFLOP",token) == 0)
            new->type = FLIPFLOP;
        /*it writes the new type*/
        token = strtok(NULL," ");
        strcpy(new->name,token);

        new->memory = 0;

        token = strtok(NULL," ");
        INPUT* in = findInput(inputHead,token);
        if(in != NULL)
                new->input1 = in;
        else
        {
            GATE* inGate = findGate(gateHead,token);
            new->input1 = NULL;
            new->gateIn1 = inGate;
        }
        if(new->type == NOT || new->type == FLIPFLOP)
            continue;

        token = strtok(NULL," ");
        INPUT* in2 = findInput(inputHead,token);
        if(in2 != NULL)
                new->input2 = in2;
        else
        {
            GATE* inGate2 = findGate(gateHead,token);
            new->input2 = NULL;
            new->gateIn2 = inGate2;
        }
        /*search the gates and inputs*/
    }

    fclose(circuitFile);
    while(!feof(inputFile))/*it read until end of file*/
    {
        clearBuffer(buffer,1024);
        bufferSize = readLine(buffer,inputFile);
        token = strtok(buffer," ");
        INPUT* h = inputHead;
        do
        {
            h->val = atoi(token);
            h = h->next;
            token = strtok(NULL," ");
        } while (token != NULL);

        GATE* gateHeadCopy = gateHead;
        while (gateHeadCopy->next != NULL)
        {
            gateHeadCopy = gateHeadCopy->next;
        }
        

        printf("%d\n",evaluate(gateHeadCopy));
        /*it prints outputs and call the evaluate*/
    }

    fclose(inputFile);/*close the file and */

    freeNamesGate(gateHead);/*free all the head*/
    freeNamesInput(inputHead);
    free(gateHead);
    free(inputHead);
    
}
