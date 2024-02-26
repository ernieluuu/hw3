#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot)
{
	if (head != nullptr)
	{
		// recursive statement
		llpivot(head->next, smaller, larger, pivot);

		if (head->val <= pivot)
		{
			Node* temp = new Node(head->val, smaller);
			smaller = temp;
			delete head;
			return;
		}

		if (head->val > pivot)
		{
			Node* temp = new Node(head->val, larger);
			larger = temp;
			delete head;
			return;
		}
	}
}