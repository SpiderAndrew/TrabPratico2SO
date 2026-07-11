# Trabalho Prático 2: Processamento Paralelo com Threads ⚔️

Este repositório contém o desenvolvimento, os benchmarks e os resultados do Segundo Trabalho Prático da disciplina de **Sistemas Operacionais**. O projeto explora o paradigma de computação paralela focado em alto desempenho através do desenvolvimento de uma aplicação temática de jogos denominada **Simulador de Dano (Produto Escalar) - "The Battle Threads"**.


## Informações Institucionais

* **Instituição:** Universidade Federal do Amazonas (UFAM)
* **Departamento:** Instituto de Computação (IComp)
* **Disciplina:** Sistemas Operacionais
* **Professor:** João Marcos Bastos Cavalcanti
* **Data de Entrega:** Julho de 2026


## Equipe de Desenvolvimento

Abaixo estão apresentados os membros acadêmicos responsáveis pela execução do projeto, organizados em ordem alfabética:

| Nome Completo | Matrícula |
| :--- | :---: |
| Andrew Donovan Coelho Santos | 22152016 |
| Francisco Felipe Barros dos Santos | 22152031 |
| Gabriel Henrique de Souza Nazaré | 22053696 |
| Gladston Gabriel Tavares Almeida | 22400546 |

# Relatório de Benchmarks e Desempenho ⚔️
**Projeto:** Simulador de Dano (Produto Escalar) - "The Battle Threads"  
**Responsável:** Dev 1 - Francisco  


## Ambiente de Testes (Hardware e SO)

Os testes de benchmark foram executados no seguinte ambiente computacional:

* **Sistema Operacional:** Microsoft Windows 11 Home Single Language (Versão 10.0.26200 Compilação 26200)
* **Fabricante do Sistema:** SAMSUNG ELECTRONICS CO., LTD.
* **Modelo do Sistema:** 750XGK (PC baseado em X64)
* **Processador:** 13th Gen Intel(R) Core(TM) i5-1335U @ 1300 Mhz
* **Núcleos / Threads:** 10 Núcleos físicos / 12 Processadores lógicos


## Resultados Obtidos

A tabela abaixo consolida os dados de tempo de execução e o ganho de performance (*speedup*) gerados ao comparar o processamento sequencial e o processamento paralelo com múltiplas threads:

| Tamanho do Vetor (N) | Quantidade de Threads | Tempo Sequencial (s) | Tempo Paralelo (s) | Speedup Obtido |
| :--- | :---: | :---: | :---: | :---: |
| 15.000.000 | 2 | 0.029615 | 0.017825 | **1.66x** |
| 20.000.000 | 10 | 0.041314 | 0.012114 | **3.41x** |
| 30.000.000 | 10 | 0.060147 | 0.017594 | **3.42x** |
| 40.000.000 | 10 | 0.094172 | 0.022612 | **4.16x** |
| 50.000.000 | 10 | 0.144255 | 0.028257 | **5.11x** |
| 60.000.000 | 10 | 0.115421 | 0.036540 | **3.16x** |
| 70.000.000 | 10 | 0.150610 | 0.043533 | **3.46x** |
| 80.000.000 | 10 | 0.254597 | 0.044708 | **5.69x** |
| 100.000.000 | 10 | 0.228655 | 0.055405 | **4.13x** |
| 1.000.000.000 | 10 | 67.229043 | 21.620400 | **3.11x** |


## Conclusões da Análise

A partir dos dados coletados sob a arquitetura do processador **Intel i5-1335U** (que dispõe de 10 núcleos físicos), as seguintes conclusões foram validadas:

### 1. Eficácia do Multithreading
Em todos os cenários testados, a abordagem paralela reduziu drasticamente o tempo de execução em relação ao modelo sequencial. A divisão equilibrada de blocos de dados entre os processadores lógicos provou-se altamente eficaz para acelerar o cálculo do produto escalar.

