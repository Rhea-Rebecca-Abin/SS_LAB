#include <stdio.h>
#include <string.h>

void main() {
    FILE *fp_ou, *fp_len, *fp_sy, *fp_opc, *fp_samp;
    int i, j, len, reclen = 0, loc;
    char label[20], opcode[10], operand[10], mnemonic[10], code[10], symnam[10], symloc[10], a[20], b[20], count[20], s, start[10];

    fp_ou = fopen("intermediate.txt", "r");
    fp_len = fopen("length.txt", "r");
    fp_sy = fopen("symtab.txt", "r");
    fp_opc = fopen("optab.txt", "r");
    fp_samp = fopen("sample.txt", "w");

    printf("\n Pass 2 of a two pass assembler: \n");
    printf(" \n\n");
    printf("Header Record :\n");

    fscanf(fp_ou, "\t%s\t%s\t%s\n", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        strcpy(start, operand);
        fscanf(fp_len, "%d", &len);
    }

    printf("H^%s^00%s^0000%d\t", label, start, len);
    printf("\n Text Record:\n");
    printf("T^00%s^", start);

    reclen += 6;

    fscanf(fp_ou, "%d\t%s\t%s\t%s", &loc, label, opcode, operand);

    while (strcmp(opcode, "END") != 0) {
        fseek(fp_opc, 0, SEEK_SET);

        while (fscanf(fp_opc, "%s %s", mnemonic, code) != EOF) {
            if (strcmp(opcode, mnemonic) == 0) {
                fseek(fp_sy, 0, SEEK_SET);

                while (fscanf(fp_sy, "%s\t%s", symnam, symloc) != EOF) {
                    if (strcmp(operand, symnam) == 0) {
                        reclen += 6;
                        fprintf(fp_samp, "%s%s^", code, symloc);
                        break;
                    }
                }
                break;
            }
        }

        if ((strcmp(opcode, "BYTE") == 0) || (strcmp(opcode, "WORD") == 0)) {
            if (strcmp(opcode, "WORD") == 0) {
                fprintf(fp_samp, "00000%s^", operand);
                reclen += 6;
            } else {
                if (strcmp(opcode, "BYTE") == 0) {
                    j = 0;
                    for (i = 2; i < strlen(operand) - 1; i++) {
                        count[j++] = operand[i];
                    }
                    count[j] = '\0';

                    fseek(fp_opc, 0, SEEK_SET);
                    while (fscanf(fp_opc, "%s %s", a, b) != EOF) {
                        if (strcmp(count, a) == 0) {
                            fprintf(fp_samp, "0000%s", b);
                            reclen += 6;
                            break;
                        }
                    }
                }
            }
        }
        fscanf(fp_ou, "%d %s %s %s", &loc, label, opcode, operand);
    }

    fclose(fp_samp);
    FILE *fp_read = fopen("sample.txt", "r");
    printf("%X^", reclen / 2);

    while ((s = fgetc(fp_read)) != EOF) {
        printf("%c", s);
    }

    printf("\n End Record :\n");
    printf("E^00%s\n\n", start);

    fclose(fp_ou);
    fclose(fp_sy);
    fclose(fp_opc);
    fclose(fp_len);
    fclose(fp_read);
}

