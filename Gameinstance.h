/*
 * Gameinstance.h
 *
 *  Created on: 9 may. 2017
 *      Author: elver
 */

#ifndef GAMEINSTANCE_H_
#define GAMEINSTANCE_H_

class Game_instance {
private:
	int window;

public:
	Game_instance();
	virtual ~Game_instance();
	void launch();
	void window_move();
	char* get_window_as_string();
	int get_window();
	void window_resize(int x, int y);
};

#endif /* GAMEINSTANCE_H_ */
