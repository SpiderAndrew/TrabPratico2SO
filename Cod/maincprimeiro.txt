#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

double *vetor_A;
double *vetor_B;
double soma_paralela = 0.0;
pthread_mutex_t mutex_soma;

// Estrutura para passar os limites do vetor para cada thread
typedef struct {
    long inicio;
    long fim;
} ThreadArgs;

void* calcular_dano_parcial(void* arg) {
    ThreadArgs* limites = (ThreadArgs*) arg;
    double soma_local = 0.0;

    // Calcula o pedaço do vetor
    for (long i = limites->inicio; i < limites->fim; i++) {
        soma_local += vetor_A[i] * vetor_B[i];
    }

    // Adiciona ao total global com exclusão mútua
    pthread_mutex_lock(&mutex_soma);
    soma_paralela += soma_local;
    pthread_mutex_unlock(&mutex_soma);

    pthread_exit(NULL);
}

// Função auxiliar para calcular a diferença de tempo em segundos
double calcular_tempo(struct timespec inicio, struct timespec fim) {
    return (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
}

int main() {
    long N;
    int num_threads;
    struct timespec inicio, fim;
    double tempo_seq, tempo_par;

    // 1. Receber as entradas do usuário
    printf("--- Simulador de Dano (Produto Escalar) ---\n");
    printf("Digite o tamanho do vetor (ex: 10000000): ");
    if (scanf("%ld", &N) != 1) return 1;
    printf("Digite o numero de threads: ");
    if (scanf("%d", &num_threads) != 1) return 1;

    // 2. Alocação Dinâmica (evita estourar a memória stack)
    vetor_A = (double*) malloc(N * sizeof(double));
    vetor_B = (double*) malloc(N * sizeof(double));

    if (vetor_A == NULL || vetor_B == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    printf("\nGerando vetores com %ld elementos...\n", N);
    srand(time(NULL)); // Inicializa a semente aleatória
    for (long i = 0; i < N; i++) {
        vetor_A[i] = (double)(rand() % 100) / 10.0;
        vetor_B[i] = (double)(rand() % 100) / 10.0;
    }

    // 3. Execução Sequencial (Para comparação)
    printf("Calculando de forma sequencial...\n");
    double soma_sequencial = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (long i = 0; i < N; i++) {
        soma_sequencial += vetor_A[i] * vetor_B[i];
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    tempo_seq = calcular_tempo(inicio, fim);

    // 4. Execução Paralela
    printf("Calculando de forma paralela com %d threads...\n", num_threads);
    pthread_t* threads = (pthread_t*) malloc(num_threads * sizeof(pthread_t));
    ThreadArgs* args = (ThreadArgs*) malloc(num_threads * sizeof(ThreadArgs));
    
    pthread_mutex_init(&mutex_soma, NULL);
    
    long tamanho_bloco = N / num_threads;

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    
    for (int i = 0; i < num_threads; i++) {
        args[i].inicio = i * tamanho_bloco;
        // Garante que a última thread pegue o resto caso a divisão não seja exata
        args[i].fim = (i == num_threads - 1) ? N : (i + 1) * tamanho_bloco;
        
        pthread_create(&threads[i], NULL, calcular_dano_parcial, (void*)&args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &fim);
    tempo_par = calcular_tempo(inicio, fim);

    // 5. Exibir Resultados
    printf("\n--- Resultados ---\n");
    printf("Resultado Sequencial: %.2f (Tempo: %f segundos)\n", soma_sequencial, tempo_seq);
    printf("Resultado Paralelo:   %.2f (Tempo: %f segundos)\n", soma_paralela, tempo_par);
    printf("Speedup: %.2fx\n", tempo_seq / tempo_par);

    // Limpeza
    pthread_mutex_destroy(&mutex_soma);
    free(vetor_A);
    free(vetor_B);
    free(threads);
    free(args);

    return 0;
}