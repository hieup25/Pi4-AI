#include <iostream>
#include "opencv2/opencv.hpp"
#include "Core/Framework/ncnn/Detector.hpp"
#include "Core/ApiSupport/FileIO.hpp"
//facedetect
#include "Core/Framework/mnn/UltraFace.hpp"

#include <chrono>
using namespace std::chrono; 
int main(int argc, char** argv)
{
    std::cout << "Run Main" << std::endl;
    // Detector exec;
    // FileIO file;
    // std::vector<st_Obj> obj;
    // std::vector<std::string> lables;

    // cv::Mat f = cv::imread("../1.jpg");
    // std::string p_bin = "../models/ncnn/PersonCount.bin";
    // std::string p_param =  "../models/ncnn/PersonCount.param";
    // file.loadLabel("../models/ncnn/PersonCount.txt", lables);
    // exec.init(p_bin.c_str(), p_param.c_str());
    // auto start1 = high_resolution_clock::now();
    
    // exec.execute(f, obj, lables, 512, 512, 0.5f);

    // auto stop1 = high_resolution_clock::now();
	// auto duration1 = duration_cast<microseconds>(stop1 - start1);

    // std::cout << "COUNT: " << obj.size() << " | Time: " << duration1.count() << std::endl;
    // for (auto &box : obj)
    // {
    //     cv::rectangle(f, box.rect, CV_RGB(255,0,0), 2);
    // }
    // cv::imwrite("../result.jpg", f);

    std::string path_models = "../models/mnn/face_detect/version-RFB/RFB-320-quant-ADMM-32.mnn";
    UltraFace ultraface(path_models, 320, 240, 4, 0.65); // config model input
    // cv::Mat frame = cv::imread("../test_fd.jpg");
    cv::Mat frame = cv::imread("../1.jpg");
    std::cout << "Size: " << frame.size() << std::endl;
    std::vector<FaceInfo> face_info;
    ultraface.detect(frame, face_info);
    for (auto face : face_info) 
    {
        cv::Point pt1(face.x1, face.y1);
        cv::Point pt2(face.x2, face.y2);
        cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2);
    }
    cv::imwrite("../result_fd.jpg", frame);
    return 0;
}