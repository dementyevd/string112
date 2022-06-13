#include<iostream>

using namespace std;

class String112 {
	char* str{ nullptr };
	int len{ 0 };
public:
	String112() {

	}

	String112(const char* str) {
		this->len = strlen(str);
		this->str = new char[this->len + 1];
		strcpy_s(this->str, this->len + 1, str);
	}

	String112(int cnt, char s) {
		this->len = cnt;
		this->str = new char[this->len + 1];
		for (int i = 0; i < this->len; i++) {
			this->str[i] = s;
		}
		this->str[this->len] = '\0';
	}

	String112(const char* str, int len) {
		this->len = len;
		this->str = new char[len + 1];
		for (int i = 0; i < len; i++) {
			this->str[i] = str[i];
		}
		this->str[this->len] = '\0';
	}

	String112& setString(const String112& right) {
		this->Clear();
		if (right.str != nullptr) {
			this->len = right.len;
			this->str = new char[this->len + 1];
			strcpy_s(this->str, this->len + 1, right.str);
		}
		return *this;
	}

	void addString(const String112& right) {
		if (right.str == nullptr) return;
		if (this->str == nullptr) {
			this->setString(right);
			return;
		}
		this->len += right.len;
		char* nstr = new char[this->len + 1];
		strcpy_s(nstr, this->len + 1, this->str);
		strcat_s(nstr, this->len + 1, right.str);
		delete[] this->str;
		this->str = nstr;
	}

	void print() const {
		if (this->str != nullptr)
			cout << this->str;
	}

	void Clear() {
		if (this->str != nullptr) {
			delete[] this->str;
			this->str = nullptr;
			this->len = 0;
		}
	}

	String112(const String112& obj) {
		if (obj.str != nullptr) {
			this->len = obj.len;
			this->str = new char[obj.len + 1];
			strcpy_s(this->str, this->len + 1, obj.str);
		}
	}

	String112& operator=(const String112& obj) {
		if (this == &obj)
			return *this;
		this->~String112();
		if (obj.str != nullptr) {
			this->len = obj.len;
			this->str = new char[obj.len + 1];
			strcpy_s(this->str, this->len + 1, obj.str);
		}
		return *this;
	}

	String112(String112&& obj) {
		swap(this->str, obj.str);
		swap(this->len, obj.len);
	}

	String112& operator=(String112&& obj) {
		if (this == &obj)
			return *this;
		swap(this->str, obj.str);
		swap(this->len, obj.len);
		obj.Clear();
		return *this;
	}

	String112& operator+=(const String112& s) {
		this->addString(s);
		return *this;
	}

	int length() const { return this->len; }

	~String112() {
		if (this->str != nullptr) {
			delete[] str;
			this->str = nullptr;
			this->len = 0;
		}
	}

	char& operator[](int index) {
		return this->str[index];
	}

	const char& operator[](int index) const {
		return this->str[index];
	}

	void reverse() {
		for (int i = 0; i < this->len / 2; i++) {
			swap(this->str[i], this->str[this->len - i - 1]);
		}
	}

	bool empty() const {
		return this->str == nullptr;
	}

	void replace(char from, char to) {
		for (int i = 0; i < this->len; i++) {
			if (this->str[i] == from)
				this->str[i] = to;
		}
	}

	void remove(char a) {
		int count = 0;
		for (int i = 0; i < this->len; i++) {
			if (this->str[i] == a)
				count++;
		}
		char* nstr = new char[this->len - count + 1];
		for (int i = 0, k = 0; i < this->len + 1; i++) {
			if (this->str[i] != a) {
				nstr[k] = this->str[i];
				k++;
			}
		}
		this->len -= count;
		delete[] this->str;
		this->str = nstr;
	}

	friend ostream& operator<<(ostream& os, const String112& s);
	friend istream& operator>>(istream& is, String112& s);
	friend bool operator==(const String112& a, const String112& b);
	friend bool operator>(const String112& a, const String112& b);
	friend bool operator<(const String112& a, const String112& b);
};

bool operator==(const String112& a, const String112& b) {
	if (a.len != b.len)
		return false;
	for (int i = 0; i < a.len; i++) {
		if (a.str[i] != b.str[i])
			return false;
	}
	return true;
}

bool operator!=(const String112& a, const String112& b) {
	return !(a == b);
}

bool operator>(const String112& a, const String112& b) {
	if (a.len != b.len)
		return a.len > b.len;
	int sumA = 0;
	int sumB = 0;
	for (int i = 0; i < a.len; i++) {
		sumA += int(a.str[i]);
	}
	for (int i = 0; i < a.len; i++) {
		sumB += int(b.str[i]);
	}
	return sumA > sumB;
}

bool operator>=(const String112& a, const String112& b) {
	return (a > b || a == b);
}

bool operator<(const String112& a, const String112& b) {
	if (a.len != b.len)
		return a.len < b.len;
	int sumA = 0;
	int sumB = 0;
	for (int i = 0; i < a.len; i++) {
		sumA += int(a.str[i]);
	}
	for (int i = 0; i < a.len; i++) {
		sumB += int(b.str[i]);
	}
	return sumA < sumB;
}

bool operator<=(const String112& a, const String112& b) {
	return (a < b || a == b);
}

String112 operator+(const String112& s1, const String112& s2) {
	String112 tmp = s1;
	tmp += s2;
	return tmp;
}

ostream& operator<<(ostream& os, const String112& s) {
	s.print();
	return os;
}

istream& operator>>(istream& is, String112& s) {
	char* str = new char[1000000];
	is >> str;
	//is.getline(str, 100000);
	s.setString(str);
	delete[] str;
	return is;
}

void main() {
	String112 s;
	String112 s1 = "H";
	String112 s3 = "h";
	s1 > s3 ? cout << "Yes" : cout << "No";
}