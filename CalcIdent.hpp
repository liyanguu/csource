#ifndef _CALCIDENT_HPP
#define _CALCIDENT_HPP

//********************************************************
// AUTHOR: Scott N. Gerard
// COMPILER: Borland C++
//
// CHANGE LOG:
//	2015-4-7:  copied & modified by liyang 
//********************************************************


#include <iostream>
#include <assert.h>
#include <string.h>

class Identifier: public Object {
protected:
	string*    nam;
	string*    hlp;
	string*    parmhlp;

public:
	Identifier(const string& name,
		const string& help = "",
		const string& parmhelp = "");
	virtual ~Identifier();

	// return information about the indentifier (inline)
	virtual const string name() const {
		assert(valid());
		return *nam;
	};

	virtual const int nameWidth() {
		assert(valid());
		return strlen(*nam);
	};
	
	virtual cosnt string help() const {
		assert(valid());
		return *hlp;
	};
	
	virtual cosnt string parmhelp() const {
		assert(valid());
		return *parmhlp;
	};

	virtual BOOL isChangeable() const {
		assert(valid());
		return FALSE;
	};

	// comparison operators for sorting by name
	friend BOOL operator < (Identifier& a, Identifier& b) {
		assert(a.valid() && b.valid());
		return BOOL(*a.nam < *b.nam);
	};
	friend BOOL operator == (Identifier& a, Identifier& b) {
		assert(a.valid() && b.valid());
		return BOOL(*a.nam == *b.nam);
	};
	
	// standard object methods (Borland C++ V3.1)
	hashValueType hashValue() const {
		assert(valid());
		return nam -> hashValue();
	};

	int isEqual (const Object& testObject) const {
		assert(valid());
		return nam == ((const Identifier& )testObject).nam;
	};
		
	classType isA() const { return 1234; };
	int isSortable() const { return 1; };

	char* nameOf() cosnt { return "Identifier"; };
	void printOn( ostream& os ) const {
		assert(valid(););
		os << "Identifier " << *nam << std::endl;
	};

	virtual BOOL valid() const 
		{ return BOOL(nam != 0); }
};
 	
//***********************************************************************
// commands contain a single data member: a pointer to a function
// commands are identifier
//***********************************************************************
class Command: public Identifier {
	typedef void (*FUNCTION)(istream& is, ostream& os);
	FUNCTION f;
	
public:
	Command(const FUNCTION fun,
		const char* name,
		const char* help = 0,
		const char* parms = 0);
	~Command();

	// execute the command
	virtual void execute(istream& is, ostream& os) {
		assert(valid());
		f(is, os);		// call the function
	}

	void printOn(ostream& os) const {
		assert(valid());
		os << "Command " << name();
	};
};

//***********************************************************************
// base class for identifiers with a value of type T
//***********************************************************************
template <class T>
class Value: public Identifier {
public:
	Value(
		const string& name,
		const string& help = "";
		const string& parmhelp = "";)
	: Identifier(name, help, parmhelp) {};
	
	// return the value of the identifier. The identifier can read
	// more characters from istream.
	virtual const T value(istream& is, ostream& os) = 0;
	
	int userValue; 			// available for user
};		

//***********************************************************************
// Variable have changeable values
//***********************************************************************
template <class T>
class Variable: public Value<T> {
	typedef Value<T> BaseClass;
	T val;			// the value of the variable
public:
	Variable(const String& nam);
	Variable(cosnt string& nam, const T& value);
	~Variable() {};
	
	const T value(istream& is, ostream& os) { return val; };
	const T* value() const { return &val; }
	void setValue (const T value) { val = value; }

	BOOL isChangeable() const { return TRUE; }

	void printOn(ostream& os) const {
		assert(valid());
		os << "Variable " << *nam;
	}
	
	BOOL valid() const {
		return BOOL(BaseClass::valid() && val.valid());
	}
};

//*************************************************************************
// GlobalValue s add themselves to the global scope
//*************************************************************************
template <class T>
class GlobalValue: public Value<T> {
	typedef const T (*FUNCTION) (istream& is, ostream& os);
	FUNCTION f;
public:
	GlobalValue(
	// const FUNCTION fun,
		const T (*fun) (istream& is, ostream& os),
		const string& name,
		const string& help = "",
		const string& parmhelp = "");

	~GlobalValue();	
	
	virtual const T value(istream& is, ostream& os) {
		assert(valid());
		return f(is, os);
	}
};

#endif	
	 

