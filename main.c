#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
// inclusão da biblioteca do windos para usar os recursos de limpar a tela
/*
#ifdef WINDOWS
#include <Windows.h>
#endif
*/
#ifdef _WIN64
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef struct NO {
  int disco;
  struct NO *prox; // ponteiro para o proximo
} NO;

typedef struct PILHA {
  NO *topo; // ponteiro para o topo
} PILHA;

void inicializaPilha(PILHA *p) { p->topo = NULL; }

void empilha(int disco, PILHA *p) {
  NO *ptr = (NO *)malloc(sizeof(NO)); // alocação dinâmica
  if (ptr == NULL) {
    printf("Erro de alocação de nó!\n");
    return;
  } else {
    ptr->disco = disco;
    ptr->prox = p->topo;
    p->topo = ptr;
  }
}

int desempilha(PILHA *p) {
  NO *ptr = p->topo; // no de backup
  int dado;
  if (ptr == NULL) {
    printf("Pilha Vazia!");
    return -1;
  } else {
    p->topo = ptr->prox; // apontando para o proximo que vai ser o topo
    ptr->prox = NULL;    // Desligando o antigo tipo da pilha
    dado = ptr->disco;
    free(ptr);
    return dado;
  }
}
// função para imprimir as 3 pilhas uma ao lado da outra
void imprimePilha(PILHA *p1, PILHA *p2, PILHA *p3) {
  NO *ptr1 = p1->topo;
  NO *ptr2 = p2->topo;
  NO *ptr3 = p3->topo;
  do {
    if (ptr1 != NULL) {
      printf("\n\t%d ", ptr1->disco);
      ptr1 = ptr1->prox;
    } else {
      printf("\n\t- ");
      ptr1 = NULL;
    }
    if (ptr2 != NULL) {
      printf("\t\t%d ", ptr2->disco);
      ptr2 = ptr2->prox;
    } else {
      printf("\t\t- ");
      ptr2 = NULL;
    }
    if (ptr3 != NULL) {
      printf("\t\t%d ", ptr3->disco);
      ptr3 = ptr3->prox;
    } else {
      printf("\t\t- ");
      ptr3 = NULL;
    }
  } while (ptr1 != NULL || ptr2 != NULL || ptr3 != NULL);

  printf("\n");
}
// função que procura em qual torre está o disco que quero mover
/*obs: procura só no topo pq como é uma pilha só posso remover do topo
ou seja o ultimo q entra é o primeiro que sai
*/
int imprimeregra() {
  int op;
  system("cls || clear");
  printf("\n******************************************");
  printf("\n***           Torre de Hanoi           ***");
  printf("\n******************************************");
  printf("\n* O jogo Torre de Hanoi tem o objetivo   *");
  printf("\n* fazer o jogador mover todos os discos  *");
  printf("\n* que estão na torre A para a torre C.   *");
  printf("\n* Regras básicas:                        *");
  printf("\n* -> Um disco maior não pode ficar sobre *");
  printf("\n*    um disco menor                      *");
  printf("\n* -> Mover o disco do topo primeiro      *");
  printf("\n* -> Usar a torre B como auxiliar        *");
  printf("\n******************************************");
  printf("\n*Press algum numero + enter para iniciar*\n");
  return scanf("%i", &op);
}
int procuraNoTopo(PILHA *p) {
  NO *ptr = p->topo;
  if (ptr == NULL) {
    printf("Pilha vazia!\n");
    return -1;
  } else {
    return ptr->disco;
  }
}

/*Função que verifica se o movimento que o jogador quer fazer com o disco
é válido se for retorna o numero do disco, caso contrario retorna -1*/
/*Essa função vai receber a pilha que o jogador que mover o disco e depois vai
verificar se há algum disco já existente nessa fila se houver irá realizar as
operações de decisão parasaber se o movimento é válido respeitando a regra que
um disco maior não pode ficar sobre um menor
*/
int validaMovimento(PILHA *p, int disco) {
  NO *ptr = p->topo;
  if (ptr == NULL) { // se null pilha vazia, movimento válido
    return disco;
  } else { // pilha com discos
    if (procuraNoTopo(p) >
        disco) { // verifica se o disco que está no topo da pilha é maior que o
                 // que eu quero inserir, movimento válido
      return disco;
    } else { // caso contrário movimento inválido
      printf("\nMovimento inválido!");
      return -1;
    }
  }
}
/*
Função para validar a vitória do jogador se a pilha da torre 1 e a pilha da
torre 2 estiverem vazias é pq ele completou a torre 3
*/
int validaVitoria(PILHA *p1, PILHA *p2) {
  NO *ptr1 = p1->topo;
  NO *ptr2 = p2->topo;

  if (ptr1 == NULL && ptr2 == NULL) {
    return 1;
  } else {
    return 0;
  }
}

