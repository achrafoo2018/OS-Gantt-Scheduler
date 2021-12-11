#include "main.h"


void RR(char configFile[],int q){
   struct node *processesList = getProcessesListFromFile(configFile);
   printProcessTable(processesList);
   bubbleSort(processesList, 1, false); // Asc Sort List Based On TA (which is on index 1 in DATA array)
   struct Queue *queue = createQueueFromLinkedList(processesList);  
   struct node *tmp=sortByTaPreemptive(queue,q);
   addIdleNodes(tmp);
   printGanttChart(tmp, "Round Robin");
}
int main(int argc, char *argv[]) {
   int Q;
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else{
      do{
         printf("Enter a Quantum : ");
         scanf("%d",&Q);
         if( Q >= 1){
            RR(argv[1],Q);
         }
         else{
            printf("A quantum must be greater than or equal to 1!\n");
         }
      }while(Q<1);
   }
   return 0;
}