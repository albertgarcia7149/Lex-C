//-----------------------------------
//Albert Garcia
//awgarcia
//pa2
//-----------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

void freeArray(char **a,int m){
	for(int i=0;i<m;i++){
		free(a[i]);
	}
	free(a);
}

int main(int argc, char * argv[]){
	
	FILE *in,*out,*linecounter;
	char line[MAX_LEN];
	int count=0;
	
	if(argc!=3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	linecounter=fopen(argv[1],"r");
	if(linecounter==NULL){
		printf("Unable to open file %s for reading\n",argv[1]);
		exit(1);
	}
	while(fgets(line,MAX_LEN,linecounter)!=NULL){
		count++;
	}
	fclose(linecounter);
	
	
	in=fopen(argv[1],"r");
	out=fopen(argv[2],"w");
	if(in==NULL){
		printf("Unable to open file %s for reading\n",argv[1]);
		exit(1);
	}
	if(out==NULL){
		printf("Unable to open file %s for writing\n",argv[2]);
		exit(1);
	}
	/*-------
	char **input=malloc(count * sizeof(char));
	for(int i=0;i<count;i++){
		input[i]=malloc(MAX_LEN * sizeof(char));
	}
	//---------*/
	char input[count][MAX_LEN];
	List L =newList();
	
	for(int i=0;fgets(line,MAX_LEN,in)!=NULL;i++){
		strcpy(input[i], line);
	}
	//strcat(input[count-1],"\n");
	
	/*printf("&d",sizeof(input)/sizeof(char));
	for(int i=1; fgets(line,MAX_LEN,in)!=NULL;i++){
		strncat(input[i],line,MAX_LEN);
		printf(input[i]);
		printf(line);
	}*/
	
	
	for(int i=0;i<count;i++){
		//printf("%d\n",
		if(length(L)==0){
			append(L,i);
		}else{
			moveFront(L);
			while(index(L)!=-1 && strcmp(input[i],input[get(L)])>0){
				moveNext(L);
			}
			if(index(L)==-1){
				append(L,i);
			}else{
				insertBefore(L,i);
			}
		}
	}

	moveFront(L);
	while(index(L)!=-1){
		fprintf(out,input[get(L)]);
		moveNext(L);
	}
	
	//freeArray(input,count);
	freeList(&L);
	//clear(L);
	fclose(in);
	fclose(out);
	return 0;
}