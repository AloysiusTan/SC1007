#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);

    printf("%c",cur->id);
}

void buildTree(BTNode** node, char* preO, char* postO)
{
  // First create the root node which is the first character of preO and last character of postO.
  BTNode* root = (BTNode*)malloc(sizeof(BTNode));
  *node = root;
  root->id = *preO;
  // n = strlen(preO)
  int n = 0;
  while (preO[n] != '\0') n++;
  if (n == 1) {
    root->left = NULL;
    root->right = NULL;
  }
  else {
    // There is at least one child, look for the left id in the postO string.
    char leftid = preO[1];
    int i = 0;
    while (postO[i] != leftid) i++;
    i++;
    char preOnew[MAX_N];
    char postOnew[MAX_N];
    // strncpy(preOnew, &preO[1], i);
    for (int x = 0; x < i; x++) preOnew[x] = preO[1+x];
    preOnew[i] = '\0';
    // strncpy(postOnew, postO, i);
    for (int x = 0; x < i; x++) postOnew[x] = postO[x];
    postOnew[i] = '\0';
    buildTree(&root->left, preOnew, postOnew); // Build the left subtree.
    int j = n - i - 1;
    if (j == 0) {
      root->right = NULL;
    }
    else {
      // There is at least one member of the right child!
      // strncpy(preOnew, &preO[1+i], j);
      for (int x = 0; x < j; x++) preOnew[x] = preO[1+i+x];
      preOnew[j] = '\0';
      // strncpy(postOnew, &postO[i], j);
      for (int x = 0; x < j; x++) postOnew[x] = postO[i+x];
      postOnew[j] = '\0';
      buildTree(&root->right, preOnew, postOnew);
    }
  }
}
