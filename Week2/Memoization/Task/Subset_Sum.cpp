#include <iostream>
#include <chrono>

#define Loop(i,a,b) for (int i = a ; i < b ; i++)
#define MOD 1000000007

typedef long long int ll;

using namespace std;
using namespace chrono;
/*
    * THE PROBLEM:
    * Give an array of integers, you need to find the maximum total sum a subset could have such that no two elements 
    * in the subset are adjacent.
    
    * Sample Input:
      6
      6 4 3 2 1 5
    * Sample Output:
      14
    * Explanantion:
    * The subset {6,3,5} which has no two adjacent elements is the one with maximum total sum.
    * TASK:
    * You need to design an O(n) algorithm (ie one which takes a linear time in the input size) to solve this problem.
    * Hint : Think about prefix of the array.
*/
ll Count = 0;
// Declare some variable here for memoization

ll solution(ll* A, ll n, ll index,ll* subsum){
    Count++; // Do not remove this line

    if(subsum[index]!=-1){
      return subsum[index];
    }
    else{
      if (solution(A,n,index-2,subsum)+A[index] > solution(A,n,index-3,subsum)+A[index-1]){
        subsum[index] =subsum[index-2] +A[index]; 
        return subsum[index-2] +A[index];
      }  else{
        subsum[index]=subsum[index-3]+A[index-1];
        return subsum[index-3]+A[index-1];
      }
    }

    return 0; // Placeholder line
}
int main(){
    ll n;
    cin >> n;
    ll* A = new ll[n];
    Loop(i,0,n) cin >> A[i];
    auto start = high_resolution_clock::now();
    ll subsum[n];
    Loop(i,0,n) subsum[i] = -1;
    subsum[0] = A[0];
    subsum[1] = A[0]>A[1]?A[0]:A[1];
    subsum[2] = A[1]>A[0]+A[2]?A[1]:A[0]+A[2];
    ll sum = solution(A,n,n - 1,subsum);
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<duration<double>>(end - start);
    cout << "Maximum subset sum\t" << sum << "\n";
    cout << "Time spent(s)\t\t" << elapsed.count() << "\n"; 
    cout << "Number of recursive calls\t" << Count << "\n";
    delete [] A;
}