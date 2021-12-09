#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  

struct node {
   char *data[4]; // [Process_Name, TA, TE, Priority]
   struct node *next;
};
 
// The queue, front stores the front node of LL and rear stores the last node of LL
struct Queue {
   struct node *front, *rear;
};
 

/* Function to bubble sort the given linked list based on an index to compare with */
void bubbleSort(struct node *start, int comparisonIndex, bool isDesc);
  
/* Function to swap data of two nodes a and b */
void swap(struct node *a, struct node *b);

/* Function to reverse a linked list recursively */
struct node* inverseLinkedList(struct node *node);

/* Function that reads processes from config file and returns linked list of processes */
struct node *getProcessesListFromFile(char *configFile);

/* Function to remove white spaces from string */
char *remove_white_spaces(char *str);

/* Function to sort by TA and TE or Priority */
void bubbleSortByTwoIndexes(struct node *start, int comparisonIndex1, int comparisonIndex2, bool Desc);

/* Function to sort by TE or Priority */
void sortByTwoIndexes(struct node *head, int comparisonIndex1, int comparisonIndex2, bool Desc);

/* Function to print Gantt chart */
void printGanttChart(struct node *head, char *algorithmName);

/* Function to print Table of processes */
void printProcessTable(struct node *head);

/* Function to add Idle nodes to print them in gantt diagram */
void addIdleNodes(struct node *head);

/* Function to sort process by TA preemptive */
struct node *sortByTaPreemptive(struct Queue *queue, int quantum);

/* Function to create an empty Queue */
struct Queue* createQueue();

/* The function to add an element to queue q */
void enQueue(struct Queue* q, struct node *element);

/* Function to remove element from given queue q */
struct node* deQueue(struct Queue* q);

/* Function to create Queue from LinkedList */
struct Queue *createQueueFromLinkedList(struct node *head);

/* Function to create a new linked list node */
struct node* newNode(struct node *dataNode);

/* The function to add an element to queue q */
void enQueue1(struct Queue* q, struct node *element);

void affiche1(struct node*res);



void printProcessTable(struct node *head){ 
   printf("\n******************** Processes Table *********************\n\n");
   struct node *tmp = head;
   puts(" +---------+---------------+----------------+-----------+");
   puts(" |   PID   | Arrival Time  | Execution Time | Priority  |");
   puts(" +---------+---------------+----------------+-----------+");

   while(tmp){
      printf(" |  %4s   |      %2s       |       %2s       |    %2s     |\n"
            , tmp->data[0], tmp->data[1], tmp->data[2], tmp->data[3] );
      puts(" +---------+---------------+----------------+-----------+");
      tmp = tmp->next;
   }
 
}


void printGanttChart(struct node *head, char *algorithmName){
   printf("\n******************** %s Gant Chart ***********************\n\n", algorithmName);
   struct node *tmp = head;
   printf(" +");
   while(tmp){
      for(int j=0; j <= atoi(tmp->data[2]); j++) printf("--");
      printf("+");
      tmp = tmp->next;
   }
   printf("\n |");
   tmp = head;
   // printing process id in the middle
   while(tmp) {
      for(int j=0; j < atoi(tmp->data[2]) - 1; j++) printf(" ");
      printf("%3s", tmp->data[0]);
      for(int j=0; j < atoi(tmp->data[2]); j++) printf(" ");
      printf("|");
      tmp = tmp->next;
   }
   printf("\n +");
   tmp = head;
   // printing bottom bar
   while(tmp){
      for(int j=0; j <= atoi(tmp->data[2]); j++) printf("--");
      printf("+");
      tmp = tmp->next;
   }
   printf("\n ");
   tmp = head;
   // printing the time line
   printf("%s", head->data[1]);
   int ta = atoi(head->data[1]), te;
   int finish = ta;
   while(tmp){
      for(int j=0; j <= atoi(tmp->data[2]); j++) printf("  ");
      ta = atoi(tmp->data[1]);
      te = atoi(tmp->data[2]);
      int idle = (finish < ta) ? (ta - finish) : 0;
      finish += te + idle;
      if(finish > 9) printf("\b"); // backspace : remove 1 space
      printf("%d", finish);
      tmp = tmp->next;
   }
   printf("\n");
   printf("\n***********************************************************\n\n");
}


void addIdleNodes(struct node *head){
   struct node *tmp = head->next, *prev = head;
   int finish = atoi(head->data[1]) + atoi(head->data[2]);
   while(tmp){
      int ta = atoi(tmp->data[1]);
      int te = atoi(tmp->data[2]);
      int idle = (ta > finish) ? (ta - finish) : 0;
      if(idle > 0){
         struct node *newNode = (struct node*)malloc(sizeof(struct node));
         for(int i=0; i<4; i++)
            newNode->data[i] = (char *)malloc(sizeof(char) * 100);
         newNode->data[0] = "-";
         sprintf(newNode->data[1], "%d", finish);
         sprintf(newNode->data[2], "%d", idle);
         newNode->data[3] = "0";
         newNode->next = prev->next;
         prev->next = newNode;
      }
      finish += te + idle;
      tmp = tmp->next;
      prev = prev->next;
   }
}


