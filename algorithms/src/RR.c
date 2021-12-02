#include "main.h"


void RR(char configFile[],int q){
   struct node *processesList = getProcessesListFromFile(configFile);
   bubbleSort(processesList, 1, false); // Asc Sort List Based On TA (which is on index 1 in DATA array)
   struct node *tmp = processesList;
   sortByTaPreemptive(tmp, 1, 2,q);
   //tmp = processesList;
   //displayResult(tmp);
}  

int main(int argc, char *argv[]) {
    int Q;
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else{
      printf("Enter a Quantum : ");
      scanf("%d",&Q);
      RR(argv[1],Q);
   }
   return 0;
}