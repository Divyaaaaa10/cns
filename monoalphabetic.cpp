#include<bits/stdc++.h>
using namespace std;
char uniqtext[26]; 

string readPlainText(){
	ifstream fin;
	string ptext;

	fin.open("plaintext.txt");
	fin >> ptext;
	fin.close();

	return ptext;
}

void writecipherText(string ctext)
{
	ofstream fout;
	fout.open("ciphertext.txt");
	fout << ctext;
	fout.close();
}

void permute(char a[], int l, int r, vector<string>& keyspace) 
{
	if(l == r)
	{
		keyspace.push_back(a);
	}
	else
	{
		for(int i = l; i <= r; i++)
		{
			swap(a[l], a[i]); 
			permute(a, l+1, r, keyspace);
			swap(a[l], a[i]);
		}
	}
}





vector<string> genKeySpace(string plaintext)
{
	set<char> uniqSet;
	vector<string> keyspace; // contains all possible permutation of letters in plaintext
	int count = 0;

	for(int i=0; i < plaintext.length(); i++)
	{
		uniqSet.insert(plaintext[i]);
	}
	for(set<char>::iterator it = uniqSet.begin(); it != uniqSet.end(); it++)
	{
		uniqtext[count++] = (*it);
	}

	permute(uniqtext, 0, strlen(uniqtext)-1, keyspace);
	return keyspace;
}


string encrypt(string unique, string key)
{
	string plaintext = readPlainText();
	string ciphertext = "";

	for(int i=0; i < plaintext.length(); i++)
	{
		int idx = unique.find(plaintext[i]);
		ciphertext += key[idx];
	}
	return ciphertext;
}


void showFrequency(string pt , string ct)
{
	map<char , int > mPlain ;
	map<char , int > mCipher ;

	for(int i =0 ;i < pt.length() ; i++)
	{
		mPlain[pt[i]]++ ;
		mCipher[ct[i]]++ ;
	}
	cout<<"\nFrequency\t\tPlaintext Character\t\tCiphertext character" <<endl;
	cout<<"=========\t\t===================\t\t====================" <<endl;
	for(int i=0 ; i<pt.length() ; i++)
	{
		cout<< (float)mPlain[pt[i]]/pt.length() << "\t\t\t\t" << pt[i] << "\t\t\t\t" << ct[i] << endl ;
	}
}

int main()
{
	srand(time(NULL)) ;

	string plaintext = readPlainText() ;
	cout<<"Plain text = \t" << plaintext << endl;

	vector<string> keyspace = genKeySpace(plaintext);
	string key = keyspace[rand()%keyspace.size()];

	cout<<"Unique chars = \t" << uniqtext <<endl;
	cout<<"Chosen key = \t" << key <<endl;

	string ciphertext = encrypt(uniqtext , key) ;
	writecipherText(ciphertext) ; // write ciphertext to file
	showFrequency(plaintext , ciphertext) ;
}

