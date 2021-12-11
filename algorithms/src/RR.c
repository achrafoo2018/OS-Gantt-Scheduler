#include "main.h"

struct node *sortByTaPreemptive(struct Queue *queue, int quantum){
   struct node *Res = NULL;
   int finish=atoi(queue->front->data[1]),exec;
   struct node *tmp;
   struct node *process = (struct node*)malloc(sizeof(struct node));
   while(queue->front){
      process->data[0] = strdup(queue->front->data[0]);
      process->data[1] = strdup(queue->front->data[1]);
      process->data[2] = strdup(queue->front->data[2]);
      process->data[3] = strdup(queue->front->data[3]);

      deQueue(queue);
   
      struct node *Node = (struct node*)malloc(sizeof(struct node));

      if(atoi(process->data[2]) <= quantum){
         Node = newNode(process);
         if (Res == NULL){
            Res=Node;
            tmp=Res;
         }
         else{
            tmp->next = Node;
            tmp=tmp->next;
         }    
         finish += atoi(process->data[2]);
      }else{
            Node=newNode(process);
            sprintf(Node->data[2],"%d",quantum);
            if (Res == NULL){
               Res=Node;
               tmp=Res;
            }
            else{
               tmp->next = Node;
               tmp=tmp->next;
            }

            int ta = atoi(process->data[1]);
            int idle = finish < ta ? (ta - finish) : 0;
            exec= atoi(process->data[2]) - quantum;
            sprintf(process->data[2], "%d", exec); 
            finish += quantum + idle;
            sprintf(process->data[1], "%d", finish);
            enQueue(queue,process);
      }
  }
  return Res;
}


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