#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define DIM 10

struct tarefa{
    char name[24];
    char responsibles[24][24];
    float creation_date;
    float lim_date;
    float conclusion_date;
    char description[30];
};
typedef struct tarefa tarefa;


int resposibles_number = 1;
char responsible[24] = "";
//Registar uma nova tarefa
void register_new_task(tarefa *task){
    //name
    char responsibles[10][10];
    printf("\nPlease give the task a name\n");
    //scanf("%s", task.name);
    strcpy(task->name, "test name");

    printf("\nplease list how many resposibles there are\n"); //TODO: change this for file format for teams and stuff
    //scanf("%d", &resposibles_number);
    resposibles_number = 1;

    for(int i = 0; i < resposibles_number; i++){
        printf("\nplease write the name of the responsible number %d\n", i);
        //scanf("%s", responsible);
        strcpy(responsible, "some beutiful name");
        strcpy(task->responsibles[i], responsible);
    }

    printf("\nplease inserts today's date in the format yyyymmdd\n");
    //scanf("%f", &task->creation_date);
    task->creation_date = 20250430;

    printf("\nplease insert the limit date in the format yyyymmdd\n");
    task->lim_date = 20250431;

    printf("\nPlease write a small description of the task\n");
    //scanf("%s", &task->description);
    strcpy(task->description, "descirption");
}

void change_data(tarefa *task){ //modify "data limite de execusao" "O responsavel" ou a "descicao"
    bool loop = true;
    while(loop){
        int choice;
        printf("please select what you want to modify\n");
        printf("current state: \n");
        //current state
        printf("%0.0f\n", task->lim_date);
        for(int i = 0; i < resposibles_number; i++) {
            printf("Responsible #%d: %s\n", i + 1, task->responsibles[i]);
        }
        printf("%s \n", task->description);
        //--------------
        printf("1- limit date | 2- responsible | 3- description | 4- exit");
        scanf("%d", &choice);

        switch(choice){
            case(1):
                printf("\nplease insert new limit date\n");
                scanf("%f", &task->lim_date);
                break;
            case(2):
                printf("\nplease insert new responsible\n");
                for(int i = 0; i < resposibles_number; i++){
                    printf("\nplease write the name of the responsible number %d\n", i);
                    //scanf("%s", responsible);
                    strcpy(responsible, "some beutiful name");
                    strcpy(task->responsibles[i], responsible);
                }
                break;
            case(3):
                //scanf("%s", &task->description);
                strcpy(task->description, "descirption");
                break;
            case(4):
                loop = false;
                break;
        }
    }
}

int choice;
int main(){
    struct tarefa current_task;
    while(1){
        printf("what action do you pretend to execute");
        printf("Tarefas\n\t1- Registar nova tarfa\n\t2-alterar dados de uma tarefa\n\t3-Definir pessoa\n\t4-concluir tarefa\n\t5-eliminar uma tarefa");
        scanf("%d", &choice);

        switch(choice){
            case(1): //Register and create a new task
                register_new_task(&current_task);
                break;
            case(2): //Alterate task's data
                change_data(&current_task);
                break;
        }

        printf("%s \n", current_task.name);
        for(int i = 0; i < resposibles_number; i++) {
            printf("Responsible #%d: %s\n", i + 1, current_task.responsibles[i]);
        }
        printf("%0.0f\n", current_task.creation_date);
        printf("%0.0f\n", current_task.lim_date);
        printf("%0.0f\n", current_task.conclusion_date);
        printf("%s", current_task.description);
    }
}