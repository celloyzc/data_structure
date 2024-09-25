#include <stdio.h>

void printtoken(char* token);

int main(){
	FILE *fp;  
   char buff[255];//creating char array to store data of file  
   fp = fopen("a.txt", "r");  
   while(fscanf(fp, "%s", buff)!=EOF){ 
   printf("A"); 
   printf("%s ", buff );  
   }  
   fclose(fp);
}
