

#ifndef VLE_UTILS_STATE_HPP
#define VLE_UTILS_STATE_HPP

#include <iostream>
#include <vector>

namespace vle { namespace utils {






struct Position
{
	int i;
	int j;
};


class State 
{
	public:
	static std::vector<State *> states;
	static int n;
	
	 State () {}
	 State (Position pos) { p = pos;states.emplace_back(this); n++;}
	 State (Position pos, std::string v) { p = pos; val = v;states.emplace_back(this);n++;}
	 State (int i, int j, std::string v) { p.i=i; p.j=j;  val=v; states.emplace_back(this);n++;}
	 ~State () = default;
	 
	 void setState(int i, int j, std::string v) 
		 {
			 p.i=i; p.j=j ;val=v;
		 } 
	
	 
	Position getPosition() {return p;} 
	void setPosition(Position pos) {p = pos;} 
	std::string getVal() {return val;}
	void setVal(std::string v) {val=v;}
	
	static int nb();
	int nbs() {return n;}
	 
	 private:
	 
	 Position p;
	 std::string val; 
	 
	 
	
	
};

}} // namespace vle utils

#endif
