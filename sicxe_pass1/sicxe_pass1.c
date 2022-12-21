#include<stdio.h>
#include<Stdlib.h>
#include<string.h>

int locctr = 0,size=0,op1=0,r1=0,m=0,o1=0;
int startingAddress = 0;
char nem[20],nem2[20];
int index1=0,sym_size=0;

struct instruction {

    char location[20];
	char label[20];
	char opcode[20];
	char operand[50];
	int len;

};
struct instruction s[50];

struct symbols
 {
     char sym_name[20];
     char sym_addr[20];
 };
 struct symbols symtab[10];

 struct opcodes
 {
     char opc[20];
     char value[20];
 };
 struct opcodes opcode1[10];
 struct opcodes registers[10];

 void store_instr(char *temp,struct instruction *s)
 {
     o1=0;
     char temp1[30],temp2[30];
     strcpy(temp1,temp);

     int length=0,i=0;
     char *pch = strtok (temp," ");
     strcpy_s(temp2,30,pch);
    // printf("%s\n",temp2);
    if(pch[0]=='.')
    {
        o1=1;
        printf("comment line\n");
    }
  while (pch != NULL)
  {
    length++;
    pch = strtok (NULL, " ");
  }
 if(o1==0)
 {

   if(length==1)
  {
      char *str = strtok (temp1," ");
      strcpy_s(s->opcode,20,str);
      strcpy(s->label,"");
      s->len=1;
      size++;

  }
  else if(length==3)
  {
      char *str = strtok (temp1," ");
      strcpy_s(s->label,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s->opcode,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s->operand,20,str);
      s->len=3;
      size++;
  }
  if(length==2)
  {
      char *str = strtok (temp1," ");
      strcpy_s(s->opcode,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s->operand,20,str);
      s->len=2;
      strcpy(s->label,"");
      size++;
  }
 }
 }

 int search1(char *s_opcode)
 {
     FILE *fp3;
     int flag=0;
    fp3=fopen("test2.txt","r");
    while(!feof(fp3))
            {
                char op[20],check[10];
                int add;

                fgets(op,30,fp3);
                char *str = strtok(op," ");

                strcpy_s(check,20,str);
                if(strcmp(check,s_opcode)==0)
                {

                    flag=1;
                    str = strtok (NULL, " ");
                    strcpy_s(nem,20,str);
                    break;
                }
            }
            return flag;
            fclose(fp3);
 }

 void initialise()
 {
     FILE *fp3;
    fp3=fopen("test2.txt","r");
    while(!feof(fp3))
            {
                char op[20],check[10];
                int add;

                fgets(op,30,fp3);
                char *str = strtok(op," ");

                strcpy_s(opcode1[op1].opc,20,str);

                    str = strtok (NULL, " ");
                    strcpy_s(opcode1[op1].value,20,str);
                    op1++;

                }

            fclose(fp3);
 }

 int search(char s_opcode[20])
 {
     int flag=0,k;
     for(k=0;k<op1;k++)
     {
        // int len1=strlen(opcode1[k].opc);
         //printf("%d\n",len1);
         //char test_opc[20];
         //strncpy(test_opc,opcode1[k].opc,len1-1);
         if(strcmp(opcode1[k].opc,s_opcode)==0)
         {
             flag=1;
             break;
         }
     }
     return flag;
 }

 int search_symbol(char s_symbol[20])
 {
     int error=0,k;
     for(k=0;k<sym_size;k++)
     {
         if(strcmp(symtab[k].sym_name,s_symbol)==0)
         {
             error=1;
             break;
             printf("Duplicate symbol\n");
         }
     }
     return error;
 }

 void init()
{
	FILE* ptr = fopen("registers.txt", "r");
	while(!feof(ptr))
            {
                char op[20],check[10];
                int add;

                fgets(op,30,ptr);
                char *str = strtok(op," ");

                strcpy_s(registers[r1].opc,20,str);
                    str = strtok (NULL, " ");
                    strcpy_s(registers[r1].value,20,str);
                    r1++;

                }

}
int search_register(char a[20])
{
    //printf("%s\n",a);
    int flag=0,k,r_len,e,y=0;
    if(strchr(a,',')!=NULL)
        {
            r_len=strlen(a);
            for(e=0;e<r_len-1;e++)
            {
                if(a[e]!=',')
                {
                  flag=0;
                  for(k=0;k<r1;k++)
                  {
                      if(registers[k].opc[0]==a[e])
                    {
                        flag=1;
                        break;
                    }
                  }
                  if(flag==0)
                  {
                      y=1;
                      printf("invalid registers\n");
                  }
                }
            }
            if(y==1)
            {
                flag=0;
            }
        }
        if(strlen(a)==2)
    {
        for(k=0;k<r1;k++)
        {
        if(registers[k].opc[0]==a[0])
        {
            flag=1;
            break;
        }
        }
    }

    return flag;
}
 int main()
 {
    char temp[20];
    int start,i=0,j=0,a=0,check=0,p=0,y=0,flag2=0;

    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1=fopen("test1.txt","r");
    fp4=fopen("intermediate_out.txt","w+");
    fp5=fopen("symbol_table.txt","w+");
    if(fp1==NULL)
    {
        printf("Input file error");
        return(-1);
    }
    while(!feof(fp1))
    {
        //printf("%d\n",1);
        fgets(temp, 40, fp1);
        store_instr(temp,&s[index1]);
        printf("\n");
        index1++;
    }

    //printf("%d",index1);
    //printf("%d\n",size);
    initialise();

    //printf("%s\n",s[1].opcode);
    //For first input line
    if(strcmp(s[0].opcode,"START")==0)
    {
        start=strtol(s[0].operand,NULL,16);
        locctr=strtol(s[0].operand,NULL,16);
        fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[0].label,s[0].opcode,s[0].operand);
    }
    else
    {
        start=0;
        locctr=0;
        fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[0].label,s[0].opcode,s[0].operand);
    }

    //looping till the end
    i=1;
    //printf("%d\n",op1);
    init();
    //printf("%d\n",r1);
    while(strcmp(s[i].opcode,"END")!=0)
    {
        flag2=0;
        check=0;
        if(strcmp(s[i].label,"")!=0)
        {
            if(s[i].len==3)
            {

            a=search_symbol(s[i].label);
            if(a==0)
            {
                fprintf(fp5,"%s %X\n",s[i].label,locctr);
            }
            }
        }

            //printf("%s\n",s[i].opcode);

        if(search_register(s[i].operand)== 1)
        {

            if(s[i].len==2)
            {
                fprintf(fp4,"%X\t\t%s\t%s\n",locctr,s[i].opcode,s[i].operand);
            }
            if(s[i].len==3)
            {
                //printf("%s\n","Heyy");
                fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[i].label,s[i].opcode,s[i].operand);
            }
            m++;
            locctr += 2;
            flag2=1;
        }

        if(flag2==0)
        {

        if(s[i].len==1)
        {
          char t1[20];
          strcpy(t1,"");
          strncpy(t1,s[i].opcode,strlen(s[i].opcode)-1);
          check=search1(t1);
        if(check==1)
        {

            fprintf(fp4,"%X\t\t%s\t\n",locctr,s[i].opcode);
            locctr=locctr+3;
        }
        else
        {
            fprintf(fp4,"%X\t\t%s\t\n",locctr,s[i].opcode);
            locctr=locctr+1;
        }
        }
        else
        {
            check=search1(s[i].opcode);
            if(check==1)
        {
             if(s[i].len==2)
            {
                fprintf(fp4,"%X\t\t%s\t%s\n",locctr,s[i].opcode,s[i].operand);
            }
            if(s[i].len==3)
            {
                fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[i].label,s[i].opcode,s[i].operand);
            }
             locctr=locctr+3;
        }
        }

        if(s[i].opcode[0]=='+')
        {
            fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[i].label,s[i].opcode,s[i].operand);
            locctr=locctr+4;
        }

        else if(strcmp(s[i].opcode, "WORD") == 0) {
			fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[i].label,s[i].opcode,s[i].operand);
			locctr += 3;
		} else if(strcmp(s[i].opcode, "RESW") == 0) {

			fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[i].label,s[i].opcode,s[i].operand);
			locctr += (3 * strtol(s[i].operand, NULL, 10));
		} else if(strcmp(s[i].opcode, "RESB") == 0) {

			fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[i].label,s[i].opcode,s[i].operand);
			locctr = locctr + strtol(s[i].operand, NULL, 10);
		} else if(strcmp(s[i].opcode, "BYTE") == 0) {
			if(s[i].operand[0] == 'X') {

				fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[i].label,s[i].opcode,s[i].operand);
				locctr = locctr + ((strlen(s[i].operand)-3)/2);
			} else if(s[i].operand[0] == 'C') {

				fprintf(fp4,"%X\t%s\t%s\t%s\n",locctr,s[i].label,s[i].opcode,s[i].operand);
				locctr = locctr + (strlen(s[i].operand)-4);
			}
		}
        }

        i++;
    }
       //printf("%d\n",p);
       //printf("%d\n",m);
       fprintf(fp4,"%X\t\t%s\t%s\n",locctr,s[i].opcode,s[i].operand);


    return 0;
 }
