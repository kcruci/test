#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>


typedef struct stNode{
        int data;
        stNode* next;
}Node;

Node * makelink();
Node * makesortlink();


void print_node(const Node * head);
Node * reverse(Node * head);

//递归
Node * recursion_merge(Node * head1, Node * head2);
Node * do_recursion(Node * head1, Node * head2);

Node * merge2(Node * head1, Node * head2);

Node * recursion_merge(Node * head1, Node * head2)
{
	if(!head1&&!head2) return NULL;

	if(!head1) return head2;
	if(!head2) return head1;

	Node* newhead = new Node();
	newhead->next = NULL;

	newhead->next = do_recursion(head1->next, head2->next);
	return newhead;
}


Node * do_recursion(Node * node1, Node * node2)
{
	if(!node1&&!node2) return NULL;

	if(!node1) return node2;
	if(!node2) return node1;
	if(node1->data <= node2->data)
	{
		node1->next = do_recursion(node1->next, node2);
		return node1;
	}
	else
	{
		node2->next = do_recursion(node1, node2->next);
		return node2;
	}
}

Node * reverse(Node * head)
{
	//head 泄漏
	if(!head) return NULL;
	
	Node* newhead = new Node();
	newhead->next = NULL;
	Node * current = head->next;
	Node * next = NULL;
	while(current)
	{
		next = current->next;
		current->next = newhead->next;
		newhead->next = current;
		current = next;
	}
	head  = newhead;

	return head;
}

void print_node(const Node * head)
{
	if(!head){
		fprintf(stderr, "head is null=================\n\n");
		return ;
	}
	Node * dataptr = head->next;
	fprintf(stderr, "print_node begin=================\n");
	while(dataptr)
	{
		fprintf(stderr, "%d\t", dataptr->data );
		dataptr = dataptr->next;
	}
	fprintf(stderr, "\nprint_node end=================\n\n");
}


Node * makesortlink(int count)
{
	if(count<=0) return NULL;

	Node* head = new Node();
	head->next = NULL;

	Node * curr  = head;

	for (int i = 0; i < count; ++i)
	{
		Node *newnode = new Node();
		newnode->data = i;
		curr->next  = newnode;
		curr = newnode;	/* code */
	}
	return head;

}


Node * makelink(int count)
{
	if(count<=0) return NULL;

	Node* head = new Node();
	head->next = NULL;

	Node * curr  = head;

	for (int i = 0; i < count; ++i)
	{
		Node *newnode = new Node();
		newnode->data = rand()%10;
		curr->next  = newnode;
		curr = newnode;	/* code */
	}
	return head;

}


int main(int argc, char * argv[])
{
	srand(time(NULL));
	Node * head = makelink(10);
	print_node(head);

	Node * newhead = reverse(head);

	print_node(newhead);


	Node * head1 = makesortlink(2);
	print_node(head1);
	Node * head2 = makesortlink(3);
	print_node(head2);

	Node * mergehead1 = recursion_merge(head1, head2);
	print_node(mergehead1);

	return 0;

}