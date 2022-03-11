// Write a program to check whether a given identifier is valid or not.

#include<iostream>
using namespace std;

bool isValidIdentifier(string str)
{
	if(str.length() <= 0)
		return false;
	if(!isalpha(str[0]) and str[0] != '_')
		return false;
	
	for(char c: str)
	{
		if(!isalpha(c) and !isdigit(c) and c!='_')
			return false;
	}
	
	return true;
	
}

int main()
{
	cout<<"--- To check whether a given identifier is valid or not ---\n\n";
	
	string str;
	while(true)
	{
		cout<<"Enter identifier (# to stop):   ";
		cin>>str;
		if(str=="#")
			break;
		
		if(isValidIdentifier(str))
		{
			cout<<"Valid\n";
		}
		else
		{
			cout<<"Invalid\n";
		}
	}
	
}
