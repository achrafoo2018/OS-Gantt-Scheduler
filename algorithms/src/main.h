#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  

struct node {
   char *data[4]; // [Process_Name, TA, TE, Priority]
   struct node *next;
};

/* Function to bubble sort the given linked list based on an index to compare with*/
void bubbleSort(struct node *start, int comparisonIndex, bool isDesc);
  
/* Function to swap data of two nodes a and b*/
void swap(struct node *a, struct node *b);

/* Function to reverse a linked list recursively */
struct node* inverseLinkedList(struct node *node);

/* Function that reads processes from config file and returns linked list of processes */
struct node *getProcessesListFromFile(char *configFile);

/* function to remove white spaces from string */
char *remove_white_spaces(char *str);

/* Function to sort by TA and TE */
void bubbleSortByTwoIndexes(struct node *start, int comparisonIndex1, int comparisonIndex2);

/* Function to sort by TE */
void sortByTwoIndexes(struct node *head, int comparisonIndex1, int comparisonIndex2);

/* Function to print Gantt chart */
void printGanttChart(struct node *head);

/* Function to print Table of processes */
void printProcessTable(struct node *head);

/* Function to add Idle nodes to print them in gantt diagram */
void addIdleNodes(struct node *head);

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


void printGanttChart(struct node *head){
   printf("\n******************** Gant Chart *************************\n\n");
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
   printf("\n\n\n");

}


void addIdleNodes(struct node *head){
   struct node *tmp = head->next, *prev = head;
   int finish = atoi(head->data[1]) + atoi(head->data[2]);
   while(tmp && tmp->next){
      int ta = atoi(tmp->data[1]);
      int te = atoi(tmp->data[2]);
      int idle = (ta > finish) ? (ta - finish) : 0;
      if(idle > 0){
         struct node *newNode = (struct node*)malloc(sizeof(struct node));
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


void bubbleSortByTwoIndexes(struct node *start, int comparisonIndex1, int comparisonIndex2){
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
         if (i1 > ni1 || (i1 == ni1 && i2 > ni2)){ 
               swap(ptr1, ptr1->next);
               swapped = 1;
         }
         ptr1 = ptr1->next;
      }
      lptr = ptr1;
   }while (swapped);
}


void sortByTwoIndexes(struct node *head, int comparisonIndex1, int comparisonIndex2){
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
         if(ni1 <= finish && i2 > ni2 ){
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
