/*
 * classifier.cpp
 *
 *  Created on: 11 may. 2017
 *      Author: elver
 */

#include "Classifier.h"

#include <iostream>
#include <experimental/filesystem>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace cv::ml;

namespace fs = std::experimental::filesystem;


Classifier::Classifier() {
	// TODO Auto-generated constructor stub

}

Classifier::~Classifier() {
	// TODO Auto-generated destructor stub
}

void Classifier::create_training_data(string path){

	vector<Mat> training_img_vector;
    for (auto & p : fs::directory_iterator(path)){

    	Mat aux_mat = imread(p.path().string());
    	// Check if image is loaded successfully
    	if(!aux_mat.data || aux_mat.empty())
    	{
    		cout << "Problem loading image " << p << " for training." << endl;
    	}

    	training_img_vector.push_back(aux_mat);
    }

    training_mat = Mat(training_img_vector.size(),(training_img_vector[0].rows * training_img_vector[0].cols),CV_32FC1);
    int img = 0;
    for (auto a : training_img_vector) {
    	int ii = 0; // Current column in training_mat
    	for (int i = 0; i<a.rows; i++) {
    	    for (int j = 0; j < a.cols; j++) {
    	        training_mat.at<float>(img,ii++) = a.at<uchar>(i,j);
    	    }
    	}
		img++;
    }

    int labels_data[] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};//labels hardcoded for now CHANGE THIS
    labels = Mat(training_mat.rows,1,CV_32SC1,labels_data);
    //training_mat.convertTo(training_mat,CV_32FC1);

	return;
}

void Classifier::create_svm(){

	svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::RBF);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 1000000, 1e-6));
	return;
}

void Classifier::train_svm(){

	svm->train(training_mat, ROW_SAMPLE, labels);
	cout << "SVM IS TRAINED : " << svm->isTrained() << " " << svm->isClassifier() << endl;
	svm->save("classifier_model");

	return;
}

void Classifier::model_load(){
	svm->load("classifier_model");
	cout << svm->isTrained() << endl;
}

void Classifier::get_card_number(Mat input_sample){
	float f = svm->predict(input_sample);
	cout << "PREDICIOTN IS : " << f << endl;
}
