#include <bits/stdc++.h>
using namespace std;
// key: permutation of 0..n-1 given as vector<int> of length n (values 0..n-1 unique)
string columnar_encrypt(const string &pt, const vector<int>&key){
    int n = key.size();
    int rows = (pt.size()+n-1)/n;
    vector<string> mat(rows, string(n,'X')); // padding with X
    for(size_t i=0,k=0;i<rows && k<pt.size();++i)
      for(int j=0;j<n && k<pt.size();++j) mat[i][j]=pt[k++];
    string ct;
    for(int p=0;p<n;++p){
        int col = key[p];
        for(int r=0;r<rows;++r) ct.push_back(mat[r][col]);
    }
    return ct;
}
string columnar_decrypt(const string &ct, const vector<int>&key){
    int n = key.size();
    int rows = (ct.size()+n-1)/n;
    vector<string> mat(rows, string(n,'?'));
    int k=0;
    for(int p=0;p<n;++p){
        int col = key[p];
        for(int r=0;r<rows && k<ct.size();++r){
            mat[r][col]=ct[k++];
        }
    }
    string pt;
    for(int r=0;r<rows;++r)
      for(int c=0;c<n;++c) if(mat[r][c]!='?') pt.push_back(mat[r][c]);
    return pt;
}
int main(){
    string pt; cout<<"Plain: "; getline(cin,pt);
    string ks; cout<<"Key as perm indices separated by space (e.g. \"2 0 1\"): ";
    getline(cin,ks);
    stringstream ss(ks);
    vector<int> key; int x;
    while(ss>>x) key.push_back(x);
    string ct = columnar_encrypt(pt,key);
    cout<<"Cipher: "<<ct<<"\n";
    cout<<"Decipher: "<<columnar_decrypt(ct,key)<<"\n";
}
