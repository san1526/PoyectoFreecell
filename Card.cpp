/*
 * Card.cpp
 *
 *  Created on: 11 may. 2017
 *      Author: elver
 */

#include "Card.h"

Card::Card(string str, Mat crd) {
	card = crd;
	name = str;
}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

Mat Card::get_card_mat(){
	return card;
}

string Card::get_card_name(){
	return name;
}
