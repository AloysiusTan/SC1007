#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll){
  if (ll.size <= 1) return ll;
  ListNode* head = ll.head;
  int leftsize = ll.size / 2;
  // First rearrangement
  ListNode* lefthead = head;
  ListNode* righthead = head;
  ListNode* leftend = NULL;
  for (int i = 0; i < leftsize; i++) {
    // find the righthead
    leftend = righthead;
    righthead = righthead->next;
  }
  leftend->next = NULL;
  ListNode* pred = righthead;
  ListNode* succ = righthead->next;
  while (lefthead != NULL) {
    // insert the lefthead in between pred and succ
    pred->next = lefthead;
    lefthead = lefthead->next;
    pred->next->next = succ;
    pred = succ;
    if (succ != NULL) succ = succ->next;
  }
  head = righthead;
  // Second rearrangement
  lefthead = head;
  righthead = head;
  leftend = NULL;
  for (int i = 0; i < leftsize; i++) {
    // find the righthead
    leftend = righthead;
    righthead = righthead->next;
  }
  leftend->next = NULL;
  pred = lefthead;
  succ = lefthead->next;
  while (succ != NULL) {
    // insert the righthead in between pred and succ
    pred->next = righthead;
    righthead = righthead->next;
    pred->next->next = succ;
    pred = succ;
    succ = succ->next;
  }
  pred->next = righthead;
  ll.head = lefthead;
  return ll;
}
