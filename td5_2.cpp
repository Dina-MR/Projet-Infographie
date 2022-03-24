#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

// Function Headers
void incrustation(Mat _front, Mat _back, Mat _alpha, int x, int y);
void question1();
void incrustationGlasses(Mat _front, Mat _back, Mat _alpha);
void detectAndDisplayVideo(VideoCapture caption, Mat front, Mat alpha);
int question2();

// Global variables
String face_cascade_name = "/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/haarcascade_frontalface_alt.xml";

String face_and_eyes_cascade_name = "/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/haarcascade_eye_tree_eyeglasses.xml";

CascadeClassifier face_cascade, face_and_eyes_cascade;

int main( int argc, const char** argv )
{
    //question1();
    question2();
    return 0;
}

/* QUESTION 1 */
void question1()
{
    Mat back = imread("/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/background.JPG");
    Mat front = imread("/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/personage.png");
    Mat alpha = imread("/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/personage_alpha.png");
    if(front.empty() || back.empty() || alpha.empty())
    {
        printf("Erreur : une image manque\n");
    }
    int x = back.cols - alpha.cols;
    int y = back.rows - alpha.rows;
    incrustation(front, back, alpha, x, y);
}

void incrustation(Mat _front, Mat _back, Mat _alpha, int x, int y)
{
    Mat front = _front.clone();
    Mat back = _back.clone();
    Mat alpha = _alpha.clone();
    Mat backbis;
    backbis = back(Rect(x, y, alpha.cols, alpha.rows));
    
    // Conversion en float
    front.convertTo(front, CV_32FC3);
    back.convertTo(back, CV_32FC3);
    backbis.convertTo(backbis, CV_32FC3);
    alpha.convertTo(alpha, CV_32FC3, 1.0/255);
    
    // Image de sortie
    Mat incrus = Mat::zeros(front.size(), front.type());
    Mat outImage = back.clone();
    
    // Multiplication front x alpha
    multiply(alpha, front, front);
    
    Mat test = Scalar::all(1.0)-alpha;
    // Multiplication back x (1 - alpha)
    multiply(test, backbis, backbis);
    
    // Ajout du masque
    add(front, backbis, incrus);
    incrus.copyTo(outImage(Rect(x, y, alpha.cols, alpha.rows)));
    
    // Affichage
    imshow("Montage", outImage/255);
    waitKey(0);
}

void incrustationGlasses(Mat _front, Mat _back, Mat _alpha)
{
    std::vector<Rect> eyes;
    std::vector<Rect> faces;

    Mat frame_gray;
    
    cvtColor(_back, frame_gray, COLOR_BGR2GRAY );
    equalizeHist(frame_gray, frame_gray );
    
    //-- Detect eyes
    //face_and_eyes_cascade.detectMultiScale(frame_gray, eyes, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    
    /*if(eyes.size() == 2)
    {
        // Resize image depending on eyes
        int glasses_width = eyes[0].width + eyes[1].width;
        int glasses_height = eyes[0].height + eyes[1].height;
        Mat front_resize, alpha_resize;
        resize(_alpha, alpha_resize, Size(glasses_width, glasses_height), INTER_LINEAR);
        resize(_front, front_resize, Size(glasses_width, glasses_height), INTER_LINEAR);

        // Display frame
        incrustation(front_resize, _back, alpha_resize, eyes[0].x, eyes[0].y);
    }
    else
        imshow("TEST", _back);*/
    
    if(faces.size() > 0)
    {
        int glasses_width = faces[0].width;
        int glasses_height = faces[0].height*0.5;
        Mat front_resize, alpha_resize;
        resize(_alpha, alpha_resize, Size(glasses_width, glasses_height), INTER_LINEAR);
        resize(_front, front_resize, Size(glasses_width, glasses_height), INTER_LINEAR);

        // Display frame
        incrustation(front_resize, _back, alpha_resize, faces[0].x, faces[0].height);
    }
    else
        imshow("TEST", _back);
    waitKey(0);
}


/* QUESTION 2 */
int question2()
{
    Mat front = imread("/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/sunglasses.png");
    Mat alpha = imread("/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/alpha.png");
    VideoCapture caption("/Users/macbook/Documents/UFR SCIENCES - Informatique/Cours/Infographie/TP5bis/moodle/video_one.mp4");
    
    if(!face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading 2nd cascade\n"); return -1; };
    if(!face_and_eyes_cascade.load( face_and_eyes_cascade_name ) ){ printf("--(!)Error loading 2nd cascade\n"); return -1; };
    
    detectAndDisplayVideo(caption, front, alpha);
    return 0;
}

void detectAndDisplayVideo(VideoCapture caption, Mat front, Mat alpha)
{
    Mat frame;
    
    while(true)
    {
        caption >> frame;
        if(frame.empty()) break;
        incrustationGlasses(front, frame, alpha);
        //imshow("Vidéo", frame);
        if(waitKey(1) == 27) break;
    }
}
