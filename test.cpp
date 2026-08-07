#include<bits/stdc++.h>

using namespace std;

int main(){
    int a=10,b=20;
    cout<<a<<b<<"\n";
    a=a^b;
    b=a^b;
    a=a^b;
    cout<<a<<b;

    return 0;
}