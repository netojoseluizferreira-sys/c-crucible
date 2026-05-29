#include <stdio.h>

int main(void){
    char string[50], c, nova_string[50];

    scanf("%s", string);
    scanf(" %c", &c);

    int i = 0, j = 0;
    while (*(string + i) != '\0') {
        if (*(string + i) != c) {
            *(nova_string + j) = *(string + i);
            j++;
        }
        i++;
    }
    *(nova_string + i + 1) = '\0';

    printf("%s", nova_string);

    return 0;
}