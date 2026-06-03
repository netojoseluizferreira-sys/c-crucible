// 086 — A Tumba dos Alinhamentos (Alinhamento de Memória)
// Compara duas structs com os mesmos campos em ordens diferentes,
// demonstrando o impacto do padding e alinhamento no tamanho final.
//
// Struct A: char, int, char → padding após cada char para alinhar o int
//   Layout: [c1][_][_][_][x][x][x][x][c2][_][_][_] = 12 bytes
// Struct B: int, char, char → int já alinhado, chars agrupados
//   Layout: [x][x][x][x][c1][c2][_][_] = 8 bytes
//
// Conclusão: declarar campos em ordem decrescente de tamanho (maior primeiro)
// reduz o padding e economiza memória.
#include <stdio.h>

int main(void) {
    // Ordem ineficiente: char, int, char → 12 bytes (3 padding p/ cada char)
    typedef struct {
        char c1;
        int  x;
        char c2;
    } A;

    // Ordem eficiente: int, char, char → 8 bytes (apenas 2 bytes de padding)
    typedef struct {
        int  x;
        char c1;
        char c2;
    } B;

    printf("%zu\n%zu\n", sizeof(A), sizeof(B));

    return 0;
}