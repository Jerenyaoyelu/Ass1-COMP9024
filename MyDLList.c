#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct DLList{
	char data[255];
	struct DLList *next;
	struct DLList *prev;
};
//time_complexity:O(1)

struct DLList *createNode(char v[]){
	// create a variable in the heap of memory, 
	//this will stop this variable vanished when this function is finished(which local variable will do).
	struct DLList *new = (struct DLList*)malloc(sizeof(new));
	strcpy(new->data,v);
	new->next = NULL;
	new->prev =NULL;
	return new;
}
//time_complexity:O(1)

struct DLList *CreateDLListFromFileDlist(const char *filename){
	FILE *fp;
	char node_data[255];
	struct DLList *head = NULL;
	struct DLList *tail = NULL;
	if (strncmp(filename,"stdin", 5)==0){
		while(1){
			gets(node_data);
			if(strlen(node_data)==0){
				break;
			}
			struct DLList * newnode = createNode(node_data);//newnode here is a local variable which will be cleared after this function is done.
			if (head==NULL){
				head = newnode;
				tail = newnode;
			}else{
				tail->next = newnode;
				newnode->prev = tail;
				tail = tail->next;
			}
		}
	}else{
		fp=fopen(filename,"r");
		if(fp==NULL){
			printf("Error occurs when opening file!");
			return NULL;
		}
		while(1){
			// //fgetc read one char at a time(including space),read char assigned to an int
			// c=fgetc(fp);
			fscanf(fp,"%s",node_data);
			if(feof(fp)){
				break;
			}
			struct DLList * newnode = createNode(node_data);//newnode here is a local variable which will be cleared after this function is done.
			if (head==NULL){
				head = newnode;
				tail = newnode;
			}else{
				tail->next = newnode;
				newnode->prev = tail;
				tail = tail->next;
			}
		}
		fclose(fp);
	}
	return head;
}
//assume the len of DLL is n, then time_complexity:O(n)

void printDLList(struct DLList *u ){
	// This will cause "bus error:10", why??
	// while(u!=NULL){
	// 	printf("%s\n",u->data);
	// 	u = u->next;
	// }
	struct DLList *p = u;
	while(p!=NULL){
		printf("%s\n",p->data);
		p = p->next;
	}
}
//assume the len of DLL is n, then time_complexity:O(n)

struct DLList *cloneList(struct DLList *u){
	//question: when define copy_head with dynamic memory allocation(malloc()), the value of each node in the copied list canot be printed out.
	//why??
	struct DLList *copy_head;
	struct DLList *copy_tail;
	while (u!=NULL){
		struct DLList * newcopy = createNode(u->data);
		if (copy_head==NULL){
			copy_head = newcopy;
			copy_tail = newcopy;
		}else{
			copy_tail->next = newcopy;
			newcopy->prev = copy_tail;
			copy_tail = copy_tail->next;
		}
		u = u->next;
	}
	return copy_head;
}
//assume the len of DLL is n, then time_complexity:O(n)

bool ispresent(struct DLList *u, char data[255]){
	struct DLList *is = u;
	while(is !=NULL){
		if(strncmp(is->data, data, 255) == 0){	
			return 1;
		}
		is = is->next;
	}
	return 0;
}

struct DLList *setUnion(struct DLList *u, struct DLList *v){
	//it is not good to change the original lists.
	//so we need create a new list.
	struct DLList *ulist = NULL;
	struct DLList *p = u;
	// struct DLList *p2 = NULL;
	//BUG: when using clonelist function, causing segmentation fault!
	//result: cloned list mistakenly assigned to wrong pointer p2 instead of ulist!!
	ulist = cloneList(v);
	// while(p2 != NULL){
	// 	struct DLList * new = createNode(p2->data);
	// 	if(setU == NULL){
	// 		setU = new;
	// 	}else{
	// 		new->next = setU;
	// 		setU->prev = new;
	// 		setU = new;
	// 	}
	// 	p2 = p2->next;
	// }
	while(p != NULL){
		char newData[255];
		strcpy(newData,p->data);
		p = p->next;
		if(ispresent(v,newData)){
			continue;
		}else{
			struct DLList * new2 = createNode(newData);
			new2->next = ulist;
			ulist->prev = new2;
			ulist = new2;
		}
	}
	return ulist;
}


struct DLList *setIntersection(struct DLList *u, struct DLList *v){
	struct DLList *insec = NULL;
	struct DLList *t1 = u;
	while(t1!=NULL){
		if(ispresent(v,t1->data)){
			struct DLList * new = createNode(t1->data);
			if (insec == NULL){
				insec = new;
			}else{
				new->next = insec;
				insec->prev = new;
				insec = new;
			}
		}
		t1=t1->next;
	}
	return insec;
}

// when pointer is passed to a function as a parameter, the pointer canot be modified, because this is an outer pointer.
// in this case, we need to pass another pointer pointing to this one as the parameter, then we can modify this outer pointer inside this function.
// In the textbook, we dont have to pass a pointer of pointer to free the list, but here we do. 
// So my guess is because the head of the list is not defined in dynamic memory allocation, which free()becomes useless, 
// so we have to use a pointer of pointer to modify the head of the list.
// otherwise, no matter how, when printing head after this free() function, a 3 will be outputed just like what happened before.
// This guessing needs to be proved in future after gaining a better understanding of C.
void freeDLList(struct DLList **u){
	while((*u)!=NULL){
		struct DLList *temp = (*u)->next;
		free(*u);
		*u = temp;
	}
}
//assume the len of DLL is n, then time_complexity:O(n)

int main(void){
	char *f1 = "test.txt";
	char *f2 = "test2.txt";
	struct DLList *h;
	struct DLList *copy;
	struct DLList *su;
	struct DLList *si;
	struct DLList *t;
	h = CreateDLListFromFileDlist(f1);
	printf("\nThe doubly linked list is:\n");
	printDLList(h);
	printf("\n");
	copy = cloneList(h);
	printf("\nThe identical copied doubly linked list is:\n");
	printDLList(copy);
	
	freeDLList(&copy);
	printDLList(copy);

	printf("\nAnother doubly linked list is:\n");
	t = CreateDLListFromFileDlist(f2);
	printDLList(t);
	// printf("\nThe union of doubly linked lists is:\n");
	// su = setUnion(h, t);
	// printDLList(su);
	printf("\nThe intersection of doubly linked lists is:\n");
	si = setIntersection(h, t);
	printDLList(si);
	return 0;
}