#include "main.h"

void priority(char configFile[]){
   struct node *processesList = getProcessesListFromFile(configFile);
   bubbleSortByTaPriority(processesList, 1, 3); // Sort List by Ta & Priority to get First process to run
   struct node *tmp = processesList;
   sortByTaPriority(tmp, 1, 3);
   tmp = processesList;
   displayResult(tmp);
}  

int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else{
      priority(argv[1]);
   }
   return 0;
}