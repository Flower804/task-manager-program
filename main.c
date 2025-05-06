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
    tarefas = fopen("tarefas.csv", "a");

    char buffer[16] = {0};

    //initiate new line
    fputs("\n", tarefas);

    //write task name
    fputs(task->name, tarefas);
    fputs(";", tarefas); //end section

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
    scanf("%s", task->name);
    //strcpy(task->name, "test name");

    printf("\nplease list how many resposibles there are\n"); //TODO: change this for file format for teams and stuff
    scanf("%d", &resposibles_number);
    //resposibles_number = 1;
    if(resposibles_number != 1){
        fputs("Equipa 1: ", tarefas);
    }
    for(int i = 0; i < resposibles_number; i++){
        printf("\nplease write the name of the responsible number %d\n", i);
        scanf("%s", responsible);
        //strcpy(responsible, "some beutiful name");
        
        strcpy(task->responsibles[i], responsible);
    }

    printf("\npor favor insira a data limite:\n");
    scanf("%f", &task->lim_date);
    
    task->conclusion_date = 0;

    printf("\nPlease write a small description of the task\n");
    scanf("%s", &task->description);
    //strcpy(task->description, "descirption");
    write_file(task);
}

void eliminate_task(int delete_line) {
    FILE *fileptr1, *fileptr2;
    char filename[] = "tarefas.csv";
    char temp_filename[] = "replica.c";
    char line[1024];
    int current_line = 1;

    fileptr1 = fopen(filename, "r");
    if (!fileptr1) {
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    fileptr2 = fopen(temp_filename, "w");
    if (!fileptr2) {
        fclose(fileptr1);
        printf("Erro ao criar o arquivo temporário.\n");
        return;
    }

    while (fgets(line, sizeof(line), fileptr1)) {
        if (current_line != delete_line) {
            fputs(line, fileptr2);
        }
        current_line++;
    }

    fclose(fileptr1);
    fclose(fileptr2);

    remove(filename);
    rename(temp_filename, filename);

    // Print updated file
    fileptr1 = fopen(filename, "r");
    if (fileptr1) {
        printf("\nArquivo atualizado:\n");
        while (fgets(line, sizeof(line), fileptr1)) {
            printf("%s", line);
        }
        fclose(fileptr1);
    }
}

void change_data() {
    FILE *file = fopen("tarefas.csv", "r");
    if (!file) {
        printf("Erro: não foi possível abrir o ficheiro.\n");
        return;
    }

    char *lines[9];
    int line_count = 0;

    
    char buffer[1025];
    while (fgets(buffer, sizeof(buffer), file) && line_count < 9) {
        lines[line_count] = strdup(buffer);  
        printf("%d: %s", line_count, buffer);
        line_count++;
    }
    fclose(file);

    int line_to_edit;
    printf("\nQual linha deseja alterar? ");
    scanf("%d", &line_to_edit);
    getchar();  

    if (line_to_edit <= 0 || line_to_edit >= line_count) {
        printf("Linha inválida.\n");
        return;
    }

    char *line_copy = strdup(lines[line_to_edit]);
    char *cells[6];
    int i = 0;
    char *token = strtok(line_copy, ";");
    while (token && i < 6) {
        cells[i++] = token;
        token = strtok(NULL, ";");
    }

    if (i != 6) {
        printf("Erro ao analisar a linha.\n");
        free(line_copy);
        return;
    }

    printf("\nAtual:\nResponsável: %s\nData limite: %s\nDescrição: %s\n",cells[1], cells[3], cells[5]);

   
    int choice;
    printf("\nO que deseja alterar?\n1 - Responsável\n2 - Data limite\n3 - Descrição\nEscolha: ");
    scanf("%d", &choice);
    getchar();  

    char new_value[256];
    printf("Novo valor: ");
    fgets(new_value, sizeof(new_value), stdin);
    new_value[strcspn(new_value, "\n")] = 0;  

    switch (choice) {
        case 1:
            cells[1] = new_value;
            break;
        case 2:
            cells[3] = new_value;
            break;
        case 3:
            cells[5] = new_value;
            break;
        default:
            printf("Escolha inválida.\n");
            free(line_copy);
            return;
    }

    char updated_line[1025];
    snprintf(updated_line, sizeof(updated_line), "%s;%s;%s;%s;%s;%s\n",cells[0], cells[1], cells[2], cells[3], cells[4], cells[5]);

    lines[line_to_edit] = strdup(updated_line);

    file = fopen("tarefas.csv", "w");
    if (!file) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    for (int j = 0; j < line_count; j++) {
        fputs(lines[j], file);
    }
    fclose(file);
}

void change_person(tarefa *task){ //TODO: this
    FILE *file = fopen("tarefas.csv", "r");
    if (!file) {
        printf("Erro: não foi possível abrir o ficheiro.\n");
        return;
    }

    char *lines[9];
    int line_count = 0;

    
    char buffer[1025];
    while (fgets(buffer, sizeof(buffer), file) && line_count < 9) {
        lines[line_count] = strdup(buffer);  
        printf("%d: %s", line_count, buffer);
        line_count++;
    }
    fclose(file);

    int line_to_edit;
    printf("\nQual linha deseja alterar? ");
    scanf("%d", &line_to_edit);
    getchar();  

    if (line_to_edit <= 0 || line_to_edit >= line_count) {
        printf("Linha inválida.\n");
        return;
    }

    char *line_copy = strdup(lines[line_to_edit]);
    char *cells[6];
    int i = 0;
    char *token = strtok(line_copy, ";");
    while (token && i < 6) {
        cells[i++] = token;
        token = strtok(NULL, ";");
    }

    if (i != 6) {
        printf("Erro ao analisar a linha.\n");
        free(line_copy);
        return;
    }

    printf("\nqual o nome do novo responsavel?\n");
    char new_value[256];
    printf("Novo valor: ");
    fgets(new_value, sizeof(new_value), stdin);
    new_value[strcspn(new_value, "\n")] = 0;  

    cells[1] = new_value;

    char updated_line[1025];
    snprintf(updated_line, sizeof(updated_line), "%s;%s;%s;%s;%s;%s\n",cells[0], cells[1], cells[2], cells[3], cells[4], cells[5]);

    lines[line_to_edit] = strdup(updated_line);

    file = fopen("tarefas.csv", "w");
    if (!file) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    for (int j = 0; j < line_count; j++) {
        fputs(lines[j], file);
    }
    fclose(file);
}

void set_complete(tarefa *task){
    FILE *file = fopen("tarefas.csv", "r");
    if (!file) {
        printf("Erro: não foi possível abrir o ficheiro.\n");
        return;
    }

    char *lines[9];
    int line_count = 0;

    
    char buffer[1025];
    while (fgets(buffer, sizeof(buffer), file) && line_count < 9) {
        lines[line_count] = strdup(buffer);  
        printf("%d: %s", line_count, buffer);
        line_count++;
    }
    fclose(file);

    int line_to_edit;
    printf("\nQual linha deseja alterar? ");
    scanf("%d", &line_to_edit);
    getchar();  

    if (line_to_edit <= 0 || line_to_edit >= line_count) {
        printf("Linha inválida.\n");
        return;
    }

    char *line_copy = strdup(lines[line_to_edit]);
    char *cells[6];
    int i = 0;
    char *token = strtok(line_copy, ";");
    while (token && i < 6) {
        cells[i++] = token;
        token = strtok(NULL, ";");
    }

    if (i != 6) {
        printf("Erro ao analisar a linha.\n");
        free(line_copy);
        return;
    }

    printf("\nqual a data atual?\n");
    char new_value[256];
    printf("Data: ");
    fgets(new_value, sizeof(new_value), stdin);
    new_value[strcspn(new_value, "\n")] = 0;  

    cells[4] = new_value;

    char updated_line[1025];
    snprintf(updated_line, sizeof(updated_line), "%s;%s;%s;%s;%s;%s\n",cells[0], cells[1], cells[2], cells[3], cells[4], cells[5]);

    lines[line_to_edit] = strdup(updated_line);

    file = fopen("tarefas.csv", "w");
    if (!file) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    for (int j = 0; j < line_count; j++) {
        fputs(lines[j], file);
    }
    fclose(file);
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
    int choise;
    bool flag = false;

    printf("\nQue equipa pertende alocar para a tarefa?\n");
    while (ch != EOF){
        printf("%c", ch);
        ch = getc(teams);
    }
    rewind(teams);

    scanf("%d", &choise);
    getchar(); //clear newline
    
    int count = 1;
    char buffer[250];
    while(fgets (buffer, sizeof(buffer), teams)){
        if(count == choise){
            flag = true;
            break;
        }
        count++;
    }

    if(flag){
        printf("choosen team is %s", buffer);
    }
    fclose(teams);

    FILE *file = fopen("tarefas.csv", "r");

    char *lines[9];
    int line_count = 0;

    char read_buffer[1025];
    while (fgets(read_buffer, sizeof(read_buffer), file) && line_count < 9) {
        lines[line_count] = strdup(read_buffer);  
        printf("%d: %s", line_count, read_buffer);
        line_count++;
    }
    fclose(file);

    int line_to_edit;
    printf("\nPara qual tarefa perdente alocar a equipa ");
    scanf("%d", &line_to_edit);
    getchar();

    char *line_copy = strdup(lines[line_to_edit]);
    char *cells[6];
    int i = 0;
    char *token = strtok(line_copy, ";");
    while (token && i < 6) {
        cells[i++] = token;
        token = strtok(NULL, ";");
    }

    buffer[strcspn(buffer, "\n")] = 0;

    cells[1] = strdup(buffer);

    char updated_line[1025];
    snprintf(updated_line, sizeof(updated_line), "%s;%s;%s;%s;%s;%s\n",cells[0], cells[1], cells[2], cells[3], cells[4], cells[5]);

    lines[line_to_edit] = strdup(updated_line);

    file = fopen("tarefas.csv", "w");
    if (!file) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    for (int j = 0; j < line_count; j++) {
        fputs(lines[j], file);
    }
    fclose(file);
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

    int lines_in_file = -1;
    char ch;
    while(!feof(file)){
        ch = fgetc(file);
        if(ch == '\n'){
            lines_in_file++;
        }
    }

    printf("%d", lines_in_file);
    int j = 1;
    char tasks[lines_in_file][256];
    int durations[lines_in_file];

    rewind(file);

    char line[1024];
    float todays_date;
    printf("por favor insira a data de hoje no formato ddmmaaaa");
    scanf("%f", &todays_date);

    //skip first line of the file
    fgets(line, sizeof(line), file);

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
    for(int i = 0; i < (lines_in_file-1); i++){
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

void delete_by_year(int year) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", year);

    FILE *file = fopen("tarefas.csv", "r");
    if (!file) {
        printf("Erro: ficheiro não encontrado.\n");
        return;
    }

    int line_number = 0;
    int lines_to_delete[1024];  // stores line numbers to delete
    int delete_count = 0;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        line_number++;

        if (strstr(line, buffer)) {
            char line_copy[1024];
            strcpy(line_copy, line);

            char *cells[6];
            int i = 0;

            char *divisor = strtok(line_copy, ";");
            while (divisor != NULL && i < 6) {
                cells[i++] = divisor;
                divisor = strtok(NULL, ";");
            }

            if (i == 6 && strstr(cells[2], buffer)) {
                lines_to_delete[delete_count++] = line_number;
            }
        }
    }
    fclose(file);

    // Delete lines in reverse order to avoid index shifting
    for (int i = delete_count - 1; i >= 0; i--) {
        eliminate_task(lines_to_delete[i]);
    }
}


int create_year_csv(){
    int year;
    printf("De qual ano pertende criar o ficheiro?");
    scanf("%d", &year);

    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", year);

    FILE *file, *new_file;
    int line_number = 0;
    file = fopen("tarefas.csv", "r");
    
    char mid_file_name[15] = "";
    strcat(mid_file_name, "tarefas_de_");
    strcat(mid_file_name, buffer);

    char new_file_name[15] = "";
    strcpy(new_file_name, mid_file_name);
    strcat(new_file_name, ".csv");

    new_file = fopen(new_file_name, "w");
    fputs("Tarefa;Realizada por;Data de criação;Data limite;Data conclusão;Descrição \n", new_file);

    if(!file){
        printf("error: file not found");
        return -1;
    }

    char line[1024];
    int lines_to_delete[1024];
    int counter = 0;
    //skip writing header
    fgets(line, sizeof(line), file);
    while(fgets(line, sizeof(line), file)){
        char line_to_write[126];
        strcpy(line_to_write, line);
        line[strcspn(line, "\n")] = 0;
        line_number++;

        if(strstr(line, buffer)){
            char *cells[6];
            int i = 0;
        
            char *divisor = strtok(line, ";");
            while(divisor != NULL && i<6){
                cells[i++] = divisor;
                divisor = strtok(NULL, ";");
            }

            if(i == 6){
                if(strstr(cells[2], buffer) != NULL){
                    printf("nome de tarefa: %s | inicio: %s in line %d\n", cells[0], cells[2], line_number);
                    lines_to_delete[counter] = line_number;
                    fputs(line_to_write, new_file);
                    counter++;
                }
            } else {
                printf("no cells found error");
            }
        }
    }
    if(counter != 0){
        delete_by_year(year);
    }

    fclose(new_file);
    fclose(file);
    return year;
}

void average_concluded_time_original(){
    FILE *file;
    
    file = fopen("tarefas.csv", "r");
    if(!file){
        printf("error: file not found");
        return;
    }

    float duration = 0;
    int count = 0;
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

                duration = duration + (second_duration - first_duration);
                count++;
            } else {
                printf("no cells found error");
            }
        }
    }
    float final_duration = duration/count;
    printf("a duracao media e %0.2f \n", final_duration);
    fclose(file);
}

