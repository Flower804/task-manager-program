#include<stdio.h>
#include<stdlib.h>
#define DIM 10

struct tarefa{
    char name[24];
    char autor[24][24];
    float creation_date;
    float lim_date;
    float conclusion_date;
    char description [1][30];
};
typedef struct tarefa tarefa;



int choice;
int main(){
    printf("what action do you pretend to execute");
    printf("Tarefas\n\t1- Registar nova tarfa\n\t2-alterar dados de uma tarefa\n\t3-Definir pessoa\n\t4-concluir tarefa\n\t5-eliminar uma tarefa");
    scanf("%d", &choice);
    
}