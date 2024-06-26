#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    char label[10], opcode[10], operand[10], la[10], arg[10], def1[10], def2[10];
    FILE *finput, *fexpTab, *fnamTab, *fdefTab, *fargTab;
    int in = 1, i, flag = 0, macroHeaderPrinted = 0;

    finput = fopen("input2.txt", "r");
    fexpTab = fopen("expanded.txt", "w+");
    fnamTab = fopen("namtab.txt", "w+");
    fdefTab = fopen("definition.txt", "w+");
    fargTab = fopen("argtab.txt", "w+");

    fscanf(finput, "%s%s%s", label, opcode, operand);

    while (!feof(finput)) {
        if (!macroHeaderPrinted && strcmp(opcode, "MACRO") == 0) {
            fprintf(fexpTab, "\t.%s\tN1,N2\n", label);
            macroHeaderPrinted = 1;
        }

        if (strcmp(opcode, "MACRO") == 0) {
            fprintf(fnamTab, "%s\n", label);
            fprintf(fdefTab, "%s\t%s\n", label, operand);
            fscanf(finput, "%s%s%s", label, opcode, operand);
            while (strcmp(opcode, "MEND") != 0) {
                if (operand[0] == '&') {
                    fprintf(fdefTab, "%s\t?%d\n", opcode, in);
                    in++;
                } else {
                    fprintf(fdefTab, "%s\t%s\n", opcode, operand);
                }
                fscanf(finput, "%s%s%s", label, opcode, operand);
            }
            fprintf(fdefTab, "%s\t**\n", opcode);
        } else {
            rewind(fnamTab);
            fscanf(fnamTab, "%s", la);
            while (!feof(fnamTab)) {
                if (strcmp(la, opcode) == 0) {
                    flag = 1;
                    freopen("argtab.txt", "w+", fargTab);
                    for (i = 0; i < strlen(operand); i++) {
                        if (operand[i] != ',') {
                            fprintf(fargTab, "%c", operand[i]);
                        } else {
                            fprintf(fargTab, "\n");
                        }
                    }
                    rewind(fdefTab);
                    fscanf(fdefTab, "%s%s", def1, def2);
                    while (!feof(fdefTab)) {
                        if (strcmp(def1, la) == 0) {
                            fscanf(fdefTab, "%s\t%s", def1, def2);
                            rewind(fargTab);
                            fscanf(fargTab, "%s", arg);
                            while (strcmp(def1, "MEND") != 0) {
                                fprintf(fexpTab, "-\t%s\t%s\n", def1, arg);
                                fscanf(fdefTab, "%s%s", def1, def2);
                                fscanf(fargTab, "%s", arg);
                            }
                            break;
                        }
                        fscanf(fdefTab, "%s%s", def1, def2);
                    }
                }
                fscanf(fnamTab, "%s", la);
            }
            if (flag == 0) {
                fprintf(fexpTab, "%s\t%s\t%s\n", label, opcode, operand);
            }
            flag = 0;
        }
        fscanf(finput, "%s%s%s", label, opcode, operand);
    }
    printf("Single Pass macro processor successful\n");

    fclose(finput);
    fclose(fnamTab);
    fclose(fdefTab);
    fclose(fexpTab);
    fclose(fargTab);
}

