#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	triPartition(&head, pivot);
	printList(head);
	deleteList(&head);

	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

void triPartition(ListNode** head, int pivot){
  ListNode* less = NULL;
  ListNode* lessend = NULL;
  ListNode* equal = NULL;
  ListNode* equalend = NULL;
  ListNode* greater = NULL;
  ListNode* greaterend = NULL;
  ListNode* ll = *head;
  ListNode* thisnode;
  if (ll == NULL) return;
  // Filter all the nodes into their respective categories (less, equal or
  // greater than pivot)
  while (ll != NULL) {
    thisnode = ll;
    ll = ll->next;
    if (thisnode->item < pivot) {
      if (less == NULL) {
        less = thisnode;
        lessend = thisnode;
      } else {
        lessend->next = thisnode;
        lessend = thisnode;
      }
    } else if (thisnode->item == pivot) {
      if (equal == NULL) {
        equal = thisnode;
        equalend = thisnode;
      } else {
        equalend->next = thisnode;
        equalend = thisnode;
      }
    } else {
      if (greater == NULL) {
        greater = thisnode;
        greaterend = thisnode;
      } else {
        greaterend->next = thisnode;
        greaterend = thisnode;
      }
    }
    thisnode->next = NULL;
  }
  // Reassemble the list by joining up less -> equal -> greater
  ListNode* newhead = less;
  ListNode* newend = lessend;
  if (newhead == NULL) {
    newhead = equal;
    newend = equalend;
  } else {
    if (equal != NULL) {
      newend->next = equal;
      newend = equalend;
    }
  }
  if (newhead == NULL) newhead = greater;
  else newend->next = greater;
  *head = newhead;
}