void novoMenu(int jogadas) {
  system("cls || clear");
  printf("\n***************************************");
  printf("\n***         Torre de Hanoi          ***");
  printf("\n***************************************");
  printf("\n\t Jogadas: %i \n", jogadas);
}

int main() {

  /*O imprime regra tem que retornar alguma coisa então somente quando o usuário
   * presionar qualquer tecla que o jogo irá começar a rodar ...*/
  imprimeregra();

  int jogadas = 0;
  int vencedor = 0;
  int disco;
  char torre;

  PILHA *TorreA = (PILHA *)malloc(sizeof(PILHA));
  PILHA *TorreB = (PILHA *)malloc(sizeof(PILHA));
  PILHA *TorreC = (PILHA *)malloc(sizeof(PILHA));
  if (TorreA == NULL || TorreB == NULL || TorreC == NULL) {
    printf("Erro de alocação da pilha!");
    exit(0);
  } else {
    inicializaPilha(TorreA);
    inicializaPilha(TorreB);
    inicializaPilha(TorreC);
    // inicializando os discos na torre A
    novoMenu(jogadas);
    empilha(3, TorreA);
    empilha(2, TorreA);
    empilha(1, TorreA);
    imprimePilha(TorreA, TorreB, TorreC);
    printf(" ------- ------- -------\n");
    printf("\tA\t\tB\t\tC");

    do {

      if (jogadas == 0) {

        // Solicitando a jogada do usuário Disco que quer mover + local
        printf("\nInforme a sua jogada.\n ");
        printf("Disco: ");
        scanf("%i", &disco);
        printf("Torre: ");
        scanf("%c", &torre);
        torre = getchar();
        jogadas++;

        if ((disco == 1 || disco == 2 || disco == 3) &&
            (torre == 'A' || torre == 'B' || torre == 'C' || torre == 'a' ||
             torre == 'b' || torre == 'c')) {
          // se o disco está na torre A ele só pode mover para a Tore B ou C
          // Não faço a vaçidação de movimento na primeira jogada pq as outras
          // pilhas estão vazias...
          if (torre == 'B' || torre == 'b') {
            novoMenu(jogadas);
            empilha(TorreA->topo->disco, TorreB);
            desempilha(TorreA);
            imprimePilha(TorreA, TorreB, TorreC);
            printf(" ------- ------- -------\n");
            printf("\tA\t\tB\t\tC");
            printf("\n");

          } else if (torre == 'C' || torre == 'c') {
            novoMenu(jogadas);
            empilha(TorreA->topo->disco, TorreC);
            desempilha(TorreA);
            imprimePilha(TorreA, TorreB, TorreC);
            printf(" ------- ------- -------\n");
            printf("\tA\t\tB\t\tC");
            printf("\n");
          }
        } else {

          printf("Jogada Inválida!");
          usleep(1000 * 1000);
          jogadas--;
        }
      } else {
        system("cls || clear");
        novoMenu(jogadas);
        imprimePilha(TorreA, TorreB, TorreC);
        printf(" ------- ------- -------\n");
        printf("\tA\t\tB\t\tC");
        printf("\nInforme a sua jogada.\n");
        printf("Disco: ");
        scanf("%i", &disco);
        printf("Torre: ");
        scanf("%c", &torre);
        torre = getchar();
        jogadas++;

        if ((disco == 1 || disco == 2 || disco == 3) &&
            (torre == 'A' || torre == 'B' || torre == 'C' || torre == 'a' ||
             torre == 'b' || torre == 'c')) {
          // procuro em qual torre o disco está
          if (procuraNoTopo(TorreA) == disco) {
            // se cair aqui sei q o disco tá na torre A
            if (torre == 'B' || torre == 'b') {
              // se cair aqui é pq quer mandar o disco para torre B

              // validar o movimento
              if (validaMovimento(TorreB, disco) != -1) {
                novoMenu(jogadas);
                empilha(TorreA->topo->disco, TorreB);
                desempilha(TorreA);
                imprimePilha(TorreA, TorreB, TorreC);
                printf(" ------- ------- -------\n");
                printf("\tA\t\tB\t\tC");
                printf("\n");
                vencedor = validaVitoria(TorreA, TorreB);
              } else {
                // se cair aqui é pq a valida movimento retornou -1
                printf("\n\n\n*******Movimento Inválido*******");

                usleep(1000 * 1000);
                system("cls || clear");
                jogadas--; // deccremento a jogada para não contar como um
                           // movimento
              }

            } else if (torre == 'C' || torre == 'c') {
              // se cair aqui é pq quer mandar o disco para torre C
              // validar o movimento
              if (validaMovimento(TorreC, disco) != -1) {
                novoMenu(jogadas);
                empilha(TorreA->topo->disco, TorreC);
                desempilha(TorreA);
                imprimePilha(TorreA, TorreB, TorreC);
                printf(" ------- ------- -------\n");
                printf("\tA\t\tB\t\tC");
                printf("\n");
                vencedor = validaVitoria(TorreA, TorreB);
              } else {
                // se cair aqui é pq a valida movimento retornou -1
                printf("Movimento Inválido");
                usleep(1000 * 1000);
                jogadas--; // deccremento a jogada para não contar como um
                           // movimento
              }
            } else {
              printf("Inválido!");
              jogadas--;
            }

          } else if (procuraNoTopo(TorreB) == disco) {
            // sei q o disco tá na torre B
            if (torre == 'A' || torre == 'a') {
              // se cair aqui é pq quer mandar o disco para torre A
              if (validaMovimento(TorreA, disco) != -1) {
                novoMenu(jogadas);
                empilha(TorreB->topo->disco, TorreA);
                desempilha(TorreB);
                imprimePilha(TorreA, TorreB, TorreC);
                printf(" ------- ------- -------\n");
                printf("\tA\t\tB\t\tC");
                printf("\n");
                vencedor = validaVitoria(TorreA, TorreB);
              } else {
                // se cair aqui é pq a valida movimento retornou -1
                printf("Movimento Inválido");
                usleep(1000 * 1000);
                jogadas--; // deccremento a jogada para não contar como um
                           // movimento
              }

            } else if (torre == 'C' || torre == 'c') {
              // se cair aqui é pq quer mandar o disco para torre C
              // valida movimento
              if (validaMovimento(TorreC, disco) != -1) {
                novoMenu(jogadas);
                empilha(TorreB->topo->disco, TorreC);
                desempilha(TorreB);
                imprimePilha(TorreA, TorreB, TorreC);
                printf(" ------- ------- -------\n");
                printf("\tA\t\tB\t\tC");
                printf("\n");
                vencedor = validaVitoria(TorreA, TorreB);
              } else {
                // se cair aqui é pq a valida movimento retornou -1
                printf("Movimento Inválido");
                usleep(1000 * 1000);
                jogadas--; // deccremento a jogada para não contar como um
                           // movimento
              }
            } else {
              printf("Inválido!");
              jogadas--;
            }

          } else if (procuraNoTopo(TorreC) == disco) {
            // o disco tá na torre C

            if (torre == 'A' || torre == 'a') {
              // se cair aqui é pq quer mandar o disco para torre A
              // valida movimento
              if (validaMovimento(TorreA, disco) != -1) {
                novoMenu(jogadas);
                empilha(TorreC->topo->disco, TorreA);
                desempilha(TorreC);
                imprimePilha(TorreA, TorreB, TorreC);
                printf(" ------- ------- -------\n");
                printf("\tA\t\tB\t\tC");
                printf("\n");
                vencedor = validaVitoria(TorreA, TorreB);
              } else {
                // se cair aqui é pq a valida movimento retornou -1
                printf("Movimento Inválido");
                usleep(1000 * 1000);
                jogadas--; // deccremento a jogada para não contar como um
                           // movimento
              }

            } else if (torre == 'B' || torre == 'b') {
              // se cair aqui é pq quer mandar o disco para torre B
              // valida movimento
              if (validaMovimento(TorreB, disco) != -1) {
                novoMenu(jogadas);
                empilha(TorreC->topo->disco, TorreB);
                desempilha(TorreC);
                imprimePilha(TorreA, TorreB, TorreC);
                printf(" ------- ------- -------\n");
                printf("\tA\t\tB\t\tC");
                printf("\n");
                vencedor = validaVitoria(TorreA, TorreB);
              } else {
                // se cair aqui é pq a valida movimento retornou -1
                printf("Movimento Inválido");
                usleep(1000 * 1000);
                jogadas--; // deccremento a jogada para não contar como um
                           // movimento
              }
            } else {
              printf("Inválido!");
              usleep(1000 * 1000);
              jogadas--;
            }

          } else {
            printf("\nDisco Inválido!");
            usleep(1000 * 1000);
            jogadas--;
          }
        } else {
          printf("Jogada Inválida!");
          usleep(1000 * 1000);
          jogadas--;
        }
      }

    } while (vencedor == 0);
    novoMenu(jogadas);
    printf("Parabéns você Venceu!");
    printf("\nJogar Novamente:\n1-Sim\n2-Não\n->");
    int aux;
    scanf("%i", &aux);
    if (aux == 1) {
      main();
      vencedor = 0;
    } else {
      printf("Obrigado por jogar...");
    }
  }
}
