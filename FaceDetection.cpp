// Please do change the path to your respective file destination beforehand
//Breif explaination of this code will be uploaded soon.

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp> // Used for creating windows
#include <opencv2/imgproc.hpp> // Usede for image processing 
#include<opencv2/opencv.hpp>
#include<opencv2/objdetect.hpp> // Used for object detection and face detection
#include <time.h> // Live FPS Counter will be added soon, this header file is used for the same
#include <iostream>
#include<string>

using namespace cv;
using namespace std;

void main(int argc, char** argv) {
   
    Mat img; // We store our webcam input in this
    VideoCapture real_time(0);
    String Path = "Resources/haarcascade_frontalface_default.xml"; // Path for the XML file for face detection, already provided 
    CascadeClassifier faceClass;
    faceClass.load(Path); // This is for loading the XML file
    
    if (faceClass.empty()) { // To warn user if the XML file is not loaded
        cout << "XML File not loaded." << endl;
    } 
    vector<Rect> faces;
   
    while (true) { // Used for iterating though frames of the video input via webcam
       
        faceClass.detectMultiScale( img , faces , 1.1 , 8 , CASCADE_SCALE_IMAGE , Size(65,65)  ); // You can increase the size here to improve the speed and fluidity of the output 
        
        real_time.read(img); // This is used to read data of every frame
        
        for(int i = 0; i < faces.size(); i++) {
            Mat faceROI = img(faces[i]); // ROI here stands for Region Of Intrest 
            rectangle(img, faces[i], Scalar(255, 0, 255) , 3 ); // This is used for creating a Rectange around the face, through the values calculated through code on line 30
            putText(img, to_string(faces.size()), Point(10, 40), FONT_ITALIC, 1, Scalar(255,0,255), 3); // This is used to output the count of number of faces in the frame
        }
        
        imshow("Web Output", img); // This is used for output of the final frames after processing and editing
        
        //waitKey(1);
       
        if (waitKey(10) == 27) { // Use esc buttton to end the output terminal
            break;
        }
        
    }
}
