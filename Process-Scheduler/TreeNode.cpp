#include "TreeNode.h"

TreeNode:: TreeNode(int val)
{
	data = val;
	left = right = nullptr;
}


void TreeNode::setdata(int d)
{
	data = d;
}
int TreeNode::getdata()
{
	return data;
}
void TreeNode::setleft(TreeNode* p)
{
	left = p;
}
TreeNode*& TreeNode::getleft()
{
	return left;
}
void TreeNode::setright(TreeNode* p)
{
	right = p;
}
TreeNode*& TreeNode::getright()
{
	return right;
}

