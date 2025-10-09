// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais  ---
// Redefinidas para o uso correto da estrutura
#define NOME_MAX 30
#define COR_MAX 10 
#define MAX_TERRITORIOS 5 // Número máximo de territórios (tropas) que você quer cadastrar

// --- Estrutura de Dados C ---
 
struct Territorio {
    char nome[NOME_MAX];
    char cor[COR_MAX];
    int quantidade_tropas; // Agora armazena o número inteiro de tropas
};

// Função utilitária para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main() {
    // Inicialização CORRETA da variável de contagem
    struct Territorio mapa[MAX_TERRITORIOS];
    int total_territorios = 0; // Inicialize a contagem!
    int opcao;

    do {
        printf("=================================================\n");
        printf("============== GAME WAR (SIMPLIFICADO) ==============\n");
        printf("0 - Para sair\n");
        printf("1 - Para cadastrar um Território/Tropa\n");
        printf("2 - Exibir Territórios/Tropas\n");
        printf("=================================================\n");
        printf("Escolha uma opção: ");
        
        // Use scanf para ler a opção e limpe o buffer logo em seguida
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada(); // Limpa o buffer se a entrada não for um número
            opcao = -1; // Força o 'default'
        }
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                printf("\n--- Cadastro de Território/Tropa ---\n");
                
                if(total_territorios < MAX_TERRITORIOS) {
                    
                    // 1. Lendo a Cor
                    printf("Digite a cor da tropa (Ex: Azul): ");
                    // fgets lê a string E a quebra de linha ('\n').
                    fgets(mapa[total_territorios].cor, COR_MAX, stdin);
                    // Opcional: Remover o '\n' lido pelo fgets
                    mapa[total_territorios].cor[strcspn(mapa[total_territorios].cor, "\n")] = 0;

                    // 2. Lendo o Nome
                    printf("Digite o nome do teritório (Ex: Brasil): ");
                    fgets(mapa[total_territorios].nome, NOME_MAX, stdin);
                    // Opcional: Remover o '\n' lido pelo fgets
                    mapa[total_territorios].nome[strcspn(mapa[total_territorios].nome, "\n")] = 0;

                    // 3. Lendo a Quantidade de Tropas (Inteiro)
                    // Para ler o inteiro de forma segura, vamos ler a string e converter
                    char temp_str[10]; // Buffer temporário para a leitura do número
                    printf("Digite a quantidade de tropas (Número): ");
                    
                    if (fgets(temp_str, 10, stdin) != NULL) {
                        // Converte a string lida (temp_str) para um inteiro
                        if (sscanf(temp_str, "%d", &mapa[total_territorios].quantidade_tropas) == 1) {
                            total_territorios++;
                            printf("\n** Território/Tropa registrado com sucesso! **\n");
                        } else {
                            printf("\n** ERRO: Quantidade de tropas inválida. Tente novamente. **\n");
                        }
                    } else {
                        printf("\n** ERRO na leitura da quantidade de tropas. **\n");
                    }
                    
                } else {
                    printf("\n** Número de territórios máximo (%d) atingido! **\n", MAX_TERRITORIOS);
                }
                break; // Adicionado 'break'

            case 2: 
                printf("\n--- Lista de Territórios/Tropas ---\n");

                if(total_territorios == 0) {
                    printf("Nenhum território/tropa foi cadastrado.\n");
                } else {
                    for(int i = 0; i < total_territorios; i++) {
                        printf("=================================================\n"); 
                        printf("Território %d\n", i + 1);
                        printf("Nome: %s\n", mapa[i].nome);
                        printf("Cor: %s\n", mapa[i].cor);
                        // %d para exibir o inteiro
                        printf("Tropas: %d\n", mapa[i].quantidade_tropas); 
                    }
                    printf("=================================================\n");
                }

                printf("\nPressione Enter para continuar\n");
                getchar();
                break;

            case 0:
                printf("SAINDO...\n");
                break;

            default:
                printf("OPÇÃO INVÁLIDA.\n");
                printf("TENTE NOVAMENTE.\n");
                // getchar() já foi chamado dentro do case 2. 
                // Para o default, vamos manter o getchar para a pausa
                printf("\nPressione Enter para continuar\n");
                getchar(); 
                break;
        } 
    } while (opcao != 0);

    return 0;
}