### 2. Comportamento do Speedup e Gargalo de Memória (*Memory Bound*)
Embora a execução tenha utilizado 10 threads na maioria dos testes, o aumento de velocidade não escalou linearmente em 10x (flutuando entre 3.11x e 5.69x). Isso ocorre por dois motivos comuns em computação de alto desempenho:
* **Largura de Banda da RAM:** O produto escalar exige pouca complexidade matemática da CPU, mas demanda leitura constante e massiva de dados. Em vetores gigantescos, o barramento de memória torna-se o gargalo primário, limitando o teto do *speedup*.
* **Escalonamento Dinâmico:** Pequenas oscilações nos tempos (como a variação observada entre os tamanhos de 50M e 60M) são decorrentes do gerenciamento de processos do próprio Sistema Operacional em segundo plano.

### 3. Escalabilidade em Arquivos Massivos
O impacto real do processamento paralelo fica evidente no teste extremo com **1 bilhão de elementos**. Enquanto a execução sequencial travou o fluxo por mais de 1 minuto (67,22 segundos), a execução paralela resolveu o problema em apenas 21,62 segundos. Isso comprova que a arquitetura multithread implementada se paga à medida que o volume de dados e o estresse do sistema aumentam.

### 4. Eficiência no Uso de Sincronismo
Os ótimos tempos obtidos confirmam a eficiência da lógica aplicada com os mecanismos de sincronização (`pthreads`). A estratégia de acumular somas locais temporárias e aplicar a trava do `mutex` apenas uma vez no encerramento de cada thread evitou o problema crítico de *overhead* por contenção de travas, garantindo fluidez e performance máxima ao hardware utilizado.

# Relatório de Benchmarks e Desempenho ⚔️
**Responsável:** Dev 2 - Andrew


# Ambiente de Testes (Hardware e SO)

Os testes de benchmark foram executados no seguinte ambiente computacional:

- **Sistema Operacional:** Microsoft Windows 11 (Ambiente executado via VS Code / PowerShell)
- **Processador:** AMD Ryzen 5 7535HS (Arquitetura Rembrandt - 6nm) com Radeon Graphics
- **Núcleos / Threads:** 6 Núcleos físicos / 12 Processadores lógicos (Tecnologia SMT Ativa)
- **TDP Máximo:** 45.0 W


# Resultados Obtidos

A tabela abaixo consolida os dados de tempo de execução e o ganho de desempenho (*speedup*) obtidos ao comparar o processamento sequencial e o processamento paralelo utilizando diferentes quantidades de *threads*, sob uma carga fixa de **1.000.000.000 (1 bilhão) de elementos**.

| Tamanho do Vetor (N) | Quantidade de Threads | Tempo Sequencial (s) | Tempo Paralelo (s) | Speedup Obtido |
| :------------------: | :-------------------: | :------------------: | :----------------: | :------------: |
| 1.000.000.000 | 1 | 93.768346 | 90.863439 | **1.03x** |
| 1.000.000.000 | 2 | 69.337095 | 53.973848 | **1.28x** |
| 1.000.000.000 | 3 | 62.061597 | 39.123334 | **1.59x** |
| 1.000.000.000 | 4 | 81.147965 | 41.602109 | **1.95x** |
| 1.000.000.000 | 5 | 66.272848 | 29.697844 | **2.23x** |
| 1.000.000.000 | 6 | 65.597486 | 29.526060 | **2.22x** |
| 1.000.000.000 | 8 | 81.017747 | 27.259575 | **2.97x** |
| 1.000.000.000 | 9 | 67.569243 | 26.163510 | **2.58x** |
| 1.000.000.000 | 10 | 67.880849 | 24.191588 | **2.81x** |
| 1.000.000.000 | 11 | 64.580439 | 25.237038 | **2.56x** |
| 1.000.000.000 | 12 | 66.311644 | 25.461271 | **2.60x** |


# Conclusões da Análise

A partir dos dados coletados sob a arquitetura do processador **AMD Ryzen 5 7535HS**, que dispõe de **6 núcleos físicos e 12 processadores lógicos (SMT)**, as seguintes conclusões foram obtidas.

## 1. Escalabilidade até o Limite dos Núcleos Físicos

O algoritmo paralelo apresentou ganho de desempenho consistente conforme o número de *threads* foi aumentado até atingir **5 e 6 threads**, reduzindo o tempo de processamento de aproximadamente **90,86 segundos** para cerca de **29 segundos**.

O ganho observado nessa faixa (aproximadamente **2,23x**) está diretamente relacionado aos **6 núcleos físicos** disponíveis no processador, permitindo que cada thread seja executada em um núcleo dedicado sem competição direta pelos recursos internos da CPU.


