#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int which_to_take(int size, int stepg, int step){
  if (step<stepg) { return step; }
  else {return 1+step; }
}

int reduce(vector<vector<vector<int>>> s){
  int correct_idx, sizeofcorrect;
  bool flag = true;
  while(flag) {
    correct_idx = (sizeof (s[0][0]) / sizeof (int))-1;
    sizeofcorrect = 32;
    cout << "{";

    while (sizeofcorrect<=2) {
      correct_idx--;
      sizeofcorrect = s[correct_idx].size(); 
    }
    cout << correct_idx;

    for (int i=0; i<sizeofcorrect; i++) {
      vector<vector<int>> new_thingy;
      for (int x=0; x<sizeofcorrect-1; x++) {
        for (int y=0; y<sizeofcorrect-1; y++) {
          new_thingy[x][y] = s[correct_idx]
                              [which_to_take(sizeofcorrect, i, x)]
                              [which_to_take(sizeofcorrect, i, y)];
          if (x==0) { new_thingy[x][y] *= pow(-1,1+i+1)*s[correct_idx][0][i]; }
        }
      }
      cout << new_thingy[0][0] << endl;
      s.push_back(new_thingy);
    }
    s.erase(s.begin()+correct_idx);

    for (int i=0; i<s.size(); i++) { if (s[i].size() != 2) { flag = false; } }
  }

  int cummirovanie = 0;
  for (int i=0; i<s.size(); i++) {
    cummirovanie += (s[i][0][0]*s[i][1][1] - s[i][1][0]*s[i][0][1]);
  }
  return cummirovanie;
}

int main(){
  int size, determinant;
  cin >> size;
  assert(size>2);

  vector<vector<vector<int>>> s;
  vector<vector<int>> qq;
  for (int n1=0; n1<size; n1++) {
    vector<int> q;
    for (int n2=0; n2<size; n2++) {
      int e; 
      cin >> e;
      q.push_back(e);
    }
    qq.push_back(q);
  }
  s.push_back(qq);
  int res = reduce(s);
  cout << res;
}
