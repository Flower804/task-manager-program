#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define DIM 10
//because C doesn't have THE SIMPLE FUNCTION OF A TRY CATCH we have to do it myself
#define try bool __HadError=false;
#define catch(x) ExitJmp:if(__HadError)
#define throw(x) {__HadError=true;goto ExitJmp;}


struct tarefa{
    char name[24];
    char responsibles[24][24];
    float creation_date;
    float lim_date;
    float conclusion_date;
    char description[30];
};
typedef struct tarefa tarefa;

FILE *tarefas;

int resposibles_number = 1;
char responsible[24] = "";
//Registar uma nova tarefa
void register_new_task(tarefa *task){
    tarefas = fopen("C:\\Users\\brash\\OneDrive\\Ambiente de Trabalho\\oihn\\tarefas.csv", "a");

    //Start new line in file
    fputs("\n", tarefas);

    //TODO: substitute strcpy to insert data into the file

    fseek(tarefas, 0,EOF);

    //name

    printf("\nPlease give the task a name\n");
    //scanf("%s", task.name);
    strcpy(task->name, "test name");
    fputs(task->name, tarefas);

    fputs(";", tarefas);

    printf("\nplease list how many resposibles there are\n"); //TODO: change this for file format for teams and stuff
    //scanf("%d", &resposibles_number);
    resposibles_number = 1;
    if(resposibles_number != 1){
        fputs("Equipa 1: ", tarefas);
    }
    for(int i = 0; i < resposibles_number; i++){
        printf("\nplease write the name of the responsible number %d\n", i);
        //scanf("%s", responsible);
        strcpy(responsible, "some beutiful name");
        fputs(responsible, tarefas);
        fputs(", ", tarefas);
        //strcpy(task->responsibles[i], responsible);
    }

    fputs(";", tarefas);

    printf("\nplease inserts today's date in the format yyyymmdd\n");
    //scanf("%f", &task->creation_date);
    task->creation_date = 20250430;
    char buffer[16] = {0};
    sprintf(buffer, "%f", task->creation_date);
    fputs(buffer, tarefas);

    fputs(";", tarefas);

    printf("\nplease insert the limit date in the format yyyymmdd\n");
    task->lim_date = 20250431;
    sprintf(buffer, "%f", task->lim_date);
    fputs(buffer, tarefas);

    fputs(";", tarefas);
    

    printf("\nPlease write a small description of the task\n");
    //scanf("%s", &task->description);
    strcpy(task->description, "descirption");
    fputs(task->description, tarefas);

    fputs(";", tarefas);
    fclose(tarefas);
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
        printf("Tarefas\n\t1- Registar nova tarfa\n\t2-alterar dados de uma tarefa\n\t3-Definir pessoa\n\t4-concluir tarefa\n\t5-eliminar uma tarefa\n\t 6-stop process");
        scanf("%d", &choice);

        switch(choice){
            case(1): //Register and create a new task
                register_new_task(&current_task);
                break;
            case(2): //Alterate task's data
                change_data(&current_task);
                break;
            case(6):
                return 1;
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