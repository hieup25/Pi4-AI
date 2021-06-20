#pragma once
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "ncnn/net.h"
#include "ncnn/benchmark.h"

struct st_Obj
{
    cv::Rect rect;
    int obj_id;
    std::string label;
    std::string type_number_plate;
    float score;
};

class Detector
{
private:
    ncnn::Net ncnn_net;
    ncnn::UnlockedPoolAllocator pool_alloc;
    ncnn::PoolAllocator pool_alloc_workspace;
public:
    Detector(/* args */);
    ~Detector();
    bool init(const char* path_bin, const char* path_param);
    uint32_t execute(const cv::Mat& img, std::vector<st_Obj>& objects, std::vector<std::string>& labels, int input_width, int input_height, float threshold);
};

Detector::Detector(/* args */)
{
}

Detector::~Detector()
{
}
bool Detector::init(const char* path_bin, const char* path_param)
{
    ncnn::Option opt_detect;
    opt_detect.lightmode = true;
    opt_detect.num_threads = 4;
    // opt_detect.blob_allocator = &pool_alloc;
    // opt_detect.workspace_allocator = &pool_alloc_workspace;
    // opt_detect.use_packing_layout = true;
    // opt_detect.use_fp16_arithmetic = true;
    // opt_detect.use_fp16_storage =true;
    // opt_detect.use_fp16_packed = true;
    // opt_detect.use_sgemm_convolution = true;
    // opt_detect.use_winograd_convolution = true;

    this->ncnn_net.opt = opt_detect;
    // this->ncnn_net.opt.num_threads = 4; //You need to compile with libgomp for multi thread support
    // this->ncnn_net.opt.use_vulkan_compute = true; //You need to compile with libvulkan for gpu support
    // this->ncnn_net.opt.use_winograd_convolution = true;
    // this->ncnn_net.opt.use_sgemm_convolution = true;
    // this->ncnn_net.opt.use_fp16_packed = true;
    // this->ncnn_net.opt.use_fp16_storage = true;
    // this->ncnn_net.opt.use_fp16_arithmetic = true;
    // this->ncnn_net.opt.use_packing_layout = true;
    // this->ncnn_net.opt.use_shader_pack8 = false;
    // this->ncnn_net.opt.use_image_storage = false;

    int p_1 = this->ncnn_net.load_param(path_param);
    int p_2 = this->ncnn_net.load_model(path_bin);
    return (p_1 == 0 && p_2 == 0) ? true : false;
}
uint32_t Detector::execute(const cv::Mat& img, std::vector<st_Obj>& objects, std::vector<std::string>& labels, int input_width, int input_height, float threshold)
{
    int img_w = img.cols;
    int img_h = img.rows;
    ncnn::Mat in = ncnn::Mat::from_pixels_resize(img.data, ncnn::Mat::PIXEL_BGR2RGB, img.cols, img.rows, input_width, input_height);
    const float mean_vals[3] = {0, 0, 0};
    const float norm_vals[3] = {1 / 255.f, 1 / 255.f, 1 / 255.f};
    in.substract_mean_normalize(mean_vals, norm_vals);
    ncnn::Extractor ex = this->ncnn_net.create_extractor();
    ex.input("data", in);
    ncnn::Mat out;
    ex.extract("output", out);

    objects.clear();
    for (int i = 0; i < out.h; i++)
    {
        const float* values = out.row(i);
        st_Obj object;
        object.label        = labels[(int)values[0] - 1];
        object.obj_id       = (int)values[0] - 1;
        object.score        = (values[1] < 0) ? 0 : (values[1]);
        object.rect.x       = ((values[2] * img_w) < 0) ? 0 : (values[2] * img_w);
        object.rect.y       = ((values[3] * img_h) < 0) ? 0 : (values[3] * img_h); 
        object.rect.width   = values[4] * img_w - object.rect.x;
        if(object.rect.width + object.rect.x > img_w)
            object.rect.width = img_w - object.rect.x;
        object.rect.height  = values[5] * img_h - object.rect.y;
        if(object.rect.height + object.rect.y > img_h)
            object.rect.height = img_h - object.rect.y;
        objects.push_back(object);
    }
    return 0;
}