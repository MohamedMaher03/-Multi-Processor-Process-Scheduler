#pragma once

class TreeNode
{
private:
	int data;
	TreeNode* left;
	TreeNode* right;
public:
	TreeNode(int val);
	void setdata(int d);
	int getdata();
	void setright( TreeNode* p);
	TreeNode*& getright();
	void setleft(TreeNode* p);
	TreeNode*& getleft();


};


