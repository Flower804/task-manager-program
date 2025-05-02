#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char buffer[1000];
    char *data;

    printf("run started\n");

    FILE *tarefas = fopen("C:\\Users\\brash\\OneDrive\\Ambiente de Trabalho\\oihn\\tarefas.csv", "r");


    if(tarefas == NULL){
        perror("something wrong happened");
        return -1;
    } 
    printf("file opened sucesfully\n");
    
    fgets(buffer, sizeof(buffer), tarefas);
    printf("%s \n", buffer);

    data = strtok(buffer,";");
    printf("first token is %s\n", data);
}