//
// Created by chenjun on 2020/5/25.
//

#ifndef CENTERFACE_H
#define CENTERFACE_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>

enum NMS_TYPE{nms_union, nms_min};

typedef struct FaceInfo{
	float x1;
	float y1;
	float x2;
	float y2;
	float score;
	float area;
	float landmark[10];
} Facestruct;

class DBface
{
public:
	int init(std::string model_file);
	int detect(cv::Mat &image, std::vector<FaceInfo> & face);

private:
	int pre_process(cv::Mat image, cv::Mat &output);
	void dynamic_resize(int src_h, int src_w, int stride=32);
	void get_ids(float *data, int h, int w, float score, std::vector<std::pair<int, int>> & ids);
	void nms(std::vector<FaceInfo> & input, std::vector<FaceInfo> & output, float nmsthreshold=0.3);
	int decode(float *pool_hm, float *box, float *landmark, std::vector<FaceInfo> & face, float score_thresh=0.4);
	void squarebox(std::vector<FaceInfo> & face);
	float Exp(float x);
	
private:
	int fixed_h = 0;            // for fixed size inference
	int fixed_w = 0;
	float fix_scale_h = 1.f;
	float fix_scale_w = 1.f;
	int max_image_size = 416;


	const int stride = 4;
	NMS_TYPE nms_type = nms_union;

	int d_h, d_w;
	float scale_h,scale_w;
	int image_h, image_w;
};

#endif //DEMO_TEST_H
