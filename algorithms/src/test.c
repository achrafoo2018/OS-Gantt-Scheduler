#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  

struct node {
   char *data[4]; // [Process_Name, TA, TE, Priority]
   struct node *next;
};

// file d attente
struct file {
   struct node *tete; 
   struct node *queue;
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

/* Function to sort by TA and Priority */
void bubbleSortByTaPriority(struct node *start, int comparisonIndex1, int comparisonIndex2);


/* Function to sort by TE */
void sortByTwoIndexes(struct node *head, int comparisonIndex1, int comparisonIndex2);

/* Function to sort by Priority */
void sortByTaPriority(struct node *head, int comparisonIndex1, int comparisonIndex2);

/* function to sort by ta preemtive*/
void sortByTaPreemptive(struct node *head, int comparisonIndex1, int comparisonIndex2,int q);

/* Function to insert in end of list */
void insertFin(struct node *head, char *p[4]);

/* Function to insert in end of file */
void enfiler(struct file *f, char *p[4]);

/* Function to delete the first element of file */
void defiler(struct file *f, char *p[4]);



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

void displayResult(struct node *head){
   int ta = atoi(head->data[1]), te;
   int start = ta, finish = ta;
   while(head){
      ta = atoi(head->data[1]);
      te = atoi(head->data[2]);
      int idle = (finish < ta) ? (ta - finish) : 0;
      start = finish + idle;
      finish += te + idle;
      printf("%s %d-->%d\n", head->data[0], start, finish);
      head = head->next;
   }
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
         int ta1 = atoi(ptr1->data[comparisonIndex1]);
         int ta2 = atoi(ptr1->next->data[comparisonIndex1]);
         int te1 = atoi(ptr1->data[comparisonIndex2]);
         int te2 = atoi(ptr1->next->data[comparisonIndex2]);
         if (ta1 > ta2 || (ta1 == ta2 && te1 > te2)){ 
               swap(ptr1, ptr1->next);
               swapped = 1;
         }
         ptr1 = ptr1->next;
      }
      lptr = ptr1;
   }while (swapped);
}

void bubbleSortByTaPriority(struct node *start, int comparisonIndex1, int comparisonIndex2){
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
         int ta1 = atoi(ptr1->data[comparisonIndex1]);
         int ta2 = atoi(ptr1->next->data[comparisonIndex1]);
         int pr1 = atoi(ptr1->data[comparisonIndex2]);
         int pr2 = atoi(ptr1->next->data[comparisonIndex2]);
         if (ta1 > ta2 || (ta1 == ta2 && pr1 < pr2)){ 
               swap(ptr1, ptr1->next);
               swapped = 1;
         }
         ptr1 = ptr1->next;
      }
      lptr = ptr1;
   }while (swapped);
}

void sortByTwoIndexes(struct node *head, int comparisonIndex1, int comparisonIndex2){
   int t_a, t_e;
   while(head){ 
      int finish = atoi(head->data[comparisonIndex1]) + atoi(head->data[2]);
      struct node *head2 = head->next;
      while(head2 && head2->next){
         if((atoi(head2->data[comparisonIndex1]) <= finish &&
            atoi(head2->next->data[comparisonIndex1]) <= finish) &&
            atoi(head2->data[comparisonIndex2]) > atoi(head2->next->data[comparisonIndex2])){
            for (int i = 0; i < 4; i++){
               char *t = head2->next->data[i];
               head2->next->data[i] = head2->data[i];
               head2->data[i] = t;
            }
         }
         t_a = atoi(head2->data[comparisonIndex1]);
         t_e = atoi(head2->data[comparisonIndex2]);
         int idle = (finish < t_a) ? (t_a - finish) : 0;
         finish += t_e + idle;
         head2 = head2->next;
      }
      head = head->next;
   }
}

void sortByTaPriority(struct node *head, int comparisonIndex1, int comparisonIndex2){
   int t_a, t_e;
   while(head){ 
      int finish = atoi(head->data[comparisonIndex1]) + atoi(head->data[2]);
      struct node *head2 = head->next;
      while(head2 && head2->next){
         if((atoi(head2->data[comparisonIndex1]) <= finish &&
            atoi(head2->next->data[comparisonIndex1]) <= finish) &&
            atoi(head2->data[comparisonIndex2]) < atoi(head2->next->data[comparisonIndex2])){
            for (int i = 0; i < 4; i++){
               char *t = head2->next->data[i];
               head2->next->data[i] = head2->data[i];
               head2->data[i] = t;
            }
         }
         t_a = atoi(head2->data[comparisonIndex1]);
         t_e = atoi(head2->data[comparisonIndex2]);
         int idle = (finish < t_a) ? (t_a - finish) : 0;
         finish += t_e + idle;
         head2 = head2->next;
      }
      head = head->next;
   }
}



void sortByTaPreemptive(struct node *head, int comparisonIndex1, int comparisonIndex2,int q){
   //int t_a, t_e;
   struct node *Res=NULL;
   struct file *f=NULL;
   
   // linked list to save the first process w nhot el ta w Q feha el if
   insertFin(Res,head->data);
   
   while(head){ 
      int finish;
      if(atoi(head->data[comparisonIndex2]) < q)
      {
         finish = atoi(head->data[comparisonIndex1]) + atoi(head->data[comparisonIndex2]);
      }
      else
      {
         finish = atoi(head->data[comparisonIndex1]) + q;
      }
      //insert head in file
      enfiler(f,head->data);
      struct node *head2 = head->next;
      //delete head in file
      defiler(f,head->data);
      while(head2){
         if(atoi(head2->data[comparisonIndex1]) <= finish )  
         {          
         //insert head2 in file 
         enfiler(f,head2->data);
         }        
         head2 = head2->next;
      }
      // insert head in file
      enfiler(f,head->data);
      //ken te wfe ena7ih ml file
      
      //aka linked list nsavi feha e theny eli howa awel element f file ndefilih w aprés naawed n'emplih ken mazel makamalesh e te
      insertFin(Res,f->tete->data);

      head = head->next;
   }
  
}

void insertFin(struct node *l,char *p[4]){
   struct node *process;

   process=(struct node*)malloc(sizeof(struct node));
   *process->data = *p;


   if(l==NULL){
      process->next=l;
      l=process;
   }
   else{
      // récupérer le dernier processus de la liste
      while (l->next != NULL){
         l=l->next;
      }
      process->next = NULL;
      l->next=process;
   }

}

void enfiler(struct file *f, char *p[4]){
   struct node *process;
   process=(struct node*)malloc(sizeof(struct node));
   *process->data = *p;
   process->next=NULL;

   if(f == NULL){
      f->tete=process;
   }
   else{
      f->queue->next=process;
   }
   f->queue=process;
}

void defiler(struct file *f, char *p[4]){
   struct node *process;
   process=f->tete;
   p=f->tete->data;
   f->tete=f->tete->next;
   if(f->tete == NULL){
      f->queue = NULL;
   }
   free(process);
}

/*void afficher(struct file *f){
   while(f!=NULL){
      printf(" | %s | %s | %s | %s \n ",f->tete->data[0],f->tete->data[1],f->tete->data[2],f->tete->data[3]);
      printf(" --------- \n ");
      *f=f->tete->next;
   }
}*/






