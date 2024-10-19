#include "DES.h"
#include "permutation.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encryption(string plaintext, vector<string> keys) {

    //error was here; did not remember IP or FP
    string permuted = "";
    for(int i = 0; i < 64; i++) {
        permuted += plaintext[IP[i] - 1];
    }
    
    string left = permuted.substr(0, 32);
    string right = permuted.substr(32, 32);
    
    // 16 rounds
    for(int round = 0; round < 16; round++) {
        string right_expanded = expansion(right);
        
        string xored = XOR(right_expanded, keys[round], 48);
        
        string substituted = sBox(xored);
        
        string permuted_right = pBox(substituted);
        
        string new_right = XOR(left, permuted_right, 32);
        
        left = right;
        right = new_right;  //forgot this swap 
    }
    
    string combined = right + left; 
    string encrypted = "";
    for(int i = 0; i < 64; i++) {
        encrypted += combined[FP[i] - 1];
    }
    
    return encrypted;
}
string decryption(string encrypted, vector<string> keys) {
    string permuted = "";
    for(int i = 0; i < 64; i++) {
        permuted += encrypted[IP[i] - 1];
    }
    
    string left = permuted.substr(0, 32);
    string right = permuted.substr(32, 32);
    
    for(int round = 15; round >= 0; round--) { //reverse for loop here 
        string right_expanded = expansion(right);
        
        string xored = XOR(right_expanded, keys[round], 48);
        
        string substituted = sBox(xored);
        
        string permuted_right = pBox(substituted);
        
        string new_right = XOR(left, permuted_right, 32);
        
        left = right;
        right = new_right;
    }
    
    //outside the for loop 
    string combined = right + left; 
    string decrypted = "";
    for(int i = 0; i < 64; i++) {
        decrypted += combined[FP[i] - 1];
    }
    
    return decrypted;
}
