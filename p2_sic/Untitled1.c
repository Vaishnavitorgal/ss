#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int size=0;

struct instr{
    char locaddr[30];
    char label[30];
    char operand[30];
    char opcode[30];
    int len;
};

struct instr s[20];

struct symtab{
    char name[30];
    char value[30];
};
struct symtab sym[10];

void add(char line[],struct instr *st)
{
    int len=0;
    char *pr ;
    //printf("%s",line);
    char *stemp;
    strcpy(stemp,line);
    char *strp = strtok(line," ");
    printf("h: %s\n",strp);
    //printf("%s\n",strp);
    while(strp !=NULL){
        len++;
        strp = strtok(NULL," ");
        printf("h: %s\n",strp);
    }
    //printf("hi");

    /*if(len == 3)
    {
        pr = strtok(stemp," ");
        strcpy(st->locaddr,pr);
        pr = strtok(NULL," ");
        strcpy(st->opcode,pr);
        pr = strtok(NULL," ");
        strcpy(st->operand,pr);
        st->len=3;
    }
    else{

    }*/
}

int main()
{
    printf("gi");
    FILE *fp = fopen("int.txt","r");
    char line[100];
    int index =0 ;

    if(fp==NULL){
        printf("Not Opened");
        exit(0);
    }

    while(fgets(line,30,fp)!=NULL)
    {
        //printf("hi");
        //printf("%s",line);
        add(line,&s[index]);
        //printf("hi");
        index++;
    }

    //for(int i =0 ;i<(index-1); i++){
      //  printf("%s",s[i].opcode);
    //}
    fclose(fp);

    return(0);
}
