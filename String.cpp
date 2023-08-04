#include "String.h"
#include <math.h>

String::String() : m_str(nullptr), m_length(0)
{}
String::String(char str) : m_str(&str), m_length(1)
{}

String::String(char* str) : m_str(new char[strlen(str) + 1]), m_length(static_cast<int>(strlen(str)))
{
	strcpy(m_str, str);
}

String::String(const char* str) : m_str(new char[strlen(str) + 1]), m_length(static_cast<int>(strlen(str)))
{
	strcpy(m_str, str);
}

String::String(const String& original) : m_str(new char[strlen(original.m_str) + 1]), m_length(original.m_length)
{
	strcpy(m_str, original.m_str);
}

String::String(String&& original) noexcept : m_str(original.m_str), m_length(original.m_length)
{}

String::~String() {
	if (m_str != nullptr && m_length > 1)
		delete[] m_str;
	else if (m_str != nullptr)
		delete m_str;
	m_length = 0;
}

String& String::operator = (const String& rhs) {
	if (this != &rhs) {
		if (rhs.m_str != nullptr) {
			delete[] m_str;
			m_str = new char[strlen(rhs.m_str) + 1];
			strcpy(m_str, rhs.m_str);
		}
		else if (rhs.m_str == nullptr) {
			delete[] m_str;
		}
	}
	m_length = rhs.m_length;
	return *this;
}

String& String::operator = (String&& rhs) noexcept {
	if (this != &rhs) {
		if (rhs.m_str != nullptr) {
			delete[] m_str;
			m_str = new char[strlen(rhs.m_str) + 1];
			strcpy(m_str, rhs.m_str);
		}
		else if (rhs.m_str == nullptr) {
			delete[] m_str;
		}
	}
	m_length = rhs.m_length;
	return *this;
}


bool String::operator < (const String& rhs) {
	bool retVal = false;
	if (m_str != nullptr && rhs.m_str != nullptr) {
		if (strcmp(m_str, rhs.m_str) < 0)
			retVal = true;
	}
	else if (rhs.m_str != nullptr)
		retVal = true;
	return retVal;
}

bool String::operator < (String&& rhs) {
	bool retVal = false;
	if (m_str != nullptr && rhs.m_str != nullptr) {
		if (strcmp(m_str, rhs.m_str) < 0)
			retVal = true;
	}
	else if (rhs.m_str != nullptr)
		retVal = true;
	return retVal;
}

bool String::operator < (const String& rhs) const {
	bool retVal = false;
	if (m_str != nullptr && rhs.m_str != nullptr) {
		if (strcmp(m_str, rhs.m_str) < 0)
			retVal = true;
	}
	else if (rhs.m_str != nullptr)
		retVal = true;
	return retVal;
}

bool String::operator > (const String& rhs) {
	bool retVal = false;
	if (m_str != nullptr && rhs.m_str != nullptr) {
		if (strcmp(m_str, rhs.m_str) > 0)
			retVal = true;
	}
	else if (m_str != nullptr)
		retVal = true;
	return retVal;
}

bool String::operator > (String&& rhs) {
	bool retVal = false;
	if (m_str != nullptr && rhs.m_str != nullptr) {
		if (strcmp(m_str, rhs.m_str) > 0)
			retVal = true;
	}
	else if (m_str != nullptr)
		retVal = true;
	return retVal;
}

bool String::operator > (const String& rhs) const {
	bool retVal = false;
	if (m_str != nullptr && rhs.m_str != nullptr) {
		if (strcmp(m_str, rhs.m_str) > 0)
			retVal = true;
	}
	else if (m_str != nullptr)
		retVal = true;
	return retVal;
}

bool String::operator <= (const String& rhs) {
	bool retVal = false;
	retVal = !(m_str > rhs.m_str);
	return retVal;
}

bool String::operator <= (String&& rhs) {
	bool retVal = false;
	retVal = !(m_str > rhs.m_str);
	return retVal;
}

bool String::operator <= (const String& rhs) const {
	bool retVal = false;
	retVal = !(m_str > rhs.m_str);
	return retVal;
}

bool String::operator == (const String& rhs) {
	bool retVal = false;
	if (rhs.m_str != nullptr && m_str != nullptr)
		retVal = (strcmp(m_str, rhs.m_str) == 0);
	else if (rhs.m_str == nullptr && m_str == nullptr)
		retVal = true;
	return retVal;
}

