#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readfile()
{
  ifstream infile("input.txt");
  if (infile.good())
  {
    string sLine;
    getline(infile, sLine);
    return sLine;
  }
  else
  {
  	cout <<"Reading error\n";
  }
  infile.close();
}

int accept(string prefix)
{
	int z=0;
	int len2=prefix.length();
	string data = readfile();
    for (int i=0; i<len2; i++){
    	z+=prefix[i] ^ data[i];
        if (z == 60){
        	return 0;
		};    
	}
    return 1;
}

int fill(string prefix)
{
	string rec = prefix;
	int len=prefix.length();
	if (len==30){
		for (int i=0; i<208-len; i++){
			prefix+=(((((prefix[i] ^ prefix[i+1])+'0')^prefix[i+4])+'0')^prefix[i+6])+'0';
		}
		if (accept(prefix)==1){
			cout << rec<<endl;
			ofstream out("L1.txt", ios::app);
			out<<rec<<endl;
			out.close();
		}}
	else if (len==31){
		for (int i=0; i<208-len; i++){
			prefix+=(prefix[i] ^ prefix[i+3])+'0';
		}
		if (accept(prefix)==1){
			cout << rec<<endl;
			ofstream out("L2.txt", ios::app);
			out<<rec<<endl;
			out.close();
		}}
	else
	{
		cout << "Filing error"<<endl;}
}



void genreg(int n, string const& prefix = "" ){
    if (!n){
        fill(prefix);
        return;
    }
    genreg(n-1, prefix + '0');
    genreg(n-1, prefix + '1');
}

int sum(char x, char y, char s, char z){
	if (int(z)==(int(s)*int(x))^(1^int(s))*int(y)){
		return 1;
	}
	return 0;
}


void genl3(string z, string l1, string l2, int n, int c=0, string prefix = "") {
    if (!n) {
        for (int i=0; i<prefix.length(); i++)
        {
        	if (sum(l1[i],l2[i],prefix[i], z[i])==0){
        		return;
			}
		}
		int len=prefix.length();
		for (int i=0; i<z.length()-len; i++){
			prefix+=((((((((((prefix[i] ^ prefix[i+1])+'0')^prefix[i+2])+'0')^prefix[i+3])+'0')^prefix[i+5])+'0')^prefix[i+7])+'0');
			if (sum(l1[i+len],l2[i+len],prefix[i], z[i+len])==0){
				return;
			}	
		}
		ofstream out("result.txt", ios::app);
		out<<l1<<endl<<l2<<endl<<prefix<<endl;
		out.close();
        return;
    };
    if (l1[c]!=l2[c])
    {
    	(z[c]==l1[c] ? genl3(z, l1, l2, n-1, c+1, prefix + '1'): genl3(z, l1, l2, n-1, c+1, prefix + '0'));
	}
	else
	{
		genl3(z, l1, l2, n-1, c+1, prefix + '0');
   		genl3(z,l1, l2, n-1, c+1, prefix + '1');
	};
}


int main()
{
	int fnumber;
	do
	{
		cout << "Choose your function: 1 - count L1, 2 - count L2, 3 - count L3, 4 - Exit\n";
		cin >>	fnumber;
		switch (fnumber){
			case 1:
				cout <<"Counting L1...\n";
				genreg(30);
				break;
			case 2:
				cout <<"Counting L2...\n";
				genreg(31);
				break;
			case 3:
				cout <<"Counting L3...\n";
				ifstream file1("L1.txt");
					string l1;
				ifstream file2("L2.txt");
					string l2;
				string z = readfile();
				while(getline(file1, l1))
				{
					while(getline(file2, l2))
					{
						genl3(z, l1, l2, 32);
					}
				}
				break;
			}
	}
	while (fnumber!=4);
}
