#include<iostream>
#include<thread>
#define numthrds 8

class Matrix{
    private:
        int** M;
        int n,m;
    public:
        Matrix(int n,int m){
            this->n = n;
            this->m = m;
            this->M = new int*[n]; 
            for(int i=0;i<n;i++){
                this->M[i] = new int[m];
                for(int j=0;j<m;j++){
                    this->M[i][j] = 0;
                }
            }
        };
        ~Matrix(){
            for(int i=0;i<n;i++) delete[] this->M[i];
            delete[] this->M;
        }
        int getelement(int a,int b){
            return this->M[a][b];
        }
        void setelement(int a,int b,int val){
            this->M[a][b] = val;
            return;
        }
        void displayMatrix() {
            for(int i=0;i <this->n; i++) {
                for(int j=0;j <this->m;j++) {
                    std::cout << this->M[i][j] << " ";
                }
                std::cout << "\n";
            }
        }
};


void spinner(int n,int k,int m,Matrix* a,Matrix* b,Matrix* c,int i){
    for(int x=0;x<=(n-i-1)/numthrds;x++){
        int xori = x*numthrds + i;
        for(int y=0;y<m;y++){
            int temp=0;
            for(int ai = 0;ai<k;ai++){
                temp += a->getelement(xori,ai)*b->getelement(ai,y);
            }
            c->setelement(xori,y,temp);
        }
    }
}



int main(){
    int n,k,m;
    n=k=m=8;
    Matrix a(n,k),b(k,m),c(n,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            int temp;
            std::cin>>temp;
            a.setelement(i,j,temp);
        }
    }
    for(int i=0;i<k;i++){
        for(int j=0;j<m;j++){
            int temp;
            std::cin>>temp;
            b.setelement(i,j,temp);
        }
    }
    std::thread* threads = new std::thread[numthrds];
    for(int i=0;i<numthrds;i++){
        threads[i] = std::thread(spinner,n,k,m,&a,&b,&c,i);
    }
    for(int i=0;i<numthrds;i++){
        threads[i].join();
    }
    c.displayMatrix();
}