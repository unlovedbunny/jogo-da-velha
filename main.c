#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void FImprimeTabuleiro(char Tabuleiro[3][3]);
void FZerarTabuleiro(char Tabuleiro[3][3]);
void FCoordenadaJogada(char Tabuleiro[3][3], int *jogador, char nomes[2][20]);
void FImprimeData(void);
char FNomes(char nomes[2][20]);
int FGanhou(char Tabuleiro[3][3], int *jogador, char nomes[2][20]);


int main(void) {
  // main funcionando
  char Tabuleiro[3][3], nomes[2][20];
  int jogador = 1, op, jogadas = 0;
  
  FILE *arq = fopen("ranking.txt", "a");
  if(arq == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return 2;
  }

  do {
    printf("\n");
    printf("\t\t\t#######################################\n");
    printf("\t\t\t#          ##### Instruções #####     #\n");
    printf("\t\t\t#                                     #\n");
    printf("\t\t\t#  Digite 1 para começar/continuar o  #\n");
    printf("\t\t\t#  jogo ou 0 para sair do programa a  #\n");
    printf("\t\t\t#  qualquer momento.                  #\n");
    printf("\t\t\t#                                     #\n");
    printf("\t\t\t#  Qualquer outro caractere ou número #\n");
    printf("\t\t\t#  fará o menu se repetir.            #\n");
    printf("\t\t\t#                                     #\n");
    printf("\t\t\t#   Instruções compreendidas?         #\n");
    printf("\t\t\t#######################################\n");
    printf("\nDigite sua opção: ");
    scanf("%d", &op);
  
  
    if (op == 1) {
        
      FNomes(nomes);
      FZerarTabuleiro(Tabuleiro);

      do {
        do{
        FImprimeTabuleiro(Tabuleiro);
        FCoordenadaJogada(Tabuleiro, &jogador, nomes);
        FGanhou(Tabuleiro, &jogador, nomes);
          
        jogadas++;
          
        }while(FGanhou(Tabuleiro, jogador, nomes) == 0 && jogadas < 9); //looping do jogo
        
        
      } while (op == 1); // pra saber se o jogador quer continuar jogando ou não
      
    } else if (op == 0) {
      printf("\nObrigado por jogar!");
      exit(0);
    }else{
      printf("\nOpção '%d' Inválida. Tente Novamente\n", op);
    }
  } while (op != 1);
  fclose(arq);
  return 0;
}

void FImprimeTabuleiro(char Tabuleiro[3][3]) {
  int i, j, jogadas = 0, ganhou = 0, jogador = 1;
  system("cls || clear");

  printf("\n\n\t 0   1   2\n");
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (j == 0) {
        printf("\t");
      }
      printf(" %c ", Tabuleiro[i][j]);
      if (j < 2) {
        printf("|");
      }
      if (j == 2) {
        printf("%d", i);
      }
    }
    if (i < 2)
      printf("\n\t-----------\n");
  }
  printf("\n\n");
  
  return;
}

void FCoordenadaJogada(char (*Tabuleiro)[3], int *jogador, char nomes[2][20]) // O compilador não precisa saber que é uma matriz 3x3; só precisa saber o tipo e o tamanho de cada linha da matriz.
{
  // encontrar coordenada funcionando
  int linha, coluna, jogadas = 0;

  do {

    printf("\nJOGADOR %d (%s):\n Digite a Coluna que deseja preencher: ", *jogador, nomes[*jogador - 1]);
    getchar();
    scanf("%d", &coluna);
    printf("Digite a Linha que deseja preencher: ");
    scanf("%d", &linha);

  } while (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || Tabuleiro[linha][coluna] != ' '); // se for != ' ' significa que a coordenada está ocupada

  // salvar coordenada na matriz
  if (*jogador == 1) {
    Tabuleiro[linha][coluna] = '0';
    *jogador = 2;
  } else {
    Tabuleiro[linha][coluna] = 'X';
    *jogador = 1; // a jogada passa para o outro jogador
  }
  
 
  jogadas++;

  return;
}

void FZerarTabuleiro(char Tabuleiro[3][3]) {
  // funcionando
  int i, j;

  // iniciar cada elemento da matriz c espaço vazio

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Tabuleiro[i][j] = ' ';
    }
  }
}

