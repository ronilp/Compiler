struct tree
{
  char *data;
  struct tree *child;
  struct tree *sibling;
};

extern void preorder(struct tree *p);

extern struct tree *search(struct tree* root, char *data);

extern struct tree *createNode(char *data);

struct tree *insert(struct tree *root, char *parent, char *data);
