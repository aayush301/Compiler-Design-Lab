// Write a program to implement recursive descent parser

// Parser is made for the following grammar:
/**
 * E->TE'
 * E'->+TE'|-TE'|null
 * T-> FT'
 * T'->*FT'|/FT'|null
 * F-> id|num|(E)
**/

#include <iostream>
using namespace std;

bool E(string &str, int &i);
bool Ed(string &str, int &i);
bool T(string &str, int &i);
bool Td(string &str, int &i);
bool F(string &str, int &i);

bool E(string &str, int &i)
{
  cout << "E->TE'" << endl;
  if (!T(str, i))
    return false;
  if (!Ed(str, i))
    return false;
  return true;
}

bool Ed(string &str, int &i)
{
  if (i >= str.length())
  {
    cout << "E'->null" << endl;
  }
  if (str[i] == '+')
  {
    i++;
    cout << "E'->+TE'" << endl;
    if (!T(str, i))
      return false;
    if (!Ed(str, i))
      return false;
  }
  else if (str[i] == '-')
  {
    i++;
    cout << "E'->-TE'" << endl;
    if (!T(str, i))
      return false;
    if (!Ed(str, i))
      return false;
  }
  else
  {
    cout << "E'->null" << endl;
  }
  return true;
}

bool T(string &str, int &i)
{
  cout << "T->FT'" << endl;
  if (!F(str, i))
    return false;
  if (!Td(str, i))
    return false;
  return true;
}

bool Td(string &str, int &i)
{
  if (i >= str.length())
  {
    cout << "T'->null" << endl;
  }
  if (str[i] == '*')
  {
    i++;
    cout << "T'->*FT'" << endl;
    if (!F(str, i))
      return false;
    if (!Td(str, i))
      return false;
  }
  else if (str[i] == '/')
  {
    i++;
    cout << "T'->/FT'" << endl;
    if (!F(str, i))
      return false;
    if (!Td(str, i))
      return false;
  }
  else
  {
    cout << "T'->null" << endl;
  }
  return true;
}

bool F(string &str, int &i)
{
  if (i >= str.length())
    return false;
  if (isalpha(str[i]))
  {
    i++;
    cout << "F->id" << endl;
  }
  else if (isdigit(str[i]))
  {
    i++;
    cout << "F->digit" << endl;
  }
  else if (str[i] == '(')
  {
    i++;
    cout << "F->(E)" << endl;
    if (!E(str, i))
      return false;
    if (i >= str.length() or str[i] != ')')
      return false;
    i++;
  }
  else
  {
    return false;
  }
  return true;
}

void parseString(string &str)
{
  int i = 0;
  if (!E(str, i) or i != str.length())
    cout << "Rejected" << endl;
  else
    cout << "Accepted" << endl;
}

int main()
{
  string str;
  char ch = 'y';
  while (ch == 'y' || ch == 'Y')
  {
    cout << "\nEnter the input string to be parsed:  ";
    cin >> str;
    parseString(str);
    cout << "\nDo you want to parse more? (y/n) ";
    cin >> ch;
  }
}
