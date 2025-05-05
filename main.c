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

    int responsible; //idicates if it's a team or not
    char team[24];
};
typedef struct tarefa tarefa;

FILE *tarefas;

void write_file(tarefa *task){
    tarefas = fopen("C:\\Users\\brash\\OneDrive\\Ambiente de Trabalho\\oihn\\tarefas.csv", "a");

    char buffer[16] = {0};

    //initiate new line
    fputs("\n", tarefas);

    //write task name
    fputs(task->name, tarefas);
    fputs(";", tarefas); //end section

    //write responsibles
    //if(task->responsibles != *1){  //in case of multiple responsibles
    //    char team = strcat("Equipa", task->team);
    //    
    //    fputs(team, tarefas);
    //}
    //for(int i = 0; i < resposibles_number; i++){
    //    fputs(task->responsibles[i], tarefas);
    //    fputs(", ", tarefas);
    //}
    fputs(";", tarefas);

    //write creation date
    sprintf(buffer, "%0.0f", task->creation_date);
    fputs(buffer, tarefas);
    fputs(";", tarefas);

    //write limit date
    sprintf(buffer, "%0.0f", task->lim_date);
    fputs(buffer, tarefas);
    fputs(";", tarefas);

    if(task->conclusion_date != 0){
        sprintf(buffer, "%0.0f", task->conclusion_date);
        fputs(buffer, tarefas);
    } else {
        fputs("on-going", tarefas);
    }
    fputs(";", tarefas);

    //write description
    fputs(task->description, tarefas);
    fputs(";", tarefas);
    fclose(tarefas);
}


int resposibles_number = 1;
char responsible[24] = "";
//Registar uma nova tarefa
void register_new_task(tarefa *task){
    //name

    printf("\nPlease give the task a name\n");
    //scanf("%s", task.name);
    strcpy(task->name, "test name");

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
        
        //strcpy(task->responsibles[i], responsible);
    }


    printf("\nplease inserts today's date in the format yyyymmdd\n");
    //scanf("%f", &task->creation_date);
    task->creation_date = 20250430;

    printf("\nplease insert the limit date in the format yyyymmdd\n");
    //scanf("%f", &task->lim_date);
    task->lim_date = 20250431;
    
    task->conclusion_date = 0;

    printf("\nPlease write a small description of the task\n");
    //scanf("%s", &task->description);
    strcpy(task->description, "descirption");
    
}