## 2. Efeito do SMT (Simultaneous Multithreading) e Limitações de Desempenho

Embora o processador ofereça **12 processadores lógicos** através da tecnologia **SMT**, o aumento do número de threads além da quantidade de núcleos físicos não resultou em crescimento linear do desempenho.

O melhor resultado foi obtido utilizando **8 threads**, alcançando um **speedup de 2,97x**.

Como o cálculo do produto escalar possui baixa intensidade computacional, porém elevada demanda de leitura de memória, duas threads lógicas compartilhando o mesmo núcleo físico passam a disputar os mesmos recursos internos da CPU, aumentando o overhead de gerenciamento e reduzindo a eficiência do paralelismo.

Esse comportamento explica a queda do speedup para **2,56x** com **11 threads**, estabilizando em aproximadamente **2,60x** com **12 threads**.


## 3. Gargalo de Barramento de Memória (*Memory Bound*)

O processamento de um vetor contendo **1 bilhão de elementos** evidencia um comportamento clássico de aplicações **Memory Bound**.

Apesar da elevada capacidade de processamento do processador, a velocidade de acesso à memória RAM torna-se o principal fator limitante da execução. Dessa forma, grande parte do tempo é consumida aguardando a chegada dos dados à CPU, provocando ciclos de espera (*memory stalls*).

Esse gargalo impede que o speedup se aproxime do valor teórico ideal de aproximadamente **6x**, correspondente ao número de núcleos físicos disponíveis.


## 4. Flutuação dos Tempos Sequenciais e Comportamento Térmico

Os tempos obtidos durante as execuções sequenciais oscilaram entre aproximadamente **62,06 segundos** e **93,76 segundos**.

Essa variação é esperada em ambientes computacionais de uso geral submetidos a cargas intensivas e pode ser explicada principalmente pelos seguintes fatores:

### • Gerenciamento Dinâmico de Frequência (*Thermal Throttling*)

O elevado esforço computacional gerado pelas operações envolvendo bilhões de elementos aumenta significativamente a temperatura do processador.

Como o Ryzen 5 7535HS possui **TDP máximo de 45 W**, o sistema reduz automaticamente a frequência de operação (Turbo Boost) para manter a temperatura dentro dos limites seguros de funcionamento.

### • Escalonamento do Sistema Operacional

Durante a execução dos testes, processos e serviços executados em segundo plano pelo Windows também competem pelos recursos do processador.

Essa disputa pelo tempo de CPU (*timeslice*) provoca pequenas variações entre diferentes execuções, influenciando principalmente os tempos do algoritmo sequencial.


# Considerações Finais

Os resultados demonstram que a implementação paralela utilizando **Pthreads** proporcionou ganhos significativos de desempenho quando comparada à versão sequencial.

Entretanto, também evidenciam limitações inerentes ao hardware, como a saturação dos núcleos físicos, os efeitos do SMT e o gargalo imposto pela largura de banda da memória RAM. Dessa forma, observa-se que o aumento indiscriminado do número de threads não garante ganhos proporcionais de desempenho, sendo fundamental considerar as características da arquitetura do processador e da aplicação desenvolvida.


# Relatório de Benchmarks e Desempenho ⚔️
**Responsável:** Dev 3 - Gabriel

## 1. Introdução e Contexto do Projeto
Este relatório apresenta a consolidação dos dados de desempenho e tempo de execução obtidos durante a bateria de testes do mecanismo de combate (Produto Escalar de Vetores), que simula o cálculo de uma batalha multidimensional contra o Boss final do jogo. O objetivo principal deste estudo é avaliar o comportamento, a eficiência e a escalabilidade do algoritmo sob uma abordagem sequencial clássica em comparação com a abordagem paralela utilizando a biblioteca POSIX Threads (pthreads).

Os testes foram conduzidos sob o papel e a responsabilidade do **Dev 3**, mapeando de forma rigorosa os impactos gerados pelo tamanho do vetor (carga de trabalho) e pela quantidade de threads concorrentes alocadas na execução.

