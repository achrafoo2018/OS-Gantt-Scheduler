#include "main.h"

void fifo(char *configFile){
   struct node *processesList = getProcessesListFromFile(configFile);
   printProcessTable(processesList);
   bubbleSort(processesList, 1, false); // Asc Sort List Based On TA 
   addIdleNodes(processesList);
   printGanttChart(processesList, "FIFO");
}  

int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else
      fifo(argv[1]);
   return 0;
}
