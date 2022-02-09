// Write a program to count number of tokens (keywords and identifiers) in a program.

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<string> keywords = {
	"alignas", "alignof", "asm", "auto", "bool", "break", "case", "catch",
	"char", "char16_t", "char32_t", "class", "const", "constexpr", "const_cast", "continue",
	"decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
	"explicit", "export", "extern", "false", "float", "for", "friend", "goto",
	"if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept",
	"nullptr", "operator", "private", "protected", "public", "register",
	"reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert",
	"static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
	"true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
	"virtual", "void", "volatile", "wchar_t", "while", "and", "and_eq", "bitand",
	"bitor", "compl", "not", "not_eq", "or", "or_eq", "xor", "xor_eq"
};

bool binary_search(vector<string>::iterator itr1, vector<string>::iterator itr2, string str)
{
	if (itr1 >= itr2)
		return false;
	auto mid = itr1 + (itr2 - itr1) / 2;
	if (*mid == str)
		return true;
	if (*mid < str)
		return binary_search(mid + 1, itr2, str);
	return binary_search(itr1, mid - 1, str);
}

bool isKeyword(string &str)
{
	if (str.length() == 0)
		return false;
	return binary_search(keywords.begin(), keywords.end(), str);
}

bool isIdentifier(string &str)
{
	if (str.length() == 0)
		return false;
	if (!isalpha(str[0]) and str[0] != '_')
		return false;

	for (char c : str)
	{
		if (!isalpha(c) and !isdigit(c) and c != '_')
			return false;
	}
	return true;
}

bool isDelimiter(char c)
{
	return !isalpha(c) and !isdigit(c) and c != '_';
}

int findNoOfTokens(string &str)
{
	int tokens = 0;
	int n = str.length();
	int left = 0, right = 0;

	while (right <= n)
	{
		if (right == n and left != right)
		{
			string curr = str.substr(left);
			if (isKeyword(curr) or isIdentifier(curr))
				tokens++;
			break;
		}

		if (str[right] == '"')
		{
			right++;
			while (right < n and str[right] != '"')
				right++;
			right++;
			if (right >= n)
				break;
			left = right;
		}

		if (str[right] == '\'')
		{
			right++;
			while (right < n and str[right] != '\'')
				right++;
			right++;
			if (right >= n)
				break;
			left = right;
		}

		if (!isDelimiter(str[right]))
		{
			right++;
		}
		else if (isDelimiter(str[right]) and left == right)
		{
			left++;
			right++;
		}
		else if (isDelimiter(str[right]) and left != right)
		{
			string curr = str.substr(left, right - left);
			if (isKeyword(curr) or isIdentifier(curr))
			{
				tokens++;
			}
			left = right;
		}
	}
	return tokens;
}

string readFile()
{
	string file, str, temp;
	cout << "Enter program file: ";
	cin >> file;
	fstream fin(file);

	while (getline(fin, temp))
	{
		str += temp + '\n';
	}
	return str;
}

int main()
{
	cout << "\n----------- Aayush 2K19/CO/009 -----------\n";

	string str = readFile();
	cout << "The no. of tokens (keywords and identifiers) in the program are: ";
	cout << findNoOfTokens(str) << endl<<endl;
}