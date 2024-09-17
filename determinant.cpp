#include <cmath>
#include <iostream>
#include <vector>

using namespace std;


int which_to_take(int step_global, int step){
  if (step<step_global) return step;
  else return 1+step;
}

double compute(vector<tuple<int,double**>>* s){
    int correct_idx, size_of_correct, trash;
    bool stage_1 = true;
    while (stage_1) {
      cout << "stage 1 started\n";
      stage_1 = false;
      correct_idx = (*s).size();

      do {
        correct_idx--;
        size_of_correct = get<0>((*s)[correct_idx]);
        cout << size_of_correct << endl << correct_idx << endl;
      } while (size_of_correct<=2);

      cout << "index found " << correct_idx << endl;

      for (int global_step=0; global_step<size_of_correct; global_step++){
        double** lesser_matrix = new double* [size_of_correct-1];
        //cout << "LM\n";
        for (int x=0; x<size_of_correct-1; x++){
          double* lesser_matrix_row = new double [size_of_correct-1];
          //cout << "LMR\n";
          for (int y=0; y<size_of_correct-1; y++){
            //cout << global_step << "\t" << x << "\t" << y << endl;
            lesser_matrix_row[y] = (get<1>((*s)[correct_idx]))[x+1]
                                    [which_to_take(global_step, y)];
            if (y==0) lesser_matrix_row[y] *= 
              pow(-1,global_step)*get<1>((*s)[correct_idx])[0][global_step];
            cout << "object added" << lesser_matrix_row[y] << endl;
          }
          lesser_matrix[x] = lesser_matrix_row;
        }
        (*s).push_back(tuple(size_of_correct-1, lesser_matrix));
        //delete [] lesser_matrix_row;
        //delete [] lesser_matrix;
        cout << "lesser matrix pushed\n";
      }
      (*s).erase((*s).begin()+correct_idx);
      for (int i=0; i<(*s).size(); i++) { if ( get<0>((*s)[i])!=2 ) { stage_1 = true; } }
    }
  cout << "counting ans\n";
  int ans=0;
  for (int i=0; i<(*s).size(); i++){
  ans+= ( (get<1>((*s)[i]))[0][0]*  (get<1>((*s)[i]))[1][1])-
        ( (get<1>((*s)[i]))[1][0]*  (get<1>((*s)[i]))[0][1]);
  }
  return ans;
}


int main(){
  int size, determinant;
  cin >> size;
  vector<tuple<int,double**>> s;
  double** matrix = new double* [size];
  for (int n1=0; n1<size; n1++) {
    double* matrix_row = new double [size];
    for (int n2=0; n2<size; n2++) {
      cin >> matrix_row[n2];
    }
    matrix[n1] = matrix_row;
    //delete [] matrix_row;
  }
  s.push_back(tuple(size, matrix));
  //delete [] matrix;
  int res = compute(&s);
  cout << res;
}
