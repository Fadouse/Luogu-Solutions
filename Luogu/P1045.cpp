#include <bits/stdc++.h>
using namespace std;

// Multiply two numbers (given as decimal strings) modulo 10^500.
// The result is represented in its “normal order” (most-significant digit first)
// but its value is always in [0, 10^500).
string multiply_mod(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    // store digits in reverse order
    vector<int> A(n), B(m);
    for (int i = 0; i < n; i++) 
        A[i] = a[n-1-i] - '0';
    for (int j = 0; j < m; j++) 
        B[j] = b[m-1-j] - '0';
        
    vector<int> res(n + m, 0);
    for (int i = 0; i < n; i++){
        long long carry = 0;
        for (int j = 0; j < m; j++){
            long long tmp = (long long)res[i+j] + (long long)A[i]*B[j] + carry;
            res[i+j] = tmp % 10;
            carry = tmp / 10;
        }
        int pos = i + m;
        while(carry){
            long long tmp = res[pos] + carry;
            res[pos] = tmp % 10;
            carry = tmp / 10;
            pos++;
        }
    }
    // keep only lower 500 digits (i.e. the first 500 digits in our vector)
    if(res.size() > 500)
        res.resize(500);
        
    // convert back to normal order string
    string s;
    for (int i = res.size()-1; i >= 0; i--)
        s.push_back(res[i] + '0');
    // remove extra leading zeros (except the case of "0")
    int idx = 0;
    while(idx < s.size()-1 && s[idx]=='0') idx++;
    return s.substr(idx);
}

// Fast modular exponentiation to compute 2^exp mod 10^500.
string modExp(string base, long long exp) {
    string result = "1";
    while(exp > 0) {
        if(exp & 1)
            result = multiply_mod(result, base);
        base = multiply_mod(base, base);
        exp /= 2;
    }
    return result;
}

// Subtract one from a decimal number represented as a string.
// Assumes the string is a valid non-negative integer value.
string subtractOne(const string &s) {
    string res = s;
    int i = res.size()-1;
    while(i >= 0) {
        if(res[i] > '0'){
            res[i]--;
            break;
        } else {
            res[i] = '9';
            i--;
        }
    }
    // remove possible extra leading zeros (if any)
    int idx=0;
    while(idx < res.size()-1 && res[idx]=='0')
        idx++;
    return res.substr(idx);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long P;
    cin >> P;
    
    // Compute the total number of digits in 2^P - 1
    // Note: 2^P and 2^P - 1 have the same digit count.
    int totalDigits = floor(P * log10(2)) + 1;
    cout << totalDigits << "\n";
    
    // Compute 2^P mod 10^500 using fast exponentiation.
    string modVal = modExp("2", P);
    // Now compute (2^P - 1) mod 10^500.
    // Handle the subtraction; note that subtracting one from "0" should yield 10^500 - 1,
    // but 2^P mod 10^500 will not be "0" (since 2^P is not divisible by 5).
    string lastPart = subtractOne(modVal);
    
    // Pad the result to 500 digits with leading zeros if needed.
    if(lastPart.size() < 500)
        lastPart = string(500 - lastPart.size(), '0') + lastPart;
        
    // Print the last 500 digits in 10 lines of 50 digits.
    for(int i = 0; i < 10; i++){
        cout << lastPart.substr(i*50, 50) << "\n";
    }
    
    return 0;
}