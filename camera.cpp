//
//  main.cpp
//  Camera_Capture
//
//  Created by zhoufan on 15/5/24.
//  Copyright (c) 2015年 zhoufan. All rights reserved.
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

const char* pstrSrcWnd = "Src";  
const char* pstrBHistWnd = "b plane";  
const char* pstrGHistWnd = "g plane";  
const char* pstrRHistWnd = "r plane"; 


IplImage* doCanny(IplImage* image_input,
                  double lowThresh,
                  double highThresh,
                  double aperture)
{
    if(image_input->nChannels != 1)
        return (0);

    IplImage* image_output = cvCreateImage(cvGetSize(image_input),
                                           image_input->depth,
                                           image_input->nChannels);

    cvCanny(image_input,image_output,lowThresh,highThresh,aperture);

    return(image_output);
}


int main(int argc, char* argv[])
{
    cvNamedWindow("Camera" , CV_WINDOW_AUTOSIZE );

	    //创建窗口  
    //cvNamedWindow(pstrSrcWnd,1);  
    //cvNamedWindow(pstrBHistWnd,1);  
    //cvNamedWindow(pstrGHistWnd,1);  
    //cvNamedWindow(pstrRHistWnd,1);  

    CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
    assert(capture != NULL);

   CvVideoWriter* video=NULL;

    IplImage *frame = 0;
    frame = cvQueryFrame(capture);
    cout<<frame->width<<"x"<<frame->height<<endl;
   video=cvCreateVideoWriter("camera.avi", CV_FOURCC('D','I','V','X'), 25,cvSize(frame->width,frame->height)); //创建CvVideoWriter对象并分配空间
       if(video) //如果能创建CvVideoWriter对象则表明成功
       {
          cout<<"VideoWriter has created."<<endl;
       }
   int i = 0;
   int n;
   while (i < 1000) 
  {
	frame=cvQueryFrame(capture); //从CvCapture中获得一帧
	 if(!frame)
	 {
		cout<<"Can not get frame from the capture."<<endl;
		break;
	}
	n=cvWriteFrame(video,frame); //判断是否写入成功，如果返回的是1，表示写入成功
  	cout<<i<<"\t"<<n<<endl;
	i++;
  }

    IplImage *frame_edge = cvCreateImage(cvGetSize(frame),
                                         IPL_DEPTH_8U,
                                         1);
    while(1)
    {
        frame = cvQueryFrame(capture);
        if(!frame) break;

 	cvShowImage(pstrSrcWnd,frame); 

        cvConvertImage(frame,frame_edge,0);
        frame = cvCloneImage(frame_edge);
	
	cvSaveImage("my.jpg", frame);	

        frame_edge = doCanny(frame_edge,70,90,3);

        cvShowImage("Camera",frame_edge);
	cvSaveImage("my_edge.jpg", frame_edge);
        char c = cvWaitKey(15);
        if(c == 27)  break;
    }

    cvReleaseVideoWriter(&video);
    cvReleaseCapture(&capture);
    cvReleaseImage( &frame_edge );
    cvReleaseImage( &frame);


    return (int)0;
}
