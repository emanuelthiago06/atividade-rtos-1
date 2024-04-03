#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 1000
#define MAX_FIELD_SIZE 100

int main() {
    FILE *file = fopen("dados_municipios.csv", "r"); 
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
            field = strtok(NULL, ";\n");
            column_number++;
        }
        row_number++;
    }

    fclose(file); // Close the file
    return 0;
}