void change_data(tarefa *task){ //modify "data limite de execusao" "O responsavel" ou a "descicao"

    tarefas = fopen("C:\\Users\\brash\\OneDrive\\Ambiente de Trabalho\\oihn\\tarefas.csv", "a");

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

void change_person(tarefa *task){ //TODO: this
    printf("please");
}

void set_complete(tarefa *task){
    printf("please insert what date it is");
    scanf("%f", task->conclusion_date);

}

void eliminate_task(int delete_line){
    FILE *fileptr1, *fileptr2;
    char filename[40] = "tarefas.csv";
    char ch;
    int temp = 1;

    //open file in read mode
    fileptr1 = fopen("tarefas.csv", "r");
    ch = getc(fileptr1);
   while (ch != EOF){
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    //rewind
    rewind(fileptr1);
    //open new file in write mode
    fileptr2 = fopen("replica.c", "w");
    ch = 'A';
    while (ch != EOF){
        ch = getc(fileptr1);
        //except the line to be deleted
        if (temp != delete_line){
            //copy all lines in file replica.c
            putc(ch, fileptr2);
        }
        if (ch == '\n'){
            temp++;
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.c", filename);
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF){
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    fclose(fileptr1);
}

//PESSOAS E EQUIPAS
void criar_equipas(){
    FILE *file;

    file = fopen("output/teams.txt", "a");
    fputs("\n", file);
    fputs("Equipa", file);
    char ch;
    int numero_de_membros, lines;
    
    printf("Please indicate how many memebres there are on the team");
    scanf("%d", &numero_de_membros);

    while(!feof(file)){
      ch = fgetc(file);
      if(ch == '\n'){
        lines++;
      }
    }
    char buffer[40];
    sprintf(buffer, "%d", lines);
    fputs(buffer, file);

    for(int i = 0; i < numero_de_membros; i++){
        char name[16];
        printf("please insert the number of your member");
        scanf("%s", name);
        fputs(name, file);
    }
}
void alocar_equipa(){
    FILE *teams;

    teams = fopen("output/teams.txt", "r");
    char ch;
    int choise, lines; 
    bool flag = false;

    printf("\nQue equipa pertende alocar para a tarefa?\n");
    while (ch != EOF){
        printf("%c", ch);
        ch = getc(teams);
    }
    while(!feof(teams)){
        ch = fgetc(teams);
        if(ch == '\n'){
            lines++;
        }
    }
    scanf("%d", &choise);
    

    fclose(teams);
}


//LISTS
void list_execution(tarefa *task){
    FILE *file;
    
    file = fopen("tarefas.csv", "r");
    if(!file){
        printf("error: file not found");
        return;
    }

    char line[1024];
    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;

        if(strstr(line, "on-going")){
            char *cells[6];
            int i = 0;
        
            char *divisor = strtok(line, ";");
            while(divisor != NULL && i<6){
                cells[i++] = divisor;
                divisor = strtok(NULL, ";");
            }

            if(i == 6){
                printf("nome de tarefa: %s | inicio: %s\n", cells[0], cells[2]);
            } else {
                printf("no cells found error");
            }
        }
        //char *name = strtok(line, ";");
        //char *responsible = strtok(NULL, ";");
        //char *creation_date = strtok(NULL, ";");
        //char *lim_date = strtok(NULL, ";");
        //char *conclusion_date = strtok(NULL, ";");
        //char *description = strtok(NULL, ";");
//
        //if(strcmp(conclusion_date, "on-going") == 0){
        //    printf("tarefa: %s\n", name);
        //    printf("data de inicio: %s\n", creation_date);
        //}
    }
    fclose(file);
}

void list_concluded(tarefa *task){
    FILE *file;
    
    file = fopen("tarefas.csv", "r");
    if(!file){
        printf("error: file not found");
        return;
    }

    char line[1024];
    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;

        if(!strstr(line, "on-going")){
            char *cells[6];
            int i = 0;
        
            char *divisor = strtok(line, ";");
            while(divisor != NULL && i<6){
                cells[i++] = divisor;
                divisor = strtok(NULL, ";");
            }

            if(i == 6){
                printf("Tarefa: %s | Duracao: %s\n", cells[0], cells[4]);
            } else {
                printf("no cells found error");
            }
        }
    }
    fclose(file);
} 


int choice;
int main(){
    struct tarefa current_task;
    //while(1){
        printf("what action do you pretend to execute");
        printf("Tarefas\n\t1- Registar nova tarfa\n\t2-alterar dados de uma tarefa\n\t3-Definir pessoa\n\t4-concluir tarefa\n\t5-eliminar uma tarefa\nPessoas e equipas\n\t6-criar e guardar equipa\n\t7-alocar equipa\nListar \n\t8-Listar em execusao \n\t9-listar concluidas\n\t10-stop process");
        scanf("%d", &choice);

        switch(choice){
            case(1): //Register and create a new task
                register_new_task(&current_task);
                break;
            case(2): //Alterate task's data
                change_data(&current_task);
                break;
            case(3):
                change_person(&current_task);
                break;
            case(4):
                set_complete(&current_task);
                break;
            case(5):
                printf("\nwhat tarefa do you want to delete?\n");
                int line;
                scanf("%d", &line);

                eliminate_task(line);
                break;
            case(6):
                criar_equipas();
                break;
            case(7):
                alocar_equipa();
                break;
            case(8):
                list_execution(&current_task);
                break;
            case(9):
                list_concluded(&current_task);
                break;
            case(10):
                return 1;
                break;
        }

        //printf("%s \n", current_task.name);
        //for(int i = 0; i < resposibles_number; i++) {
        //    printf("Responsible #%d: %s\n", i + 1, current_task.responsibles[i]);
        //}
        //printf("%0.0f\n", current_task.creation_date);
        //printf("%0.0f\n", current_task.lim_date);
        //printf("%0.0f\n", current_task.conclusion_date);
        //printf("%s", current_task.description);
    //}
}