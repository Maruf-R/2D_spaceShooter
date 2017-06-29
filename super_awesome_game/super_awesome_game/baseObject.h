#include "include\SDL.h"

/* Contains the location and position of objects, 
** setters and getters for them
*/

class baseObject{
protected:
	SDL_Rect position;

public:
	/*-------------------------------------
		setters
	-------------------------------------*/
	//for position
	void setX(int sx);
	void setY(int sy);
	void setH(int sh);
	void setW(int sw);

	/*-------------------------------------
		getters
	-------------------------------------*/
	//for getting the position values
	int getX();
	int getY();
	int getH();
	int getW();

	//for position
	SDL_Rect getPosition();
};