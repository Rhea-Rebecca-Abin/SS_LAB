#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passone(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3]);

int main(){
    char label[10],opcode[10],operand[10];
    char code[10],mnemonic[10];
    passone(label,opcode,operand,code,mnemonic);
    return 0;
    }
void passone(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3]){
      int locctr,length,start;
      FILE *fp1,*fp2,*fp3,*fp4,*fp5;
      fp1=fopen("input.txt","r");
      fp2=fopen("optab.txt","r");
      fp3=fopen("symtab.txt","w");
      fp4=fopen("intermediate.txt","w");
      fp5=fopen("length.txt","w");
      
      fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
      if(strcmp(opcode,"START")==0){
             start=atoi(operand);
             locctr=start;
             fprintf(fp4,"%s\t%s\t%s\n",label,opcode,operand);
             fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);}
      else{
            locctr=0;}
            
      while(strcmp(opcode,"END")!=0){
             fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                   
             if(strcmp(label,"**")!=0){
                   fprintf(fp3,"%s\t%d\n",label,locctr);
                   }
                   
             //read from optab
            fscanf(fp2,"%s\t%s",code,mnemonic);
             while(strcmp(code,"END")!=0){
                 if(strcmp(opcode,code)==0){
                    locctr+=3;
                    break;
                    }
             fscanf(fp2,"%s\t%s",code,mnemonic);
           }
             if(strcmp(opcode,"RESW")==0){
                    locctr+=3*(atoi(operand));
                    }
                    
                    
                    
             else if(strcmp(opcode,"WORD")==0){
                  locctr+=3;}
                  
             else if(strcmp(opcode,"RESB")==0){
                   locctr+=atoi(operand);
                   }
             else if(strcmp(opcode,"BYTE")==0){
                   locctr++;
                   }
             fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
             }
             
             fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
             
             fclose(fp1);
             fclose(fp2);
             fclose(fp3);
             fclose(fp4);
             
             length=locctr-start;
             fprintf(fp5,"%x",length);
             fclose(fp5);
             
             printf("Successfully executed pass one of two pass assembler");}
            
            
            
            
            
