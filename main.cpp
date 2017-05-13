/*
 * main.cpp
 *
 *  Created on: 9 may. 2017
 *      Author: elver
 */

#include "Gameinstance.h"
#include "FrameProcessor.h"
#include "Classifier.h"
#include "GameSolver.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){

	Game_instance game;
	FrameProcessor framer;
	Classifier cls;
	GameSolver solver;

	game.launch();
	game.window_move();
	game.window_resize(900,800);
	framer.grab_frame();
	framer.frame_preprocces();
	//framer.frame_show_debug();
	framer.get_card_images(false);
	cls.get_base_data();
	//cls.cmp_hist(framer.get_sample(atoi(argv[1])));
	cls.make_board(framer.get_cards_vector());
	solver.make_solution();
	solver.solution_parser();
	solver.try_solve();

	return 0;
}

