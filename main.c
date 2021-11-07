#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

const char ALGORITHMS_FOLDER[] = "./algorithms/exec/";
struct algorithm{
    int n;
    char name[500];
    char location[500];
};

int main(int argc, char *argv[]){
    if(argc == 1){
        printf("Usage: %s <config>\n", argv[0]);
        exit(1);
    }

    DIR *algorithms;
    struct dirent *dir;
    algorithms = opendir(ALGORITHMS_FOLDER);
    printf("Veuillez choisir un algorithme d'ordonancement : \n");
    struct algorithm algorithmChoices[100];
    if (algorithms)
    {
        int i = 1;
        while ((dir = readdir(algorithms)) != NULL)
        {
            if(dir->d_type == DT_DIR){
                continue;
            }
            struct algorithm algo;
            algo.n = i;
            strcpy(algo.name, dir->d_name);
            char loc[500] = "";
            strcat(loc, ALGORITHMS_FOLDER);
            strcat(loc, dir->d_name);
            strcpy(algo.location, loc);
            algorithmChoices[i] = algo;
            printf("\t%d - %s\n", i, dir->d_name);
            i++;
        }
        closedir(algorithms);
    }
    int choix;
    printf("Entrer votre choix : ");
    scanf("%d", &choix);
    char command[500] = "";
    strcat(command, algorithmChoices[choix].location);
    char configFile[100] = " ";
    strcat(configFile, argv[1]);
    strcat(command, configFile);
    system(command);
}