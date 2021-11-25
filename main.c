#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char ALGORITHMS_FOLDER[] = "./algorithms/build/";

struct algorithm{
    int n;
    char name[500];
    char location[500];
};


int getNumberOfAlgorithms(DIR *algorithms){
    int nb = 0;
    struct dirent *dir;
    while ((dir = readdir(algorithms)) != NULL){
        if(dir->d_type == DT_DIR)
            continue;
        nb++;
    }
    return nb;
}

struct algorithm *getListOfSchedulingAlgorithms(int numberOfAlgorithms){
    DIR *algorithms;
    struct dirent *dir;
    algorithms = opendir(ALGORITHMS_FOLDER); // pointer to files in src
    printf("Choose a scheduling algorithm : \n");
    struct algorithm *algorithmChoices;
    algorithmChoices = (struct algorithm*)malloc(numberOfAlgorithms * sizeof(struct algorithm ) ); 
    if (algorithms){
        int i = 1;
        while ((dir = readdir(algorithms)) != NULL){
            if(dir->d_type == DT_DIR)
                continue;
            struct algorithm algo;
            algo.n = i;
            strcpy(algo.name, dir->d_name);
            char loc[500] = "";
            strcat(loc, ALGORITHMS_FOLDER);
            strcat(loc, dir->d_name);
            strcpy(algo.location, loc);
            algorithmChoices[i] = algo;
            printf("\t%d - %s\n", i, dir->d_name); // printing the menu
            i++;
        }
        closedir(algorithms);
    }
    return algorithmChoices;
}


void clear_stream(FILE *in){
    int ch;
    clearerr(in);
    do
        ch = getc(in);
    while (ch != '\n' && ch != EOF);
    clearerr(in);
}

int getUserChoice(int nbOfAlgorithms){
    int choice = -1;
    while(1){
        printf("Enter your choice : ");
        while(scanf("%d", &choice) != 1){
            clear_stream(stdin);
            printf("Invalid integer. Please try again: ");
            fflush(stdout);
        };
        if(choice > nbOfAlgorithms || choice < 1)
            printf("Choose a number from the menu!\n");
        else // user gave a choice within the menu
            break;
    }
    return choice;
}

int main(int argc, char *argv[]){
    if(argc == 1){
        printf("Usage: %s <config>\n", argv[0]);
        exit(1);
    }
    DIR *algorithmsFiles = opendir(ALGORITHMS_FOLDER); // pointer to count nb of files
    int nbOfAlgorithms = getNumberOfAlgorithms(algorithmsFiles);
    struct algorithm *algorithmChoices = getListOfSchedulingAlgorithms(nbOfAlgorithms);
    int choice = getUserChoice(nbOfAlgorithms);
    char command[500] = "";
    strcat(command, algorithmChoices[choice].location);
    char configFile[100] = " ";
    strcat(configFile, argv[1]);
    strcat(command, configFile);
    system(command);
}