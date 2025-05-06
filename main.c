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


struct data{
    int ano, mes, dia;
};
typedef struct data data;

data le_data(){
    data d;
    printf("Insira a data no formato dd-mm-aaaa: ");
    scanf("%d-%d-%d", &d.dia, &d.mes, &d.ano);
    return d;

}

int data_dias(data d){
    int dias;
    dias= d.ano*365 + d.mes*30 + d.dia;  
    return dias;
}

FILE *tarefas;

//bubble sort stuff
void swap(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(arr, j, j + 1);
            }
        }
    }
}

//TODO:simplify this :ass: FLower
int separate_float(int original_number, int objective){ //meaning objectives 1 -> days 2-> months 3-> years
    int dia = (original_number/1000000);
    int mes = (original_number/10000) % 100;
    int ano = original_number % 10000;
    if(objective == 1){ 
        return dia;
    } else if(objective == 2){
        return mes;
    } else { //assume 3
        return ano;
    }
}

int float_to_days(int days, int months, int year){ //returnts tottal of days
    int total_days;
    total_days = year*365;
    total_days = total_days + months*31;
    total_days = total_days + days;

    return total_days;
}

void write_file(tarefa *task){
    tarefas = fopen("C:\\Users\\brash\\OneDrive\\Ambiente de Trabalho\\oihn\\tarefas.csv", "a");

    char buffer[16] = {0};

    //initiate new line
    fputs("\n", tarefas);

    //write task name
    fputs(task->name, tarefas);
    fputs(";", tarefas); //end section

    //TODO: idk if this is importante so I won't erase it just yet :ass: Flower

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
    data d;
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

    printf("\npor favor insira a data limite:\n");
    //scanf("%f", &task->lim_date);
    //task->lim_date = le_data();
    
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
                int first_duration, second_duration;
                float creation_date = strtof(cells[2], NULL);
                first_duration = float_to_days(separate_float(creation_date, 1), separate_float(creation_date, 2), separate_float(creation_date, 3));

                float end_date = strtof(cells[4], NULL);
                second_duration = float_to_days(separate_float(end_date, 1), separate_float(end_date, 2), separate_float(end_date, 3));

                printf("Tarefa: %s | Duracao: %d\n", cells[0], (second_duration - first_duration));
            } else {
                printf("no cells found error");
            }
        }
    }
    fclose(file);
}

void exceed_limit(tarefa *task){
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
            float todays_date;
            printf("por favor insira a data de hoje no formato ddmmaaaa");
            scanf("%f", &todays_date);

            if(i == 6){
                float creation_date = strtof(cells[2], NULL);
                int creation_duration = float_to_days(separate_float(creation_date, 1), separate_float(creation_date, 2), separate_float(creation_date, 3));

                float limit_date = strtof(cells[3], NULL);
                int limit_duration = float_to_days(separate_float(limit_date, 1), separate_float(limit_date, 2), separate_float(limit_date, 3));

                if(limit_duration > creation_duration){
                    int today_duration = float_to_days(separate_float(todays_date, 1), separate_float(todays_date, 2), separate_float(todays_date, 3));

                    printf("Tarefa: %s superado: %d", cells[0], today_duration - limit_duration);
                }
            } else {
                printf("no cells found error");
            }
        }
    }
}

void concluded_after(){
    FILE *file;

    file = fopen("tarefas.csv", "r");   
    if(!file){
        printf("erro: file not found");
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
                float end_date = strtof(cells[4], NULL);
                int concluded_duration = float_to_days(separate_float(end_date, 1), separate_float(end_date, 2), separate_float(end_date, 3));

                float limit_date = strtof(cells[3], NULL);
                int limit_duration = float_to_days(separate_float(limit_date, 1), separate_float(limit_date, 2), separate_float(limit_date, 3));

                if(limit_duration < concluded_duration){
                    printf("Tareda: %s | tempo excedido: %d \n", cells[0], concluded_duration - limit_duration);
                } else {
                    printf("no cells found error\n");
                }
            }
        }
    }
}

void search_task_by_team(){
    FILE *file, *teams;

    file = fopen("tarefas.csv", "r");
    teams = fopen("output/teams.txt", "r");

    int choice;
    if((file == NULL) || (teams == NULL)){
        printf("Sorry an error ocurred opening the files");
        return;
    }
    //print contents of the txt file
    char ch;
    while((ch = fgetc(teams)) != EOF){
        putchar(ch);
    }
    printf("\nPor favor escolha que equipa pertende ver as tarefas\n");
    scanf("%d", &choice);

    char line[256];
    char defined_team[50];
    int count = 0;
    rewind(teams);
    while(fgets(line, sizeof(line), teams) != NULL){
        if(count == (choice - 1)){
            strcpy(defined_team, line);
            defined_team[strcspn(defined_team, "\n")] = 0; //strip new line from the line
            break;
        } else {
            count++;
        }
    }
    printf("%s\n", defined_team);
    char second_search[1024];
    int matches = 0;
    while(fgets(second_search, sizeof(second_search), file)){
        second_search[strcspn(second_search, "\n")] = 0;

        if(strstr(second_search, defined_team)){
            char *cells[6];
            int i = 0;

            char *divisor = strtok(second_search, ";");
            while(divisor != NULL && i<6){
                cells[i++] = divisor;
                divisor = strtok(NULL, ";");
            }
            if(i == 6){
                printf("name: %s", cells[0]);
                matches++;
            } else {
                printf("no tasks found");
            }
        }
    }    
    if(matches == 0){
        printf("no matches found");
    }

    fclose(file);
    fclose(teams);
}

