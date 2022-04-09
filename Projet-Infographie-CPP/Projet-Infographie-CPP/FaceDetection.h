#pragma once
#ifndef FACE_DETECTION	
#define FACE_DETECTION	

#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
using namespace cv;

// Variables
extern String CASCADE_PATH;
extern CascadeClassifier face_cascade;

// Fonctions
int loadCascade();
void detectOneFace(Mat frame);
int detectOneFaceMultiPic(vector<Mat> images);

#endif
