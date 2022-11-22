// CPP Program to multiply two matrix using pthreads
#include <bits/stdc++.h>
using namespace std;

// maximum size of matrix
#define MAX 4

// maximum number of threads
#define MAX_THREAD 4

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
int step_i = 0;

void* multi(void* arg)
{
        int i = step_i++; //i denotes row number of resultant matC

        for (int j = 0; j < MAX; j++)
        for (int k = 0; k < MAX; k++)
                matC[i][j] += matA[i][k] * matB[k][j];
        return NULL;
}

// Driver Code
int main() {
  // read file values in matA and matB
  ifstream inputA("./inputA.txt");
  while (!inputA.eof()) {
    for (int i = 0; i < MAX; i++) {
      for (int j = 0; j < MAX; j++) {
        inputA >> matA[i][j];
      }
    }
  }
  ifstream inputB("./inputB.txt");
  while (!inputB.eof()) {
    for (int i = 0; i < MAX; i++) {
      for (int j = 0; j < MAX; j++) {
        inputB >> matB[i][j];
      }
    }
  }
  inputA.close();
  inputB.close();
  // declaring four threads
  pthread_t threads[MAX_THREAD];

  // Creating four threads, each evaluating its own part
  for (int i = 0; i < MAX_THREAD; i++) {
          int* p;
          pthread_create(&threads[i], NULL, multi, (void*)(p));
  }

  // joining and waiting for all threads to complete
  for (int i = 0; i < MAX_THREAD; i++)
          pthread_join(threads[i], NULL);
  ofstream output("./output.txt");
  for (int i = 0; i < MAX; i++) {
          for (int j = 0; j < MAX; j++)
                output << matC[i][j] << " ";
         output << endl;
  }
  cout <<"NHAN MA TRAN THANH CONG"<<endl;
  return 0;
}
