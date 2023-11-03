#ifndef _BTREE
#define _BTREE

class tnode {
 public:
   int val;
   tnode *left;
   tnode *right;
};

class bstree {
 public:
   bstree();
   bstree(const bstree & tree);
   ~bstree();

   bool search(int Value);
   void insert(int Value);
   void printInOrderIterative();
   void printInOrderRecursive();

 private:
   void dhelper(tnode * Tree);
   void phelper(tnode * Tree);
   bool shelper(int Value, tnode * Tree);
   bool ihelper(int Value, tnode * &Tree);

   tnode *root;
};
#endif