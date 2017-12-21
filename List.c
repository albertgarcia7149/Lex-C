//-----------------------------------
//Albert Garcia
//awgarcia
//pa2
//-----------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//STRUCTS
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	Node head;
	Node tail;
	Node cursor;
	int length;
	int index;
}ListObj;

//NODE CONSTRUCTOR
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data=data;
	N->next=NULL;
	N->prev=NULL;
	return(N);
}
//NODE DESTRUCTOR
void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN=NULL;
	}
}
//LIST CONSTRUCTOR
List newList(void){
	List L;
	L=malloc(sizeof(ListObj));
	L->head=NULL;
	L->tail=NULL;
	L->cursor=NULL;
	L->index=-1;
	L->length=0;
	return(L);
}
//LIST DESTRUCTOR
void freeList(List* pL){
	if (pL!=NULL && *pL!=NULL){
		while(!isEmpty(*pL)){
			deleteBack(*pL);
		}
		free(*pL);
		*pL=NULL;
	}
}

//HELPER FUNCTION
int isEmpty(List L){
	if(L==NULL){
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
	}
	return(L->length==0);
}
//ACCESS FUNCTIONS
int length(List L){
	if(L==NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->length);
}
int index(List L){
	if(L==NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return(L->index);
}
int front(List L){
	if(L==NULL){
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	return(L->head->data);
}
int back(List L){
	if(L==NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}
	return(L->tail->data);
}
int get(List L){
	if(L==NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling get() on an empty List\n");
		exit(1);
	}
	if( L->index <0){
		printf("List Error: calling get() on undefined cursor (index=-1)\n");
		exit(1);
	}
	if (L->index > L->length){
		printf("List Error: calling get() on bad index (index>=length)\n");
		exit(1);
	}
	return(L->cursor->data);
}
int equals(List A,List B){
	int eq=0;
	Node N=NULL;
	Node M=NULL;
	
	if(A==NULL || B==NULL){
		printf("List Error: calling equals() on NULL Queue reference\n");
		exit(1);
	}
	
	eq=(A->length == B->length);
	N=A->head;
	M=B->head;
	while(eq && N!=NULL){
			eq= (N->data==M->data);
			N=N->next;
			M=M->next;
	}
//	freeNode(&N);
//	freeNode(&M);
	return eq;
}

	


//MANIPULATION PROCEDURES
void clear(List L){ //might not work--------------------------------------------------
	if(L==NULL){
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	while(!isEmpty(L)){
		deleteBack(L);
	}
	
	
//   free(&L);
	L=NULL; 
//	freeList(&L);
//	L=NULL;             
	
}
void moveFront(List L){
	if(L==NULL){
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if(!isEmpty(L)){
		L->index=0;
		L->cursor=L->head;
	}
	
}
void moveBack(List L){
	if(L==NULL){
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(1);
	}
	if(!isEmpty(L)){
		L->index=L->length-1;
		L->cursor=L->tail;
	}
}
void movePrev(List L){
	if(L==NULL){
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	if(L->cursor!=NULL){
		if(L->cursor==L->head){
			L->cursor=NULL;
			L->index=-1;
		}else{
			L->cursor=L->cursor->prev;
			L->index--;
		}
	}
}
void moveNext(List L){
	if(L==NULL){
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}
	if(L->cursor!=NULL){
		if(L->cursor==L->tail){
			L->cursor=NULL;
			L->index=-1;
		}else{
			L->cursor=L->cursor->next;
			L->index++;
		}
	}
}
void prepend(List L, int data){
	Node N = newNode(data);
	
	if(L==NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		L->head=N;
		L->tail=N;
	}else{
		N->next=L->head;
		L->head->prev=N;
		L->head=N;
		L->index++;
	}
	L->length++;
}
void append(List L,int data){
	Node N= newNode(data);
	
	if(L==NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		L->head=N;
		L->tail=N;
	}else{
		N->prev=L->tail;
		L->tail->next=N;
		L->tail=N;
	}
	L->length++;
}
void insertBefore(List L,int data){
	if(L==NULL){
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	if(!isEmpty(L) && L->index > -1){
		if(L->cursor == L->head){
			prepend(L,data);
		}else{
			Node N= newNode(data);
			L->cursor->prev->next=N;
			N->next=L->cursor;
			N->prev=L->cursor->prev;
			L->cursor->prev=N;
			L->index++;
			L->length++;
		}
	}
}
void insertAfter(List L,int data){
	if(L==NULL){
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}
	if(!isEmpty(L) && L->index >-1){
		if(L->cursor==L->tail){
			append(L,data);
		}else{
			Node N= newNode(data);
			L->cursor->next->prev=N;
			N->prev=L->cursor;
			N->next=L->cursor->next;
			L->cursor->next=N;
			L->length++;
		}
	}
}
void deleteFront(List L){
	if(L==NULL){
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);
	}else{
		Node N = NULL;
		N=L->head;
		if(length(L)>1){
			L->head=L->head->next;
			L->head->prev=NULL;
			L->index--;
			if(L->index==-1){
				L->cursor=NULL;
			}
		}else{
			L->head=NULL;
			L->tail=NULL;
			L->index=-1;
			L->cursor=NULL;
		}
		L->length--;
		freeNode(&N);
	}
}
void deleteBack(List L){
	if(L==NULL){
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling deleteBack() on an empty List\n");
        exit(1);
	}else{
		Node N = NULL;
		N=L->tail;
		if(length(L)>1){
			L->tail=L->tail->prev;
			L->tail->next=NULL;
			//N->prev=NULL;
			if(L->cursor==N){
				L->index=-1;
				L->cursor=NULL;
			}
		}else{
			L->head=NULL;
			L->tail=NULL;
			L->index=-1;
			L->cursor=NULL;
		}
		L->length--;
		freeNode(&N);
	}
}
void delete(List L){
	if(L==NULL){
		printf("List Error: calling delete() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling delete() on an empty List\n");
        exit(1);
	}
	if(L->index<0){
		printf("List Error: calling delete() with an undefined pointer (index=-1)\n");
	}
	if(L->cursor==L->tail){
		deleteBack(L);
	}else if(L->cursor==L->head){
		deleteFront(L);
	}else{
		Node A = NULL;
		Node B = NULL;
		Node N = L->cursor;
		A=L->cursor->prev;
		B=L->cursor->next;
		A->next=B;
		B->prev=A;
		L->cursor=NULL;
		L->index=-1;
		L->length--;
//		freeNode(&A);
//		freeNode(&B);
//		freeNode(&N);
	}
}
// Other operations 
void printList(FILE* out, List L){
	Node N =NULL;
	
	if(L==NULL){
		printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
	}
	for(N=L->head; N!=NULL; N=N->next){
		printf("%d ",N->data);
	}
	printf("\n");
//	 freeNode(&N);
}
List copyList(List L){
	List A = newList();
	Node N = NULL;
	
	if(L==NULL){
		printf("List Error: calling copyList() on NULL List reference\n");
        exit(1);
	}
	for(N=L->head; N!=NULL; N=N->next){
		append(A,N->data);
	}
//	freeNode(&N);
	return A;
}

