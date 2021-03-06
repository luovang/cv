#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

string face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
string window_name = "人脸识别";

void detectAndDisplay( Mat frame );

int main( int argc, char** argv ){
    Mat image;
    image = imread( argv[1]);

    if( argc != 2 || !image.data ){
        printf("[error] 没有图片\n");
        return -1;
    }

    if( !face_cascade.load( face_cascade_name ) ){ 
        printf("[error] 无法加载级联分类器文件！\n");
        return -1; 
    }

    detectAndDisplay(image);

    waitKey(0);    
}

void detectAndDisplay( Mat frame ){
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( int i = 0; i < faces.size(); i++ ){
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    }

    imshow( window_name, frame );
}
