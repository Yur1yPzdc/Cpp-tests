#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int which_to_take(int size, int stepg, int step){
  if (step<stepg) { return step; }
  else {return 1+step; }
}

int main(){
  vector<tuple<int, int**>> a;
  int size;
  cin >> size;
  int** q = new int* [size];
  for (int i=0; i<size; i++) {
    int* qq = new int [size];
    for (int j=0; j<size; j++) {
      *(qq+j) = j;
    }
    *(q+i) = qq;
    //delete [] qq;
  }
  a.push_back(tuple(size, q));
  //delete [] q;

  cout << get<0>(a[0]) << endl << **(get<1>(a[0]));
  return 0;
}
