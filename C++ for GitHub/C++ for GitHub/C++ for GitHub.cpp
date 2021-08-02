#include <iostream>
#include <string.h>

class String
{
	size_t len;
	char* str;
public:
	String(size_t lenP) : len{ lenP }, str{ new char[lenP] {} } {}
	String(const char* strP) : len{ strlen(strP) }, str{ new char[strlen(strP) + 1] }
	{
		strcpy_s(str, strlen(strP) + 1, strP);
	}
	String(const String& object) : len{ object.len }, str{ new char[strlen(object.str) + 1] }
	{
		strcpy_s(str, strlen(object.str) + 1, object.str);
	}
	String(String&& object);

	String& setStr(const char* strP);

	String& enterStr()
	{
		std::cout << "Enter string not more " << getLen() << " symbols" << '\n';
		std::cin.getline(str, len);
		return *this;
	}

	size_t getLen()const { return len; }
	const char* getStr()const { return str; }

	String& operator=(const String& object);
	String& operator=(String&& object);
	friend std::ostream& operator<<(std::ostream& out, const String& object);

	char operator[](int idx) { return *(str + idx); }

	int operator()(int symb);
	int operator()(const char* found);
	operator int() { return strlen(str); }

	~String() { delete[] str; }
};

String& String::setStr(const char* strP)
{
	len = strlen(strP);
	delete[] str;
	str = new char[len + 1];
	strcpy_s(str, len + 1, strP);
	return *this;
}

String::String(String&& object) : len{ object.len }, str{ object.str }
{
	object.len = 0;
	object.str = nullptr;
}

String& String::operator=(const String& object)
{
	if (this == &object) { return *this; }

	delete[] str;

	len = object.len;
	str = new char[object.len + 1];
	strcpy_s(str, object.len + 1, object.str);

	return *this;
}

String& String::operator=(String&& object)
{
	if (this == &object) { return *this; }

	delete[] str;

	len = object.len;
	str = object.str;

	object.len = 0;
	object.str = nullptr;

	return *this;
}

std::ostream& operator<<(std::ostream& out, const String& object)
{
	if (object.str) { out << object.str << '\n'; }
	else { out << "[empty string]"; }
	return out;
}

int String::operator()(int symb)
{
	char* found{ strchr(str, symb) };

	return found ? (int)(found - str) : -1;
}

int String::operator()(const char* strFound)
{
	char* found{ strstr(str, strFound) };

	return found ? (int)(found - str) : -1;
}
int main()
{
	String string_1(80);
	string_1.enterStr();
	std::cout << string_1 << '\n';

	string_1.setStr("It's a wonderful world !");
	std::cout << string_1 << '\n';

	String string_2{ "Hello world !" };
	std::cout << string_2 << '\n';

	String copyString{ string_2 };
	std::cout << copyString << '\n';

	String string_3{ std::move(string_2) };
	std::cout << string_3 << '\n';
	std::cout << string_2 << '\n';
	std::cout << '\n';

	std::cout << string_3[4] << '\n';
	std::cout << string_3('o') << '\n';
	std::cout << string_3('g') << '\n';
	std::cout << '\n';

	std::cout << string_1("wor556ld") << '\n';
	std::cout << string_1("Hi") << '\n';

	std::cout << "The lenghs of string is - " << string_1.operator int() << " symbols" << '\n';

	return 0;
}
