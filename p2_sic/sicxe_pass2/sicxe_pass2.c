#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int i=0,j,locctr,flag2=0,size,x=0,text_len=0,a=0,b=0,resb=0,lp=0,index1=0,len_text,comp=0,error_len,r1=0,f1=0,f2=0,len_text;
char addr[20],y2[4],y3[4];
char nem[20],nem2[20];
char object_code[20];
 struct instruction
 {
    char location[20];
    char label[20];
    char opcode[20];
    char operand[20];
    char object[20];
    int len;
 };
struct instruction s1[12];

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

 void store_instr(char *temp,struct instruction *s1)
 {
    // printf("Heyy\n");
    char temp1[40];
    strcpy(temp1,temp);
    int length=0,i=0;
    char *pch = strtok (temp,"  ");
    if(strcmp(pch,".\n")==0)
    {
        printf("%s\n","comment line\n");
    }
    while (pch != NULL)
    {
        length++;
        pch = strtok (NULL, " ");
        //printf("%d\n",length);
    }

    if(length==1)
    {
        printf("HI\n");
    }
   if(length==2)
  {
      //printf("Heyy\n");
      int er=0;
      char *str = strtok (temp1," ");
      strcpy_s(s1->location,20,str);

         str = strtok (NULL, " ");
        strcpy_s(s1->opcode,20,str);
        s1->len=2;
        size++;
       // printf("%s\n",str);

  }
  else if(length==3)
  {
      //printf("Hii\n");
      char *str = strtok (temp1," ");
      strcpy_s(s1->location,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s1->opcode,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s1->operand,20,str);
      s1->len=3;
      size++;

  }
  else if(length==4)
  {
      //printf("Hiii\n");
      char *str = strtok (temp1,"   ");
      strcpy_s(s1->location,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s1->label,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s1->opcode,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s1->operand,20,str);
      s1->len=4;
      size++;
  }
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
    f1=0,f2=0;
    int flag=0,k,r_len,e,y=0,q1=0,q2=0;
    if(strchr(a,',')!=NULL)
        {
            f1=1;
            printf("yes\n");
            q1=0,q2=0;
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
                        if(q1==0)
                        {
                            strcpy(y2,registers[k].value);
                            q1++;
                        }
                        if(q1==1)
                        {
                            strcpy(y3,registers[k].value);
                        }
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
        f2=1;
        for(k=0;k<r1;k++)
        {
        if(registers[k].opc[0]==a[0])
        {
            strcpy(y2,registers[k].value);
            flag=1;
            break;
        }
        }
    }

    return flag;
}
 int search(char *s_opcode)
 {
     FILE *fp3;
     int flag=0;
    fp3=fopen("sicxe_opc.txt","r");
    while(!feof(fp3))
            {
                char op[20],check[10];
                fgets(op,30,fp3);
                char *str = strtok(op," ");

                strcpy_s(check,20,str);
                int len1=strlen(check);
                if(strncmp(check,s_opcode,len1)==0)
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


 void check_len()
 {
     int jk=0;
     len_text=0;
     jk=comp;
     printf("%d\n",jk);
     error_len=0;
     while(strcmp(s1[jk].opcode,"END")!=0)
     {
         if(s1[jk].len==2)
         {
             if(search(s1[jk].opcode)==1)
                len_text=len_text+1;
         }
         if(search_register(s1[jk].operand)==1)
         {
             len_text=len_text+2;
         }
         else if(strcmp(s1[jk].opcode,"RSUB\n")==0)
         {
             len_text=len_text+3;

             }
         else if(strcmp(s1[jk].opcode,"WORD")==0)
         {
             len_text=len_text+3;

         }
         else if(strcmp(s1[jk].opcode,"BYTE")==0)
         {
             int b_len;
             b_len=strlen(s1[jk].operand);
             if(s1[jk].operand[0]=='C')
                len_text=len_text+b_len-4;
             else if(s1[jk].operand[0]=='X')
             {
                printf("%d\n",len_text);
                len_text=len_text+((b_len-4)/2);
             }

         }
         else if(strcmp(s1[jk].opcode,"RESB")==0)
         {
             error_len=1;
         }
         else if(strcmp(s1[jk].opcode,"RESW")==0)
         {
             error_len=1;
         }
         if(len_text>30)
         {
             error_len=1;
         }
         if(error_len==1)
         {
             comp=jk+1;
             break;
         }
         jk++;

     }

 }


 void initialise()
 {

     FILE *fp2;
     int n=0;
     char j[20];
    fp2=fopen("symbol.txt","r");
    //printf("%d\n",2);
    while(!feof(fp2))
            {
                fgets(j,30,fp2);
                char *str = strtok(j," ");
                strcpy_s(symtab[n].sym_name,20,str);
                str = strtok (NULL, " ");
                strcpy_s(symtab[n].sym_addr,20,str);
                n++;
            }
    fclose(fp2);
 }


int main()
{

    initialise();
    int loop=0,flag=0,i=0,flag_sym=0,t_len;
    char lo[10],lo1[10],lab[10],opc[10],oper[10],lab1[10],oper1[10],opc1[10],temp[30],ad[10];
    char length[10]="0023";
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1=fopen("int1.txt","r");
    fp4=fopen("sicxe_out.txt","w+");
    fp5=fopen("sicxe_object.txt","w+");
    init();
    if(fp1==NULL)
    {
        printf("Input file error");
        return(-1);
    }
    fscanf(fp1,"%s\t%s\t%s\t%s",lo1,lab1,opc1,oper1);

    if(strcmp(opc1,"START")==0)
    {
       fprintf(fp4,"%s\t%s\t%s\t%s\n",lo1,lab1,opc1,oper1);
       fclose(fp1);
    }

    fprintf(fp5,"%s%6s%6s%6s\n","H",lab1,oper1,length);
    fprintf(fp5,"%s%s%s ","T"," ",oper1);
    fp1=fopen("int1.txt","r");
    while(!feof(fp1))
    {
        fgets(temp, 40, fp1);
        store_instr(temp,&s1[index1]);
        printf("\n");
        //printf("%s\n",s[index1].location);
        index1++;

    }
    fclose(fp1);
    printf("%d\n",index1);
    //handling format1 instructions
    i=0;
    printf("%s\n",s1[9].opcode);
    int k=0;
    i=1;
     printf("%s\n",s1[8].operand);
     check_len();
     fprintf(fp5,"%d",len_text);
   while(strcmp(s1[i].opcode,"END")!=0)
    {

        resb=0;
       int fin=0;
       if(strcmp(s1[i].opcode, "BASE") == 0)
		{
			fprintf(fp4, "     %s %s %s\n", s1[i].label,s1[i].opcode,s1[i].operand);
			continue;
		}
    //handling format2
        if(search_register(s1[i].operand)== 1)
        {
            if(search(s1[i].opcode)==1)
            {
                fin=1;
                char p1[10]="";
                strncpy(p1,nem,2);
                if(f1==1)
                {
                    char y4[4]="",y5[4]="";
                    strncpy(y4,y2,1);strncpy(y5,y3,1);
                    strcat(p1,y4);strcat(p1,y5);
                    printf("%s\n",p1);

                }
                else if(f2==1)
                {
                    char y4[4]="";
                    strncpy(y4,y2,1);
                    strcat(p1,y4);strcat(p1,"0");
                    printf("%s\n",p1);

                }
                char y6[5]="";
                strncpy(y6,s1[i].operand,strlen(s1[i].operand)-1);
                fprintf(fp4,"%s\t\t%s\t%s\t%s\n",s1[i].location,s1[i].opcode,y6,p1);
                fprintf(fp5," %s",p1);
            }

        }


        //handling format1
        if(s1[i].len==2)
        {
            int check=0;
            if(strcmp(s1[i].opcode,"RSUB\n")==0)
            {
                char r1[10];
                strncpy(r1,s1[i].opcode,strlen(s1[i].opcode)-1);
                check=1;fin=1;
                fprintf(fp4,"%s\t\t%s\t\t%s\n",s1[i].location,"RSUB","4F0000");
                fprintf(fp5," %s","4F0000");
            }
            else if(strcmp(s1[i].opcode,"END")==0)
            {
                check=1;
            }
            else if(search(s1[i].opcode)==1)
                {
                    char r1[10]="";
                    strncpy(r1,s1[i].opcode,strlen(s1[i].opcode)-1);
                    char r2[10]="";
                    strncpy(r2,nem,strlen(nem)-1);fin=1;
                    fprintf(fp4,"%s\t\t%s\t\t%s\n",s1[i].location,r1,r2);
                    fprintf(fp5," %s",r2);
                }
            else
            {
              printf("invalid");
            }

          }

          if(strcmp(s1[i].opcode,"BYTE")==0)
        {
            int j1;
            //printf("yess");
           char object_code[10];
           strcpy(object_code,"");
           char byte_test[10];
           int b_len=0;
           if(s1[i].operand[0]=='C')
           {
              b_len=strlen(s1[i].operand);
              b_len=b_len-3;
               for(j1=2;j1<(b_len+1);j1++)
                {
                    int y=s1[i].operand[j1];
                    itoa(y,byte_test,16);
                    strcat(object_code,byte_test);

                }
           // fprintf(fp5,"%s%s"," ",object_code);
            printf("%s\n",object_code);
            //strcpy(s[x].object,object_code);

           }

           else if(s1[i].operand[0]=='X')
           {

               strcpy(object_code,"");
               char test[5]="";
               for(int p=2;p<strlen(s1[i].operand)-2;p++)
                {
                    test[p-2]=s1[i].operand[p];
                    strcpy(object_code,test);
                }
            //fprintf(fp5,"%s%s"," ",object_code);
            printf("%s\n",object_code);
            //strcpy(s[x].object,object_code);
           }

           char te[10]=""; fin=1;
           strncpy(te,s1[i].operand,strlen(s1[i].operand)-1);
             fprintf(fp4,"%s\t\t%s\t%s\t%s\n",s1[i].location,s1[i].opcode,te,object_code);
            fprintf(fp5," %s",object_code);
        }
        if(fin==0)
        {
            if(strcmp(s1[i].opcode,"RESB")==0)
            {
                resb=1;
            }
            if(strcmp(s1[i].opcode,"RESW")==0)
            {
                resb=1;
            }
            char t1[5]="";
            if(s1[i].len==3)
            {
                strncpy(t1,s1[i].operand,strlen(s1[i].operand)-1);
                fprintf(fp4,"%s\t\t%s\t%s\n",s1[i].location,s1[i].opcode,t1);
            }
            else if(s1[i].len==4)
            {
                strncpy(t1,s1[i].operand,strlen(s1[i].operand)-1);
                fprintf(fp4,"%s\t%s\t%s\t%s\n",s1[i].location,s1[i].label,s1[i].opcode,t1);
            }
        }
        if(resb==1)
        {
            check_len();
            fprintf(fp5,"%s\n","");
            fprintf(fp5,"%s %s %d ","T",s1[i+1].location,len_text);
        }

        i++;
    }
    fprintf(fp5,"\n%s %6s","E",oper1);
    fprintf(fp4,"%s\t\t%s\n",s1[i].location,s1[i].opcode);

   return 0;
}
