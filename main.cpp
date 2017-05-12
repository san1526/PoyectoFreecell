/*
 * main.cpp
 *
 *  Created on: 9 may. 2017
 *      Author: elver
 */

#include "Gameinstance.h"
#include <iostream>
#include "FrameProcessor.h"
#include "Classifier.h"

using namespace std;

int main(){

	Game_instance game;
	FrameProcessor framer;
	Classifier classifier;

	game.launch();
	game.window_move();
	game.window_resize(900,800);
	framer.grab_frame();
	framer.frame_preprocces();
	//framer.frame_show_debug();
	framer.get_card_images(false);
	classifier.create_training_data("/home/elver/Proyectos/p_Freecell/trainingData/numbers");
	classifier.create_clasiffier();
	classifier.train_clasiffier();
	//classifier.model_load();
	classifier.get_card_number(framer.get_sample(15));
	return 0;
}

