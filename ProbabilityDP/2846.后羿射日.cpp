#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double p;
int k1,k2;
double x,y,ans;
vector<double> A,B,C,D;


int main() {
    cin>>p>>k1>>k2;
    //cerr<<k1<<k2<<endl;
    A.resize(k1,0.0);
    B.resize(k1,0.0);
    C.resize(k2,0.0);
    D.resize(k2,0.0);

    //cerr<<1<<endl;


    A[k1-1] = 1-p; B[k1-1] = 1;
    C[k2-1] = p;   D[k2-1] = 1;

    //cerr<<2<<endl;
    for (int i = k1-2 ; i > 0 ; --i) {
        A[i] = p*A[i+1] + 1.0 - p;
        B[i] = 1 + p*B[i+1];
    }
    for (int i = k2-2 ; i > 0 ; --i) {
        C[i] = (1.0 - p)*C[i+1] + p;
        D[i] = (1.0 - p)*D[i+1] + 1;
    }

    y = (C[1] * B[1] + D[1])/(1 - C[1] * A[1]);
    x = A[1] * y + B[1];

    //cerr<<x<<endl<<y<<endl;

    ans = 1.0 + p * x + (1.0 - p) * y;
    cout<<fixed<<setprecision(3)<<ans<<endl;
    return 0;
}