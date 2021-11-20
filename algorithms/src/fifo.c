#include "main.h"

void fifo(char *configFile){
   struct node *processesList = getProcessesListFromFile(configFile);
   bubbleSort(processesList, 1, false); // Asc Sort List Based On TA (which is on index 1 in DATA array)
   int ta = atoi(processesList->data[1]), te;
   int start = ta, finish = ta;
   struct node *tmp = processesList;
   while(tmp){
      ta = atoi(tmp->data[1]);
      te = atoi(tmp->data[2]);
      int idle = (finish < ta) ? (ta - finish) : 0;
      start = finish + idle;
      finish += te + idle;
      printf("%s %d-->%d\n", tmp->data[0], start, finish);
      tmp = tmp->next;
   }
}  

int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else
      fifo(argv[1]);
   return 0;
}
