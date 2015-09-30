#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    FILE *fp1, *fp2;
    char line[16];

    /* check file opening*/     
    fp1 = fopen("./all-names.txt", "r");
    if (fp1 == NULL){
        printf("cannot open ./all-names.txt\n");
        return 0;
    }
    fp2 = fopen("./all-names2.txt", "a");

    int i = 0;
    while (fgets(line, sizeof(line), fp1) != NULL){ 
        while (((line[i]>='a'&&line[i]<='z') || (line[i]>='A'&&line[i]<='Z'))){
            i++;
        }
        line[i]='\0';
        line[0] = tolower(line[0]);
        fwrite(line, sizeof(char), i, fp2);
        putc('\n',fp2);
        i = 0;
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}