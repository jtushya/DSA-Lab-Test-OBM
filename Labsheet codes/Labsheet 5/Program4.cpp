#include <bits/stdc++.h>
using namespace std;

bool hasSubsetSum(int a[], int requiredSum, int idx)
{
  // Complete the base case. Return appropriate value for the below if statement
  if (requiredSum == 0)
    return true;

  if (idx < 0)
  {
    return requiredSum == 0;
  }

  if (a[idx] <= requiredSum)
  {
    // Make appropriate recursive call when currValue is picked
    // Check if value of requiredSum and idx should change or not
    // Fill the arguments marked as '?'

    bool pickValueAtIdx = hasSubsetSum(a, requiredSum-a[idx], ?);

    // Make appropriate recursive call when currValue is not picked
    // Check if value of requiredSum and idx should change or not
    
    bool notPickValueAtIdx = hasSubsetSum(a,  requiredSum, idx-1);

    // We should get a subset either on picking curr value or not,
    // Hence, we return OR of both values;
    return pickValueAtIdx || notPickValueAtIdx;
  }
  else
  {
    // Since a[idx]>requiredSum, we cannot pick the value at a[idx]
    // Hence, we return notPickValueAtIdx only.
    // Make appropriate recursive call when currValue is not picked
    // Check if value of requiredSum and idx should change or not
 
    bool notPickValueAtIdx = hasSubsetSum(a, requiredSum, idx-1);

    return notPickValueAtIdx;
  }
}

int main()
{
  int n;
  int sum;
  cout << "Enter the number of elements: ";
  cin >> n;
  int a[n];
  cout << "Enter the non-negative elements:\n";

  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }

  cout << "Enter the required sum: ";
  cin >> sum;

  if (hasSubsetSum(a, sum, n - 1)) // we call the recursive function initially with idx=n-1
  {
    cout << "A subset exists with sum equal to " << sum << endl;
  }
  else
  {
    cout << "No subset exists with sum equal to " << sum << endl;
  }
}