## 2. Especificações do Ambiente de Teste
Para garantir a reprodutibilidade e a correta interpretação dos tempos observados, detalha-se a seguir a configuração de hardware utilizada para a execução de todos os testes:
* **Processador (CPU):** AMD Ryzen 5 7500F (Arquitetura Raphael, Litografia de 5 nm)
* **Configuração de Núcleos:** 6 Núcleos Físicos / 12 Threads Lógicas (Tecnologia de Multithreading Simultâneo)
* **Frequência de Operação (Clock):** ~4027.59 MHz (Frequência Base observada durante a execução)
* **Memória Cache:** Cache L1 de 6 x 32 KB, Cache L2 de 6 x 1 MB e Cache L3 de 32 MB compartilhados

---

## 3. Tabela Consolidada de Resultados

Abaixo está a tabela contendo todos os dados coletados a partir dos arquivos de saída gerados pelo simulador, cobrindo as volumetrias de 10 Milhões (10M), 100 Milhões (100M) e 1 Bilhão (1B) de elementos.

| Tamanho do Vetor | Quantidade de Threads | Tempo Sequencial (s) | Tempo Paralelo (s) | Speedup Alcançado |
| :--- | :---: | :---: | :---: | :---: |
| **10 Milhões (10M)** | 1 | 0.006952 | 0.007278 | 0.96x |
| | 2 | 0.006329 | 0.004249 | 1.49x |
| | 4 | 0.007042 | 0.003508 | 2.01x |
| | 6 | 0.006275 | 0.003973 | 1.58x |
| | 8 | 0.006354 | 0.003861 | 1.65x |
| | 10 | 0.006307 | 0.003678 | 1.71x |
| | 12 | 0.006891 | 0.003703 | 1.86x |
| **100 Milhões (100M)**| 1 | 0.068987 | 0.068950 | 1.00x |
| | 2 | 0.066745 | 0.036319 | 1.84x |
| | 4 | 0.066011 | 0.030386 | 2.17x |
| | 6 | 0.068159 | 0.030034 | 2.27x |
| | 8 | 0.077836 | 0.029900 | 2.60x |
| | 10 | 0.065303 | 0.029899 | 2.18x |
| | 12 | 0.066411 | 0.033678 | 1.97x |
| **1 Bilhão (1B)** | 1 | 1.346253 | 0.821492 | 1.64x |
| | 2 | 1.196036 | 0.352023 | 3.40x |
| | 4 | 0.967164 | 0.294469 | 3.28x |
| | 6 | 0.680484 | 0.289755 | 2.35x |
| | 8 | 0.676241 | 0.288274 | 2.35x |
| | 10 | 0.675221 | 0.289629 | 2.33x |
| | 12 | 0.671555 | 0.291089 | 2.31x |

---

## 4. Análise Crítica e Conclusões Técnicas

Com base no levantamento quantitativo de dados, derivam-se três comportamentos principais da computação paralela associada a este hardware específico:

### A. O Impacto do Overhead em Cargas Leves (10M)
Quando o vetor possui 10 milhões de elementos, o trabalho computacional puro de multiplicação e soma é extremamente rápido. Nestes cenários pequenos, o custo que o Sistema Operacional enfrenta para criar, gerenciar, escalonar e sincronizar as threads concorrentes (conhecido como *overhead*) sobressai-se ao ganho do paralelismo bruto. 
* Com **1 thread**, a versão paralela levou 0.007278 segundos, resultando em um retrocesso de eficiência (**Speedup de 0.96x**).
* O ponto ótimo nesta faixa ocorreu com **4 threads** (**Speedup de 2.01x**). Acima disso, os tempos flutuaram sem apresentar ganho linear devido à disputa das threads por frações irrelevantes de dados.

### B. Estabilização e Eficiência em Cargas Médias (100M)
Aumentando a volumetria em dez vezes, a divisão do trabalho começa a justificar o uso de concorrência. O tempo de execução da versão sequencial estabilizou em torno de 0.06s. 
* O pico absoluto de performance nesta carga foi atingido com **8 threads**, reduzindo o tempo para 0.029900 segundos e gerando um **Speedup de 2.60x**.
* Adicionar mais linhas de execução (10 e 12 threads) causou perda de eficiência, reduzindo o Speedup para 2.18x e 1.97x. Isso demonstra o limite de saturação onde a troca de contexto entre threads ultrapassa a capacidade de paralelização do laço.

