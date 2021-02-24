
#include <vector>
#include <map>
#include <iostream>
using namespace std;


class VigenereCipher {
	public:
	int period = 0;
	char *ItoC = nullptr;
	map<char, int>CtoI;
	vector<vector<char> > VigenereSquare;
	//char ItoC[10] = {'A', 'B', 'D', 'E', 'C', 'R', 'Y', 'P', 'T', 'O'};
	//map<char, int> CtoI {
	//	{'A', 0}, {'B', 1}, {'D', 2}, {'E', 3}, {'C', 4},
	//	{'R', 5}, {'Y', 6}, {'P', 7}, {'T', 8}, {'O', 9}
	//};
	
	VigenereCipher (string character){
		SetParameter(character);
		MakeVigenereSquare();
	}
	~VigenereCipher (){ delete ItoC; }
	
	void SetParameter(string character){
		cout << endl << "---Setting parameters by character given..." << endl;
		cout << "character: " << character << endl;
		period = character.length();
		ItoC = new char[period];
		for(int i = 0; i < period; i++){
			ItoC[i] = character[i];
			CtoI[character[i]] = i;
		}
	}
	
	void MakeVigenereSquare(){
		for(int i = 0; i < period; i++){
		VigenereSquare.push_back(vector<char>());
			for(int j = 0; j < period; j++){
				VigenereSquare[i].push_back(ItoC[(i+j)%period]);
			}
		}
	}
	void PrintSquare(){
		int k = 0;
		cout << endl << "---VigenereSquare--" << endl;
		cout << " |";
		for(int i = 0; i < period; i++) cout << ItoC[i] << " ";
		cout  << endl << "-+";
		for(int i = 0; i < period; i++) cout << "--";
		cout << endl;
		for(auto i: VigenereSquare){
			cout << ItoC[k] << "|";
			for(auto j: i) cout << j << " ";
			cout << endl;
			k++;
		}
	}
	
	string E(string plain, string key){
		string cipher;
		int plainLen = plain.length(), keyLen = key.length();
		cout << endl << "---Encrypt---" << endl;
		cout << "plain: " << plain << ", length: " << plainLen << endl;
		cout << "key: " << key << ", length: " << keyLen << endl;
		for(int i = 0; i < plainLen; i++){
			cipher += VigenereSquare[CtoI[key[i%keyLen]]][CtoI[plain[i%plainLen]]];
		}
		cout << "result of Encrypt: " << cipher << endl;
		return cipher;
	}
	
};


int main(int argc, char *argv[]){
	VigenereCipher vc("ABDECRYPTO");
	vc.PrintSquare();
	vc.E("ABC", "ABC");

	return 0;
}