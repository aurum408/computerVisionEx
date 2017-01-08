#include <iostream>
#include <algorithm>
#include <cv.hpp>
#include <string>
#include <highgui.h>
#include <map>
#include <random>
#include <array>
#include <math.h>
#include <fstream>
#include <iostream>



using namespace cv;
using namespace std;


Mat modGrad(Mat img){

    //Mat img();

    int cols = img.cols;
    int rows = img.rows;
    Mat out (rows, cols, CV_8UC1);

    int temp[] = {0,0};
    //xy
    for(int i = 1; i<=rows; i++){
        uchar *u1 = img.ptr<uchar>(i);
        uchar *u2 = out.ptr<uchar>(i);
        for(int j = 1; j<= cols; j++){
            temp[0] = u1[j] - (u1-1)[j];
            temp[1] = u1[j] - (u1)[j-1];
            u2[j] = (uchar)sqrt(pow(temp[0],2) + pow(temp[1],2));
        }
    }

    return out;
}

Mat smoothGrad(Mat img){
    int cols = img.cols;
    int rows = img.rows;
    Mat out (rows, cols, CV_8UC1);

    for(int i = 1; i< img.rows; i++){
        uchar *u1 = img.ptr<uchar>(i);
        uchar *u2 = out.ptr<uchar>(i);
        for(int j =1; j< img.cols; j++){
                u2[j] = (uchar)((u1[j] + u1[j-1] + u1[j+1]
                        + (u1-1)[j] + (u1+1)[j] + (u1-1)[j-1]
                        + (u1-1)[j+1] + (u1+1)[j-1] + (u1+1)[j+1]) );
        }

    }

    return out;
}

vector<pair<unsigned int, int>> sortPixels(vector<Mat> imgs){
    pair<unsigned int, int> P; // pixel value and number of picture
    vector<pair<unsigned int, int>> pixels; //
    vector<pair<unsigned int, int>> sortedPixels;
    int dataSize = (imgs.at(0)).cols * (imgs.at(0)).rows;
    for(unsigned long i = 0; i<dataSize; i++){
        for(unsigned long j = 0; j < imgs.size(); j++){
            uchar* data = (imgs.at(j).data);
            P = make_pair(data[i],j);
            pixels.push_back(P);
        }
        sort(pixels.begin(), pixels.end());
        sortedPixels.push_back(pixels.at(0));
        pixels.clear();
    }

    return sortedPixels;
}

void readBMP(string filename){
    static constexpr size_t HEADER_SIZE = 54;
    ifstream bmp(filename, ios::binary);
    array<char, HEADER_SIZE> header;
    bmp.read(header.data(), header.size());

    auto width = *reinterpret_cast<u_int *>(&header[18]);
    int height = *reinterpret_cast<uint32_t *>(&header[22]);
    int bitPerPixel = *reinterpret_cast<uint32_t *>(&header[28]);
    int colors = *reinterpret_cast<uint32_t *>(&header[46]);
    int mainColors = *reinterpret_cast<uint32_t *>(&header[50]);

    cout << "width: " << width << endl;
    cout << "height: " << height << endl;
    cout << "bits per pixel: " << bitPerPixel << endl;
    cout << "amount of colors: " << colors << endl;
    cout << "important colors: " << mainColors << endl;
}

int main() {

    String path ("/Users/anastasia/ClionProjects/computerVisionEx/input/*.bmp");
    vector<String> fn;
    vector<Mat> inpData;
    vector<Mat> proData;
    vector<pair<unsigned int, int>> pixels;
    glob(path,fn, true);
    for(size_t k = 0; k< fn.size(); k++){
        Mat im = imread(fn[k], IMREAD_GRAYSCALE);
        inpData.push_back(im);
    }

    for(unsigned int i = 0; i < inpData.size(); i++){
        Mat img = smoothGrad(modGrad(inpData.at(i)));
        proData.push_back(img);
    }

    //pixels = sortPixels(proData);
    //cout << pixels.size();

    String f = "/Users/anastasia/ClionProjects/computerVisionEx/input/1_0001.bmp";

    readBMP(f);

//pair <unsigned int, Mat> grads;


    return 0;
}