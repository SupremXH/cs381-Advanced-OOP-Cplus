#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
class BigInteger {
public:
	char *arr;
	int size;
	BigInteger(char *arr, int size) {
		this->arr = arr;
		this->size = size;
	}
	BigInteger(string s) {
		size = s.length();
		arr = new char[size];
		for (int i = 0; i < size; i++) {
			arr[i] = s.at(size - 1 - i);
		}
	}
	BigInteger operator -(BigInteger &b) {
		int carry = 0;
		char *c = new char[size];
		for (int i = 0; i < b.size; i++) {

			int sum = (arr[i] - '0' - (b.arr[i] - '0') - carry);
			if (sum < 0) {
				sum += 10;
				carry = 1;
			} else
				carry = 0;
			c[i] = sum + '0';
		}
		c[b.size] = arr[b.size] + carry;
		for (int i = b.size + 1; i < size; i++) {
			c[i] = arr[i];
		}
		BigInteger d(c, size);
		return d;
	}
	BigInteger operator +(BigInteger &b) {
		int carry = 0;
		int length = size > b.size ? size : b.size;
		char *c = new char[length];
		int i = 0;
		for (i = 0; i < size && i < b.size; i++) {
			int sum = (arr[i] - '0' + b.arr[i] - '0' + carry);
			c[i] = sum % 10 + '0';
			carry = sum / 10;
		}
		while (i < size) {
			int sum = (arr[i] - '0' + carry);
			c[i] = sum % 10 + '0';
			carry = sum / 10;
			i++;
		}
		while (i < b.size) {
			int sum = (b.arr[i] - '0' + carry);
			c[i] = sum % 10 + '0';
			carry = sum / 10;
			i++;
		}
		if (carry > 0) {
			length++;
			char *temp = new char[length];
			temp[length] = carry + '0';
			c = temp;
		}
		BigInteger d(c, length);
		return d;
	}
	BigInteger operator *(BigInteger &b) {
		char *c = new char[size + b.size];
		int n1 = 0;
		int n2 = 0;
		for (int i = 0; i < size + b.size; i++)
			c[i] = '0';
		for (int i = 0; i < size; i++) {
			int carry = 0;
			n2 = 0;
			for (int j = 0; j < b.size; j++) {
				int sum = (arr[i] - '0') * (b.arr[j] - '0') + c[n1 + n2] - '0'
						+ carry;
				carry = sum / 10;
				c[n1 + n2] = sum % 10 + '0';
				n2++;
			}
			if (carry > 0)
				c[n1 + n2] += carry;
			n1++;
		}
		BigInteger d(c, size + b.size);
		return d;
	}
	friend ostream& operator <<(ostream &os, BigInteger b);
};

ostream& operator <<(ostream &os, BigInteger b) {
	for (int i = b.size - 1; i >= 0; i--)
		cout << b.arr[i];
	cout << endl;
	return os;
}
;
int main() {
	BigInteger a("2345566777844567");
	BigInteger b("9999988777765768009998");
	cout<<"a:"<<endl;
	cout << a;
	cout<<"b:"<<endl;
	cout << b;
	BigInteger c = a + b;
	cout<<"a+b:"<<endl;
	cout << c;
	BigInteger d = b - a;
	cout<<"b-a:"<<endl;
	cout << d;
	BigInteger e = a * b;
	cout<<"a*b:"<<endl;
	cout << e;
}

