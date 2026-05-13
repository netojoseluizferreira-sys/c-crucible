// 18 — O Cofre do Tamanho Certo
// Simula um contêiner com capacidade máxima de 255 kg (unsigned char).
// Se o peso excede 255, aplica overflow natural (módulo 256) e mostra o excesso.
// Caso contrário, mostra quanto ainda cabe no contêiner.
//
// Estratégia:
// - Usa unsigned char (8 bits, 0–255) como tipo do cofre.
// - Se peso > 255, o cast para unsigned char trunca para módulo 256 (excesso).
// - Se peso ≤ 255, subtrai de 255 para mostrar a capacidade restante.

#include <stdio.h>

int main(){
    unsigned char carga = 0;
    unsigned int peso;
    
    scanf("%u", &peso);

    if ((peso >> 8) > 0){
        // peso > 255: o que exceder o byte mais significativo é overflow
        carga += (unsigned char)peso;
        printf("%hhu kg de sobra", carga);
    } else {
        // peso ≤ 255: quanto falta para encher o cofre
        carga = (unsigned char)255;
        carga -= (unsigned char)peso;
        printf("%hhu kg de falta", carga);
    }
    
    return 0;
}