struct node* inverseLinkedList(struct node *node){
   if(node->next == NULL)
      return node;
   struct node *node1 = inverseLinkedList(node->next);
   node->next->next = node;
   node->next = NULL;
   return node1;
}


void bubbleSort(struct node *start, int comparisonIndex, bool isDesc){
   int swapped;
   struct node *ptr1;
   struct node *lptr = NULL;
   /* Checking for empty list */
   if (start == NULL)
      return;
   do{
      swapped = 0;
      ptr1 = start;
      while (ptr1->next != lptr){
         int a = atoi(ptr1->data[comparisonIndex]);
         int b = atoi(ptr1->next->data[comparisonIndex]);
         bool condition = isDesc ? a < b : a > b; // comparing based on isDesc
         if (condition){ 
               swap(ptr1, ptr1->next);
               swapped = 1;
         }
         ptr1 = ptr1->next;
      }
      lptr = ptr1;
   }while (swapped);
}
  
/* function to swap data of two nodes a and b*/
void swap(struct node *a, struct node *b){
   for(int i=0; i < 4; i++){
      char *temp = a->data[i];
      a->data[i] = b->data[i];
      b->data[i] = temp;
   }
}


char *remove_white_spaces(char *str){
	int i = 0, j = 0;
	while (str[i]){
		if (str[i] != ' ')
          str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}

struct node *getProcessesListFromFile(char *configFile){
   FILE *fp;
   fp = fopen(configFile, "r");
   if(fp == NULL) {
      perror("Unable to open file!");
      exit(1);   
   }
   char * line = NULL;
   size_t len = 0;
   ssize_t read;
   struct node *processesLinkedList = NULL;
   while ((read = getline(&line, &len, fp)) != -1) {
      if(remove_white_spaces(line)[0] == '#'){
         printf("Commentaire : %s", line);
         continue;
      }
      else if(remove_white_spaces(line)[0] == '\n')
         continue;
      struct node *newNode = (struct node*)malloc(sizeof(struct node));
      char *token = strtok(line, ":");
      int i=0;
      while(token != NULL){
         token[strcspn(token, "\n")] = 0; // deleting \n from token
         newNode->data[i] = strdup(token);
         token = strtok(NULL, ":");
         i++;
      }
      newNode->next = processesLinkedList;
      processesLinkedList = newNode;
   }
   fclose(fp);
   processesLinkedList = inverseLinkedList(processesLinkedList);
   return processesLinkedList;
}


void bubbleSortByTwoIndexes(struct node *start, int comparisonIndex1, int comparisonIndex2, bool Desc){
   int swapped;
   struct node *ptr1;
   struct node *lptr = NULL;
   /* Checking for empty list */
   if (start == NULL)
      return;
   do{
      swapped = 0;
      ptr1 = start;
      while (ptr1->next != lptr){
         int i1 = atoi(ptr1->data[comparisonIndex1]);
         int ni1 = atoi(ptr1->next->data[comparisonIndex1]);
         int i2 = atoi(ptr1->data[comparisonIndex2]);
         int ni2 = atoi(ptr1->next->data[comparisonIndex2]);
         bool condition = Desc ? i2 < ni2 : i2 > ni2;
         if (i1 > ni1 || (i1 == ni1 && condition)){ 
               swap(ptr1, ptr1->next);
               swapped = 1;
         }
         ptr1 = ptr1->next;
      }
      lptr = ptr1;
   }while (swapped);
}


void sortByTwoIndexes(struct node *head, int comparisonIndex1, int comparisonIndex2, bool Desc){
   struct node *lptr = NULL;
   bool swapped;
   do{
      swapped = false;
      int finish = atoi(head->data[1]) + atoi(head->data[2]);
      struct node *ptr1 = head->next;
      while(ptr1->next != lptr){
         int ni1 = atoi(ptr1->next->data[comparisonIndex1]);
         int i2 = atoi(ptr1->data[comparisonIndex2]);
         int ni2 = atoi(ptr1->next->data[comparisonIndex2]);
         bool condition = Desc ? i2 < ni2 : i2 > ni2;
         if(ni1 <= finish && condition){
            swap(ptr1, ptr1->next);
            swapped = true;
         }
         int ta = atoi(ptr1->data[1]);
         int te = atoi(ptr1->data[2]);
         int idle = (finish < ta) ? (ta - finish) : 0;
         finish += te + idle;
         ptr1 = ptr1->next;
      }
      lptr = ptr1;
   }while(swapped);
}


struct Queue *createQueueFromLinkedList(struct node *head){
   struct node *tmp = head;
   struct Queue *queue = createQueue();
   while(tmp){
      enQueue1(queue, tmp);
      tmp = tmp->next;
   }
   return queue;
}

// The function to add a key k to q
void enQueue1(struct Queue *q, struct node *element){
   // Create a new LL node
   struct node *temp = newNode(element);
   // If queue is empty, then new node is front and rear both
   if (q->rear == NULL) {
      q->front = q->rear = temp;
      return;
   }
   q->rear->next = temp;
   q->rear=temp;
}



// A utility function to create a new linked list node.
struct node* newNode(struct node *dataNode){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data[0] = strdup(dataNode->data[0]);
    temp->data[1] = strdup(dataNode->data[1]);
    temp->data[2] = strdup(dataNode->data[2]);
    temp->data[3] = strdup(dataNode->data[3]);
    temp->next = NULL;
    return temp;
} 
 
// A utility function to create an empty queue
struct Queue* createQueue(){
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}


// The function to add a key k to q
void enQueue(struct Queue *q, struct node *element){
   // Create a new LL node
   struct node *temp = newNode(element);
   // If queue is empty, then new node is front and rear both
   if (q->rear == NULL) {
      q->front = q->rear = temp;
      return;
   }
   if(atoi(q->rear->data[1]) <= atoi(temp->data[1])){
      q->rear->next = temp;
      q->rear = temp;
      return;
   }
   struct node *tmp = q->front->next, *prev = q->front;
   while(tmp  && tmp->next && (atoi(tmp->data[1]) <= atoi(temp->data[1])) ){
      tmp = tmp->next;
      prev = prev->next;
   }
   temp->next= prev->next;
   prev->next = temp;
}
 
// Function to remove element from given queue q
struct node* deQueue(struct Queue* q){
   // If queue is empty, return NULL.
   if (q->front == NULL)
     return q->front;
   // Store previous front and move front one node ahead
   struct node* temp = q->front;
   //struct node *ret = q->front;
   q->front = q->front->next;

   // If front becomes NULL, then change rear also as NULL
   if (q->front == NULL)
      q->rear = NULL;
   free(temp);
   return (q->front);
}

void affiche(struct Queue*q){
    printf("********* Affichage de queue apres suppression du 1er element*********** \n");

      while(q->front){

       printf("%s \n",q->front->data[0]);
       printf("%s \n",q->front->data[1]);
       printf("%s \n",q->front->data[2]);
       //printf("%s \n",queue->front->data[3]);
      printf("******************** \n");
       q->front=q->front->next;
   } 
}


void affiche1(struct node*res){
    printf("********* Affichage de Resultat*********** \n");

      while(res){

       printf("%s \n",res->data[0]);
       printf("%s \n",res->data[1]);
       printf("%s \n",res->data[2]);
       printf("%s \n",res->data[3]);
      printf("******************** \n");
       res=res->next;
   } 
}

struct node *sortByTaPreemptive(struct Queue *queue, int quantum){
   
   struct node *Res = NULL;
   int finish=atoi(queue->front->data[1]),exec;
   struct node *tmp;
   struct node *frnt;
   struct node *process = (struct node*)malloc(sizeof(struct node));
   struct node *Node;


   while(queue->front){

      process->data[0] = strdup(queue->front->data[0]);
      process->data[1] = strdup(queue->front->data[1]);
      process->data[2] = strdup(queue->front->data[2]);
      process->data[3] = strdup(queue->front->data[3]);

      frnt=deQueue(queue);
     
      Node = (struct node*)malloc(sizeof(struct node));
      
      if(atoi(process->data[2]) <= quantum){
         //finish += atoi(process->data[2]);
         //sprintf(process->data[1], "%d", finish);
   
         Node=newNode(process);
         if (Res == NULL){
            Res=Node;
            tmp=Res;
         }
         else{
         tmp->next = Node;
         tmp=tmp->next;
         }

         printf("***** queue *****");
         affiche(queue);
         affiche1(Res);
    
      }else{

            //sprintf(process->data[2], "%d", exec);    
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

           
            exec= atoi(process->data[2]) - quantum;
            sprintf(process->data[2], "%d", exec); 
            finish += atoi(process->data[1])+quantum;
            sprintf(process->data[1], "%d", finish);

             
   
            /*printf("%s \n",process->data[0]);
            printf("%s \n",process->data[1]);
            printf("%s \n",process->data[2]);
            printf("%s \n",process->data[3]);*/
       
            enQueue(queue,process);
            printf("***** queue *****");
            affiche(queue);
            affiche1(Res);
      }
      
      queue->front=frnt;

}
return Res;
}