// problem 4 ordenation
void order_by_urgency(){
    FILE *file;

    file = fopen("tarefas.csv", "r");
    if(!file){
        printf("error: file not found");
        return;
    }

    int lines_in_file = 1;
    char ch;
    while(!feof(file)){
        ch = fgetc(file);
        if(ch == '\n'){
            lines_in_file++;
        }
    }

    printf("%d", lines_in_file);
    int j = 0;
    char tasks[lines_in_file][256];
    int durations[lines_in_file];

    rewind(file);

    char line[1024];
    float todays_date;
    printf("por favor insira a data de hoje no formato ddmmaaaa");
    scanf("%f", &todays_date);

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
                strcpy(tasks[j], cells[0]);
                int today_duration = float_to_days(separate_float(todays_date, 1), separate_float(todays_date, 2), separate_float(todays_date, 3));

                float limit_date = strtof(cells[3], NULL);
                int limit_duration = float_to_days(separate_float(limit_date, 1), separate_float(limit_date, 2), separate_float(limit_date, 3));

                int duration = limit_duration - today_duration;
                durations[i] = duration;
                //printf("%d ", duration);


            } else {
                printf("cell malformation");
            }
        }
        j++;
    }
    int copy_durations[lines_in_file];
    for(int i = 0; i < lines_in_file; i++){
        durations[i] = copy_durations[i];    
    }
    bubbleSort(durations, lines_in_file);

    int pointer;
    for(int i = 0; i < lines_in_file; i++){
        printf("%d | ", durations[i]);    
    }
    printf("\n");
    for(int i = 0; i < lines_in_file; i++){
        for(int j = 0; j < lines_in_file; j++){
            if(durations[i] == copy_durations[j]){
                copy_durations[j] = 0;
                printf("%s | ", tasks[j]);
            }
        }
    }

}

void average_duration(){
    FILE *file, *teams;

    file = fopen("tarefas.csv", "r");
    teams = fopen("output/teams.txt", "r");

    int choice;
    if((file == NULL) || (teams == NULL)){
        printf("Sorry an error ocurred opening the files");
        return;
    }

    char ch;
    while((ch = fgetc(teams)) != EOF){
        putchar(ch);
    }
    printf("\nPor favor escolha que equipa pertende verificar o media de tempo\n");
    scanf("%d", &choice);

    char line[256];
    char defined_team[50];
    int count = 0;
    rewind(teams);
    while(fgets(line, sizeof(line), teams) != NULL){
        if(count == (choice - 1)){
            strcpy(defined_team, line);
            defined_team[strcspn(defined_team, "\n")] = 0;
            break;
        } else {
            count++;
        }
    }

    char second_search[1024];
    int matches = 0;
    int duration = 0;
    while(fgets(second_search, sizeof(second_search), file) != NULL){
        second_search[strcspn(second_search, "\n")] = 0;

        if(strstr(second_search, defined_team) && !strstr(line, "on-going")){
            char *cells[6];
            int i = 0;

            char *divisor = strtok(second_search, ";");
            while(divisor != NULL && i<6){
                cells[i++] = divisor;
                divisor = strtok(NULL, ";");
            }

            if(i == 6){
                matches++;
                float creation_date = strtof(cells[2], NULL);
                int creation_duration = float_to_days(separate_float(creation_date, 1), separate_float(creation_date, 2), separate_float(creation_date, 3));

                float end_date = strtof(cells[4], NULL);
                int concluded_duration = float_to_days(separate_float(end_date, 1), separate_float(end_date, 2), separate_float(end_date, 3));

                duration = duration + (concluded_duration - creation_duration); 
            } else {
                printf("line malformed \n");
            }
        }
    } 
    if(matches != 0){
        float average_duration = duration/matches;
        printf("A equipa %s , tem uma media de duracao de tarefa de %0.2f", defined_team, average_duration);
    }
}

