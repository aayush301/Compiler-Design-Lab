// Write a program to design Finite Automata that accepts all strings ending with “ing”, over ∑= a to z. (example “anything”, “something”, “nothing”, etc.)

#include<iostream>
#include<vector>
using namespace std;

class DFA
{
	int numOfStates;
	vector<char>alphabet;
	int initialState;
	int finalState;
	vector<vector<int>>transitionFn;
	
	public:
	DFA()
	{
		numOfStates = 4;
		initialState = 0;
		finalState = 3;
		constructTransitionFn();
	}
	
	void constructTransitionFn()
	{
		// Starting with q0
		transitionFn = vector<vector<int>>(numOfStates, vector<int>(26, -1));
		transitionFn[0]['i'-'a'] = 1;
		for (int i = 0; i < 26; i++)
		{
			if(i == ('i'-'a'))
				continue;
			transitionFn[0][i] = 0;
		}
		
		
		// Starting with q1
		transitionFn[1]['i'-'a'] = 1;
		transitionFn[1]['n'-'a'] = 2;
		for (int i = 0; i < 26; i++)
		{
			if(i == ('i'-'a') or i == ('n'-'a'))
				continue;
			transitionFn[1][i] = 0;
		}
		
		
		// Starting with q2
		transitionFn[2]['i'-'a'] = 1;
		transitionFn[2]['g'-'a'] = 3;
		for (int i = 0; i < 26; i++)
		{
			if(i == ('i'-'a') or i == ('g'-'a'))
				continue;
			transitionFn[2][i] = 0;
		}
		
		
		// Starting with q3
		transitionFn[3]['i'-'a'] = 1;
		for (int i = 0; i < 26; i++)
		{
			if(i == ('i'-'a'))
				continue;
			transitionFn[3][i] = 0;
		}
		
	}
	
	bool accepts(string str)
	{
		int currState = initialState;
		for(char c:str)
		{
			currState = transitionFn[currState][c-'a'];
		}
		
		return currState == finalState;
	}
};



int main()
{
	
	cout<<"\n----------- Aayush 2K19/CO/009 -----------\n";
	cout<<"DFA to accept all strings ending with 'ing'\n\n";
	
	
	DFA fa;
	string str;
	while(true)
	{
		cout<<"Enter string (# to stop):   ";
		cin>>str;
		if(str=="#")
			break;
		bool b = fa.accepts(str);
		if(b)
			cout<<"Accepted"<<endl<<endl;
		else
			cout<<"Not accepted"<<endl<<endl;
	}
	
}
