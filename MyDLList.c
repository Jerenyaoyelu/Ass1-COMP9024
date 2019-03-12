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
	char *s;
	struct DLList *head;
	struct DLList *tail;
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
		if(is->data == data){
			return 1;
		}
		is = is->next;
	}
	return 0;
}

struct DLList *setUnion(struct DLList *u, struct DLList *v){
	struct DLList *p = u;
	while(p!=NULL){
		struct DLList *temp = p;
		p = p->next;
		if(p!=NULL){
			p->prev = NULL;
		}
		temp->next = NULL;
		if(ispresent(v,temp->data)){
			continue;
		}else{
			temp->next = v;
			v->prev = temp;
			v = temp;
		}
	}
	return v;
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
	char *filename = "test.txt";
	struct DLList *h;
	struct DLList *copy;
	struct DLList *su;
	struct DLList *si;
	struct DLList *t;
	// h = CreateDLListFromFileDlist(filename);
	// printf("The doubly linked list is:\n");
	// printDLList(h);
	// printf("\n");
	// copy = cloneList(h);
	// printf("The identical copied doubly linked list is:\n");
	// printDLList(copy);
	
	// freeDLList(&copy);
	// printDLList(copy);

	//problem: when running setunion and setintersection, no out.
	h = CreateDLListFromFileDlist(filename); 
	t = CreateDLListFromFileDlist(filename);
	t = CreateDLListFromFileDlist(filename);
	t = CreateDLListFromFileDlist(filename);
	printDLList(t);
	// su = setUnion(h, t);
	// // si = setIntersection(h, t);
	// printDLList(su);
	return 0;
}