void max_and_min_duration(){
    FILE *file;
    
    file = fopen("tarefas.csv", "r");
    if(!file){
        printf("error: file not found");
        return;
    }

    int max_duration = 0;
    char max_name[25] = "";
    char max_owner[25] = "";
    int min_duration = __INT_MAX__;
    char min_name[25] = "";
    char min_owner[25] = "";
    char line[1024];
    //skip first line of the file
    fgets(line, sizeof(line), file);

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

                int duration = second_duration - first_duration;
                if(duration > max_duration){
                    max_duration = duration;
                    strcpy(max_name, cells[0]);
                    strcpy(max_owner, cells[1]);
                }
                if(min_duration > duration){
                    min_duration = duration;
                    strcpy(min_name, cells[0]);
                    strcpy(min_owner, cells[1]);
                }
            } else {
                printf("no cells found error");
            }
        }
    }
    printf("A tarefa com duracao maxima teve a duracao de %d, sendo a tarefa %s efectuada por %s \n", max_duration, max_name, max_owner);
    printf("A tarefa com menor duracao teve a duracao de %d, sendo a tarefa %s efectuada por %s \n", min_duration, min_name, min_owner);
    fclose(file);
}

void average_concluded_time_deleted(int year){
    FILE *file;
    
    char str_year[5];
    sprintf(str_year, "%d", year);
    char file_name[25] = "";
    strcat(file_name, "tarefas_de_");
    strcat(file_name, str_year);
    strcat(file_name, ".csv");
    file_name[strcspn(file_name, "\n")] = 0;
    printf("%s ", file_name);

    file = fopen(file_name, "r");
    if(!file){
        printf("error: file not found");
        return;
    }

    float duration = 0;
    int count = 0;
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

                duration = duration + (second_duration - first_duration);
                count++;
            } else {
                printf("no cells found error");
            }
        }
    }
    float final_duration = duration/count;
    printf("a duracao media e %0.2f \n", final_duration);
    fclose(file);
}

