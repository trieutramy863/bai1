#include <bits/stdc++.h>
using namespace std;
int egcd(int a,int b,int &x,int &y){
    if(b==0){ x=1; y=0; return a;}
    int x1,y1; int g=egcd(b,a%b,x1,y1);
    x=y1; y=x1 - (a/b)*y1; return g;
}
int modinv(int a,int m){
    int x,y;
    if(egcd(a,m,x,y)!=1) return -1;
    x%=m; if(x<0) x+=m;
    return x;
}
string affine_encrypt(const string&s,int a,int b){
    string r=s;
    for(size_t i=0;i<s.size();++i){
        char c=s[i];
        if(isupper(c)) r[i]=char((a*(c-'A')+b)%26 + 'A');
        else if(islower(c)) r[i]=char((a*(c-'a')+b)%26 + 'a');
        else r[i]=c;
    }
    return r;
}
string affine_decrypt(const string&s,int a,int b){
    int a_inv = modinv(a,26);
    if(a_inv==-1) return "Invalid a (no inverse)";
    string r=s;
    for(size_t i=0;i<s.size();++i){
        char c=s[i];
        if(isupper(c)) r[i]=char((a_inv*((c-'A')-b+26*10))%26 + 'A');
        else if(islower(c)) r[i]=char((a_inv*((c-'a')-b+26*10))%26 + 'a');
        else r[i]=c;
    }
    return r;
}
int main(){
    string s; int a,b;
    cout<<"Text:\n"; getline(cin,s);
    cout<<"a b: "; cin>>a>>b;
    cout<<"Cipher: "<<affine_encrypt(s,a,b)<<"\n";
    cout<<"Decipher: "<<affine_decrypt(affine_encrypt(s,a,b),a,b)<<"\n";
}
