#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include "ExpTree.h"

#ifndef NFA_H
#define NFA_H

using namespace std;

string test(string str);

struct transition
{
	string p;
	string a;
	string q;
};

struct states
{
	string name;
	vector<states*> next;
	bool connect;
};

class NFA
{
public:
	NFA(){}
	NFA(string filename);
	string ParikhImage();

private:
	void setX(vector<string>& v);
	void setOut(vector<string>& v);
	void setIn(vector<string>& v);
	void setStart(vector<string>& v);
	void setT(vector<string>& v);
	void setFlag(vector<string>& v);
	void checkConnected(vector<string>& v);

	vector<string> Q;
	vector<string> sigma;
	string q0;
	vector<string> T;
	vector<transition> transitions;
	stack<states*> st;
	map<string,states*> connected;
};



#endif
