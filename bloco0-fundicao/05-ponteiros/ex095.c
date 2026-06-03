// 095 — O Espelho da Verdade (const com Ponteiros)
// Demonstra a diferença entre qualificações const em múltiplos níveis
// de indireção. Um ponteiro para const (const int *q) promete não
// modificar o valor apontado, mas a promessa é apenas no primeiro
// nível. Quando se cria um ponteiro duplo para esse ponteiro (int **qq),
// a indireção dupla ignora a promessa do nível intermediário.
//
// **qq: tenta acessar o valor através do caminho com const (q),
//       mas a promessa de imutabilidade está apenas em *q, não em **qq.
//       O compilador permite a leitura, mas rejeitaria **qq = 10;.
//
// **pp: acessa o valor através do caminho sem const (p),
//       sem restrições. O compilador permite leitura e escrita.
//
// O código abaixo apenas lê e imprime os valores, sem tentar modificá-los
// através dos ponteiros duplos, demonstrando o acesso via indireção.
#include <stdio.h>

int main(void) {
    int numero;
    int *p;           // ponteiro simples (sem const)
    const int *q;     // ponteiro para const: promete não modificar *q
    int **pp;         // ponteiro duplo (sem const)
    const int **qq;   // ponteiro duplo para ponteiro-para-const

    scanf("%d", &numero);

    p = &numero;      // p aponta para numero
    q = &numero;      // q também aponta para numero, mas com promessa const
    pp = &p;          // pp aponta para p
    qq = &q;          // qq aponta para q

    // Ambos acessam o valor de numero via dupla indireção
    // **qq: segue qq → q → numero (q promete const, mas a leitura é permitida)
    // **pp: segue pp → p → numero (sem restrições)
    printf("%d\n", **qq - 1);  // numero - 1
    printf("%d\n", **pp - 1);  // numero - 1

    return 0;
}