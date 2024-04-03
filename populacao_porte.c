#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_LINE_SIZE 1000
#define MAX_FIELD_SIZE 100

float calcularPopulacaoTotalPorPorte(char *arquivoEntrada, char *porte) {
    float totalPopulacao = 0;
    float numero_somas = 0; 
    FILE *file = fopen(arquivoEntrada, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char line[MAX_LINE_SIZE];
    while (fgets(line, sizeof(line), file)) {
        char *field = strtok(line, ";\n");
        int column_number = 0;
        while (field != NULL) {
            if (column_number == 6) { 
                char populacao[MAX_FIELD_SIZE]; 
                strcpy(populacao, field);
                field = strtok(NULL, ";\n"); 
                if (field != NULL && strcmp(field, porte) == 0) { 
                    totalPopulacao += atof(populacao); 
                    numero_somas += 1;
                }
                break; 
            }
            field = strtok(NULL, ";\n");
            column_number++;
        }
    }

    fclose(file); 
    if (numero_somas == 0) return 0; // Evita divisão por zero
    return totalPopulacao / numero_somas;
}

int main() {
    char *portes[] = {"Pequeno I","Pequeno II","Médio","Grande","Metrópole"};
    int tamanho = sizeof(portes) / sizeof(portes[0]);

    FILE *arquivoSaida = fopen("populacao_porte.txt", "w");
    if (arquivoSaida == NULL) {
        fprintf(stderr, "Erro ao criar arquivo de saída.\n");
        return 1;
    }

    for (int i = 0; i < tamanho; i++) {
        float totalPopulacao = calcularPopulacaoTotalPorPorte("dados_municipios.csv", portes[i]);
        fprintf(arquivoSaida, "%s\t%.2f\n", portes[i], totalPopulacao); 
    }

    fclose(arquivoSaida); 

    return 0;
}
