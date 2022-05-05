// Write a program to implement operator precedence parser

// Grammar in this program is:
// E -> E*E | E+E | (E) | E^E | id

#include <iostream>
#include <iomanip>
using namespace std;

char prec[9][9] = {
    /*          +    -    *    /    ^   id    (    )    $  */
    /*  +  */ {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    /*  -  */ {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    /*  *  */ {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    /*  /  */ {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    /*  ^  */ {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    /* id  */ {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'},
    /*  (  */ {'<', '<', '<', '<', '<', '<', '<', '>', 'e'},
    /*  )  */ {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'},
    /*  $  */ {'<', '<', '<', '<', '<', '<', '<', '<', '>'},
};

int getIndexInTable(char c)
{
  switch (c)
  {
  case '+':
    return 0;
  case '-':
    return 1;
  case '*':
    return 2;
  case '/':
    return 3;
  case '^':
    return 4;
  case '(':
    return 6;
  case ')':
    return 7;
  case '$':
    return 8;
  default:
    return 5;
  }
}

void parseString(string str)
{
  int fieldWidth = max((int)str.length() + 2, 10);
  str += '$';
  string stack = "$";
  int i = 0;

  cout << left << setw(fieldWidth) << "Stack";
  cout << right << setw(fieldWidth) << "Input" << setw(fieldWidth) << "Action" << endl;
  while (i < str.length())
  {
    cout << left << setw(fieldWidth) << stack;
    cout << right << setw(fieldWidth) << str.substr(i);
    int top = stack.length() - 1;
    char c1 = stack[top];
    char c2 = str[i];
    if (c1 == '$' and c2 == '$')
    {
      cout << setw(fieldWidth) << "Accept" << endl;
      return;
    }
    char pre = prec[getIndexInTable(c1)][getIndexInTable(c2)];
    if (pre == '<' or pre == '=')
    {
      stack.push_back(c2);
      i++;
      cout << setw(fieldWidth) << string("Push ") + c2 << endl;
    }
    else
    {
      char c = stack.back();
      stack.pop_back();
      cout << setw(fieldWidth) << string("Pop ") + c << endl;
    }
  }
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
