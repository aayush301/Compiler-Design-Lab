// Write a program to check whether a given line is comment or not.

#include<iostream>
using namespace std;

bool isComment(string str)
{
	int n = str.length();
	if(str[0] == '/' and str[1] == '/')
		return true;
	if(str[0] == '/' and str[1] == '*' and str[n-2] == '*' and str[n-1] == '/')
		return true;
	return false;
}

int main()
{
	cout<<"\n----------- Aayush 2K19/CO/009 -----------\n";
	string str;
	cout<<"Enter line:\n";
	cin>>str;
	
	bool b = isComment(str);
	if(b)
	{
		cout<<"The given line is a comment\n";
	}
	else
	{
		cout<<"The given line is not a comment\n";
	}
}