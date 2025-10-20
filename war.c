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
#include <time.h> 

// --- Constantes Globais ---
#define NOME_MAX 30
#define COR_MAX 10
#define MAX_BUFFER 10 

// --- Estrutura de Dados C ---
struct Territorio {
    char nome[NOME_MAX];
    char cor[COR_MAX];
    int tropas;
};

typedef struct Territorio Territorio;

// --- Protótipos das Funções ---
void limparBufferEntrada();
Territorio* alocarMapa(int *max_territorios);
void liberarMemoria(Territorio* mapa);
void cadastrarTerritorio(Territorio* mapa, int max_territorios, int *total_territorios);
void exibirTerritorios(const Territorio* mapa, int total_territorios);
void atacar(Territorio* atacante, Territorio* defensor);
int rolarDado();
void iniciarAtaque(Territorio* mapa, int total_territorios);

// --- Implementação das Funções (Omissas por brevidade, permanecem as mesmas) ---

/**
 * @brief Limpa o buffer de entrada do teclado (stdin).
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Aloca dinamicamente memória para o vetor de territórios.
 * @param max_territorios Ponteiro para armazenar o tamanho alocado.
 * @return Ponteiro para o primeiro elemento do vetor de Territorio.
 */
Territorio* alocarMapa(int *max_territorios) {
    int tamanho;
    char temp_str[MAX_BUFFER];

    printf("=================================================\n");
    printf("Quantos territórios no máximo o mapa terá? ");
    
    // Leitura segura do número
    if (fgets(temp_str, MAX_BUFFER, stdin) != NULL) {
        if (sscanf(temp_str, "%d", &tamanho) == 1 && tamanho > 0) {
            *max_territorios = tamanho;
            // Aloca a memória usando calloc (inicializa com zero)
            Territorio* mapa = (Territorio*)calloc(*max_territorios, sizeof(Territorio));
            if (mapa == NULL) {
                perror("Erro na alocação de memória");
                exit(EXIT_FAILURE);
            }
            printf("Memória alocada com sucesso para %d territórios.\n", *max_territorios);
            return mapa;
        }
    }
    
    printf("Entrada inválida. Usando o padrão de 5 territórios.\n");
    *max_territorios = 5;
    Territorio* mapa = (Territorio*)calloc(*max_territorios, sizeof(Territorio));
    if (mapa == NULL) {
        perror("Erro na alocação de memória");
        exit(EXIT_FAILURE);
    }
    return mapa;
}

/**
 * @brief Libera a memória alocada dinamicamente.
 * @param mapa Ponteiro para a memória a ser liberada.
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória liberada com sucesso.\n");
    }
}

/**
 * @brief Cadastra um novo território no mapa.
 * @param mapa Ponteiro para o array de territórios.
 * @param max_territorios Tamanho máximo do array.
 * @param total_territorios Ponteiro para o contador de territórios cadastrados.
 */
void cadastrarTerritorio(Territorio* mapa, int max_territorios, int *total_territorios) {
    printf("\n--- Cadastro de Território ---\n");
    
    Territorio* novo_territorio = mapa + *total_territorios;

    if(*total_territorios < max_territorios) {
        
        char temp_str[MAX_BUFFER]; 

        // 1. Lendo a Cor
        printf("Digite a cor da tropa (Ex: Azul): ");
        fgets(novo_territorio->cor, COR_MAX, stdin);
        novo_territorio->cor[strcspn(novo_territorio->cor, "\n")] = 0; 

        // 2. Lendo o Nome
        printf("Digite o nome do teritório (Ex: Brasil): ");
        fgets(novo_territorio->nome, NOME_MAX, stdin);
        novo_territorio->nome[strcspn(novo_territorio->nome, "\n")] = 0; 

        // 3. Lendo a Quantidade de Tropas
        printf("Digite a quantidade de tropas (Mín. 1): ");
        
        if (fgets(temp_str, MAX_BUFFER, stdin) != NULL) {
            if (sscanf(temp_str, "%d", &novo_territorio->tropas) == 1 && novo_territorio->tropas >= 1) {
                (*total_territorios)++;
                printf("\n** Território '%s' registrado com sucesso! **\n", novo_territorio->nome);
            } else {
                printf("\n** ERRO: Quantidade de tropas inválida (Deve ser um número inteiro >= 1). **\n");
            }
        } else {
            printf("\n** ERRO na leitura da quantidade de tropas. **\n");
        }
        
    } else {
        printf("\n** Número de territórios máximo (%d) atingido! **\n", max_territorios);
    }
}

/**
 * @brief Exibe todos os territórios cadastrados.
 * @param mapa Ponteiro para o array de territórios.
 * @param total_territorios Número de territórios a exibir.
 */
void exibirTerritorios(const Territorio* mapa, int total_territorios) {
    printf("\n--- Lista de Territórios/Tropas ---\n");

    if(total_territorios == 0) {
        printf("Nenhum território/tropa foi cadastrado.\n");
    } else {
        for(int i = 0; i < total_territorios; i++) {
            printf("=================================================\n"); 
            printf("ID: %d\n", i);
            printf("Nome: %s\n", (mapa + i)->nome);
            printf("Cor: %s\n", (mapa + i)->cor);
            printf("Tropas: %d\n", (mapa + i)->tropas); 
        }
        printf("=================================================\n");
    }
}

