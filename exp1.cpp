#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

// Caeser Cipher

class CaeserCipher {
    private:
        int key;
    public:
        CaeserCipher(int key){
            this->key = key;
        }
            string encrypt(string pt){
                // Lowercasing for simplicity
                transform(pt.begin(), pt.end(), pt.begin(), ::tolower);

                string ct = "";
                for(char c: pt){
                    char n = (((c-97)+this->key)%26)+97;
                    ct.push_back(n);
                }

                return ct;
            }

            string decrypt(string ct){
                // Lowercase
                transform(ct.begin(), ct.end(), ct.begin(), ::tolower);

                string pt = "";
                for(char c: ct){
                    char n = (((c-97)-this->key+26)%26)+97;
                    pt.push_back(n);
                }

                return pt;
            }
};

vector<string> test = {
    "amanisagoodboy",
    "HelloWorld"
};


int main(){
    CaeserCipher sol(5);
    
    for(string t: test){
        cout<<"Original String: "<<t<<"\n";
        cout<<"Encrypted String: "<<sol.encrypt(t)<<"\n";
        cout<<"Decrypted Sring: "<<sol.decrypt(sol.encrypt(t))<<"\n\n";
    }

    return 0;
}