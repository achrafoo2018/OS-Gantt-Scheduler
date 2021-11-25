
#include "main.h"  

void SRT(char configFile[]){
   struct node *processesList = getProcessesListFromFile(configFile);
   bubbleSortByTwoIndexes(processesList, 1, 2); // Sort List by Ta & Te to get First process to run
   struct node *tmp = processesList;
   sortByTwoIndexes(tmp, 1, 2);
   tmp = processesList;
   displayResult(tmp);
}


int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else
      SRT(argv[1]);
   return 0;
}
