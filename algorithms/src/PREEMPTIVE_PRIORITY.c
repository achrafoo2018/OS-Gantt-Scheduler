
#include "main.h"  


void insertInPosition(struct node *head, struct node *newNode, int finish){
   struct node *tmp = head->next;
   struct node *prev = head;
   if(head == NULL){
      head = newNode;
      return;
   }
   while(tmp &&
          atoi(newNode->data[3]) <= atoi(tmp->data[3]) &&
          atoi(tmp->data[1]) <= finish){
      prev = prev->next;
      tmp = tmp->next;
   }
   newNode->next = tmp;
   prev->next = newNode;
}


void PriorityPreemptive(struct node *head){
   struct node *tmp = head;
   int finish = atoi(tmp->data[1]);
   while(tmp){
      struct node *tmp2 = tmp->next;
      while(tmp2){
         int ta = atoi(tmp->data[1]);
         int idle = ta > finish ? ta - finish : 0;
         int diffta = atoi(tmp2->data[1]) - (finish+idle);
         diffta = diffta < 0 ? 0 : diffta;
         bool condition = atoi(tmp2->data[1]) <= (finish+idle+atoi(tmp->data[2])) &&  atoi(tmp2->data[3]) > atoi(tmp->data[3]);
         if(diffta == 0 && condition)
            swap(tmp, tmp2);
         else if(condition){
            if(atoi(tmp->data[2]) > diffta){
               struct node *remainderNode = newNode(tmp);
               sprintf(remainderNode->data[2], "%d", (atoi(tmp->data[2])-diffta));
               insertInPosition(tmp, remainderNode, finish+idle);
            }
            sprintf(tmp->data[2], "%d", diffta);
            swap(tmp->next, tmp2);
            break;
         }
         tmp2 = tmp2->next;
      }
      int ta = atoi(tmp->data[1]);
      int idle = ta > finish ? ta-finish : 0;
      finish += atoi(tmp->data[2]) + idle;
      tmp = tmp->next;
   }
}


void PreemptivePriority(char configFile[]){
   struct node *processesList = getProcessesListFromFile(configFile);
   printProcessTable(processesList);
   bubbleSortByTwoIndexes(processesList, 1, 2, false); // Sort List by Ta & Te to get First process to run
   PriorityPreemptive(processesList);
   addIdleNodes(processesList);
   printGanttChart(processesList, "Pre-emptive Priority");
}


int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else
      PreemptivePriority(argv[1]);
   return 0;
}
