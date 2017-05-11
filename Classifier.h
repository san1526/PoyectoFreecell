/*
 * classifier.h
 *
 *  Created on: 11 may. 2017
 *      Author: elver
 */

#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace cv::ml;

using namespace std;

class Classifier {
private:
	Ptr<SVM> svm;
	Mat training_mat;
	Mat labels;
public:
	Classifier();
	virtual ~Classifier();
	void create_training_data(string path);
	void create_svm();
	void train_svm();
	void model_load();
	void get_card_number(Mat input_sample);
};

#endif /* CLASSIFIER_H_ */
