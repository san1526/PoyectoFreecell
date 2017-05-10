/*
 * Framegraber.cpp
 *
 *  Created on: 9 may. 2017
 *      Author: elver
 */

#include "FrameProcessor.h"

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

FrameProcessor::FrameProcessor() {
	// TODO Auto-generated constructor stub
	frame = imread("./frame");
	// Check if image is loaded successfully
	if(!frame.data || frame.empty())
	{
		cout << "Problem loading image!!!" << endl;
		exit(1);
	}

}

FrameProcessor::~FrameProcessor() {
	// TODO Auto-generated destructor stub
}

void FrameProcessor::grab_frame(){

	int status = 0;
	int pid = fork();
	if(pid == 0){
		execl("/usr/bin/gnome-screenshot","-B","-w","-f","frame",(char*) NULL);
	}
	while(wait(&status) != pid);
	return;
}

void FrameProcessor::frame_preprocces(){

	// Convert image to grayscale
	cvtColor(frame, frame, COLOR_BGR2GRAY);
	// Convert image to binary
	threshold(frame, frame, 50, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	//Canny(frame, frame, 100, 200);

	return;
}

void FrameProcessor::frame_show_debug(){
	imshow("Debug", frame);
	waitKey();
}

void FrameProcessor::get_card_images(){

	  vector<vector<Point> > contours;
	  vector<Vec4i> hierarchy;

	  findContours( frame, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	  vector<vector<Point> > contours_poly( contours.size() );
	  vector<Rect> boundRect( contours.size() );

	  for( size_t i = 0; i < contours.size(); i++ )
	  {
	    approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
	    boundRect[i] = boundingRect( Mat(contours_poly[i]) );
	  }

	  for (size_t i = 0; i < contours.size(); ++i) {

		  double area = contourArea(contours[i]);
		  if (area < 10e2 || 1e5 < area) continue;

		  Mat mask = Mat::zeros(frame.rows, frame.cols, CV_8UC1);
		  rectangle( mask, boundRect[i].tl(), boundRect[i].br(), Scalar(255), CV_FILLED, 8, 0 );

		  Mat card_img(frame.rows, frame.cols, CV_8UC3);
		  card_img.setTo(Scalar(0));
		  frame.copyTo(card_img, mask);

		  string file("./img/");
		  ostringstream stm;
		  stm << i ;
		  file.append(stm.str());
		  file.append(".png");
		  imwrite(file, card_img);

	  }

	  return;
}
