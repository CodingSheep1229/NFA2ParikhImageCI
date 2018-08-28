#include "NFA.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "ExpTree.h"
#include <sstream>

using namespace std;

bool in(vector<string> v,string s)
{
	for (int i=0;i<v.size();i++)
		if (s == v[i])
			return true;
	return false;
}

void print(vector<string> v)
{
	cout << "[";
	for (size_t i=0;i<v.size()-1;i++)
	{
		cout << v[i] << ", ";
	}
	cout << v[v.size()-1] << "]\n";
}

NFA::NFA(string raw)
{
	map<string, states*>::iterator iter;
	map<string, states*>::iterator iter2;
	int n1,n2,n3,n4;
	string str,str2;
	string c;

	stringstream file;

	file.str(raw);

	file >> n1 >> n2 >> n3 >> n4;

	for (int i=0;i<n1;i++)
	{
		file >> str;
		Q.push_back(str);
		states* temp = new states;
		temp->name = str;
		temp->connect = false;
		connected[str] = temp;
	}
	file >> str;
	q0 = str;
	iter = connected.find(str);
	iter->second->connect = true;
	
	st.push(iter->second);

	for (int i=0;i<n2;++i)
	{
		file >> str;
		T.push_back(str);
	}
	for (int i=0;i<n3;++i)
	{
		file >> c;
		sigma.push_back(c);
	}
	for (int i=0;i<n4;i++)
	{
		file >> str >> c >> str2;
		transition t;
		t.p = str;
		t.a = c;
		t.q = str2;
		transitions.push_back(t);
		if (str!=str2)
		{
			iter = connected.find(str);
			iter2 = connected.find(str2);
			iter->second->next.push_back(iter2->second);
		}
		
	}
}

void
NFA::setX(vector<string>& v)
{
	for (size_t i=0;i<sigma.size();i++)
	{
		int cnt = 0;
		v.push_back("r_"+sigma[i]);
		for (size_t j=0;j<transitions.size();j++)
		{
			if (transitions[j].a == sigma[i])
			{
				v.push_back("x_"+ transitions[j].p + "_" + sigma[i] + "_" + transitions[j].q);
				cnt++;
			}
		}
		if (!cnt)
			v.push_back("0");
		for (int j=1;j<cnt;j++)
		{
			v.push_back("+");
		}
		v.push_back("=");

		if (i != 0)
			v.push_back("and");
	}
}

void
NFA::setOut(vector<string>& v)
{
	for (size_t i=0;i<Q.size();i++)
	{
		int cnt = 0;
		v.push_back("out_"+Q[i]);
		for (size_t j=0;j<transitions.size();j++)
		{
			if (transitions[j].p == Q[i])
			{
				v.push_back("x_"+ transitions[j].p + "_" + transitions[j].a + "_" + transitions[j].q);
				cnt++;
			}
		}
		if (!cnt)
			v.push_back("0");
		for (int j=1;j<cnt;j++)
		{
			v.push_back("+");
		}
		v.push_back("=");
		v.push_back("and");
	}
}

void
NFA::setIn(vector<string>& v)
{
	for (size_t i=0;i<Q.size();i++)
	{
		int cnt = 0;
		v.push_back("in_"+Q[i]);
		for (size_t j=0;j<transitions.size();j++)
		{
			if (transitions[j].q == Q[i])
			{
				v.push_back("x_"+ transitions[j].p + "_" + transitions[j].a + "_" + transitions[j].q);
				cnt++;
			}
		}
		if (!cnt)
			v.push_back("0");
		for (int j=1;j<cnt;j++)
		{
			v.push_back("+");
		}
		v.push_back("=");

		v.push_back("and");
	}
}

void
NFA::setStart(vector<string>& v)
{
	for (size_t i=0;i<Q.size();i++)
	{
		if (Q[i] == q0)
		{
			v.push_back("start_"+Q[i]);
			v.push_back("and");
		}
		else
		{
			
			v.push_back("");
			v.push_back("start_"+Q[i]);
			v.push_back("not");
			v.push_back("and");
		}	
	}
}

void
NFA::setT(vector<string>& v)
{
	for (size_t i=0;i<Q.size();i++)
	{
		if (!in(T,Q[i]))
		{
			v.push_back("t_"+Q[i]);
			v.push_back("0");
			v.push_back("=");
			v.push_back("and");
		}
	}

	int cnt = 0;
	v.push_back("1");
	for (size_t i=0;i<T.size();i++)
	{
		v.push_back("t_"+T[i]);
		cnt++;
	}
	for (int i=1;i<cnt;i++)
	{
		v.push_back("+");
	}
	v.push_back("=");
	v.push_back("and");
}

void
NFA::setFlag(vector<string>& v)
{
	for (size_t i=0;i<Q.size();i++)
	{
		v.push_back("flag_"+Q[i]+"_1");
		v.push_back("flag_"+Q[i]+"_2");
		v.push_back("or");
		v.push_back("flag_"+Q[i]+"_3");
		v.push_back("or");
		v.push_back("and");
		v.push_back("flag_"+Q[i]+"_1");
		v.push_back("start_"+Q[i]);
		v.push_back("");
		v.push_back("not");
		v.push_back("t_"+Q[i]);
		v.push_back("1");
		v.push_back("=");
		v.push_back("and");
		v.push_back("in_"+Q[i]);
		v.push_back("out_"+Q[i]);
		v.push_back("1");
		v.push_back("+");
		v.push_back("=");
		v.push_back("and");
		v.push_back("=");
		v.push_back("and");
		v.push_back("flag_"+Q[i]+"_2");
		v.push_back("start_"+Q[i]);
		v.push_back("t_"+Q[i]);
		v.push_back("0");
		v.push_back("=");
		v.push_back("and");
		v.push_back("in_"+Q[i]);
		v.push_back("out_"+Q[i]);
		v.push_back("1");
		v.push_back("-");
		v.push_back("=");
		v.push_back("and");
		v.push_back("=");
		v.push_back("and");
		v.push_back("flag_"+Q[i]+"_3");
		v.push_back("in_"+Q[i]);
		v.push_back("out_"+Q[i]);
		v.push_back("=");
		v.push_back("start_"+Q[i]);
		v.push_back("t_"+Q[i]);
		v.push_back("1");
		v.push_back("=");
		v.push_back("xor");
		v.push_back("");
		v.push_back("not");
		v.push_back("and");
		v.push_back("=");
		v.push_back("and");
	}
}

void
NFA::checkConnected(vector<string>& v)
{
	while(!st.empty())
	{
		states* temp = st.top();
		st.pop();
		temp->connect = true;
		size_t sizee = temp->next.size();
		for (size_t i=0;i<sizee;i++)
		{
			st.push(temp->next[i]);
			//cout << temp->name << endl;
		}
	}
	for(map<string,states*>::iterator iterr = connected.begin(); iterr != connected.end(); iterr++)
	{
		if (!iterr->second->connect)
		{
			v.push_back("out_"+iterr->first);
			v.push_back("0");
			v.push_back("=");
			v.push_back("and");
		}
	}
}

string
NFA::ParikhImage()
{
	vector<string> v;
	setX(v);
	setOut(v);
	setIn(v);
	setStart(v);
	setT(v);
	setFlag(v);
	checkConnected(v);

	ExpTree tree(v);
	string ans = tree.z3();

	ans += "(check-sat)\n";
	ans += "(get-model)\n";
	return ans;
}

string
test(string str)
{
	NFA nfa(str);
	string ans = nfa.ParikhImage();
	return ans;
}