/**
 * @brief Simula o ataque rolando um dado (1 a 6).
 * @return O resultado do dado.
 */
int rolarDado() {
    return (rand() % 6) + 1;
}

/**
 * @brief Simula a batalha entre dois territórios e atualiza seus estados.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_ataque = rolarDado();
    int dado_defesa = rolarDado();
    
    printf("\n--- Batalha: %s vs. %s ---\n", atacante->nome, defensor->nome);
    printf("Dado Ataque (%s): %d\n", atacante->nome, dado_ataque);
    printf("Dado Defesa (%s): %d\n", defensor->nome, dado_defesa);

    if (atacante->tropas < 1) {
        printf("Ataque cancelado: %s não tem tropas suficientes para atacar.\n", atacante->nome);
        return;
    }

    if (dado_ataque > dado_defesa) {
        // Vitoria do Atacante: Território Defensor é CONQUISTADO
        
        strcpy(defensor->cor, atacante->cor);
        
        int tropas_movidas = atacante->tropas / 2;
        
        atacante->tropas -= tropas_movidas;
        defensor->tropas = tropas_movidas; 

        printf("\n*** VITÓRIA! '%s' CONQUISTOU '%s'! ***\n", atacante->nome, defensor->nome);
        printf("%d tropas movidas para o território conquistado.\n", tropas_movidas);

    } else {
        // Derrota do Atacante: Perde 1 tropa 
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
        } else {
            // Não pode ter tropas negativas
            atacante->tropas = 1; 
        }
        
        printf("\n*** DERROTA! '%s' defendeu o ataque. ***\n", defensor->nome);
        printf("O atacante '%s' perdeu 1 tropa (mínimo mantido em 1). Tropas restantes: %d.\n", atacante->nome, atacante->tropas);
    }
}

/**
 * @brief Recebe o input do usuário e inicia a simulação de ataque.
 * @param mapa Ponteiro para o array de territórios.
 * @param total_territorios Número de territórios cadastrados.
 */
void iniciarAtaque(Territorio* mapa, int total_territorios) {
    if (total_territorios < 2) {
        printf("\nÉ necessário cadastrar no mínimo 2 territórios para iniciar um ataque.\n");
        return;
    }

    exibirTerritorios(mapa, total_territorios);

    int id_atacante, id_defensor;
    char temp_str[MAX_BUFFER];

    // 1. Escolha do Atacante
    printf("\nDigite o ID do território ATACANTE: ");
    if (fgets(temp_str, MAX_BUFFER, stdin) == NULL || sscanf(temp_str, "%d", &id_atacante) != 1 || id_atacante < 0 || id_atacante >= total_territorios) {
        printf("ID do atacante inválido.\n");
        return;
    }

    // 2. Escolha do Defensor
    printf("Digite o ID do território DEFENSOR: ");
    if (fgets(temp_str, MAX_BUFFER, stdin) == NULL || sscanf(temp_str, "%d", &id_defensor) != 1 || id_defensor < 0 || id_defensor >= total_territorios) {
        printf("ID do defensor inválido.\n");
        return;
    }

    // 3. Validações
    if (id_atacante == id_defensor) {
        printf("Um território não pode atacar a si mesmo!\n");
        return;
    }

    Territorio* atacante = mapa + id_atacante;
    Territorio* defensor = mapa + id_defensor;

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("ERRO: O território atacante e defensor são da mesma cor (%s). Não é possível atacar aliados.\n", atacante->cor);
        return;
    }

    if (atacante->tropas < 2) {
        printf("O território atacante precisa de no mínimo 2 tropas (1 para atacar + 1 de reserva)!\n");
        return;
    }

    // 4. Inicia o Ataque
    atacar(atacante, defensor);

    // 5. Exibição pós-ataque
    printf("\n--- Dados atualizados pós-ataque ---\n");
    printf("Território Atacante:\n Nome: %s, Cor: %s, Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Território Defensor:\n Nome: %s, Cor: %s, Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
}


// --- Função Principal (Main) ---

int main() {
    srand(time(NULL)); 
    
    Territorio* mapa = NULL;
    int max_territorios = 0;
    int total_territorios = 0;
    int opcao;

    mapa = alocarMapa(&max_territorios);

    do {
        printf("\n=================================================\n");
        printf("============== GAME WAR (SIMPLIFICADO) ==============\n");
        printf("0 - Para sair\n");
        printf("1 - Para cadastrar um Território/Tropa\n");
        printf("2 - Exibir Territórios/Tropas\n");
        // *** OPÇÃO FALTANTE ADICIONADA AQUI ***
        printf("3 - INICIAR ATAQUE ENTRE TERRITÓRIOS\n"); 
        printf("=================================================\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada(); 
            opcao = -1;
        }
        limparBufferEntrada(); 

        switch(opcao) {
            case 1:
                cadastrarTerritorio(mapa, max_territorios, &total_territorios);
                break;

            case 2: 
                exibirTerritorios(mapa, total_territorios);
                break;

            case 3: // Opção para iniciar o ataque
                iniciarAtaque(mapa, total_territorios);
                break;

            case 0:
                printf("SAINDO...\n");
                break;

            default:
                printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE.\n");
                break;
        } 
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar\n");
            getchar(); 
        }

    } while (opcao != 0);

    liberarMemoria(mapa);

    return 0;
}