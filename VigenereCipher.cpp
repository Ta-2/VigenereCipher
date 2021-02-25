
#include <vector>
#include <map>
#include <iostream>
#include <regex>
using namespace std;


class VigenereCipher {
	public:
	int period = 0;
	vector<char> ItoC;
	map<char, int>CtoI;
	vector<vector<char> > VigenereSquare;
	//char ItoC[10] = {'A', 'B', 'D', 'E', 'C', 'R', 'Y', 'P', 'T', 'O'};
	//map<char, int> CtoI {
	//	{'A', 0}, {'B', 1}, {'D', 2}, {'E', 3}, {'C', 4},
	//	{'R', 5}, {'Y', 6}, {'P', 7}, {'T', 8}, {'O', 9}
	//};
	
	VigenereCipher (string character){
		SetParameter( CheckString(character) );
		MakeVigenereSquare();
	}
	~VigenereCipher (){}

	string CheckString(string str){
		string result;
		
		cout << endl << "---Chekking if chracter given includes unexpected characters..." << endl;
		cout << "given: " << str << endl;
		for(char s: str){
			if(('A' <= s && s <= 'Z'))result += s;
			else if(('a' <= s) && (s <= 'z'))result += (s + ('A'-'a'));
			else continue;
		}
		cout << "result: " << result << endl;
		
		return result;
	}
	
	void SetParameter(string s){
		bool modify_f = false;
	
		cout << endl << "---Setting parameters by character given..." << endl;
		cout << "given: " << s << endl;
		for(int i = 0; i < s.length(); i++){
			if(CtoI.count(s[i]) == 0){
				ItoC.push_back(s[i]);
				CtoI[s[i]] = i;
			} else modify_f = true;
		}
		period = ItoC.size();
		
		if(modify_f){
			cout << "[warning]: Some alphabets that appeared some times ware found." << endl;
			cout << "           Modified \"" << s << "\" to \"" ;
			for(char i: ItoC)cout << i;
			cout << "\"" << endl;
		}
		cout << "Complete" << endl;
		
	}
	
	void MakeVigenereSquare(){
		cout << endl << "---Creating VigenereSquare..." << endl;
		for(int i = 0; i < period; i++){
		VigenereSquare.push_back(vector<char>());
			for(int j = 0; j < period; j++){
				VigenereSquare[i].push_back(ItoC[(i+j)%period]);
			}
		}
		cout << "Completed" << endl;
	}
	
	void PrintSquare(){
		int k = 0;
		
		cout << endl << "---VigenereSquare--" << endl;
		cout << " |";
		for(char c: ItoC) cout << c << " ";
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
		plain = CheckString(plain);
		key = CheckString(key);
		int plainLen = plain.length(), keyLen = key.length();
		
		cout << endl << "---Encryption---" << endl;
		cout << "plain: " << plain << ", length: " << plainLen << endl;
		cout << "key: " << key << ", length: " << keyLen << endl;
		for(int i = 0; i < plainLen; i++){
			if(CtoI.count(key[i%keyLen]) * CtoI.count(plain[i%plainLen]) == 0){
				cout << "[error]: Unavailable character was found. return \"-\"." << endl;
				return "-";
			}
			cipher += VigenereSquare[CtoI[key[i%keyLen]]][CtoI[plain[i%plainLen]]];
		}
		cout << "result of Encrypt: " << cipher << endl;
		
		return cipher;
	}

	string D(string cipher, string key){
		string plain;
		cipher = CheckString(cipher);
		key = CheckString(key);
		int cipherLen = cipher.length(), keyLen = key.length();
		
		cout << endl << "---Decryption---" << endl;
		cout << "cipher: " << cipher << ", length: " << cipherLen << endl;
		cout << "key: " << key << ", length: " << keyLen << endl;
		for(int i = 0; i < cipherLen; i++){
			if(CtoI.count(key[i%keyLen]) * CtoI.count(cipher[i%cipherLen]) == 0){
				cout << "[error]: Unavailable character was found. return \"-\"." << endl;
				return "-";
			}
			auto it = find(VigenereSquare[CtoI[key[i%keyLen]]].begin(), VigenereSquare[CtoI[key[i%keyLen]]].end(), cipher[i]);
			size_t index = distance(VigenereSquare[CtoI[key[i%keyLen]]].begin(), it);
			plain += ItoC[index];
		}
		cout << "result of Decrypt: " << plain << endl;
		
		return plain;
	}
	
};


int main(int argc, char *argv[]){
	VigenereCipher *vc;
	string plain = "ABC";
	string cipher = "ABC";
	string key = "ABC";
	
	if(argc > 1)vc = new VigenereCipher(argv[1]);
	else vc = new VigenereCipher("ABDECRYPTO");
	vc->PrintSquare();
	
	if(argc > 3){
		cipher = vc->E(argv[2], argv[3]);
		plain = vc->D(cipher, argv[3]);
	} else {
		cipher = vc->E(plain, key);
		plain = vc->D(cipher, key);
	}
	
	delete vc;
	return 0;
}
