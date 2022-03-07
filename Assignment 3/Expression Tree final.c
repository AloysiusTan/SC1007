#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}

void createExpTree(BTNode** root,char* prefix)
{
  // First check if the root is an operator or operand.
  char c = *prefix;
  if (c != '+' && c != '-' && c != '*' && c != '/') {
    // c is an operand only!
    int currnum = 0;
    for (int i = 0; prefix[i] != '\0'; i++) {
      if (prefix[i] != ' ') {
        currnum *= 10;
        currnum += prefix[i] - '0';
      }
    }
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->item = currnum;
    node->left = NULL;
    node->right = NULL;
    *root = node;
    return;
  }

  // The root is certainly an operator.

  // Set up the stack first. The stack will keep track of the path from the root to the current working operand.
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->size = 0;
  stack->head = NULL;

  // Process the chars one by one.
  BTNode *node;
  BTNode *parent;
  int currnum = -1;
  for (int i = 0; prefix[i] != '\0'; i++) {
    char c = prefix[i];
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      // c is an operator (internal node)
      node = (BTNode *)malloc(sizeof(BTNode));
      node->item = (int)c;
      node->left = NULL;
      node->right = NULL;
      if (isEmptyStack(*stack)) {
        // This is the first operator - will be the root.
        *root = node;
      } else {
        // Not the first operator! link it to the previous node.
        parent = peek(*stack);
        if (parent->left == NULL) parent->left = node;
        else parent->right = node;
      }
      push(stack, node);
    } else if (c == ' ') {
      if (currnum != -1) {
        // Finished reading an operand.
        node = (BTNode *)malloc(sizeof(BTNode));
        node->item = currnum;
        node->left = NULL;
        node->right = NULL;
        parent = peek(*stack);
        if (parent == NULL) { return; } // Error
        if (parent->left == NULL) parent->left = node;
        else {
          parent->right = node;
          // keep popping until either the stack is empty or the top stack node has a NULL right subtree.
          while (!isEmptyStack(*stack) && peek(*stack)->right != NULL) pop(stack);
        }
        // Reset currnum.
        currnum = -1;
      }
    } else {
      if (currnum == -1) currnum = c - '0';
      else {
        currnum *= 10;
        currnum += c - '0';
      }
    }
  }
  // Done, now just finish the last operand
  if (currnum == -1) { return; } // Error
  node = (BTNode *)malloc(sizeof(BTNode));
  node->item = currnum;
  node->left = NULL;
  node->right = NULL;
  parent = peek(*stack);
  if (parent == NULL || parent->left == NULL) { return; } // Error
  parent->right = node;
  while (!isEmptyStack(*stack) && peek(*stack)->right != NULL) pop(stack);

  if (!isEmptyStack(*stack)) { return; } // Error
  free(stack);
}

void printTree(BTNode *node){
    if (node->left == NULL) {
      // operand
      printf("%d", node->item);
    } else {
      // operand
      printTree(node->left);
      printf(" %c ", (char)node->item);
      printTree(node->right);
    }
}


void printTreePostfix(BTNode *node){
  if (node->left == NULL) {
    // operand
    printf("%d", node->item);
  } else {
    // operand
    printTreePostfix(node->left);
    printf(" ");
    printTreePostfix(node->right);
    printf(" %c", (char)node->item);
  }
}

double computeTree(BTNode *node){
  if (node->left == NULL) {
    // operand
    return (double)node->item;
  } else {
    // operator
    char operator = (char)node->item;
    double left = computeTree(node->left);
    double right = computeTree(node->right);
    if (operator == '+') return left + right;
    if (operator == '-') return left - right;
    if (operator == '*') return left * right;
    if (operator == '/') return left / right;
  }
}
