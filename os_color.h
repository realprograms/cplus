#ifndef _OS_COLOR_H
#define _OS_COLOR_H

// Color Manipulor Header File
// for Windows

1: Blue
2: Green
3: Cyan
4: Red
5: Purple
6: Yellow (Dark)
7: Default white
8: Gray/Grey
9: Bright blue
10: Brigth green
11: Bright cyan
12: Bright red
13: Pink/Magenta
14: Yellow
15: Bright white

inline void SetColor(WORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// helper class
class color {
    int  c_val;
public:
	color(int val) : m_val(val) { }

	void set() const {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
};

// instances of helper class to avoid need to remember 4 is red, etc
static const color red(4);
static const color green(2);
static const color blue(1);
static const color white(7);
// etc

// overload operator<< to get manipulator to work
inline std::ostream& operator<<(std::ostream& os, const color& c) {
	c.set();
	return os;
}

#endif  // _OS_COLOR_H