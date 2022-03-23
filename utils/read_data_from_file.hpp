//
// Created by KK on 2022/3/23.
//


#include <string>
#include <fstream>

using namespace std;

string read(const string &path) {
  ifstream ifs;
  ifs.open(path, ifstream::in);
  if (!ifs.is_open()) printf("open file %s failed", path.c_str());
  string line;
  string res;
  while(getline(ifs, line)) {
    res += line + "\n";
  }
  return res;
}