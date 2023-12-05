#include <stdio.h>
#include <string.h>
void main()
{
FILE *fp_in, *fp_nam, *fp_def, *fp_arg, *fp_ou;
// file pointers
int len, i, pos = 1;
char arg[20], mne[20], op[20], label [20], macnam[20], mne1[20], op1[20], str1[10], str2[10];

fp_in = fopen("input.txt", "r");   // input file
fp_nam = fopen("namtab.txt", "w+");// namtab file
fp_def = fopen("deftab.txt", "w+");// deftab file
fp_arg = fopen("argtab.txt", "w+");// argtab file
fp_ou = fopen("out.txt", "w");// expanded code file

fscanf(fp_in, "%s\t%s\t%s", label, mne, op);  // reads first line of input file
while (strcmp(mne, "END") != 0)  // checks if mnemonic != END

{
          if (strcmp(mne, "MACRO") == 0)   // checking if it's a macro
             {
                   printf("\n Inside MACRO\n");
                   fprintf(fp_nam, "%s\n", label);// adding macro name to namtab
                   fseek(fp_nam, SEEK_SET, 0);// reset pointer to namtab to beginning
                   fprintf(fp_def, "%s\t%s\n", label, op);// enter macro prototype in to deftab
                   
                   printf("Entering macro prototype in DEFTAB\n");
                   fscanf(fp_in, "%s\t%s\t%s", label, mne, op); // read next line of input
                   while (strcmp(mne, "MEND") != 0)     // checks if mnemonic != MEND
                      {
                         if (op[0] == '&')//checks if operand begins with &
                           {
                            sprintf(str1, "%d", pos);
                            strcpy(str2, "?"); // replace parametres with positional notation
                            strcpy(op, strcat(str2, str1));
                            pos = pos + 1; }
                            fprintf(fp_def, "%s\t%s\n", mne, op); // write macro definition to deftab
                            printf("Entering macro definition in DEFTAB\n");
                            fscanf(fp_in, "%s\t%s\t%s", label, mne, op); // read next line of input
                      }
                  
                  printf("Reached MEND\n");
                  fprintf(fp_def, "%s", mne);
                  // writes MEND to deftab
                  }

          else{
                 fscanf(fp_nam, "%s", macnam);   //read macro name from namtab
                 if (strcmp(mne, macnam) == 0) // check if mnemonic from deftab, namtab match

                 {
                          len = strlen(op); // if match found, find length of operand
                          for (i = 0; i < len; i++)
                          {
                             if (op[i] != ',')
                                   fprintf(fp_arg, "%c", op[i]);
                             else
                                      fprintf(fp_arg, "\n");
// add operands to argtab
                          }


fseek(fp_def, SEEK_SET, 0);
// reset deftab pointer to its beginning
fseek(fp_arg, SEEK_SET, 0);
// reset deftab pointer to its beginning
fprintf(fp_ou, "**\t.%s\t%s\n", mne, op);
// commented macro invocation statement
printf("\n Entering commented macro invocation statement\n");
printf("**\t.%s\t%s\n", mne, op); // print in terminal

fscanf(fp_def, "%s%s", mne1, op1);
// reading a line of macro definition
while (strcmp(mne1, "MEND") != 0){
// repeat until the mnemonic is not MEND
if (op1[0] == '?')

{ fscanf(fp_arg, "%s", arg); // read argument from argtab
fprintf(fp_ou, "**\t%s\t%s\n", mne1, arg);
//print mne1 from deftab, arg from argtab

printf("\n Replace arguments in input\n");
printf("**\t%s\t%s\n", mne1, arg); // print in terminal
} else  if(op1[0] != '&')
{ fprintf(fp_ou, "**\t%s\t%s\n", mne1, op1); 
   printf("**\t%s\t%s\n", mne1, op1);
}
fscanf(fp_def, "%s%s", mne1, op1);
//read next line from deftab
}
}
else
{
fprintf(fp_ou, "%s\t%s\t%s\n", label, mne, op);
// if macro name not found in namtab
printf("\n Line from input code\n");
printf("%s\t%s\t%s\n", label, mne, op); // print in terminal
}
}

fscanf(fp_in, "%s\t%s\t%s", label, mne, op);
// reading next statement from input table
}
printf("\nLine from input code\n");
fprintf(fp_ou, "%s\t%s\t%s", label, mne, op);
// writes END to output file
printf("%s\t%s\t%s\n", label, mne, op);
// print in terminal
fclose(fp_in);
// close pointer to input file

fclose(fp_nam);
fclose(fp_def);
fclose(fp_arg);
fclose(fp_ou);
}
