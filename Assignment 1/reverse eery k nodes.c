#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

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


	reverseKNodes(&head, K);
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

void reverseKNodes(ListNode** head, int K){
  // Check that we have k nodes to reverse.
  if (K <= 0) return;
  ListNode* curr = *head;
  for (int i = 0; i < K; i++) {
      if (curr == NULL) return;
      curr = curr->next;
  }
  ListNode* nexthead = curr;
  // perform the reversal for the first k nodes.
  ListNode* pred = NULL;
  curr = *head;
  ListNode* succ = (*head)->next;
  for (int i = 0; i < K; i++) {
      if (i == 0) curr->next = nexthead;
      else curr->next = pred;
      if (i < K-1) {
          pred = curr;
          curr = succ;
          succ = succ->next;
      }
  }
  // revursively reverse the remainder of the nodes
  reverseKNodes(&((*head)->next), K);
  *head = curr;
}
