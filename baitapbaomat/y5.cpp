#include <bits/stdc++.h>
using namespace std;
string prepare_key(string key){
    string s;
    for(char c: key){
        if(!isalpha(c)) continue;
        char C = toupper(c);
        if(C=='J') C='I';
        if(s.find(C)==string::npos) s.push_back(C);
    }
    for(char c='A'; c<='Z'; ++c){
        if(c=='J') continue;
        if(s.find(c)==string::npos) s.push_back(c);
    }
    return s.substr(0,25);
}
pair<int,int> findpos(const string &table, char ch){
    int idx = table.find(ch);
    return {idx/5, idx%5};
}
string preprocess_plain(const string &pt){
    string s;
    for(char c: pt) if(isalpha(c)) { char C=toupper(c); if(C=='J') C='I'; s.push_back(C); }
    string out;
    for(size_t i=0;i<s.size();){
        char a = s[i];
        char b = (i+1<s.size()? s[i+1] : '\0');
        if(b==0){ out.push_back(a); out.push_back('X'); i++; }
        else if(a==b){ out.push_back(a); out.push_back('X'); i++; }
        else { out.push_back(a); out.push_back(b); i+=2; }
    }
    return out;
}
string playfair_encrypt(const string &pt, const string &key){
    string table = prepare_key(key);
    string pr = preprocess_plain(pt);
    string ct;
    for(size_t i=0;i<pr.size(); i+=2){
        char a=pr[i], b=pr[i+1];
        auto pa = findpos(table,a), pb=findpos(table,b);
        if(pa.first==pb.first){
            // same row -> shift right
            ct.push_back(table[pa.first*5 + (pa.second+1)%5]);
            ct.push_back(table[pb.first*5 + (pb.second+1)%5]);
        } else if(pa.second==pb.second){
            // same column -> shift down
            ct.push_back(table[((pa.first+1)%5)*5 + pa.second]);
            ct.push_back(table[((pb.first+1)%5)*5 + pb.second]);
        } else {
            // rectangle
            ct.push_back(table[pa.first*5 + pb.second]);
            ct.push_back(table[pb.first*5 + pa.second]);
        }
    }
    return ct;
}
string playfair_decrypt(const string &ct, const string &key){
    string table = prepare_key(key);
    string pt;
    for(size_t i=0;i<ct.size(); i+=2){
        char a=ct[i], b=ct[i+1];
        auto pa = findpos(table,a), pb=findpos(table,b);
        if(pa.first==pb.first){
            pt.push_back(table[pa.first*5 + (pa.second+5-1)%5]);
            pt.push_back(table[pb.first*5 + (pb.second+5-1)%5]);
        } else if(pa.second==pb.second){
            pt.push_back(table[((pa.first+5-1)%5)*5 + pa.second]);
            pt.push_back(table[((pb.first+5-1)%5)*5 + pb.second]);
        } else {
            pt.push_back(table[pa.first*5 + pb.second]);
            pt.push_back(table[pb.first*5 + pa.second]);
        }
    }
    return pt;
}
int main(){
    string key, text;
    cout<<"Key: "; getline(cin,key);
    cout<<"Plain: "; getline(cin,text);
    string ct = playfair_encrypt(text,key);
    cout<<"Cipher: "<<ct<<"\n";
    cout<<"Decipher: "<<playfair_decrypt(ct,key)<<"\n";
}
