// Please do change the path to your respective file destination beforehand

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp> //Used for creating a window to output our data
#include <opencv2/imgproc.hpp> //Used for image processing
#include<opencv2/objdetect.hpp> //Lib we used for object detection, here human faces
#include <iostream>

using namespace cv;
using namespace std;

void main() {
    
    Mat img;
    // We will use img through out the project to store the output
    VideoCapture real_time(0); // Input from default webcame, use 1 in place of 0 for external webcam, it's used for real time and fluid output
    namedWindow("Web Output"); //We just declared the window for output
    String Path = "Resources/haarcascade_frontalface_default.xml"; //This is the path of .XML file that we'll use, don't forget to add your provided location of the file
    CascadeClassifier faceClass;
    faceClass.load(Path);
    if (faceClass.empty()) { // We used it to display error incase of program fails to read the .XML file
        cout << "XML File not loaded." << endl;
    } 
    vector<Rect> faces; //Declared a vector Rectangle, that we'll use as the border of face detected
    while (true) { 
        faceClass.detectMultiScale(img, faces, 1.1, 10, CASCADE_SCALE_IMAGE, Size(30, 30)); //Change the value of 10 to adjust the quantity of detection
        real_time.read(img);
        for (int i = 0; i < faces.size(); i++) {
            Mat faceROI = img(faces[i]);
            rectangle(img, faces[i], Scalar(255, 0, 255),3,8,0); // This is used to create a rectangle around the face of the subject, change the value of 3 to adjust the thickness
        }
        imshow("Web Output", img); // We display the output using imshow
        if (waitKey(10) == 27) {
            break;
        }
    }
}
