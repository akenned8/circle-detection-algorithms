#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <chrono>



using namespace cv;
using namespace std;
using namespace std::chrono;

/** @function main */
int main(int argc, char** argv)
{
    Mat frame, hsv;
    frame = imread("/Users/alexkennedy/Downloads/IMG_1252.jpg");
     
    // Laterally invert the image / flip the image
    //flip(frame,frame,1);
     
    //Converting image from BGR to HSV color space.
    cvtColor(frame, hsv, COLOR_BGR2HSV);
     
    Mat mask1,mask2;
    
    // Creating masks to detect the upper and lower tennis ball color.
    inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask1);
    inRange(hsv, Scalar(0, 0, 221), Scalar(180, 30, 255), mask2);
     
    // Generating the final mask
    mask1 = mask1 + mask2;
    Mat kernel = Mat::ones(3,3, CV_32F);
    morphologyEx(mask1,mask1,MORPH_OPEN,kernel);
    morphologyEx(mask1,mask1,MORPH_DILATE,kernel);
     
    // creating an inverted mask to segment out the cloth from the frame
    //bitwise_not(mask1,mask2);
    
    imshow("mask", mask1);
    imshow("frame", frame);
    waitKey(0);
    
}
