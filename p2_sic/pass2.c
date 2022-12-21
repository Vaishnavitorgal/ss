#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int i=0,j,locctr,flag2=0,size,x=0,text_len=0,a=0,b=0,resb=0,lp=0,index1=0,len_text,comp=0,error_len;
char addr[20];
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
struct instruction s[12];

 struct symbols
 {
     char sym_name[20];
     char sym_addr[20];
 };
 struct symbols symtab[10];

 void store_instr(char *temp,struct instruction *s)
 {
     char temp1[40];
     strcpy(temp1,temp);
    int length=0,i=0;
    char *pch = strtok (temp," ");
    printf("%s",pch);
    if(strcmp(pch,".\n")==0)
    {
        printf("%s\n","comment line\n");
    }
    while (pch != NULL)
    {
        length++;
        pch = strtok (NULL, " ");
    }

   if(length==2)
  {
      int er=0;
      char *str = strtok (temp1," ");
      strcpy_s(s->location,20,str);
      str = strtok (NULL, " ");
      if(strcmp(str,"RSUB")==0)  //new text record anything remaining rsub and end it is error
      {
          er=1;
      }
      if(strcmp(str,"END\n")==0)
      {
          er=1;
      }
      if(er==1)
      {
        strcpy_s(s->opcode,20,str);
        s->len=2;
        size++;
      }
      else
      {
          printf("%s\n","error");
      }

  }
  else if(length==3)
  {
      char *str = strtok (temp1," ");
      strcpy_s(s->location,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s->opcode,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s->operand,20,str);
      s->len=3;
      size++;

  }
  else if(length==4)
  {
      char *str = strtok (temp1," ");
      strcpy_s(s->location,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s->label,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s->opcode,20,str);
      str = strtok (NULL, " ");
      strcpy_s(s->operand,20,str);
      s->len=4;
      size++;
  }
 }

 int search(char *s_opcode)  //searching opcode
 {
     FILE *fp3;
     int flag=0;
    fp3=fopen("opcode.txt","r");
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
                    strcpy_s(nem,20,str);   //storing in nem=address
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
     while(strcmp(s[jk].opcode,"END\n")!=0)
     {
         if(search(s[jk].opcode)==1)
         {
             len_text=len_text+3;
         }
         else if(strcmp(s[jk].opcode,"WORD")==0)
         {
             len_text=len_text+3;
         }
         else if(strcmp(s[jk].opcode,"BYTE")==0)
         {
             int b_len;
             b_len=strlen(s[jk].operand);
             b_len=b_len-4;
             len_text=len_text+b_len;
         }
         else if(strcmp(s[jk].opcode,"RESB")==0)   //id occurred then go to next text record
         {
             error_len=1;
         }
         else if(strcmp(s[jk].opcode,"RESW")==0)
             error_len=1;
         if(len_text>30)
             error_len=1;
         if(error_len==1){
             comp=jk+1;
             break;}
         jk++;
         }


}



 void start()
 {
     FILE *fp2;
     int n=0;
     char j[20];
    fp2=fopen("symbol.txt","r");
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

    start();
    int loop=0,flag=0,i=0,flag_sym=0,t_len;
    char lo[10],lo1[10],lab[10],opc[10],oper[10],lab1[10],oper1[10],opc1[10],temp[30],ad[10];
    char length[10]="0023";
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1=fopen("intermediate.txt","r");
    fp4=fopen("output.txt","w+");
    fp5=fopen("object_pgm.txt","w+");
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
    fp1=fopen("intermediate.txt","r");
    while(!feof(fp1))
    {
        fgets(temp, 40, fp1);
        store_instr(temp,&s[index1]);
        printf("\n");
        index1++;
    }
    fclose(fp1);
    check_len();  //check text record len=30
    printf("Length is : %d",len_text);
    fprintf(fp5,"%d",len_text);
    while(strcmp(s[x].opcode,"END\n")!=0)    //search object code
    {
        resb=0;
        printf("%s\n",s[x].opcode);
        flag_sym=0;
        int check=0,sym_check=0,l=0,p=0;
        char num[20];
        check=search(s[x].opcode);  //opcode present
       if(check==1)
        {
            char p1[20];
           if(s[x].len==3 || s[x].len==4)
            {
                if(strchr(s[x].operand,'X')!= NULL)    //str1,x -> str1
                {
                    char *str = strtok (s[x].operand,",");
                    strcpy(p1,s[x].operand);

                    strcpy(s[x].operand,str);
                    p=1;
                }
               for(i=0;i<5;i++)  //symbol searcch
               {
                   l=strlen(s[x].operand);
                   if(p==1)
                   {
                       l++;
                   }
                   if(strncmp(s[x].operand,symtab[i].sym_name,l-1)==0)    //to remove \n  and symbol check
                   {
                       //int temp = (strtol(symtab[i].sym_addr[0],NULL,16) + 8);
                       //char *stemp;
                       //itoa(temp,stemp,16);
                       //char *st = symtab[i].sym_addr;
                       //int i = strtol(st,NULL,16)%10;
                       //printf("Here : %x",i);
                       //printf("g ,%s",st);

                       //int a ;
                       //itoa(atoi(symtab[i].sym_name),a,16);
                       //printf("%x",a);
                       strcpy(addr,symtab[i].sym_addr);
                       flag_sym=1;
                       break;
                   }
               }
               if(p==1)
               {
                   strcpy(s[x].operand,p1);
               }
               if(flag_sym==0)
            {
                strcpy(addr,"0");  //if operand not found in symtab
            }
            }

            object_code[0]=nem[0];
            object_code[1]=nem[1];
            for(p=2;p<6;p++)   //merging location add and mnemonic value
            {
                object_code[p]=addr[p-2];
            }
            printf("%s\n",object_code);
            strcpy(s[x].object,object_code);
            fprintf(fp5,"%s%s"," ",object_code);
            text_len=text_len+3;
            printf("%d\n",text_len);
            if(s[x].len==4)
            {//output file writing

                fprintf(fp4,"%s\t%s\t%s\t%s\t\t%s\n",s[x].location,s[x].label,s[x].opcode,s[x].operand,s[x].object);
            }
            if(s[x].len==3)
            {
                int u;
                u=strlen(s[x].operand);
                char lt[20];   //remove /n  output file writing
                strncpy(lt,s[x].operand,u-1);
                fprintf(fp4,"%s\t\t%s\t%s\t\t%s\n",s[x].location,s[x].opcode,lt,object_code);
            }
        }

        if(strcmp(s[x].opcode,"BYTE")==0) //kletech
        {
           strcpy(object_code,"");
           char byte_test[10];
           int b_len=0;
           if(s[x].operand[0]=='C')
           {
              b_len=strlen(s[x].operand);
              b_len=b_len-3;
               for(i=2;i<(b_len+1);i++)
                {
                    int y=s[x].operand[i];
                    itoa(y,byte_test,16);  //ascii convert
                    strcat(object_code,byte_test);
                }
            fprintf(fp5,"%s%s"," ",object_code);
            printf("%s\n",object_code);
            strcpy(s[x].object,object_code);
           }

           else if(s[x].operand[0]=='X') //X'F1'  C'kletech'
           {
               strcpy(object_code,"");
               char test[5]="";
               for(int p=2;p<strlen(s[x].operand)-2;p++)
                {
                    test[p-2]=s[x].operand[p];
                    strcpy(object_code,test);
                }
            fprintf(fp5,"%s%s"," ",object_code);
            printf("%s\n",object_code);
            strcpy(s[x].object,object_code);
           }

           int u;
           u=strlen(s[x].operand);
           char lt[20]="";
           strncpy(lt,s[x].operand,u-1);
           fprintf(fp4,"%s\t%s\t%s\t%s\t%s\n",s[x].location,s[x].label,s[x].opcode,lt,s[x].object);
        }
        else if(strcmp(s[x].opcode,"WORD")==0)
        {
            int len=0;
            char a[10];
            len=strlen(s[x].operand);
            itoa(atoi(s[x].operand),a,16);   //hex convert  than in integer
            strcpy(object_code,a);
            int target=6,m=0;
            char padding[4]="";
            int pad_len=target-strlen(object_code);

            for(m=0;m<pad_len;m++)
            {
                strcat(padding,"0");    //00+1000(4096)   %06x
            }

            strcat(padding,object_code);
            strcpy(object_code,padding);
            printf("%s\n",object_code);
            strcpy(s[x].object,object_code);
            fprintf(fp5,"%s%s"," ",object_code);
            int u;
                u=strlen(s[x].operand);
                char lt[20]="";
                strncpy(lt,s[x].operand,u-1);
            fprintf(fp4,"%s\t%s\t%s\t%s\t\t%s\n",s[x].location,s[x].label,s[x].opcode,lt,s[x].object);

        }
        else if(strcmp(s[x].opcode,"RESB")==0)
        {
            resb=1;
            fprintf(fp4,"%s\t%s\t%s\t%s",s[x].location,s[x].label,s[x].opcode,s[x].operand);
        }
        else if(strcmp(s[x].opcode,"RESW")==0)
        {
            resb=1;
            fprintf(fp4,"%s\t%s\t%s\t%s",s[x].location,s[x].label,s[x].opcode,s[x].operand);
        }
        if(resb==1)
        {
            check_len();
            fprintf(fp5,"%s\n","");
            fprintf(fp5,"%s %s %d ","T",s[x].location,len_text);

        }
        x++;

    }
    fprintf(fp5,"\n%s %6s","E",oper1);
    fprintf(fp4,"%s\t\t%s\n",s[x].location,s[x].opcode);

    return 0;
}
