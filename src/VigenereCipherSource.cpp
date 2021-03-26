#include "VigenereCipherHeader.hpp"

VigenereCipher::VigenereCipher (string character){
	SetParameter( CheckString(character) );
	MakeVigenereSquare();
}
void VigenereCipher::SetParameter (string s){
	for(int i = 0; i < (int)s.length(); i++){
		if(CtoI.count(s[i]) == 0){
			ItoC.push_back(s[i]);
			CtoI[s[i]] = i;
		}
	}
	period = ItoC.size();
}
string VigenereCipher::CheckString (string str){
	string result;
	
	for(char s: str){
		if(('A' <= s && s <= 'Z'))result += s;
		else if(('a' <= s) && (s <= 'z'))result += (s + ('A'-'a'));
		else continue;
	}
	return result;
}
void VigenereCipher::MakeVigenereSquare(){
	for(int i = 0; i < period; i++){
	VigenereSquare.push_back(vector<char>());
		for(int j = 0; j < period; j++)
			VigenereSquare[i].push_back(ItoC[(i+j)%period]);
	}

}
void VigenereCipher::PrintSquare(){
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
string VigenereCipher::E(string plain, string key){
	string cipher;
	plain = CheckString(plain);
	key = CheckString(key);
	int plainLen = plain.length(), keyLen = key.length();
		
	for(int i = 0; i < plainLen; i++){
		if(CtoI.count(key[i%keyLen]) * CtoI.count(plain[i%plainLen]) == 0){
			return "-";
		}
		cipher += VigenereSquare[CtoI[key[i%keyLen]]][CtoI[plain[i%plainLen]]];
	}
	return cipher;
}
string VigenereCipher::D(string cipher, string key){
	string plain;
	cipher = CheckString(cipher);
	key = CheckString(key);
	int cipherLen = cipher.length(), keyLen = key.length();
	
	for(int i = 0; i < cipherLen; i++){
		if(CtoI.count(key[i%keyLen]) * CtoI.count(cipher[i%cipherLen]) == 0){
			return "-";
		}
		auto it = find(VigenereSquare[CtoI[key[i%keyLen]]].begin(), VigenereSquare[CtoI[key[i%keyLen]]].end(), cipher[i]);
		size_t index = distance(VigenereSquare[CtoI[key[i%keyLen]]].begin(), it);
		plain += ItoC[index];
	}
	return plain;	
}
