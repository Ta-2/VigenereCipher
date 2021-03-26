#include "VigenereCipherHeader.hpp"

int main(int argc, char *argv[]){
	VigenereCipher *vc;
	string plain = "ABC";
	string cipher = "ABC";
	string key = "ABC";
	
	if(argc > 1){
		cout << "string: " << argv[1] << endl;
		vc = new VigenereCipher(argv[1]);
	} else {
		cout << "string: " << key << endl;
		vc = new VigenereCipher("ABDECRYPTO");
	}
	vc->PrintSquare();
	
	if(argc > 3){
		cipher = vc->E(argv[2], argv[3]);
		plain = vc->D(cipher, argv[3]);
		cout << "key: " << argv[3] << endl;
	} else {
		cipher = vc->E(plain, key);
		plain = vc->D(cipher, key);
		cout << "key: " << key << endl;
	}
	cout << "cipher: " << cipher << endl;
	cout << "plain: " << plain << endl;
	
	delete vc;
	return 0;
}