void max_and_min_duration_deleted(int year){
    FILE *file;
    
    char str_year[5];
    sprintf(str_year, "%d", year);
    char file_name[25] = "";
    strcat(file_name, "tarefas_de_");
    strcat(file_name, str_year);
    strcat(file_name, ".csv");
    file_name[strcspn(file_name, "\n")] = 0;
    printf("%s ", file_name);

    file = fopen(file_name, "r");
    if(!file){
        printf("error: file not found");
        return;
    }

    int max_duration = 0;
    char max_name[25] = "";
    char max_owner[25] = "";
    int min_duration = __INT_MAX__;
    char min_name[25] = "";
    char min_owner[25] = "";
    char line[1024];
    //skip first line of the file
    fgets(line, sizeof(line), file);

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

                int duration = second_duration - first_duration;
                if(duration > max_duration){
                    max_duration = duration;
                    strcpy(max_name, cells[0]);
                    strcpy(max_owner, cells[1]);
                }
                if(min_duration > duration){
                    min_duration = duration;
                    strcpy(min_name, cells[0]);
                    strcpy(min_owner, cells[1]);
                }
            } else {
                printf("no cells found error");
            }
        }
    }
    printf("A tarefa com duracao maxima teve a duracao de %d, sendo a tarefa %s efectuada por %s \n", max_duration, max_name, max_owner);
    printf("A tarefa com menor duracao teve a duracao de %d, sendo a tarefa %s efectuada por %s \n", min_duration, min_name, min_owner);
    fclose(file);
}

