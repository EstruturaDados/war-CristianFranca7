//---Nível Intermediário---

//Bibliotecas Necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Estrutura dos Territórios
typedef struct{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//Função para limpar buffer
void LimparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
//Função para exibir os Territórios
void ExibirTerritorios(Territorio* mapa, int total){
    printf("\n=============ESTADO ATUAL DO MAPA===============\n");
    for(int i = 0; i < total; i++){
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
    printf("===================================================\n");
}

//Função de ataque
void atacar(Territorio* atacante, Territorio* defensor){
    printf("------------------ATAQUE---------------------\n");
    printf("%s(Exército %s) está atacando %s(Exército %s)!!\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);

//Rolagem de Dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante (%s): %d\n",atacante->nome, dadoAtacante);
    printf("Dado do defensor (%s): %d\n",defensor->nome, dadoDefensor);

//Resultado de batalha
    if (dadoAtacante > dadoDefensor){
        printf("\n%s venceu a batalha!\n", atacante->nome);

//troca de cor do território defensor
        strcpy(defensor->cor, atacante->cor);

//defensor recebe metade das tropas do atacante
        int tropasMov = atacante->tropas / 2;
        defensor->tropas = tropasMov;
        atacante->tropas -= tropasMov;

        printf("\nO território %s agora pertence ao exército %s!\n", defensor->nome, defensor->cor);
        printf("Quantidade de tropas posicionadas no território conquistado: %d\n", defensor->tropas);
    } else {
        printf("\nO defensor conseguiu resistir ao ataque!\n");

//atacante perde uma tropa
        if (atacante->tropas > 0){
            atacante->tropas--;

            printf("O exército atacante perdeu 1 tropa!\n");
        }
    }
    printf("---------------------------------------\n");
}

int main(){
    srand(time(NULL));

    int numTerritorios;

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &numTerritorios);
    LimparBufferEntrada();

    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));

    if (mapa == NULL){
        printf("Erro ao alocar memória!\n");
        return 1;
    }

//Cadastro dos Territórios

    for(int i = 0; i < numTerritorios; i++){
        printf("\n----Cadastro do Território %d---\n", i + 1);

        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Digite a cor do território: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Digite a quantidade de tropas do Território: ");
        scanf("%d", &mapa[i].tropas);
        LimparBufferEntrada();
    }

    int opcao;

    do {
        printf("\n============MENU=============\n");
        printf("1- Exibir Territórios\n");
        printf("2- Realizar Ataque\n");
        printf("0 - Sair.\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        LimparBufferEntrada();

        switch (opcao) {
            case 1:
                ExibirTerritorios(mapa, numTerritorios);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2:
                ExibirTerritorios(mapa, numTerritorios);

                int ata, def;

                printf("Digite o número do Território Atacante: ");
                scanf("%d", &ata);
                LimparBufferEntrada();

                printf("Digite o número do Território defensor: ");
                scanf("%d", &def);
                LimparBufferEntrada();

                ata--; //conversão dos números para índice
                def--;

            //Tratamento de erros
                if (ata < 0 || ata >= numTerritorios || def < 0 || def >= numTerritorios){
                    printf("Número de Território inválido!\n");
                    break;
                }

                if(strcmp(mapa[ata].cor, mapa[def].cor) == 0){
                    printf("Um território não pode atacar outro exército da mesma cor!\n");
                    break;
                }

                if(mapa[ata].tropas <= 0){
                    printf("O território atacantes não tem tropas!\n");
                    break;
                }

                if(ata == def){
                    printf("Um território não pode atacar ele mesmo!\n");
                    break;
                }

                atacar(&mapa[ata], &mapa[def]); //Função de ataque

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0: 
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção Inválida!\n");
                printf("\nPressione Enter para continuar...");
                getchar();
        }
    } while (opcao != 0);

    free(mapa);
    return 0;
}