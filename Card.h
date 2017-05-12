/*
 * Card.h
 *
 *  Created on: 11 may. 2017
 *      Author: elver
 */

#ifndef CARD_H_
#define CARD_H_

#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace cv::ml;

using namespace std;

class Card {
private:
	Mat card;
	string name;
public:
	Card(string, Mat);
	virtual ~Card();
	Mat get_card_mat();
	string get_card_name();
};

#endif /* CARD_H_ */
