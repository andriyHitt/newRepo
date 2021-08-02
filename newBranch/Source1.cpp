#include <iostream>

class String
{
	int len;
	char* str;
public:
	String(int lenP) : len{ lenP }, str{ new char[lenP] {} } {}
	String(const char* strP) : str{ initStr(strP) } {}
	String(const String& object) : len{ object.len }, str{ initStr(object.str) }{}

	String& setStr(const char* strP);
	char* initStr(const char* strP);

	String& enterStr()
	{
		std::cout << "Enter string not more " << getLen() << " symbols" << '\n';
		std::cin.getline(str, len);
		return *this;
	}

	String& print() { std::cout << str << '\n'; return *this; }

	int getLen()const { return len; }
	const char* getStr()const { return str; }

	~String() { delete[] str; }
};

String& String::setStr(const char* strP)
{
	len = strlen(strP) + 1;
	if (!str) { str = new char[len]; }
	else if (str and strlen(str) + 1 < len)
	{
		delete[] str;
		str = new char[len];
	}
	strcpy_s(str, len, strP);
	return *this;
}

char* String::initStr(const char* strP)
{
	len = strlen(strP) + 1;
	str = { new char[len] };
	strcpy_s(str, len, strP);
	return str;
}
int main()
{
	String string_1(80);
	string_1.enterStr().print();
	std::cout << '\n';

	string_1.setStr("It's a wonderful world !").print();
	std::cout << '\n';

	String string_2{ "Hello world !" };
	string_2.print();
	std::cout << '\n';

	String copyString{ string_2 };
	copyString.print();

	return 0;
}