#pragma once
#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/face.hpp"

#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;
using namespace face;

Ptr<FaceRecognizer> training(string data_file);

void testImageSample(Ptr<FaceRecognizer> model, Mat test);

void testImagesVector(Ptr<FaceRecognizer> model, vector<Mat> imgs);

