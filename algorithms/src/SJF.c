#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fifo(char config[]){
   FILE *fp;
   fp = fopen(("./%s", config), "r");
   if(fp == NULL) {
      perror("Unable to open file!");
      exit(1);   
   }
   char * line = NULL;
   size_t len = 0;
   ssize_t read;
   int i=0;
   char *tab[3][4];
   while ((read = getline(&line, &len, fp)) != -1) {
      if(line[0] == '#'){
         printf("Commentaire : %s", line);
         continue;
      }
      char *token = strtok(line, ":");
      int j=0;
      while(token != NULL){
         tab[i][j] = strdup(token);
         token = strtok(NULL, ":");
         j++;
      }
      i++;
      
   }
   fclose(fp);
   for(int i=0; i < 3; i++){ // sorting array based on TA
      for(int j=2; j > i; j--){
         if(atoi(tab[j][1]) <= atoi(tab[j-1][1])){
            for (int r = 0; r < 4; r++){
               char *t = tab[j - 1][r];
               tab[j - 1][r] = tab[j][r];
               tab[j][r] = t;
            }
         }
      }
   }
   int ta = atoi(tab[0][1]), te;
   int start = ta, finish = ta;
   for(int i=0; i < 3; i++){
      ta = atoi(tab[i][1]);
      te = atoi(tab[i][2]);
      int idle = (finish < ta) ? (ta - finish) : 0;
      start = finish + idle;
      finish += te + idle;
      printf("%s %d-->%d\n", tab[i][0], start, finish);
   }
   printf("\n");

}  

int main(int argc, char *argv[]) {
   if(argc == 1)
      printf("Usage: %s <config>\n", argv[0]);
   else{
      fifo(argv[1]);
   }
   return 0;
}