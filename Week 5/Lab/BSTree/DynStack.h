#include "bstree.h"

struct StackNode {
	tnode* node;
	StackNode *next;
};

class DynStack {
private:
	StackNode *top;

public:
	DynStack(void);
	void push(tnode*);
	void pop(tnode* &);
	bool isEmpty(void);
};
