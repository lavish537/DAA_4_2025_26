#include <iostream>
#include <vector>
using namespace std;

void sort(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr.size() - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{

    vector<int> arr1 = {2, 1, 3, 5};
    vector<int> arr2 = {6, 7, 1, 2, 1};

    // find no . of pairs sum to given sum
    int sum;
    cin >> sum;

    // brute force
    //  int count = 0;
    //  for(int i=0;i<arr1.size();i++){
    //      for(int j=0;j<arr2.size();j++){
    //          if(arr1[i]+arr2[j]==sum){
    //              cout<<"Pair found: ("<<arr1[i]<<","<<arr2[j]<<")"<<endl;
    //              count++;
    //          }
    //      }
    //  }

    // using sorting and binary search upperbound and lowerbound
    sort(arr2);
    int count = 0;
    for (int i = 0; i < arr1.size(); i++)
    {
        int x = sum - arr1[i];
        // lower bound
        int l = 0, r = arr2.size() - 1, lb = arr2.size();
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (arr2[mid] >= x)
            {
                lb = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        // upper bound
        l = 0, r = arr2.size() - 1;
        int ub = arr2.size();
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (arr2[mid] > x)
            {
                ub = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        count += (ub - lb);
    }

    cout << "Total pairs with sum " << sum << ": " << count << endl;
    return 0;
}