#include <iostream>
#include <immintrin.h>
#include <iomanip>
#include <chrono>
using namespace std;
/*

COMPUTE DOT PRODUCT OF TWO VECTORS
INPUTS :n => dimension of vectors
        vec1 => the first vector
        vec2 => the second vector

OUTPUT:dotProduct = vec1.vec2

dotProduct of two vectors is defined as summation_{i=0}^{i=n} [vec1[i]*vec2[i]];

*/
int main () {

    int n;
    cin>>n;
    float vec1[n];
    float vec2[n];
    for (int i=0; i<n; i++) {
        cin>>vec1[i];
    }
    for (int i=0; i<n; i++) {
        cin>>vec2[i];
    }
    float naiveTimeTaken = 0;
    float SIMDTimeTaken = 0;
    float dotProduct = 0;
    for (int i=0; i<1000; i++) {
        dotProduct = 0;
        auto start = chrono::high_resolution_clock::now();
        //NAIVE IMPLEMENTATION FOR COMPARISION PURPOSES
        for (int i=0; i<n; i++) {
            dotProduct += vec1[i]*vec2[i];
        }
        //NAIVE IMPLEMENTATION ENDS
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::duration<double>>(end - start);
        naiveTimeTaken += (elapsed.count())/1000;
    }

    cout<<dotProduct<<" "<<naiveTimeTaken<<" ";
    float arr0[8] = {0,0,0,0,0,0,0,0};
    for (int i=0; i<1000; i++) {
        dotProduct = 0;
        auto start2 = chrono::high_resolution_clock::now();
        //STUDENT CODE BEGINS HERE
        if(n%8 !=0)
        {   
            __m256 arr[n/8]; 
            for(int i=0;i<n-8;i+=8){
                float temp[8];
                for(int j =0;j<8;j++){
                    temp[j] = vec1[j]*vec2[j];
                }
                arr[i/8] =_mm256_loadu_ps(temp);
            }
            __m256 result = _mm256_loadu_ps(arr0);
            for(int i=0;i<n/8;i++){
                result = _mm256_add_ps(result,arr[i]);
            }
            __m128 result1[2] = {_mm256_extractf128_ps(result,0),_mm256_extractf128_ps(result,1)};
            __m128 res2 = _mm_hadd_ps(result1[0],result1[1]);
            float x[4];
            _mm_store_ps(x,res2);
            dotProduct+= x[1]+x[0] + x[2]+x[3];
            for(int i =(n/8)*8;i<n;i++){
                dotProduct += vec1[i]*vec2[i];
            }
        }else{
            __m256 arr[n/8]; 
            for(int i=0;i<n;i+=8){
                float temp[8];
                for(int j =0;j<8;j++){
                    temp[j] = vec1[j]*vec2[j];
                }
                arr[i/8] =_mm256_loadu_ps(temp);
            }
            __m256 result = _mm256_loadu_ps(arr0);
            for(int i=0;i<n/8;i++){
                result = _mm256_add_ps(result,arr[i]);
            }
            __m128 result1[2] = {_mm256_extractf128_ps(result,0),_mm256_extractf128_ps(result,1)};
            __m128 res2 = _mm_hadd_ps(result1[0],result1[1]);
            float x[4];
            _mm_store_ps(x,res2);
            dotProduct+= x[1]+x[0] + x[2]+x[3];
        }
        //END OF STUDENT CODE
        auto end2 = chrono::high_resolution_clock::now();
        auto elapsed2 = chrono::duration_cast<chrono::duration<double>>(end2 - start2);
        SIMDTimeTaken += (elapsed2.count())/1000;
    }
    cout<<dotProduct<<" "<<SIMDTimeTaken<<" ";
}