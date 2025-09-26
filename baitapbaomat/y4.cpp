#include <bits/stdc++.h>
using namespace std;
string prepare(const string&s){
    string r;
    for(char c: s) if(isalpha(c)) r.push_back(toupper(c));
    return r;
}
string vigenere_encrypt(const string &pt, const string &key){
    string p = prepare(pt);
    string k = prepare(key);
    if(k.empty()) return p;
    string out;
    for(size_t i=0;i<p.size();++i){
        int pi = p[i]-'A';
        int ki = k[i % k.size()] - 'A';
        out.push_back(char((pi + ki) % 26 + 'A'));
    }
    return out;
}
string vigenere_decrypt(const string &ct, const string &key){
    string c = prepare(ct);
    string k = prepare(key);
    if(k.empty()) return c;
    string out;
    for(size_t i=0;i<c.size();++i){
        int ci = c[i]-'A';
        int ki = k[i % k.size()] - 'A';
        out.push_back(char((ci - ki + 26) % 26 + 'A'));
    }
    return out;
}
int main(){
    string pt,key;
    cout<<"Plain: "; getline(cin,pt);
    cout<<"Key: "; getline(cin,key);
    string ct=vigenere_encrypt(pt,key);
    cout<<"Cipher: "<<ct<<"\n";
    cout<<"Decipher: "<<vigenere_decrypt(ct,key)<<"\n";
}
