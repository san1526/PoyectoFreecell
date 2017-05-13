/*
 * classifier.cpp
 *
 *  Created on: 11 may. 2017
 *      Author: elver
 */

#include "Classifier.h"
#include "Card.h"
#include <iostream>
#include <fstream>
#include <string>
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

void Classifier::get_base_data(string path){

	vector<Mat> training_img_vector;
    for (auto & p : fs::directory_iterator(path)){
    	Mat aux_mat = imread(p.path().string());
    	// Check if image is loaded successfully
    	if(!aux_mat.data || aux_mat.empty())
    	{
    		cout << "Problem loading image " << p << " for training." << endl;
    	}

    	cards.push_back(Card(p.path().filename().string(),aux_mat));
    }
	return;
}

string Classifier::cmp_hist(Mat sample){
	if(sample.size != cards[0].get_card_mat().size){
		sample.resize(cards[0].get_card_mat().rows);
		resize(sample, sample, Size(cards[0].get_card_mat().cols,cards[0].get_card_mat().rows));
	}
	sample.convertTo(sample, CV_32F);
	double low = 10;int i = 0, c = 0;
	for(auto a : cards){
		Mat aux;
		a.get_card_mat().convertTo(aux,CV_32F);
		double cmp = compareHist(sample, aux, CV_COMP_CORREL);
		if(fabs(cmp) < fabs(low)){
			low = cmp;
			c = i;
		}
		i++;
	}

	return cards[c].get_card_name();
}

void Classifier::make_board(vector<Mat> cards){

	ofstream board;
	board.open("board");

	for(int i = 51; i > 2; i=i-8)
		board << cmp_hist(cards[i]) << " ";
	board << '\n';
	for(int i = 50; i > 1; i=i-8)
		board << cmp_hist(cards[i]) << " ";
	board << '\n';
	for(int i = 49; i > 0; i=i-8)
		board << cmp_hist(cards[i]) << " ";
	board << '\n';
	for(int i = 48; i >= 0; i=i-8)
		board << cmp_hist(cards[i]) << " ";
	board << '\n';
	for(int i = 47; i > 6; i=i-8)
		board << cmp_hist(cards[i]) << " ";
	board << '\n';
	for(int i = 46; i > 5; i=i-8)
		board << cmp_hist(cards[i]) << " ";
	board << '\n';
	for(int i = 45; i > 4; i=i-8)
		board << cmp_hist(cards[i]) << " ";
	board << '\n';
	for(int i = 44; i >= 3; i=i-8)
		board << cmp_hist(cards[i]) << " ";
	board << '\n';

	return;
}

