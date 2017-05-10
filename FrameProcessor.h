/*
 * Framegraber.h
 *
 *  Created on: 9 may. 2017
 *      Author: elver
 */

#ifndef FRAMEPROCESSOR_H_
#define FRAMEPROCESSOR_H_

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class FrameProcessor {
private:
	Mat frame;
public:
	FrameProcessor();
	virtual ~FrameProcessor();
	void grab_frame();
	void frame_preprocces();
	void frame_show_debug();
	void get_card_images();
};

#endif /* FRAMEPROCESSOR_H_ */
