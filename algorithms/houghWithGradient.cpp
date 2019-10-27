#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
    Mat src, src_gray;

  /// Read the image
    src = imread("/Users/alexkennedy/Downloads/circletest2.jpg");

    if( !src.data )
        { return -1; }
    
  /// Convert it to gray
    cvtColor( src , src_gray, COLOR_RGB2GRAY);
    //cvtColor( src , src_gray, COLOR_RGB2HSV);

    //threshold(src_gray, src_gray, 90, 165, 1);
    
  /// Reduce the noise so we avoid false circle detection
    //GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
    medianBlur(src_gray, src_gray, 5);
//        imshow("hello",src_gray);
//        waitKey(0);

    vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
    HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8, 130, 50, 0, 0);
    
    for(auto x : circles) {
        cout << x <<endl;
    }
    if(circles.size() == 0) cout << "no circles detected" << endl;
  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( src, center, radius, Scalar(0,255,0), 3, 8, 0 );
   }

  /// Show your results
    namedWindow( "Hough Circle Transform Demo", WINDOW_AUTOSIZE );
  
    imshow( "Hough Circle Transform Demo", src );

  waitKey(0);
  return 0;
}