### C. Ganho Exponencial e Saturação Física em Grandes Cargas (1B)
No cenário massivo de 1 bilhão de elementos, a versão sequencial demorou até **1.346253 segundos**. No contexto de desenvolvimento de jogos, uma interrupção linear desta magnitude congelaria o frame de renderização por mais de um segundo completo, quebrando a experiência do jogador (Stuttering severo).
* Ao aplicar **2 threads**, o tempo caiu drasticamente para **0.352023 segundos**, conquistando o maior pico de eficiência registrado em toda a análise: um **Speedup de 3.40x**.
* Com **4 threads**, a performance continuou excelente, sustentando um **Speedup de 3.28x** (0.294469 segundos).
* Ao utilizar **6 threads ou mais**, o tempo estabilizou fixamente na casa de **0.28 segundos**, com um Speedup constante de aproximadamente **2.35x**. Essa estabilização inflexível indica que o sistema atingiu o gargalo de largura de banda de memória (*Memory Bandwidth Bottleneck*) ou o limite físico dos 6 núcleos reais do processador AMD Ryzen 5, impedindo novos ganhos lineares mesmo com o Hyper-Threading ativado (12 threads lógicas).

## 5. Parecer Final do Desenvolvedor (Dev 3)
A implementação do paralelismo provou-se indispensável para viabilizar cargas intensas de dados sem comprometer a fluidez da aplicação. Para o hardware testado, a configuração ideal de execução situa-se entre **2 e 4 threads**, faixa na qual o balanço entre o poder dos núcleos físicos e o custo de sincronização atinge sua máxima eficiência operacional.

-----------------------------------------------------------------------------------------------------------------------------------------

# Análise Comparativa dos Resultados ⚔️

## Responsável: Dev 4 - Gladston

### Introdução

Após a obtenção dos resultados individuais de desempenho por cada integrante da equipe, esta seção apresenta uma análise comparativa dos experimentos realizados, com o objetivo de avaliar o comportamento da implementação paralela em diferentes configurações de hardware.

Os experimentos consistiram na comparação entre a versão sequencial e a versão paralela do algoritmo, utilizando diferentes quantidades de threads e diferentes tamanhos de vetores. Para cada execução foram registrados o tempo de processamento da implementação sequencial, o tempo da implementação paralela e o Speedup obtido, permitindo analisar a eficiência da paralelização e a influência das características de cada máquina sobre o desempenho alcançado.

Inicialmente são apresentados os resultados obtidos na máquina utilizada pelo responsável desta análise, considerando quatro diferentes tamanhos de entrada. Em seguida, é realizada uma comparação entre os resultados obtidos pelos demais integrantes, utilizando como referência o experimento executado com vetores de 1 bilhão de elementos.

## Dados Experimentais

A Tabela 1 apresenta os tempos de execução obtidos para cada tamanho de vetor analisado, bem como a quantidade de threads utilizada e o Speedup correspondente. Esses dados servem como base para a construção dos gráficos e para a discussão apresentada nas seções seguintes.

### Tabela 1 – Resultados obtidos durante os experimentos


| Tamanho do Vetor | Threads | Tempo Sequencial (s) | Tempo Paralelo (s) | Speedup |
|-----------------:|--------:|---------------------:|-------------------:|---------:|
|10.000.000|2|0,0232|0,0171|1,36|
|10.000.000|4|0,0240|0,0130|1,85|
|10.000.000|6|0,0225|0,0162|1,39|
|10.000.000|8|0,0261|0,0107|2,42|
|10.000.000|10|0,0251|0,0117|2,13|
|10.000.000|12|0,0247|0,0089|2,78|
|50.000.000|2|0,1141|0,0640|1,78|
|50.000.000|4|0,1124|0,0524|2,14|
|50.000.000|6|0,1054|0,0426|2,47|
|50.000.000|8|0,1122|0,0405|2,76|
|50.000.000|10|0,1075|0,0392|2,74|
|50.000.000|12|0,1059|0,0400|2,65|
|200.000.000|2|0,609|0,252|2,41|
|200.000.000|4|0,457|0,202|2,26|
|200.000.000|6|0,422|0,133|3,16|
|200.000.000|8|0,413|0,143|2,89|
|200.000.000|10|0,404|0,135|2,99|
|200.000.000|12|0,433|0,125|3,45|
|1.000.000.000|1|86,575|66,399|1,30|
|1.000.000.000|2|93,201|45,971|2,03|
|1.000.000.000|3|88,209|40,753|2,16|
|1.000.000.000|4|115,455|35,774|3,23|
|1.000.000.000|5|77,476|30,536|2,54|
|1.000.000.000|6|109,113|35,800|3,05|
|1.000.000.000|7|80,289|31,912|2,52|
|1.000.000.000|8|113,817|22,713|5,01|
|1.000.000.000|9|79,920|11,275|7,09|
|1.000.000.000|10|109,025|19,912|5,48|
|1.000.000.000|11|81,666|21,859|3,74|
|1.000.000.000|12|115,493|23,947|4,82|

