#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>

using namespace std;

#ifndef ExpTree_H
#define ExpTree_H

class et
{
public:
	et(string v)
	{
		left = right = 0;
		value = v;
	}

friend class ExpTree;
private:
	string value;
    et* left, *right;
};


bool isOperator(string c);
bool isNumber(string c);

class ExpTree
{
public:
	ExpTree(){}
    ExpTree(vector<string> postfix);
    string z3();
    bool already(string c);

private:
	string preorder(et *t);
    et* root;
    vector<string> var;
};

#endif