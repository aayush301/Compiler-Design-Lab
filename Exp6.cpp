// Write a program to implement Lexical Analyzer for the source code stored in a file.

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
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
    "bitor", "compl", "not", "not_eq", "or", "or_eq", "xor", "xor_eq"};

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

bool isDelimiter(char c)
{
  return !isalpha(c) and !isdigit(c) and c != '_';
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

bool isOperator(char ch)
{
  vector<char> operators = {'+', '-', '*', '/', '%', '>', '<', '='};
  return (find(operators.begin(), operators.end(), ch) != operators.end());
}

bool isInteger(string str)
{
  if (str.length() == 0)
    return false;
  vector<char> valids = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  for (int i = 0; i < str.length(); i++)
  {
    char c = str[i];
    if (find(valids.begin(), valids.end(), c) == valids.end() || (c == '-' and i > 0))
      return false;
  }
  return true;
}

bool isRealNumber(string str)
{
  if (str.length() == 0)
    return false;
  vector<char> valids = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  bool hasDecimal = false;
  for (int i = 0; i < str.length(); i++)
  {
    char c = str[i];
    if (find(valids.begin(), valids.end(), c) == valids.end() and c != '.' || (c == '-' and i > 0))
      return false;
    if (c == '.')
      hasDecimal = true;
  }
  return hasDecimal;
}

vector<vector<string>> detectTokens(string &str)
{
  vector<vector<string>> tokenList;

  int tokens = 0;
  int n = str.length();
  int left = 0, right = 0;

  while (right <= n)
  {
    if (!isDelimiter(str[right]))
    {
      right++;
    }
    if (isDelimiter(str[right]) and left == right)
    {
      if (isOperator(str[right]) == true)
      {
        tokenList.push_back({string(1, str[right]), "Operator"});
      }
      right++;
      left = right;
    }
    else if (isDelimiter(str[right]) and left != right || (right == str.length() and left != right))
    {
      string subStr = str.substr(left, right - left);
      if (isKeyword(subStr))
      {
        tokenList.push_back({subStr, "Keyword"});
      }
      else if (isInteger(subStr))
      {
        tokenList.push_back({subStr, "Integer"});
      }
      else if (isRealNumber(subStr))
      {
        tokenList.push_back({subStr, "Real Number"});
      }
      else if (isIdentifier(subStr))
      {
        tokenList.push_back({subStr, "Identifier"});
      }
      left = right;
    }
  }

  return tokenList;
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

void printTokenList(vector<vector<string>> &tokenList)
{
  cout << setw(20) << "TOKEN" << setw(20) << "TOKEN TYPE" << endl;
  for (auto v : tokenList)
  {
    cout << setw(20) << v[0] << setw(20) << v[1] << endl;
  }
}

int main()
{

  string str = readFile();
  cout << "Tokens in the program are:\n\n";
  vector<vector<string>> tokenList = detectTokens(str);
  printTokenList(tokenList);
}
