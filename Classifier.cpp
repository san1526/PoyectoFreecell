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

    	Mat aux_mat = imread(p.path().string(),0);
    	// Check if image is loaded successfully
    	if(!aux_mat.data || aux_mat.empty())
    	{
    		cout << "Problem loading image " << p << " for training." << endl;
    	}

    	training_img_vector.push_back(aux_mat);
    }

    for (auto a : training_img_vector) {
    	Mat float_data;
    	a.convertTo(float_data,CV_32F);
    	training_mat.push_back(float_data.reshape(0, 1));
    }
    int labels_data[] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};//labels hardcoded for now CHANGE THIS
    labels = Mat(training_mat.rows,1,CV_32S,labels_data);

	return;
}

void Classifier::create_clasiffier(){

	kne = KNearest::create();
	kne->setDefaultK(10);

	return;
}

void Classifier::train_clasiffier(){
	Mat nMat(0,0,CV_32F);
	training_mat.convertTo(nMat,CV_32F);
	kne->train(nMat, ROW_SAMPLE, labels);
	kne->save("kne-model");
	//TODO : add save function
	return;
}

void Classifier::model_load(){

	//kne->load("kne-model");
	//TODO : add load function

	return;
}

void Classifier::get_card_number(Mat input_sample){
	Mat results(0,0,CV_32S);
	kne->findNearest(input_sample,kne->getDefaultK(),results);
	cout << "PREDICIOTN IS : " << results << endl;
}