## Análise dos Resultados

A partir dos dados apresentados na Tabela 1, foram construídos gráficos relacionando o Speedup com a quantidade de threads utilizada em cada experimento. Essa análise permite observar o comportamento da implementação paralela conforme o aumento da carga computacional e identificar como a eficiência da paralelização varia para diferentes tamanhos de entrada.

### Vetores de 10 Milhões de Elementos

<div align="center">

**Figura 1 – Speedup em função da quantidade de threads para vetores de 10 milhões de elementos.**

*(Inserir gráfico aqui)*

</div>

Observa-se que, para um vetor contendo 10 milhões de elementos, o aumento da quantidade de threads proporcionou ganhos moderados de desempenho. O maior Speedup obtido foi de **2,78**, utilizando **12 threads**.

Esse comportamento pode ser explicado pelo fato de que, para problemas relativamente pequenos, o tempo gasto na criação, distribuição e sincronização das threads representa uma parcela significativa do tempo total de execução. Dessa forma, embora o paralelismo reduza o tempo de processamento, parte desse ganho é compensada pelo overhead introduzido pelo gerenciamento das threads.

### Vetores de 50 Milhões de Elementos

<div align="center">

**Figura 2 – Speedup em função da quantidade de threads para vetores de 50 milhões de elementos.**

*(Inserir gráfico aqui)*

</div>

Com o aumento do tamanho do vetor para 50 milhões de elementos, observa-se uma melhoria no aproveitamento do paralelismo. O Speedup máximo registrado foi de **2,76**, obtido com **8 threads**, mantendo desempenho semelhante até 10 threads.

Comparando esse resultado com o experimento anterior, percebe-se que a maior carga computacional reduz proporcionalmente o impacto do overhead de criação das threads, permitindo que uma parcela maior do tempo de execução seja dedicada ao processamento efetivo dos dados.

### Vetores de 200 Milhões de Elementos

<div align="center">

**Figura 3 – Speedup em função da quantidade de threads para vetores de 200 milhões de elementos.**

*(Inserir gráfico aqui)*

</div>

Para vetores contendo 200 milhões de elementos, verifica-se uma evolução mais evidente da eficiência do algoritmo paralelo. O maior Speedup observado foi de **3,45**, utilizando **12 threads**, representando um ganho significativamente superior aos experimentos realizados com entradas menores.

Nesse cenário, a quantidade de trabalho distribuída entre as threads torna-se suficientemente grande para compensar os custos associados ao paralelismo, permitindo melhor aproveitamento dos recursos disponíveis no processador.

### Vetores de 1 Bilhão de Elementos

A Tabela 2 as especificações das maquinas usadas para fins de comparação futura após a apresentação dos resultados obtidos.

### Tabela 2 – Especificações das maquinas

| Máquina | Processador     | Núcleos | Threads | Melhor Speedup | Threads do Pico |
| ------- | --------------- | ------- | ------- | -------------: | --------------: |
| Dev 1   | Intel i5-1335U  | 10      | 12      |           3,11 |              10 |
| Dev 2   | Ryzen 5 7535HS  | 6       | 12      |           2,97 |               8 |
| Dev 3   | Ryzen 5 7500F   | 6       | 12      |           3,40 |               2 |
| Dev 4   | Intel i7-1255U  | 10      | 12      |           7,09 |               9 |




<div align="center">

**Figura 4 – Speedup em função da quantidade de threads para vetores de 1 bilhão de elementos.**

