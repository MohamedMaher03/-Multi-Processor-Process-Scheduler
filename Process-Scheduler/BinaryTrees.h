#pragma once

#include "TreeNode.h"
#include <string>
#include <iostream>
using namespace std;

class BinaryTrees
{
private:
	TreeNode* root;

	// Utility Functions - Recursive Functions --------------------------

	// Given functions
	static void rec_insert(TreeNode*& subRoot, int value);
	static void rec_destroy_tree(TreeNode*& subRoot);
	void rec_deleteValueAndDescendants(TreeNode* subtree, int value);
	void rec_printBT(const std::string& prefix, TreeNode* node, bool isLeft);


public:
	void printBT();

	// [Note]: in the above utility functions:
	// we made them static --
	// because they don't need an object of BSTree to be executed
	// in otherwords, they don't can't with the non-static data members of BSTree (the "root" data member)
	// this is a way that will prevent you from: 
	// using "root" instead of the passed "subRoot" by mistake  -> syntax error

public:
	BinaryTrees(void);
	~BinaryTrees(void);

	// Public Functions --------------------------

	// Given functions
	void insert(int value); 

	void destroy_tree(); // not const
	void deleteValueAndDescendants( int value);

	TreeNode* getRoot();

};


