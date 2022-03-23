 #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
struct node* bst(char arr[][128], int first, int last);
struct node * minValue(struct node* node);
  struct node{
        char word[128];
        struct node *left, *right,*parent;
  };

  struct node *root = NULL;
struct node* lastSuc=NULL;
struct node* lastPre=NULL;

  struct node * createNode(char *word) {
        struct node *newnode;
        newnode = (struct node *)malloc(sizeof(struct node));
        strcpy(newnode->word, word);
        newnode->left = newnode->right = newnode->parent= NULL;
        return newnode;
  }

  void insert(char *word) {
        struct node *parent = NULL, *current = NULL, *newnode = NULL;
        int res = 0;
        if (!root) {
                root = createNode(word);
                return;
        }
        for (current = root; current !=NULL;
           current = (res > 0) ? current->right : current->left) {
                res = strcasecmp(word, current->word);
                if (res == 0) {
                        printf("Duplicate entry!!\n");
                        return;
                }
                parent = current;
        }
        newnode = createNode(word);
        res > 0 ? (parent->right = newnode) : (parent->left = newnode);
        newnode->parent=parent;
        return;
  }
struct node* findPreSuc(struct node* r, char *key,int type)
{
    if (r == NULL)  return;

    if (strcasecmp(r->word,key)==0)
    {
        if (r->left != NULL&&type==1)
        {
            struct node* tmp = r->left;
            while (tmp->right)
            {
                tmp = tmp->right;
            }
            return tmp ;
        }

        if (r->right != NULL&&type==2)
        {
            struct node* tmp = r->right ;
            while (tmp->left)
            {
                tmp = tmp->left ;
            }

            return tmp ;
        }
        return NULL;
    }

    if (strcasecmp(r->word,key)==1)
    {
        lastSuc=r;
        return findPreSuc(r->left, key,type) ;
    }
    else
    {
        lastPre=r;
        return findPreSuc(r->right, key,type) ;
    }
}
  void findElement(char *str) {
        struct node *temp = NULL,*parent=NULL,*pre = NULL, *suc = NULL;
        int flag = 0, res = 0;
        if (root == NULL) {
                printf("Binary Tree is NULL");
                return;
        }
        temp = root;
        while (temp) {
                if ((res = strcasecmp(temp->word, str)) == 0) {
                        printf("Correct");
                        flag = 1;
                        break;
                }
                parent=temp;
                temp = (res > 0) ? temp->left : temp->right;
        }
        if (!flag)
        {
            printf("%s",parent->word);
            pre=findPreSuc(root,parent->word,1);
            suc=findPreSuc(root,parent->word,2);
            if (pre != NULL)
                printf(" %s",pre->word);
            else
                if(lastPre)
                    printf(" %s",lastPre->word);
                else
                    printf(" No Predecessor");

            if (suc != NULL)
                printf(" %s",suc->word);
            else
                if(lastPre)
                    printf(" %s",lastSuc->word);
                else
                    printf(" No Successor");
        }
        printf("\n");
        return;
  }
  void buildBalanced(){
    FILE *f;
    f=fopen("English-Dictionary.txt","r");
    char p[128];
    char a[3000][128];
    int b=0;
    while(!feof(f))
    {
        fscanf(f,"%s",&p);
        strcpy(a[b],p);
        b++;
    }
    root=bst(a,0,2999);
}
void build_UnBalanced(){
    FILE *f;
    f=fopen("English-Dictionary.txt","r");
    char p[128];
    while(!feof(f))
    {
        fscanf(f,"%s",&p);
        insert(p);
    }
}
struct node* bst(char arr[][128], int first, int last)
{
    int mid;
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (first > last)
        return NULL;
    mid = (first + last) / 2;
    strcpy(temp->word,arr[mid]);
    temp->left = bst(arr, first, mid - 1);
    temp->right = bst(arr, mid + 1, last);
    return temp;
}
int getDepth(struct node* node)
{
   if (node==NULL)
       return 0;
   else
   {
       int lDepth = getDepth(node->left);
       int rDepth = getDepth(node->right);

       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}
  int main() {
      buildBalanced();
      printf("Enter the Sentence: ");
      char w[128];
      int i=0;
      gets(w);
       char *pt;
            pt = strtok (w," ");
            findElement(pt);
            while(w[i]!='\0'){
            pt = strtok (NULL, " ");
            if(pt)
            findElement(pt);
            i++;
  }
      printf("\n----------------------------------------------------------------------------");
      printf("\nDepth of Tree: %d \nDepth of Left: %d \nDepth of Right: %d\n",getDepth(root),getDepth(root->right),getDepth(root->left));
        return 0;
  }
