#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Criação dos processos filhos
    pid_t pid_regiao, pid_porte, pid_estado;
    pid_regiao = fork();

    if (pid_regiao < 0) {
        perror("Erro ao criar processo filho para populacao_regiao");
        exit(EXIT_FAILURE);
    } else if (pid_regiao == 0) { // Processo filho para populacao_regiao
        execl("./populacao_regiao", "populacao_regiao", NULL);
        perror("Erro ao executar populacao_regiao");
        exit(EXIT_FAILURE);
    } else { // Processo pai
        // Criação do processo filho para populacao_porte
        pid_porte = fork();

        if (pid_porte < 0) {
            perror("Erro ao criar processo filho para populacao_porte");
            exit(EXIT_FAILURE);
        } else if (pid_porte == 0) { // Processo filho para populacao_porte
            execl("./populacao_porte", "populacao_porte", NULL);
            perror("Erro ao executar populacao_porte");
            exit(EXIT_FAILURE);
        } else { // Processo pai
            // Criação do processo filho para populacao_estado
            pid_estado = fork();

            if (pid_estado < 0) {
                perror("Erro ao criar processo filho para populacao_estado");
                exit(EXIT_FAILURE);
            } else if (pid_estado == 0) { // Processo filho para populacao_estado
                execl("./populacao_estado", "populacao_estado", NULL);
                perror("Erro ao executar populacao_estado");
                exit(EXIT_FAILURE);
            } else { // Processo pai
                // Espera todos os processos filhos terminarem
                waitpid(pid_regiao, NULL, 0);
                waitpid(pid_porte, NULL, 0);
                waitpid(pid_estado, NULL, 0);

                // Leitura e escrita dos arquivos de saída
                FILE *arquivoRegiao = fopen("populacao_regiao.txt", "r");
                FILE *arquivoPorte = fopen("populacao_porte.txt", "r");
                FILE *arquivoEstado = fopen("populacao_estados.txt", "r");
                FILE *arquivoSaida = fopen("resultados.txt", "w");

                if (arquivoRegiao == NULL || arquivoPorte == NULL || arquivoEstado == NULL || arquivoSaida == NULL) {
                    perror("Erro ao abrir os arquivos de entrada/saída");
                    exit(EXIT_FAILURE);
                }

                int ch;
                // Escreve os resultados no arquivo de saída
                while ((ch = fgetc(arquivoRegiao)) != EOF) {
                    fputc(ch, arquivoSaida);
                }
                fprintf(arquivoSaida, "\n");

                while ((ch = fgetc(arquivoPorte)) != EOF) {
                    fputc(ch, arquivoSaida);
                }
                fprintf(arquivoSaida, "\n");

                while ((ch = fgetc(arquivoEstado)) != EOF) {
                    fputc(ch, arquivoSaida);
                }

                // Fecha os arquivos
                fclose(arquivoRegiao);
                fclose(arquivoPorte);
                fclose(arquivoEstado);
                fclose(arquivoSaida);

                printf("Resultados foram escritos em resultados.txt\n");
            }
        }
    }

    return 0;
}
