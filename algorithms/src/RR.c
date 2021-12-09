#include "main.h"


void RR(char configFile[],int q){
   struct node *processesList = getProcessesListFromFile(configFile);
    printProcessTable(processesList);
   bubbleSort(processesList, 1, false); // Asc Sort List Based On TA (which is on index 1 in DATA array)
   struct Queue *queue = createQueueFromLinkedList(processesList);  
   struct node *tmp=sortByTaPreemptive(queue,q);
   addIdleNodes(tmp);
   printGanttChart(tmp, "Round Robin");

  

   /*while(queue->front){

       printf("%s \n",queue->front->data[0]);
       printf("%s \n",queue->front->data[1]);
       printf("%s \n",queue->front->data[2]);
       printf("%s \n",queue->front->data[3]);
              printf("******************** \n");
              queue->front=queue->front->next;
   }*/
   /*while(queue->front){

   struct node *process = (struct node*)malloc(sizeof(struct node)); 

   for(int i=0;i<=3;i++){
      process->data[i]=(char*)malloc(5*sizeof(char));
   }

   strcpy(process->data[0], queue->front->data[0]);
   strcpy(process->data[1], queue->front->data[1]);
   strcpy(process->data[2], queue->front->data[2]);
   strcpy(process->data[3], queue->front->data[3]);
   
   
   
   struct node *Node = (struct node*)malloc(sizeof(struct node));
   
   Node=newNode(process);
         if (Res== NULL){
            Res=Node;
         }
         else{
            while (tmp->next != NULL){
               tmp = tmp->next;
            }
         tmp->next = Node;
         }
   queue->front=queue->front->next;
   }
   affiche1(Res);*/

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