

#ifndef VLE_UTILS_STATE_HPP
#define VLE_UTILS_STATE_HPP

#include <iostream>
#include <vector>
//#include <pair>
#include <utility>

namespace vle { namespace utils {






struct Position
{
	int i;
	int j;
};


class State 
{
	/*public:
	static std::vector<State *> states;
	static int n;
	
	 State () {lastMasse=0;elapsed=0;}
	 State (Position pos) { p = pos;states.emplace_back(this); n++;lastMasse=0;}
	 State (Position pos, std::string v) { p = pos; val = v;states.emplace_back(this);n++;lastMasse=0;}
	 State (int i, int j, std::string v) { p.i=i; p.j=j;  val=v; states.emplace_back(this);n++;lastMasse=0;}
	 State (int i, int j, std::string v,float t, float m) { p.i=i; p.j=j;  val=v; states.emplace_back(this);n++; temperature=t; masse=m; lastMasse=m;}
	 virtual ~State () = default;
	 
	 
	 static int nb();
	 int nbs() {return n;}
	/* 
	 virtual void setState(int i, int j, std::string v) 
		 {
			 p.i=i; p.j=j ;val=v;
		 } 
	 virtual void setState(int i, int j, std::string v, float t, float m) 
		 {
			 p.i=i; p.j=j ;val=v; temperature=t; masse=m; lastMasse=m; 
		 }
		  virtual void setState(int i, int j, std::string v, float t, float m, int e) 
		 {
			 p.i=i; p.j=j ;val=v; temperature=t; masse=m; lastMasse=m; elapsed = e;
		 }
	  virtual void setTemperature(float t)
		 {
			 temperature = t;
		 }
	  virtual float getTemperature ()
	  {
		  return temperature;
	  }
	  
	  virtual void setMasse(float m)a
	  {
		  lastMasse = masse;
		  masse = m;
	  }
	  
	  virtual float getMasse()
	  {
		  return masse;
	  }
	   virtual float getlastMasse()
	  {
		  return lastMasse;
	  }
	 
	virtual Position getPosition() {return p;} 
	virtual void setPosition(Position pos) {p = pos;} 
	virtual std::string getVal() {return val;}
	virtual void setVal(std::string v) {val=v;}
	virtual void setElapsed(int e) {elapsed = e;}
	virtual int getElapsed(){ return elapsed;}
	virtual 
	virtual 
	 
	 private:
	 
	 Position p;
	 std::string val; 
	 float temperature;
	 float masse;
	 float lastMasse;
	 int elapsed;
	 */
	 
	 
	 
	 
	 public:
	static std::vector<State *> states;
	static int n;
	 //std::vector<Position> voisinage = {(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)};  
	 std::vector<std::pair<int, int>> voisinage = {{-2,-2},{-1,-1},{-1,0},{-1,1},{-2,2},{0,-1},{0,1},{2,-2},{1,-1},{1,0},{1,1},{2,2}};
	
	 State () {lastMasse=0;elapsed=0;}
	 State (Position pos) { p = pos;states.emplace_back(this); n++;lastMasse=0;}
	 State (Position pos, std::string v) { p = pos; val = v;states.emplace_back(this);n++;lastMasse=0;}
	 State (int i, int j, std::string v) { p.i=i; p.j=j;  val=v; states.emplace_back(this);n++;lastMasse=0;}
	 State (int i, int j, std::string v,float t, float m) { p.i=i; p.j=j;  val=v; states.emplace_back(this);n++; temperature=t; masse=m; lastMasse=m;}
	 ~State () = default;
	 
	 void setState(int i, int j, std::string v) 
		 {
			 p.i=i; p.j=j ;val=v;
		 } 
	 void setState(int i, int j, std::string v, float t, float m) 
		 {
			 p.i=i; p.j=j ;val=v; temperature=t; masse=m; lastMasse=m; 
		 }
		  void setState(int i, int j, std::string v, float t, float m, int e) 
		 {
			 p.i=i; p.j=j ;val=v; temperature=t; masse=m; lastMasse=m; elapsed = e;
		 }
	  void setTemperature(float t)
		 {
			 temperature = t;
		 }
	  float getTemperature ()
	  {
		  return temperature;
	  }
	  
	  void setMasse(float m)
	  {
		  lastMasse = masse;
		  masse = m;
	  }
	  
	  float getMasse()
	  {
		  return masse;
	  }
	   float getlastMasse()
	  {
		  return lastMasse;
	  }
	 
	Position getPosition() {return p;} 
	void setPosition(Position pos) {p = pos;} 
	std::string getVal() {return val;}
	void setVal(std::string v) {val=v;}
	void setElapsed(int e) {elapsed = e;}
	int getElapsed(){ return elapsed;}
	static int nb();
	int nbs() {return n;}
	 
	 private:
	 
	 Position p;
	 std::string val; 
	 float temperature;
	 float masse;
	 float lastMasse;
	 int elapsed;
	 
	 
	 
	
	
};

}} // namespace vle utils

#endif
