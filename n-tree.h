struct tree
{
  int data;
  struct tree *child;
  struct tree *sibling;
};

extern void preorder(struct tree *p);

extern struct tree *search(struct tree* root, int data);

extern struct tree *createNode(int data);

extern struct tree *createnary(struct tree* root, int data[]);
