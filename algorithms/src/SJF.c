
#include "main.h"  

void sjf(char configFile[]){
   struct node *processesList = getProcessesListFromFile(configFile);
   sortByTaTe(processesList, 1, 2); // Asc Sort List Based On TA (which is on index 1 in DATA array)
   struct node *tmp = processesList;
   sortByTe(tmp, 1, 2);
   tmp = processesList;
   displayResult(tmp);
}  

int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else{
      sjf(argv[1]);
   }
   return 0;
}
