#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_LINE_SIZE 1000
#define MAX_FIELD_SIZE 100


float calcularPopulacaoMediaPorRegiao(char *arquivoEntrada, char *regiao) {
    int sum_next_value = 0;
    float sum = 0; 
    float numero_somas = 0;
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
            if (column_number == 5){
                if (strcmp(field, regiao) == 0) { 
                    sum_next_value = 1;
                }
            }
            if ((column_number == 6) && (sum_next_value == 1)) {
                sum = sum + atof(field); 
                numero_somas = numero_somas+1;
                sum_next_value = 0;
            }
            field = strtok(NULL, ";\n");
            column_number++;
        }
        row_number++;
    }

    fclose(file); // Close the file
    return sum/numero_somas;
}

int main() {
    char *regioes[] = {"Região Centro-Oeste","Região Sul","Região Sudeste","Região Nordeste","Região Norte"};
    int tamanho = sizeof(regioes) / sizeof(regioes[0]);

    FILE *arquivoSaida = fopen("populacao_regiao.txt", "w");
    if (arquivoSaida == NULL) {
        fprintf(stderr, "Erro ao criar arquivo de saída.\n");
        return 1;
    }

    int i = 0;
    while (i < tamanho) {
        printf("%s\n", regioes[i]);
        float populacaoMedia = calcularPopulacaoMediaPorRegiao("dados_municipios.csv", regioes[i]); 
        fprintf(arquivoSaida, "%s\t%.2f\n", regioes[i], populacaoMedia); 
        i++; 
    }
    fclose(arquivoSaida);

    return 0;
}
