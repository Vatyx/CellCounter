////
////  main.cpp
////  openCV-hackutd
////
////  Created by Himank Yadav on 3/26/16.
////  Copyright © 2016 himankyadav. All rights reserved.
////
//
////#include <iostream>
////#include <opencv2/opencv.hpp>
//
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
////using namespace cv;
//using namespace std;
//
//cv::Mat src; cv::Mat src_gray;
//int thresh = 100;
//int max_thresh = 255;
//cv::RNG rng(12345);
//
///// Function header
//void thresh_callback(int, void* );
//
///** @function main */
//int main( int argc, char** argv )
//{
////    /// Load source image and convert it to gray
////    src = cv::imread("/Users/himankyadav/Documents/Hackathons/openCV-hackutd/openCV-hackutd/download.jpg",1);
//////    cout <<"SRC: "<< src << endl;
////    
////    /// Convert image to gray and blur it
////    cvtColor( src, src_gray, CV_BGR2GRAY );
////    blur( src_gray, src_gray, cv::Size(3,3) );
////    
////    /// Create Window
////    const char* source_window = "Source";
////    cv::namedWindow( source_window, CV_WINDOW_AUTOSIZE );
////    imshow( source_window, src );
////    
////    cv::createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
////    thresh_callback( 0, 0 );
////    
////    cv::waitKey(0);
////    return(0);
////}
//
///** @function thresh_callback */
////void thresh_callback(int, void* )
////{
////    cv::Mat canny_output;
////    vector<vector<cv::Point> > contours;
////    vector<cv::Vec4i> hierarchy;
////    
////    /// Detect edges using canny
////    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
////    /// Find contours
////    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
////    
////    /// Draw contours
////    cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
////    for( int i = 0; i< contours.size(); i++ )
////    {
////        cv::Scalar color = cvScalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
////        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
////    }
////    
////    
////    /// Show in a window
////    cv::namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
////    imshow( "Contours", drawing );
////}
//
///* We define the maximal threshold to be tried as half of the absolute maximal value in each channel*/
//    int maxBGR[3];
//    cv::Mat accu[3];
//    cv::Mat dst[3];
//    
//    
//for(unsigned int i=0; i<3;i++){
//    double min, max;
//    cv::minMaxLoc(dst[i],&min,&max);
//    maxBGR[i] = max/2;
//    /* In addition, we fill accumulators by zeros*/
//
//    accu[i]=cv::Mat(compos[0].rows,compos[0].cols,CV_8U,cv::Scalar(0));
//}
///* This loops are intended to be multithreaded using
// #pragma omp parallel for collapse(2) schedule(dynamic)
// For each channel */
//for(unsigned int i=0; i<3;i++){
//    /* For each value of threshold (m_step can be > 1 in order to save time)*/
//    for(int j=0;j<maxBGR[i] ;j += m_step ){
//        /* Temporary matrix*/
//        cv::Mat tmp;
//        std::vector<std::vector<cv::Point> > contours;
//        /* Thresholds dst by j*/
//        cv::threshold(dst[i],tmp, j, 255, cv::THRESH_BINARY);
//        /* Finds continous regions*/
//        cv::findContours(tmp, contours, CV_RETR_LIST, CV_CHAIN_APPROX_TC89_L1);
//        if(contours.size() > 0){
//            /* Tests each contours*/
//            for(unsigned int k=0;k<contours.size();k++){
//                int valid = MCF(contours[k],m_minRad,m_maxRad);
//                if(valid>0){
//                    /* I found that redrawing was very much faster if the given contour was copied in a smaller container.
//                     * I do not really understand why though. For instance,
//                     cv::drawContours(miniTmp,contours,k,cv::Scalar(1),-1,8,cv::noArray(), INT_MAX, cv::Point(-rect.x,-rect.y));
//                     is slower especially if contours is very long.
//                     */
//                    std::vector<std::vector<cv::Point> > tpv(1);
//                    std::copy(contours.begin()+k, contours.begin()+k+1, tpv.begin());
//                    /* We make a Roi here*/
//                    cv::Rect rect = cv::boundingRect(tpv[0]);
//                    cv::Mat miniTmp(rect.height,rect.width,CV_8U,cv::Scalar(0));
//                    cv::drawContours(miniTmp,tpv,0,cv::Scalar(1),-1,8,cv::noArray(), INT_MAX, cv::Point(-rect.x,-rect.y));
//                    accu[i](rect)    = miniTmp + accu[i](rect);
//                }
//            }
//        }
//        
//    }
//}
///* Make the global scoreMap*/
//cv::merge(accu,3,scoreMap);
///* Conditional noise removal*/
//if(m_minRad>2)
//cv::medianBlur(scoreMap,scoreMap,3);
//cvtColor(scoreMap,scoreMap,CV_BGR2GRAY);
//}

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat img, gray;
    cout << "Created mat objects" << endl;
    img = imread("/Users/himankyadav/Documents/Hackathons/openCV-hackutd/openCV-hackutd/download.png",1);
    cvtColor(img,img,CV_BGR2GRAY);
    Mat left=img(Rect(0,0,300,151));
    Mat right=img(Rect(300,0,img.cols-300,151));
    threshold(left,left,0,255,CV_THRESH_OTSU);
    threshold(right,right,0,255,CV_THRESH_OTSU);
    
    
    cout << "Imported image" << endl;
//    if( argc != 2 && !(img=imread(argv[1], 1)).data)
//        return -1;
    cout << "checked error code" <<endl;
//    cvtColor(img, gray, CV_BGR2GRAY);
    cout << "made image gray" <<endl;
//    cout << gray <<endl;

//    cout << "hello" << endl;
    imwrite("/Users/himankyadav/Documents/Hackathons/openCV-hackutd/openCV-hackutd/gray.jpg", gray);
    cout << "made image gray 2" <<endl;
    
//    namedWindow("image", WINDOW_AUTOSIZE);
//    imshow("image", gray);
//    waitKey(30);

    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur( img, img, Size(9, 9), 2, 2 );
    std::vector<Vec3f> circles;
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT,
                 1, 2, 100, 30,5,30);
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // draw the circle outline
        circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
//    namedWindow( "circles", 1 );
    

    imwrite( "/Users/himankyadav/Documents/Hackathons/openCV-hackutd/openCV-hackutd/circles.png", img);
    
    return 0;
}
