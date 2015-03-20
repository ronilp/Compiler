struct tree
{
  int children;
  int childID;
  char *data;
  struct tree **child;
  struct tree *parent;
};

extern void preorder(struct tree *p,FILE *fp);

extern struct tree *search(struct tree* root, char *data);

extern struct tree *createNode(char *data);

extern struct tree *insert(struct tree *parent, char *data,int numchildren);

extern struct tree *setChildren(struct tree *parent, int children);

struct tree *getNextPreorder(struct tree *p);
