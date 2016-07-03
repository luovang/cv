#include "stdio.h"  

#include "highgui.h"  

 

int main(int argc,char* argv[])  

{  

               cvNamedWindow( "avi");  

               CvCapture* capture = cvCreateFileCapture( "/Users/baidu/code/cv/mda-gfyken8vjkd7t851.mp4");  

		
 

               IplImage* frame;  

 		char filename[100];
		int i = 0;
                while(1)  

               {  

				 
				frame = cvQueryFrame(capture);
				int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);  

				int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);  

				int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);  

				int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);  

				printf("video height : %d\nvideo width : %d\nfps : %d\nframe numbers : %d\n", frameH, frameW, fps, numFrames);  
				if (NULL == capture) 
				{
					i++;
					continue;
				}
				i++;
                               cvShowImage( "avi",frame);  
				sprintf(filename, "mda-gfyken8vjkd7t851.mp4-%d.jpg", i);
				cvSaveImage(filename, frame);
                                char c = cvWaitKey(3);  

                                if(i > 1000) break;
				

               }  

               cvReleaseCapture(&capture);  

                 

               cvDestroyWindow( "avi");  

                return 0;  

}  