*(Inserir gráfico aqui)*

</div>

O experimento realizado com vetores de 1 bilhão de elementos apresentou os maiores ganhos de desempenho observados durante os testes. O Speedup máximo foi de **7,09**, alcançado com **9 threads**, demonstrando que aplicações com elevada carga computacional tendem a se beneficiar significativamente da execução paralela.

Entretanto, observa-se que o crescimento do Speedup não ocorreu de forma linear. Após atingir seu melhor desempenho, algumas configurações apresentaram redução no ganho obtido. Esse comportamento evidencia que o aumento da quantidade de threads nem sempre resulta em maior desempenho, devido ao overhead de sincronização, ao compartilhamento de recursos do processador e às limitações impostas pela arquitetura da máquina.

## Comparação entre as Máquinas

Após a análise dos experimentos realizados na máquina utilizada pelo responsável desta seção, realizou-se uma comparação entre os resultados obtidos pelos demais integrantes da equipe. Para garantir a equivalência dos testes, foram considerados exclusivamente os experimentos executados utilizando vetores de **1 bilhão de elementos**, uma vez que essa configuração foi a única presente em todas as máquinas avaliadas.

A Figura 5 apresenta a comparação do Speedup obtido em função da quantidade de threads para cada computador utilizado durante os experimentos.

<div align="center">

**Figura 5 – Comparação do Speedup obtido nas diferentes máquinas para vetores de 1 bilhão de elementos.**

*(Inserir gráfico comparativo aqui)*

</div>

Observa-se que todas as máquinas apresentaram ganhos de desempenho em relação à execução sequencial, entretanto, a evolução do Speedup variou significativamente entre elas.

A Máquina 4 apresentou o melhor desempenho geral, atingindo um Speedup máximo de **7,09**, resultado significativamente superior aos demais equipamentos analisados. Esse comportamento demonstra que sua arquitetura conseguiu aproveitar de forma mais eficiente o paralelismo oferecido pela aplicação.

A Máquina 2 apresentou crescimento gradual do Speedup, alcançando seu melhor resultado com **8 threads**, mantendo posteriormente pequenas oscilações. Esse comportamento indica uma utilização relativamente equilibrada dos recursos computacionais disponíveis.

Já a Máquina 3 apresentou um comportamento distinto das demais. Embora tenha obtido um Speedup elevado utilizando apenas duas threads, observou-se redução gradual do desempenho à medida que novas threads foram adicionadas. Esse resultado sugere que fatores como sincronização, gerenciamento das threads pelo sistema operacional ou limitações específicas do hardware influenciaram diretamente a eficiência da paralelização.

No caso da Máquina 1, os resultados disponíveis restringem-se ao experimento realizado com **10 threads**, impossibilitando uma análise da evolução do Speedup em função do aumento da quantidade de threads. Ainda assim, o resultado obtido contribui para a comparação geral entre os diferentes computadores utilizados.


## Conclusão

A análise comparativa realizada neste trabalho permitiu avaliar o comportamento da implementação paralela em diferentes cenários de execução e arquiteturas de hardware.

Os resultados demonstraram que o paralelismo proporcionou ganhos expressivos de desempenho, especialmente para problemas envolvendo grandes volumes de dados. À medida que o tamanho do vetor aumentou, observou-se crescimento do Speedup, evidenciando melhor aproveitamento dos recursos computacionais disponíveis.

Entretanto, também foi possível verificar que a utilização de um número maior de threads nem sempre resulta em maior desempenho. Após determinado ponto, fatores como sincronização, competição por recursos compartilhados e overhead de gerenciamento passam a limitar os ganhos obtidos, reduzindo a eficiência da paralelização.

A comparação entre as diferentes máquinas demonstrou que o desempenho de aplicações paralelas depende não apenas da implementação do algoritmo, mas também das características da plataforma de execução. Dessa forma, a definição da quantidade ideal de threads deve considerar tanto a natureza da aplicação quanto os recursos disponibilizados pelo hardware utilizado.

Conclui-se, portanto, que a programação paralela utilizando múltiplas threads representa uma ferramenta fundamental para aplicações de alto desempenho, desde que utilizada de forma adequada e considerando as limitações impostas pela arquitetura computacional.
