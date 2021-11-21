#include "main.h"

void fifo(char *configFile){
   struct node *processesList = getProcessesListFromFile(configFile);
   bubbleSort(processesList, 1, false); // Asc Sort List Based On TA (which is on index 1 in DATA array)
   struct node *tmp = processesList;
   displayResult(tmp);
}  

int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else
      fifo(argv[1]);
   return 0;
}
