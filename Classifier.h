/*
 * classifier.h
 *
 *  Created on: 11 may. 2017
 *      Author: elver
 */

#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

#include "Card.h"
#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace cv::ml;

using namespace std;

class Classifier {
private:
	vector<Card> cards;
public:
	Classifier();
	virtual ~Classifier();
	void get_base_data(string = "./numbers");
	string cmp_hist(Mat);
	void make_board(vector<Mat> cards_vec);
};

#endif /* CLASSIFIER_H_ */