bool String::operator == (String&& rhs) {
	bool retVal = false;
	if (rhs.m_str != nullptr && m_str != nullptr)
		retVal = (strcmp(m_str, rhs.m_str) == 0);
	else if (rhs.m_str == nullptr && m_str == nullptr)
		retVal = true;
	return retVal;
}

bool String::operator == (const String& rhs) const {
	bool retVal = false;
	if (rhs.m_str != nullptr && m_str != nullptr)
		retVal = (strcmp(m_str, rhs.m_str) == 0);
	else if (rhs.m_str == nullptr && m_str == nullptr)
		retVal = true;
	return retVal;
}


bool String::operator >= (const String& rhs) {
	bool retVal = false;
	retVal = !(m_str < rhs.m_str);
	return retVal;
}

bool String::operator >= (String&& rhs) {
	bool retVal = false;
	retVal = !(m_str < rhs.m_str);
	return retVal;
}

bool String::operator >= (const String& rhs) const {
	bool retVal = false;
	retVal = !(m_str < rhs.m_str);
	return retVal;
}


bool String::operator != (const String& rhs) {
	bool retVal = false;
	retVal = !(m_str == rhs.m_str);
	return retVal;
}

bool String::operator != (String&& rhs) {
	bool retVal = false;
	retVal = !(m_str == rhs.m_str);
	return retVal;
}

bool String::operator != (const String& rhs) const {
	bool retVal = false;
	retVal = !(m_str == rhs.m_str);
	return retVal;
}


String& String::operator ++() {
	if (m_str != nullptr)
		_strupr(m_str);
	return *this;
}

String String::operator ++(int) {
	String temp(*this);
	++(*this);
	return temp;
}


String& String::operator --() {
	if (m_str != nullptr)
		_strlwr(m_str);
	return *this;
}

String String::operator --(int) {
	String temp(*this);
	--(*this);
	return temp;
}

void String::operator += (const String& rhs) {
	if (m_str != nullptr && rhs.m_str != nullptr) {
		char* temp = new char[strlen(m_str) + strlen(rhs.m_str) + 1];
		strcpy(temp, m_str);
		strcat(temp, rhs.m_str);
		delete[] m_str;
		m_str = temp;
		m_length = static_cast<int>(strlen(m_str));
	}
	else if (m_str == nullptr && rhs.m_str != nullptr) {
		m_str = new char[strlen(rhs.m_str) + 1];
		strcpy(m_str, rhs.m_str);
		m_length = rhs.m_length;
	}
}

void String::operator += (String&& rhs) {
	if (m_str != nullptr && rhs.m_str != nullptr) {
		char* temp = new char[strlen(m_str) + strlen(rhs.m_str) + 1];
		strcpy(temp, m_str);
		strcat(temp, rhs.m_str);
		delete[] m_str;
		m_str = temp;
		m_length = static_cast<int>(strlen(m_str));
	}
	else if (m_str == nullptr && rhs.m_str != nullptr) {
		m_str = new char[strlen(rhs.m_str) + 1];
		strcpy(m_str, rhs.m_str);
		m_length = rhs.m_length;
	}
}

String String::operator + (const String& rhs) {
	String temp(*this);
	temp += rhs;
	return temp;
}

String String::operator +(String&& rhs) {
	String temp(*this);
	temp += rhs;
	return temp;
}





char& String::operator[](int index) {
	if (index > m_length)
		index = m_length - 1;
	else if (index < 0)
		index = 0;
	return m_str[index];
}

char String::operator[](int index) const {
	if (index > m_length)
		index = m_length - 1;
	else if (index < 0)
		index = 0;
	return m_str[index];
}

int String::sToI() {
	int retVal = 0;


	for (int index = 0; index != m_length; ++index) {
		retVal += (m_str[index] - 48) * static_cast<int>(pow(10, m_length - index - 1));
	}
	return retVal;
}


int String::getLength() {
	return m_length;
}

const char* String::getStr() const {
	return m_str;
}

const char* String::getStr() {
	return m_str;
}


ostream& operator << (ostream& str, const String& rhs) {
	if (rhs.getStr() != nullptr)
		str << rhs.getStr();
	else
		str << "";
	return str;
}