void number_of_tasks_online_vs_offline(){
    FILE *file, *teams;

    file = fopen("tarefas.csv", "r");
    teams = fopen("output/teams.txt", "r");

    int choice;
    if((file == NULL) || (teams == NULL)){
        printf("Sorry an error ocurred opening the files");
        return;
    }

    char ch;
    while((ch = fgetc(teams)) != EOF){
        putchar(ch);
    }
    printf("\nPor favor escolha que equipa pertende verificar o media de tempo\n");
    scanf("%d", &choice);

    char line[256];
    char defined_team[50];
    int count = 0;
    rewind(teams);
    while(fgets(line, sizeof(line), teams) != NULL){
        if(count == (choice - 1)){
            strcpy(defined_team, line);
            defined_team[strcspn(defined_team, "\n")] = 0;
            break;
        } else {
            count++;
        }
    }

    char second_search[1024];
    int matches_after = 0;
    int matches_before = 0;
    int duration = 0;
    while(fgets(second_search, sizeof(second_search), file) != NULL){
        second_search[strcspn(second_search, "\n")] = 0;

        if(strstr(second_search, defined_team) && !strstr(second_search, "on-going")){
            char *cells[6];
            int i = 0;

            char *divisor = strtok(second_search, ";");
            while(divisor != NULL && i<6){
                cells[i++] = divisor;
                divisor = strtok(NULL, ";");
            }
            if(i == 6){
                float end_date = strtof(cells[4], NULL);
                int concluded_duration = float_to_days(separate_float(end_date, 1), separate_float(end_date, 2), separate_float(end_date, 3));

                float limit_date = strtof(cells[3], NULL);
                int limit_duration = float_to_days(separate_float(limit_date, 1), separate_float(limit_date, 2), separate_float(limit_date, 3));

                if(limit_duration < concluded_duration){
                    matches_after++;
                } else if(limit_duration > concluded_duration){
                    matches_before++;
                }
            }
        } 
    }
    if((matches_after != 0) || (matches_before != 0)){
        printf("A equipa %s , tem %d tarefas concluidas apos o limite e %d tarefas concluidas antes do limite", defined_team, matches_after, matches_before);
    }
}

void tasks_on_exec(){
    FILE *file, *teams;

    file = fopen("tarefas.csv", "r");
    teams = fopen("output/teams.txt", "r");

    int choice;
    if((file == NULL) || (teams == NULL)){
        printf("Sorry an error ocurred opening the files");
        return;
    }

    char ch;
    while((ch = fgetc(teams)) != EOF){
        putchar(ch);
    }
    printf("\nPor favor escolha que equipa pertende verificar o media de tempo\n");
    scanf("%d", &choice);

    char line[256];
    char defined_team[50];
    int count = 0;
    rewind(teams);
    while(fgets(line, sizeof(line), teams) != NULL){
        if(count == (choice - 1)){
            strcpy(defined_team, line);
            defined_team[strcspn(defined_team, "\n")] = 0;
            break;
        } else {
            count++;
        }
    }

    float todays_date;
    printf("Por favor insira a data de hoje no formate ddmmaaaa");
    scanf("%f", &todays_date);

    char second_search[1024];
    int matches = 0;
    int duration[124];
    while(fgets(second_search, sizeof(second_search), file) != NULL){
        second_search[strcspn(second_search, "\n")] = 0;

        if(strstr(second_search, defined_team) && strstr(second_search, "on-going")){
            char *cells[6];
            int i = 0;

            char *divisor = strtok(second_search, ";");
            while(divisor != NULL && i<6){
                cells[i++] = divisor;
                divisor = strtok(NULL, ";");
            }
            if(i == 6){
                float creation_date = strtof(cells[2], NULL);
                int creation_duration = float_to_days(separate_float(creation_date, 1), separate_float(creation_date, 2), separate_float(creation_date, 3));
            
                int today_duration = float_to_days(separate_float(todays_date, 1), separate_float(todays_date, 2), separate_float(todays_date, 3));
                
                duration[matches] = today_duration - creation_duration;
                matches++;
            }
        } 
    }
    if(matches != 0){
        printf("A equipa %s , tem %d tarefas em execusao, tendo elas a duracao atual de", defined_team, matches);
        for(int i = 0; i < matches; i++){
            printf("%d ", duration[i]);
        }
        printf("respectivamente");
    } else {
        printf("no matches found");
    }
}

int choice;
int main(){
    struct tarefa current_task;
    //while(1){
        printf("what action do you pretend to execute");
        printf("Tarefas\n\t1- Registar nova tarfa\n\t2-alterar dados de uma tarefa\n\t3-Definir pessoa\n\t4-concluir tarefa\n\t5-eliminar uma tarefa\nPessoas e equipas\n\t6-criar e guardar equipa\n\t7-alocar equipa\nListar \n\t8-Listar em execusao \n\t9-listar concluidas\n\t10-listar ultrapasadas\n\t11-list tasks that were completed after deadline\n\t12- search tasks by team\n\t\n13-ordenar tarefas por urgencia\ndeterminar por equipas\n\t14-a duracao media de tarefas\n\t15-numero de tarefas concluidas\n\t16-numero de tarefas em execusao\n\t17-stop process");
        scanf("%d", &choice);

        //TODO: remove this, only here for debug purposses
        //separate_float(16092006);

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
                exceed_limit(&current_task);
                break;
            case(11):
                concluded_after();
                break;
            case(12):
                search_task_by_team();
                break;
            case(13):
                order_by_urgency();
                break;
            case(14):
                average_duration();
                break;
            case(15):
                number_of_tasks_online_vs_offline();
                break;
            case(16):
                tasks_on_exec();
                break;
            case(17):
                return 1;
                break;
        }
}