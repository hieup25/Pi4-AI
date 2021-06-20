#include <iostream>
#include "opencv2/opencv.hpp"
#include "Core/Framework/ncnn/Detector.hpp"
#include "Core/ApiSupport/FileIO.hpp"

#include <chrono>
using namespace std::chrono; 
int main(int argc, char** argv)
{
    std::cout << "Run Main" << std::endl;
    Detector exec;
    FileIO file;
    std::vector<st_Obj> obj;
    std::vector<std::string> lables;

    cv::Mat f = cv::imread("../1.jpg");
    std::string p_bin = "../models/ncnn/PersonCount.bin";
    std::string p_param =  "../models/ncnn/PersonCount.param";
    file.loadLabel("../models/ncnn/PersonCount.txt", lables);
    exec.init(p_bin.c_str(), p_param.c_str());
    auto start1 = high_resolution_clock::now();
    
    exec.execute(f, obj, lables, 512, 512, 0.5f);

    auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1);

    std::cout << "COUNT: " << obj.size() << " | Time: " << duration1.count() << std::endl;
    for (auto &box : obj)
    {
        cv::rectangle(f, box.rect, CV_RGB(255,0,0), 2);
    }
    cv::imwrite("../result.jpg", f);

    return 0;
}