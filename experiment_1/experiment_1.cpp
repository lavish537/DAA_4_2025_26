#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>
using namespace std::chrono;
using namespace std;
int operations = 0, maxdepth = 0,depth=0;
void complexRec(int n){
    if(n<=2){
        return;
    }
    depth++;
    maxdepth = max(maxdepth, depth);
    int p=n;
    while(p>0){
        vector<int> temp(n);
        for(int i=0;i<n;i++){
            temp[i]=i^p;
            operations+=1;
        }
        p>>=1;
        operations+=1;
    }
    vector<int> small(n);
    for(int i=0;i<n;i++){
        small[i]=i*i;
        operations+=1;
    }
    if(n%3==0){
        reverse(small.begin(),small.end());
        operations+=1;
    }
    else{
        reverse(small.begin(),small.end());
        operations+=1;
    }
    complexRec(n/2);
    complexRec(n/2);
    complexRec(n/2);
    depth--;
}
int main(){
    int n=1024;
    auto start = high_resolution_clock::now();
    complexRec(n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout<<(long long)duration.count()<<" ms"<<endl;
    cout<<"Operations: "<<operations<<endl;
    cout<<"Recursion Depth: "<<maxdepth<<endl;
    return 0;
}


/*
Reccurance relation
T(n) = 3*T(n/2) + O(nlogn + n + n)
Solving this recurrence relation using master theorem gives us:
T(n) = O(n^log2(3)) = O(n^1.585)
*/