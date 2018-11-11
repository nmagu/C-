#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v1;
    cout << v1.size() << endl;
    
    v1.push_back(10);
    
    
    cout << v1[0] << endl;
    v1[0] = 5;
    
    cout << "Size of vector: ";
    int n; cin >> n;
    
    vector<int> v2(n);
    cout << "Elements: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> v2[i];
    }
    
    reverse(v2.begin(), v2.end());
    
    for (int e: v2)
    {
        cout << e << " ";
    }
    cout << endl;
    
    vector<string> v3 = {
        "C", "C++", "Java", "Ada", "C#", "D", "Rust"
    };
    
    sort(v3.begin(), v3.end());
    
    for (string& e: v3)
    {
        cout << e << " ";
    }
    cout << endl;
    
    return 0;
}