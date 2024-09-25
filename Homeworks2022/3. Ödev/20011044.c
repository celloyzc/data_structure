#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dosya{
	char isim[20];
	struct dosya *next;
}DOSYA;

typedef struct tree{
	char word[20];
  	struct tree *left, *right;
  	DOSYA* file;
}STRUCT;


STRUCT* insertFile(STRUCT* node);
int isThere(STRUCT* node, char buf[]);
STRUCT* insertWord(STRUCT* node, char buf[], char file_name[]);
STRUCT* insertFileName(STRUCT* node, char buf[], char file_name[]);
STRUCT* newNode(char buf[],char file_name[]);
STRUCT* deleteFile(STRUCT* node);
STRUCT* deleteWord(STRUCT* root, char buf[], char file_name[]);
STRUCT* minValueNode(STRUCT* node);
STRUCT* searchWord(STRUCT* root, char buf[]);
void printInOrder(STRUCT* root);


int main(){
	STRUCT* root = NULL;
	STRUCT* tmp = NULL;
	int a;
	char kelime[20];
	do{
		printf("MENU:\n\n1-Yeni Dosya Ekle\n2-Dosya Sil\n3-Kelime Ara\n4-Cikis\n");
		printf("Islem numarasi giriniz:");
		scanf("%d",&a);
		printf("\n\n");
		if(a==1){
			
			printf("1-Yeni Dosya Ekle\n");
			root=insertFile(root);
			printf("Dosya Eklendi!\n");
			
			printf("\nInOrderPrint:\n");
			printInOrder(root);
			
		}else if(a==2){
			
			printf("2-Dosya Sil\n");
			root=deleteFile(root);
			printf("Dosya Silindi!\n");
			
			printf("\nInOrderPrint:\n");
			printInOrder(root);
			
		}else if(a==3){
			
			printf("3-Kelime Ara\n");
			printf("Aramak istediginiz kelimeyi giriniz:");
			scanf("%s",kelime);
			tmp=root;
			tmp=searchWord(tmp,kelime);
			printf("\n");
		}
		
		
	}while(a != 4);
	
return 0;	
}




STRUCT* insertFile(STRUCT* node){
	
	char file_name[20];
	char buf[20];
	
	printf("Eklenecek dosyanin ismini giriniz: ");
	scanf("%s",file_name);
	
	FILE *fp=fopen(file_name,"r");
	
	while(fscanf(fp, "%s", buf)!=EOF){                              //her kelime ayrildiginda buf'a atilir
		//printf("%s",buf);
		
		if(!isThere(node,buf)){
			node = insertWord(node,buf,file_name);                  //kelime daha once eklenmediyse eklenir
		}else{
			node = insertFileName(node,buf,file_name);              //kelime daha once eklendiyse dosya ismi eklenir
		}
		
	}
	
	fclose(fp);
	return node;
}




STRUCT* deleteFile(STRUCT* node){
	char file_name[10];
	char buf[255];
	
	printf("Silinecek dosyanin ismini giriniz: ");
	scanf("%s",file_name);
	
	FILE *fp=fopen(file_name,"r");
	
	while(fscanf(fp, "%s", buf)!=EOF){
		node = deleteWord(node,buf,file_name);
	}
	return node;
}



STRUCT* deleteWord(STRUCT* root, char buf[], char file_name[]){
	if (root == NULL) return root;

	if (strcmp(root->word,buf)>0)
    	root->left = deleteWord(root->left, buf, file_name);
	else if (strcmp(root->word,buf)<0)
    	root->right = deleteWord(root->right, buf, file_name);
    else if(root->file->next == NULL){                                           //tek bir dosyada bulunuyorsa node silinir
    	
    	if (root->left == NULL) {
      		STRUCT* temp = root->right;
      		free(root);
      	return temp;
    	}else if (root->right == NULL) {
      		STRUCT* temp = root->left;
      		free(root);
      		return temp;
    	}

    	STRUCT* temp = minValueNode(root->right);

    	strcpy(root->word,temp->word);

    	root->right = deleteWord(root->right, temp->word, file_name);
  
    	
    	
	}else{                                                                        //baska dosyalarda bulunuyorsa dosya ismi silinir
		DOSYA* tmp,*current;
		if( strcmp(root->file->isim,file_name)==0 ){                              //silinecek dosya isminin ilk node olmasi durumu
			tmp = root->file;
			root->file = root->file->next;
			free(tmp);
		}else{                                                                    //silinecek dosya isminin ilk node olmamasi durumu
			current = root->file;
			while( strcmp(current->next->isim,file_name)!=0 ){
				current = current->next;
			}
			tmp = current->next;
			current->next=current->next->next;
			free(tmp);
		}
	}
	return root;
	
}



STRUCT* minValueNode(STRUCT* node){
	STRUCT* current = node;
	while (current && current->left != NULL)
    current = current->left;

  	return current;
}




STRUCT* searchWord(STRUCT* root, char buf[]){
	if( root == NULL || ( strcmp(root->word,buf)==0 ) ){
		
		if(root == NULL){
			printf("Kelime bulunamadi !!!");
			return root;
		}else{	
			printf("Kelimenin bulundugu dosyalar: ");
			while(root->file != NULL){
				printf("%s ->",root->file->isim);
				root->file = root->file->next;
			}		
			return root;
		}
	}
	if(strcmp(root->word,buf)<0){
		return searchWord(root->right,buf);
	}
	
	return searchWord(root->left,buf);
	
}



int isThere(STRUCT* root, char buf[]){
	
	if( root == NULL || ( strcmp(root->word,buf)==0 ) ){
		
		if(root == NULL){
			return 0;
		}else{			
			return 1;
		}
	}
	if(strcmp(root->word,buf)<0){
		return isThere(root->right,buf);
	}
	
	return isThere(root->left,buf);
	
}



STRUCT* insertWord(STRUCT* root, char buf[], char file_name[]){
	
	if (root == NULL){
		return newNode(buf,file_name);
	}

  	if (strcmp(root->word,buf)>0){
  		root->left = insertWord(root->left,buf,file_name);
	}else{
	  	root->right = insertWord(root->right,buf,file_name);
	}

return root;

}



STRUCT* insertFileName(STRUCT* root, char buf[], char file_name[]){
	
	if( root == NULL || ( strcmp(root->word,buf)==0 ) ){
		
		while(root->file->next != NULL){
			root->file = root->file->next;
		}
		root->file->next = (DOSYA*)malloc(sizeof(DOSYA));
		strcpy(root->file->next->isim,file_name);
		root->file->next->next=NULL;
		return root;
	}
	if(strcmp(root->word,buf)<0){
		return insertFileName(root->right,buf,file_name);
	}
	
	return insertFileName(root->left,buf,file_name);
	
}



STRUCT* newNode(char buf[],char file_name[]) {
	
  STRUCT* temp = (STRUCT*)malloc(sizeof(STRUCT));
  strcpy(temp->word,buf);
  temp->left = temp->right = NULL;
  
  temp->file=NULL;
  temp->file = (DOSYA*)malloc(sizeof(DOSYA));
  strcpy(temp->file->isim,file_name);
  temp->file->next=NULL;
  
  
  return temp;
}



void printInOrder(STRUCT* root){
	if (root != NULL) {
  	
    // Traverse left
    printInOrder(root->left);

    // Traverse root
    printf("%s->", root->word);

    // Traverse right
    printInOrder(root->right);
  }
}
