#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "raylib.h"

// --- VARIÁVEIS DO CÁLCULO PARALELO ---
double *vetor_A;
double *vetor_B;
double soma_paralela = 0.0;
pthread_mutex_t mutex_soma;

int threads_concluidas = 0;
bool calculo_iniciado = false;
bool calculo_finalizado = false;

typedef struct
{
    long inicio;
    long fim;
} ThreadArgs;

void *calcular_dano_parcial(void *arg)
{
    ThreadArgs *limites = (ThreadArgs *)arg;
    double soma_local = 0.0;

    for (long i = limites->inicio; i < limites->fim; i++)
    {
        soma_local += vetor_A[i] * vetor_B[i];
    }

    pthread_mutex_lock(&mutex_soma);
    soma_paralela += soma_local;
    threads_concluidas++;
    pthread_mutex_unlock(&mutex_soma);

    pthread_exit(NULL);
}

double calcular_tempo(struct timespec inicio, struct timespec fim)
{
    return (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
}

int main()
{
    long N;
    int num_threads;
    struct timespec inicio, fim;
    double tempo_seq, tempo_par;

    // --- 1. FASE DE TERMINAL ---
    printf("--- The Battle Threads ---\n");
    printf("Digite a Vida do Boss (ex: 10000000): ");
    if (scanf("%ld", &N) != 1)
        return 1;
    printf("Digite a quantidade de guerreiros (threads): ");
    if (scanf("%d", &num_threads) != 1)
        return 1;

    vetor_A = (double *)malloc(N * sizeof(double));
    vetor_B = (double *)malloc(N * sizeof(double));

    if (vetor_A == NULL || vetor_B == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    printf("\nGerando dados...\n");
    srand(time(NULL));
    for (long i = 0; i < N; i++)
    {
        vetor_A[i] = (double)(rand() % 100) / 10.0;
        vetor_B[i] = (double)(rand() % 100) / 10.0;
    }

    // Calcula o HP Máximo sequencialmente para ter a base de tempo
    double soma_sequencial = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (long i = 0; i < N; i++)
    {
        soma_sequencial += vetor_A[i] * vetor_B[i];
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    tempo_seq = calcular_tempo(inicio, fim);

    double boss_hp_max = soma_sequencial;

    // --- 2. FASE VISUAL (RAYLIB) ---
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "The Battle Threads");
    SetTargetFPS(60);

    // Carregando Assets (Certifique-se de que os nomes exatos estão na mesma pasta)
    Texture2D spr_fundo = LoadTexture("Background.png");
    Texture2D spr_boss = LoadTexture("boss.png");
    Texture2D spr_guerreiro = LoadTexture("guerreiro.png");

    // Configuração do Boss (1 Linha, 8 Colunas)
    int framesBoss = 8;
    float frameWidthBoss = (float)spr_boss.width / framesBoss;
    float frameHeightBoss = (float)spr_boss.height;
    Rectangle recBoss = {0.0f, 0.0f, frameWidthBoss, frameHeightBoss};
    int currentFrameBoss = 0;

    // Configuração do Guerreiro (5 Linhas, 8 Colunas)
    int colunasGuerreiro = 8;
    int linhasGuerreiro = 5;
    float frameWidthGuerreiro = (float)spr_guerreiro.width / colunasGuerreiro;
    float frameHeightGuerreiro = (float)spr_guerreiro.height / linhasGuerreiro;
    Rectangle recGuerreiro = {0.0f, 0.0f, frameWidthGuerreiro, frameHeightGuerreiro};
    int currentFrameGuerreiro = 0;

    int framesCounter = 0;
    int framesSpeed = 10; // Velocidade da animação

    pthread_t *threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    ThreadArgs *args = (ThreadArgs *)malloc(num_threads * sizeof(ThreadArgs));
    pthread_mutex_init(&mutex_soma, NULL);

    // --- LOOP PRINCIPAL DO JOGO ---
    while (!WindowShouldClose())
    {

        // --- ATUALIZAÇÃO DA ANIMAÇÃO ---
        framesCounter++;
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;

            // Animação do Boss (sempre 8 quadros)
            currentFrameBoss = (currentFrameBoss + 1) % framesBoss;
            recBoss.x = currentFrameBoss * frameWidthBoss;

            // Animação do Guerreiro (ambas Idle e Atk têm 6 quadros utilizáveis)
            currentFrameGuerreiro = (currentFrameGuerreiro + 1) % 6;
            recGuerreiro.x = currentFrameGuerreiro * frameWidthGuerreiro;

            if (calculo_iniciado && !calculo_finalizado)
            {
                // Atacando: Usa a 3ª linha (índice 2)
                recGuerreiro.y = 2 * frameHeightGuerreiro;
            }
            else
            {
                // Parado (Idle): Usa a 1ª linha (índice 0)
                recGuerreiro.y = 0 * frameHeightGuerreiro;
            }
        }

        // --- LÓGICA DE DISPARO DAS THREADS ---
        if (IsKeyPressed(KEY_SPACE) && !calculo_iniciado)
        {
            calculo_iniciado = true;
            long tamanho_bloco = N / num_threads;
            clock_gettime(CLOCK_MONOTONIC, &inicio);

            for (int i = 0; i < num_threads; i++)
            {
                args[i].inicio = i * tamanho_bloco;
                args[i].fim = (i == num_threads - 1) ? N : (i + 1) * tamanho_bloco;
                pthread_create(&threads[i], NULL, calcular_dano_parcial, (void *)&args[i]);
                pthread_detach(threads[i]);
            }
        }

        if (calculo_iniciado && !calculo_finalizado && threads_concluidas == num_threads)
        {
            clock_gettime(CLOCK_MONOTONIC, &fim);
            tempo_par = calcular_tempo(inicio, fim);
            calculo_finalizado = true;
        }

        // --- DESENHO DA TELA ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 1. Desenha o Fundo (Esticado para a tela)
        Rectangle sourceFundo = {0.0f, 0.0f, (float)spr_fundo.width, (float)spr_fundo.height};
        Rectangle destFundo = {0.0f, 0.0f, (float)screenWidth, (float)screenHeight};
        Vector2 origemFundo = {0.0f, 0.0f};
        DrawTexturePro(spr_fundo, sourceFundo, destFundo, origemFundo, 0.0f, WHITE);

        double boss_hp_atual = boss_hp_max - soma_paralela;
        if (boss_hp_atual < 0)
            boss_hp_atual = 0;

        // 2. Barra de Vida
        DrawRectangle(150, 30, 500, 25, DARKGRAY);
        float hp_percent = (float)(boss_hp_atual / boss_hp_max);
        DrawRectangle(150, 30, (int)(500 * hp_percent), 25, RED);
        DrawText(TextFormat("HP: %.0f / %.0f", boss_hp_atual, boss_hp_max), 320, 35, 15, WHITE);

        // 3. Desenhando o Boss (escala 3x)
        Rectangle destBoss = {550, 160, frameWidthBoss * 3, frameHeightBoss * 3};
        Vector2 origem = {0, 0};
        // Inverte a imagem do boss horizontalmente se necessário (largura negativa na fonte),
        // mas aqui vamos manter normal primeiro.
        DrawTexturePro(spr_boss, recBoss, destBoss, origem, 0.0f, WHITE);

        // 4. Desenhando os Guerreiros
        for (int i = 0; i < num_threads; i++)
        {
            // Distribui eles no lado esquerdo
            float posX = 50.0f + (i * (350.0f / num_threads));
            float posY = 200.0f + (i % 3) * 20.0f;

            // Desenha com escala 3x
            Rectangle destGuerreiro = {posX, posY, frameWidthGuerreiro * 3, frameHeightGuerreiro * 3};
            DrawTexturePro(spr_guerreiro, recGuerreiro, destGuerreiro, origem, 0.0f, WHITE);

            if (calculo_iniciado && !calculo_finalizado)
            {
                DrawText("ATK!", posX + 20, posY - 10, 15, ORANGE);
            }
        }

        // 5. Textos de Interface e Resultados
        if (!calculo_iniciado)
        {
            DrawText("Aperte ESPACO para o exercito atacar!", 180, 80, 20, LIGHTGRAY);
        }
        else if (calculo_finalizado)
        {
            DrawText("BOSS DERROTADO!", 300, 80, 22, GREEN);

            // Fundo escuro para os resultados ficarem legíveis em cima da floresta
            DrawRectangle(15, 345, 400, 90, Fade(BLACK, 0.7f));
            DrawText(TextFormat("Tempo 1 Guerreiro (Seq): %.4f seg", tempo_seq), 20, 350, 18, LIGHTGRAY);
            DrawText(TextFormat("Tempo %d Guerreiros (Par): %.4f seg", num_threads, tempo_par), 20, 380, 18, SKYBLUE);
            DrawText(TextFormat("Speedup (Bonus de Dano): %.2fx", tempo_seq / tempo_par), 20, 410, 20, ORANGE);
        }

        EndDrawing();
    }

    // --- 3. LIMPEZA DA MEMÓRIA ---
    UnloadTexture(spr_fundo);
    UnloadTexture(spr_boss);
    UnloadTexture(spr_guerreiro);
    pthread_mutex_destroy(&mutex_soma);
    free(vetor_A);
    free(vetor_B);
    free(threads);
    free(args);
    CloseWindow();

    return 0;
}