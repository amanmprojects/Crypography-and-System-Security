#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class RSACryptosystem{
private:
    int p, q, d, n, phi;
public: 
    int e;
    RSACryptosystem(int p, int q){
        this->p = p;
        this->q = q;

        generateKeys();
    }

    void generateKeys(){
        this->n = p * q;
        this->phi = (p-1) * (q-1);

        // Finding e
        for(int i = 2; i < this->phi; i++){
            if(gcd(i, this->phi) == 1){
                this->e = i;
                break;
            }
        }

        // Finding d
        this->d = modInverse(e, phi);
    }

    int gcd(int a, int b){
        if (a == 0) return b;
        return gcd(b % a, a);
    }

    int modInverse(int a, int mod){
        for(int i = 1; i < mod; i++){
            if((a*i)%mod == 1){
                return i;
            }
        }
        return 0;
    }

    long long modularExponentation(long long base, long long exp, long long mod){
        long long result = 1;
        base = base % mod;
        
        while(exp > 0){
            if(exp % 2 == 1){  // If exp is odd
                result = (result * base) % mod;
            }
            exp = exp / 2;
            base = (base * base) % mod;
        }
        
        return result;
    }

    int encrypt(int pt){
        return modularExponentation(pt, this->e, this->n);
    }

    int decrypt(int ct){
        return modularExponentation(ct, this->d, this->n);
    }
};

vector<vector<int>> test = {
    {7, 13, 10},      // Example from your theory: p=7, q=13, plaintext=10
    {11, 17, 50},     // n=187, plaintext=50
    {3, 11, 5},       // n=33, plaintext=5
    {5, 7, 12},       // n=35, plaintext=12
    {13, 17, 100},    // n=221, plaintext=100
    {11, 13, 42},     // n=143, plaintext=42
    {3, 7, 8},        // n=21, plaintext=8
    {5, 11, 20}       // n=55, plaintext=20
};


int main(){
    for(auto t: test){
        int p = t[0], q = t[1], pt = t[2];
        
        RSACryptosystem rsa(p, q);
        
        cout << "========================" << "\n";
        cout << "p = " << p << ", q = " << q << "\n";
        cout << "n = " << p * q << "\n";
        cout << "phi = " << (p-1) * (q-1) << "\n";
        cout << "e = " << rsa.e << "\n";
        cout << "------------------------" << "\n";
        cout << "Plaintext: " << pt << "\n";
        
        int ct = rsa.encrypt(pt);
        cout << "Encrypted: " << ct << "\n";
        
        int decrypted = rsa.decrypt(ct);
        cout << "Decrypted: " << decrypted << "\n";
        cout << "========================" << "\n\n";
    }
    
    return 0;
}


