#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void main() {
    Mat img;
    VideoCapture real_time(0);
    namedWindow("Web Output");
    String Path = "Resources/haarcascade_frontalface_default.xml";
    CascadeClassifier faceClass;
    faceClass.load(Path);
    if (faceClass.empty()) {
        cout << "XML File not loaded." << endl;
    } 
    vector<Rect> faces;
    while (true) { 
        faceClass.detectMultiScale(img, faces, 1.1, 10, CASCADE_SCALE_IMAGE, Size(30, 30));
        real_time.read(img);
        for (int i = 0; i < faces.size(); i++) {
            Mat faceROI = img(faces[i]);
            rectangle(img, faces[i], Scalar(255, 0, 255),3,8,0);
        }
        imshow("Web Output", img);
        if (waitKey(10) == 27) {
            break;
        }
    }
}