int FGanhou(char Tabuleiro[3][3], int *jogador, char nomes[2][20]) {
  int jogadas = 0, ganhou = 0;

  FILE *arq = fopen("ranking.txt", "a+");
  if(arq == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return 2;
  }
  do {
    // por linha
    if ((Tabuleiro[0][0] == '0' && Tabuleiro[0][1] == '0' &&
         Tabuleiro[0][2] == '0') ||
        (Tabuleiro[1][0] == '0' && Tabuleiro[1][1] == '0' &&
         Tabuleiro[1][2] == '0') ||
        (Tabuleiro[2][0] == '0' && Tabuleiro[2][1] == '0' &&
         Tabuleiro[2][2] == '0')) {
      
      printf("\n\tJogador %s ganhou!\n", nomes[(*jogador % 2)]);
      fputs(nomes[(*jogador % 2)], arq);
      
      FImprimeData();
      fflush(arq);

      ganhou = 1;
    }
    if ((Tabuleiro[0][0] == 'X' && Tabuleiro[0][1] == 'X' &&
         Tabuleiro[0][2] == 'X') ||
        (Tabuleiro[1][0] == 'X' && Tabuleiro[1][1] == 'X' &&
         Tabuleiro[1][2] == 'X') ||
        (Tabuleiro[2][0] == 'X' && Tabuleiro[2][1] == 'X' &&
         Tabuleiro[2][2] == 'X')) {
      printf("\n\tJogador %s ganhou!\n", nomes[(*jogador % 2)]);
      fputs(nomes[(*jogador % 2)], arq);

      FImprimeData();
      fflush(arq);

      ganhou = 1;
    }

    // por coluna
    if ((Tabuleiro[0][0] == '0' && Tabuleiro[1][0] == '0' &&
         Tabuleiro[2][0] == '0') ||
        (Tabuleiro[0][1] == '0' && Tabuleiro[1][1] == '0' &&
         Tabuleiro[2][1] == '0') ||
        (Tabuleiro[0][2] == '0' && Tabuleiro[1][2] == '0' &&
         Tabuleiro[2][2] == '0')) {
      printf("\n\tJogador %s ganhou!\n", nomes[(*jogador % 2)]);
      fputs(nomes[(*jogador % 2)], arq);

      FImprimeData();
      fflush(arq);

      ganhou = 1;
    }
    if ((Tabuleiro[0][0] == 'X' && Tabuleiro[1][0] == 'X' &&
         Tabuleiro[2][0] == 'X') ||
        (Tabuleiro[0][1] == 'X' && Tabuleiro[1][1] == 'X' &&
         Tabuleiro[2][1] == 'X') ||
        (Tabuleiro[0][2] == 'X' && Tabuleiro[1][2] == 'X' &&
         Tabuleiro[2][2] == 'X')) {
      printf("\n\tJogador %s ganhou!\n", nomes[(*jogador % 2)]);
      fputs(nomes[(*jogador % 2)], arq);

      FImprimeData();
      fflush(arq);

      ganhou = 1;
    }
    // por diagonal principal
    if ((Tabuleiro[0][0] == '0' && Tabuleiro[1][1] == '0' &&
         Tabuleiro[2][2] == '0')) {
      printf("\n\tJogador %s ganhou!\n", nomes[(*jogador % 2)]);
      fputs(nomes[(*jogador % 2)], arq);

      FImprimeData();
      fflush(arq);

      ganhou = 1;
    }
    if ((Tabuleiro[0][0] == 'X' && Tabuleiro[1][1] == 'X' &&
         Tabuleiro[2][2] == 'X')) {
      printf("\n\tJogador %s ganhou!\n", nomes[(*jogador % 2)]);
      fputs(nomes[(*jogador % 2)], arq);

      FImprimeData();
      fflush(arq);

      ganhou = 1;
    }

    // por diagonal secundária
    if ((Tabuleiro[0][2] == '0' && Tabuleiro[1][1] == '0' &&
         Tabuleiro[2][0] == '0')) {
      printf("\n\tJogador %s ganhou!\n", nomes[(*jogador % 2)]);
      fputs(nomes[(*jogador % 2)], arq);

      FImprimeData();
      fflush(arq);

      ganhou = 1;
    }
    if ((Tabuleiro[0][2] == 'X' && Tabuleiro[1][1] == 'X' &&
         Tabuleiro[2][0] == 'X')) {
      printf("\n\tJogador %s ganhou!\n", nomes[(*jogador % 2)]);
      fputs(nomes[(*jogador % 2)], arq);

      FImprimeData();
      fflush(arq);

      ganhou = 1;
    }
    // Verificando se o tabuleiro está cheio (empate)
    int cheio = 1;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (Tabuleiro[i][j] == ' ') {
          cheio = 0;
          break;
        }
      }

      if (!cheio) // se cheio for 0, o jogo continua
        break;
    }
    if (cheio) {
       
      printf("Houve empate entre os jogadores %s e %s!\n", nomes[0], nomes[1]);
      ganhou = 1;
      fprintf(arq, "Empate entre %s e %s\n", nomes[0], nomes[1]);
      fclose(arq);
      exit(0);
    }
    break;

    } while (jogadas < 9);

  fclose(arq);
  return 0;
  }

char FNomes(char nomes[2][20]){
  int i, j, jogador;
  
  getchar();
    for(i = 0; i < 2; i++){
      printf("Digite o nome do jogador %d:\n ", i+1);
      fgets(nomes[i], 20, stdin);

      if ((strlen(nomes[i]) > 0) && (nomes[i][strlen(nomes[i]) - 1] == '\n')) {
          nomes[i][strlen(nomes[i]) - 1] = '\0';
      }
        for(j=0; nomes[i][j] != '\0'; j++){
          nomes[i][j] = toupper(nomes[i][j]);
        }
    }
  
    while (strcmp(nomes[0], nomes[1]) == 0) {
      printf("Os nomes dos jogadores não podem ser iguais. Digite novamente.\n");
      printf("Digite o nome do jogador 2: ");
      fgets(nomes[1], 20, stdin);

      if ((strlen(nomes[1]) > 0) && (nomes[1][strlen(nomes[1]) - 1] == '\n')) {
        nomes[1][strlen(nomes[1]) - 1] = '\0';
      }
      for(j = 0; nomes[1][j] != '\0'; j++){
        nomes[1][j] = toupper(nomes[1][j]);
      }
    }
  
  return 0;
}

void FImprimeData(void) {
  time_t agora = time(NULL);
  char dataHora[50]; 
    struct tm *infoTempo; 
    time(&agora);
  FILE *arq = fopen("ranking.txt", "a");
    if(arq == NULL){
      printf("Erro ao abrir o arquivo.\n");
      return;
    }
    // Converte para hora local
    infoTempo = localtime(&agora);

    // Imprime a data formatada
  strftime(dataHora, sizeof(dataHora), "\n| %d/%m/%Y | %H:%M:%S |\t", infoTempo);

  // Escreve a data formatada no arquivo
  fputs(dataHora, arq);
  fflush(arq);
}
