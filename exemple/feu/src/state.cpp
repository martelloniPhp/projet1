
/*
* @@tagdynamic@@
* @@tagdepends:@@endtagdepends
*/


#include <iostream>
#include <vector>
#include <vle/utils/State.hpp>

namespace feu {






struct Position
{
	int i;
	int j;
};


class Etat : public vle::utils::State
{
	public:
	std::vector<std::pair<int, int>> voisinage2 = {{-3,0},{-2,-2},{-1,-1},{-1,0},{-1,1},{-2,2},{0,-3},{0,-1},{0,1},{0,3},{2,-2},{1,-1},{1,0},{1,1},{2,2},{3,0}};
	//std::vector<std::pair<int, int>> voisinage2 = {{-2,0},{-1,-1},{-1,0},{-1,1},{0,-2},{0,-1},{0,1},{0,2},{1,-1},{1,0},{1,1},{2,0}};
	/*static std::vector<State *> states;
	static int n;
	static std::vector<Position> voisinage = {(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)};
	*/
	 Etat() : vle::utils::State()
	 {
		// val = "0";
	 }
	 ~Etat() = default;
	 
	 
	
	
	 
	
	
};

} // exemple


