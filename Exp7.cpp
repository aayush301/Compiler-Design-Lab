// Write a program to find FIRST set for any given grammar

// input is from a file
// Rules for input file:
// (1) Use e for epsilon
// (2) No white spaces except newline for new production
// (3) The first symbol should be start symbol
// (4) Capital letters for non-terminals and small letters for terminals except e.

// Sample input:
// S->ACB|CbB|Ba
// A->da|BC
// B->g|e
// C->h|e

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
using namespace std;

pair<char, map<char, vector<vector<char>>>> readFile()
{
  char startSymbol;
  map<char, vector<vector<char>>> productionsMap;

  ifstream fin("Exp7input.txt");
  string str;
  bool flag = 0;
  cout << "Grammar: " << '\n';

  while (getline(fin, str))
  {
    if (flag == 0)
      startSymbol = str[0], flag = 1;
    cout << str << '\n';
    vector<char> temp;
    char s = str[0];

    for (int i = 3; i < str.size(); i++)
    {
      if (str[i] == '|')
      {
        productionsMap[s].push_back(temp);
        temp.clear();
      }
      else
        temp.push_back(str[i]);
    }
    productionsMap[s].push_back(temp);
  }

  return {startSymbol, productionsMap};
}

bool dfs(char i, char org, char last, map<char, vector<vector<char>>> &productionsMap, set<char> &firstSet)
{
  bool rtake = false;
  for (auto str : productionsMap[i])
  {
    bool take = true;
    for (char c : str)
    {
      if (c == i || !take)
        break;

      if (!(c >= 'A' && c <= 'Z') && c != 'e')
      {
        // for terminal
        firstSet.insert(c);
        break;
      }
      else if (c == 'e')
      {
        // for epsilon
        if (org == i || i == last)
          firstSet.insert(c);
        rtake = true;
        break;
      }
      else
      {
        // for non-terminal
        take = dfs(c, org, str[str.size() - 1], productionsMap, firstSet);
        rtake |= take;
      }
    }
  }
  return rtake;
}

void findFIRST(map<char, set<char>> &firstResult,
               map<char, vector<vector<char>>> &productionsMap)
{
  for (auto p : productionsMap)
  {
    char c = p.first;
    set<char> firstSet;
    dfs(c, c, c, productionsMap, firstSet);
    for (auto t : firstSet)
      firstResult[c].insert(t);
  }
}

void printFIRST(map<char, set<char>> &mp)
{
  for (auto p : mp)
  {
    string ans = "";
    ans += p.first;
    ans += " = {";
    for (char r : p.second)
    {
      ans += r;
      ans += ',';
    }
    ans.pop_back();
    ans += "}";
    cout << ans << '\n';
  }
}

int main()
{
  cout << "\n----------- Aayush 2K19/CO/009 -----------\n";

  auto p = readFile();
  char startSymbol = p.first;
  map<char, vector<vector<char>>> productionsMap = p.second;
  map<char, set<char>> firstResult;

  findFIRST(firstResult, productionsMap);

  cout << "\nFIRST: " << '\n';
  printFIRST(firstResult);
}