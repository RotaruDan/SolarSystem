//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Actor.h"
#include "vector"

#ifndef GroupH
#define GroupH

using namespace std;

class Group : public Actor {

	private:
		vector<Actor*> children;

		void drawChildren();

	public:
		Group();
		~Group();

		void addChildren(Actor* actor);
		void draw();

};

#endif