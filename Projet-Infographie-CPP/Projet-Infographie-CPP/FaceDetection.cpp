#include "FaceDetection.h"

using namespace std;
using namespace cv;

String CASCADE_PATH = "../../XML/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;

// Chargement de la cascade
int loadCascade()
{
    cout << "Chargement du fichier cascade en cours ...\n";

    if (!face_cascade.load(CASCADE_PATH))
    {
        printf(" -- /!\ Erreur : la cascade n'a pas pu �tre charg�e ! -- \n");
        return -1;
    };

    cout << "Chargement du fichier cascade termin� ! \n";
    return 0;
}

// D�tection d'un visage dans une image
void detectOneFace(Mat frame)
{
    cout << "D�tection faciale en cours...\n";

    // Variables
    std::vector<Rect> faces;
    Mat frame_gray;
    Mat edited_frame = frame.clone();

    // Traitements sur l'image
    cvtColor(edited_frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // D�tection
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Mesures
    int cx = faces[0].x + faces[0].width * 0.5;
    int cy = faces[0].y + faces[0].height * 0.5;
    int rx = faces[0].width * 0.5;
    int ry = faces[0].height * 0.5;
    
    // Cr�ation du cercle de d�tection faciale
    Point center(cx, cy);
    ellipse(edited_frame, center, Size(rx, ry), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

    cout << "D�tection faciale termin�e ! Affichage des r�sultats...\n";

    // Affichage
    imshow("Projet infographie", edited_frame);
}

// D�tection de visage sur plusieurs images
int detectOneFaceMultiPic(vector<Mat> images)
{
    loadCascade();
    for (Mat image : images)
    {
        if (image.empty())
        {
            cout << "-- Erreur : l'image n'a pas pu etre charg�e --\n";
            return -1;
        }
        detectOneFace(image);
        waitKey(0);
    }
}
