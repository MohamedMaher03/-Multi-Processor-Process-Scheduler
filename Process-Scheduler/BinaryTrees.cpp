#include "BinaryTrees.h"
#include <iostream>
using namespace std;


// Given functions
	void BinaryTrees:: rec_insert(TreeNode*& subRoot,int value)
	{
		if (subRoot == nullptr)
			subRoot = new TreeNode(value);
		else if (subRoot->getleft())
		{

			//recursively call insert for the right subtree
			rec_insert(subRoot->getright(), value);

		}
		else
		{
			// recursive call on left
			rec_insert(subRoot->getleft(), value);
		}
	}




//* Deletes all the nodes in the tree.
// [Note]: subRoot is passed by ref because 
//         after deleting subRoot node we will make it point to nullptr (change subRoot)
void BinaryTrees::rec_destroy_tree(TreeNode*& subRoot)
{
	if (subRoot != nullptr)
	{
		// recursive call on left
		rec_destroy_tree(subRoot->getleft());

		// recursive call on right
		rec_destroy_tree(subRoot->getright());

		delete subRoot;
		subRoot = nullptr; // this line is why we pass subRoot by reference (subRoot = something)
	}
}




void BinaryTrees::rec_printBT(const std::string& prefix, TreeNode* node, bool isLeft)
{
	if (node != nullptr)
	{
		cout << prefix;

		cout << (isLeft ? "├─L─" : "└─R─");

		// print the value of the node
		cout << "(" << node->getdata() << ") " << std::endl;
		//string 
		// enter the next tree level - left and right branch
		rec_printBT(prefix + (isLeft ? "│   " : "    "), node->getleft(), true);
		rec_printBT(prefix + (isLeft ? "│   " : "    "), node->getright(), false);
	}
}



BinaryTrees::BinaryTrees()
{
	root = nullptr;
}


BinaryTrees::~BinaryTrees()
{
	destroy_tree();
}

// Public Functions ---------------------------------

// Given functions
void BinaryTrees::insert(int value) // not const
{
	// not const because rec_insert takes the root by reference, so may change it
	rec_insert(root, value);
}


void BinaryTrees::destroy_tree() // not const
{
	// not const because rec_destroy_tree takes the root by reference, so may change it
	rec_destroy_tree(root);
}

void BinaryTrees::deleteValueAndDescendants(int value)
{
	rec_deleteValueAndDescendants(root, value);
}

void BinaryTrees::printBT()
{
	cout << "\nPrinting BT, L means Left Child, R means Right Child (or Root)\n";
	rec_printBT("", root, false);
	cout << endl;
}


TreeNode* BinaryTrees::getRoot()
{
		return root;
}

void BinaryTrees::rec_deleteValueAndDescendants(TreeNode* subtree, int value) {
	if (subtree == NULL) {
		return;
	}

	if (value < subtree->getdata()) {
		rec_deleteValueAndDescendants(subtree->getleft(), value);
	}
	else if (value > subtree->getdata()) {
		rec_deleteValueAndDescendants(subtree->getright(), value);
	}
	else {
		rec_destroy_tree(subtree);
		subtree= NULL;
	}

	return;
}