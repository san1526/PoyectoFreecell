/*
 * main.cpp
 *
 *  Created on: 9 may. 2017
 *      Author: elver
 */

#include "Gameinstance.h"
#include <iostream>
#include "FrameProcessor.h"

using namespace std;

int main(){

	Game_instance game;
	FrameProcessor framer;

	game.launch();
	game.window_move();
	game.window_resize(900,800);
	framer.grab_frame();
	framer.frame_preprocces();
	//framer.frame_show_debug();
	framer.get_card_images();
	return 0;

}

