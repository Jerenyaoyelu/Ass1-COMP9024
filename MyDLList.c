#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<string.h>
#include<stdbool.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
	int  value;  // value (int) of this list item 
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
	int  size;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	DLList *L;

	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here
DLList *CreateDLListFromFileDlist(const char *filename)
{
	FILE *fp;
	char data_string[255];
	DLList *L;
	L = newDLList();

	if (strncmp(filename,"stdin", 5)==0){
		while(1){
			gets(data_string);
			if(strlen(data_string)==0){
				break;
			}
			DLListNode *newnode;
			newnode = newDLListNode(atoi(data_string));
			if (L->size ==0){
				L->first = newnode;
				L->last = newnode;
			}else{
				newnode->next = L->first;
				L->first->prev = newnode;
				L->first = newnode;
			}
			L->size ++;
		}
	}else{
		fp=fopen(filename,"r");
		if(fp==NULL){
			printf("Error occurs when opening file!");
			return NULL;
		}
		while(1){
			fscanf(fp,"%s",data_string);
			if(feof(fp)){
				break;
			}
			DLListNode *newnode;
			newnode = newDLListNode(atoi(data_string));
			if (L->size ==0){
				L->first = newnode;
				L->last = newnode;
			}else{
				newnode->next = L->first;
				L->first->prev = newnode;
				L->first = newnode;
			}
			L->size ++;
		}
		fclose(fp);
	}
	return L;
  
}

// clone a DLList
// put your time complexity analysis for cloneList(): O(L->size)
DLList *cloneList(DLList *u)
{
	DLList *L;
	L = newDLList();
	if (u->size == 0){
		return L;
	}else{
		DLListNode *current = u->first;
		while (current != NULL){
			DLListNode *newnode;
			newnode = newDLListNode(current->value);
			if (L->size ==0){
				L->first = newnode;
				L->last = newnode;
			}else{
				newnode->next = L->first;
				L->first->prev = newnode;
				L->first = newnode;
			}
			L->size ++;
			current  = current ->next;
		}
		return L;
	}
}

bool ispresent(DLList *u, int value){
	DLListNode *is = u->first;
	while(is != NULL){
		if(is->value == value){	
			return 1;
		}
		is = is->next;
	}
	return 0;
}

// compute the union of two DLLists u and v
DLList *setUnion(DLList *u, DLList *v)
{
	DLList *union_L;
	union_L = newDLList();
	DLListNode *current = u->first;
	union_L = cloneList(v);

	while(current != NULL){
		int newdata;
		newdata = current->value;
		current = current->next;
		if(ispresent(v,newdata)){
			continue;
		}else{
			DLListNode *newnode;
			newnode = newDLListNode(newdata);
			newnode->next = union_L->first;
			union_L->first->prev = newnode;
			union_L->first = newnode;
		}
		union_L->size ++;
	}
	return union_L;
}

// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here
DLList *setIntersection(DLList *u, DLList *v)
{
	DLList *intersection_L;
	intersection_L = newDLList();
	DLListNode *current = u->first;
	while(current!=NULL){
		if(ispresent(v,current->value)){
			DLListNode *newnode;
			newnode = newDLListNode(current->value);
			if (intersection_L->size == 0){
				intersection_L ->first = newnode;
			}else{
				newnode->next = intersection_L ->first;
				intersection_L ->first->prev = newnode;
				intersection_L ->first = newnode;
			}
			intersection_L->size++;
		}
		current=current->next;
	}
	return intersection_L;
}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here
void freeDLList(DLList *L)
{
	while(L->first != NULL){
		DLListNode * temp = L->first->next;
		free(L->first);
		L->first = temp;
	}
}


// display items of a DLList
// put your time complexity analysis for printDDList(): O(u->size)
void printDLList(DLList *u)
{
	DLListNode *p;
	p = u->first;
	while(p!=NULL){
		printf("%d\n",p->value);
		p = p->next;
	}
}

int main()
{
 DLList *list1, *list2, *list3, *list4;

 list1=CreateDLListFromFileDlist("File1.txt");
 printDLList(list1);

 list2=CreateDLListFromFileDlist("File2.txt");
 printDLList(list2);

 list3=setUnion(list1, list2);
 printDLList(list3);

 list4=setIntersection(list1, list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 printf("please type all the integers of list1\n");
 list1=CreateDLListFromFileDlist("stdin");

 printf("please type all the integers of list2\n");
 list2=CreateDLListFromFileDlist("stdin");

 list3=cloneList(list1);
 printDLList(list3);
 list4=cloneList(list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 return 0; 
}