int choice;
int main(){
    int year = 2025;
    struct tarefa current_task;
    bool flag = true; //TODO:change this back to false 
    while(1){
        printf("what action do you pretend to execute");
        printf("Tarefas\n\t1- Registar nova tarfa\n\t2-alterar dados de uma tarefa\n\t3-Definir pessoa\n\t4-concluir tarefa\n\t5-eliminar uma tarefa\nPessoas e equipas\n\t6-criar e guardar equipa\n\t7-alocar equipa\nListar \n\t8-Listar em execusao \n\t9-listar concluidas\n\t10-listar ultrapasadas\n\t11-list tasks that were completed after deadline\n\t12- search tasks by team\n\t\n13-ordenar tarefas por urgencia\ndeterminar por equipas\n\t14-a duracao media de tarefas\n\t15-numero de tarefas concluidas\n\t16-numero de tarefas em execusao\n\t17-tarefas do ano\n");
        printf("considerando as tarefas originais\n\t18-duracao media das tarefas concluidas\n\t19-a duracao maxima e minima das tarefas\nconsiderando as tarefas eliminadas\n\t20-duracao media das tarefas concluidas\n\t21-a duracao maxima e minima das tarefas");
        printf("\n\t22-stop process");
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
                year = create_year_csv();
                flag = true;
                break;
            case(18):
                if(flag){
                    average_concluded_time_original();
                } else {
                    printf("\nsorry to execute this command you must have executed the commnad 17 first\n");
                }
                break;
            case(19):
                if(flag){
                    max_and_min_duration();
                } else {
                    printf("\n no \n"); //TODO: change this to real message
                }
                break;
            case(20):
                if(flag){
                    average_concluded_time_deleted(year);
                } else {
                    printf(" ");
                }
                break;
            case(21):
                if(flag){
                    max_and_min_duration_deleted(year);
                } else {
                    printf("");
                }
                break;
            case(22):
                return 1;
                break;
        }
    }
}