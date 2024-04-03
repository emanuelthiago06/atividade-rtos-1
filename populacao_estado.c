#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_LINE_SIZE 1000
#define MAX_FIELD_SIZE 100

float calcularPopulacaoMediaPorEstado(char *arquivoEntrada, char *estado) {
    int sum_next_value = 0;
    float numero_somas = 0;
    float sum = 0; 
    FILE *file = fopen(arquivoEntrada, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_SIZE];
    int row_number = 0;
    while (fgets(line, sizeof(line), file)) { 
        char *field = strtok(line, ";\n"); 
        int column_number = 0;
        while (field != NULL) {
            printf("Row %d, Column %d: %s\n", row_number, column_number, field);
            if (column_number == 3){
                if (strcmp(field, estado) == 0) {
                    sum_next_value = 1;
                }
            }
            if ((column_number == 6) && (sum_next_value == 1)) {
                sum = sum + atof(field); 
                sum_next_value = 0;
                numero_somas+=1;
            }
            field = strtok(NULL, ";\n");
            column_number++;
        }
        row_number++;
    }

    fclose(file); 
    return sum/numero_somas;
}

int main() {
    char *estados[] = {
        "AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", 
        "MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI", "RJ", "RN", 
        "RS", "RO", "RR", "SC", "SP", "SE", "TO"
    };
    int tamanho = sizeof(estados) / sizeof(estados[0]);

    FILE *arquivoSaida = fopen("populacao_estados.txt", "w");
    if (arquivoSaida == NULL) {
        fprintf(stderr, "Erro ao criar arquivo de saída.\n");
        return 1;
    }

    int i = 0;
    while (i < tamanho) {
        printf("%s\n", estados[i]);
        float populacaoMedia = calcularPopulacaoMediaPorEstado("dados_municipios.csv", estados[i]); 
        fprintf(arquivoSaida, "%s\t%.2f\n", estados[i], populacaoMedia); 
        i++; 
    }
    fclose(arquivoSaida);

    return 0;
}
