#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string caesar_encrypt(const string &s, int t){
    string r = s;
    for (size_t i = 0; i < s.size(); ++i){
        char c = s[i];
        if (isupper(static_cast<unsigned char>(c))) r[i] = char((c - 'A' + t) % 26 + 'A');
        else if (islower(static_cast<unsigned char>(c))) r[i] = char((c - 'a' + t) % 26 + 'a');
        else r[i] = c;
    }
    return r;
}

string caesar_decrypt(const string &s, int t){
    return caesar_encrypt(s, (26 - t % 26) % 26);
}

int main(){
    string text;
    int t;
    cout << "Plain/Cipher text (one line):\n";
    getline(cin, text);
    cout << "Shift t (0-25): ";
    if (!(cin >> t)) {
        cerr << "Invalid input for shift.\n";
        return 1;
    }

    cout << "Encrypted: " << caesar_encrypt(text, t) << "\n";
    cout << "Decrypted: " << caesar_decrypt(caesar_encrypt(text, t), t) << "\n";
    return 0;
}
