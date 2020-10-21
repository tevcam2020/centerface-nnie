#include <iostream>
#include <sys/time.h>
#include <opencv2/opencv.hpp>
#include "centerface.h"

using namespace cv;
using namespace std;


unsigned long get_cur_time(void)
{
    struct timeval tv;
    unsigned long ts;

    gettimeofday(&tv,NULL);

    ts=tv.tv_sec*1000000+tv.tv_usec;
    return ts;
}


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Usage:" << argv[0] << " <test image>.\n";
		return -1;
	}
	
	DBface face;
    string face_path = "../models/centerface.wk";
    face.init(face_path);

	cv::Mat image = cv::imread(argv[1]);
	if(image.empty())
	{
		std::cout <<"load " << argv[1] << " failed!\n";
		return -1;
	}

	std::vector<FaceInfo> Faces;
	face.detect(image, Faces);
	for(int i = 0; i < Faces.size(); i ++)
	{
		cv::Rect2f bbox;
		bbox.x      = Faces[i].x1;
		bbox.y      = Faces[i].y1;
		bbox.width  = Faces[i].x2 - Faces[i].x1;
		bbox.height = Faces[i].y2 - Faces[i].y1;
		cv::rectangle(image, bbox, cv::Scalar(0, 255, 0), 2, 8, 0);
		for (int j = 0; j < 5; j++)
		{
			cv::Point2f pt;
			pt.x = Faces[i].landmark[2*j + 0];
			pt.y = Faces[i].landmark[2*j + 1];
			cv::circle(image, pt, 2, cv::Scalar(0, 0, 255), 2);
		}
	}

	cv::imwrite("results.jpg",image);
	
	return 0;
}
