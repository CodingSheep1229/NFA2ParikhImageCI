#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include "ExpTree.h"

using namespace std;


bool 
ExpTree::already(string c)
{
	for (size_t i=0;i<var.size();i++)
	{
		if (c == var[i])
			return true;
	}
	return false;
}

bool isOperator(string c)
{
    if (c == "+" || c == "-" || c == "=" || c == "and" || c == "or" || c == "not" || c == "xor")
    {
        
        return true;
    }
        
    return false;
}

bool isNumber(string c)
{
	for (size_t i=0;i<c.length();i++)
	{
		if ((int)(c[i]) < 48 || (int)(c[i]) > 57)
			return false;
	}
	return true;
}

string
ExpTree::preorder(et *t)
{
    string ans = "";
	if(t)
    {
    	if (t->left || t->right)
    		ans += "(";
    	ans += t->value;
    	ans += " ";
    	if (t->left)
        	ans += preorder(t->left);       
        if (t->right)
        	ans += preorder(t->right);
		if (t->left || t->right)
        	ans += ")";
    }
    return ans;
}

ExpTree::ExpTree(vector<string> postfix)
{
    stack<et *> st;
    et *t, *t1, *t2;

    for (int i=0; i< postfix.size(); i++)
    {
        if (!isOperator(postfix[i]))
        {
        	if (!isNumber(postfix[i]) && !already(postfix[i]))
        		var.push_back(postfix[i]);
            t = new et(postfix[i]);
            st.push(t);
        }
        else
        {

            t = new et(postfix[i]);
            t1 = st.top();
            st.pop();
            t2 = st.top();
            st.pop();

            t->right = t1;
            t->left = t2;

            st.push(t);
        }
    }
    t = st.top();
    st.pop();
    root = t;
}

string
ExpTree::z3()
{
    string ans = "";
    string type;

    for (int i=0;i<var.size();i++)
    {
    	if (var[i][0] == 'x' || var[i][0] == 'r' || var[i][0] == 'i' || var[i][0] == 'o' || var[i][0] == 't')
    		type = "Int";
    	else
    		type = "Bool";
    	ans += "(declare-const " + var[i] + " "+ type + ")\n";
    }

    for (int i=0;i<var.size();i++)
    {
    	if (var[i][0] == 'x' || var[i][0] == 'r' || var[i][0] == 'i' || var[i][0] == 'o' || var[i][0] == 't')
    	{
    		ans += "(assert (>= "+ var[i] +" 0))\n";
    	}
    	if (var[i][0] == 't')
    	{
    		ans += "(assert (<= "+ var[i] +" 1))\n";
    	}
    }

    ans += "(assert ";
    ans += preorder(root);
    ans += ")\n";
  
    return ans;
}