#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

#define IN_WIN "Orig. image"   //宏定义了显示输入图片的窗口名称
#define OUT_WIN "Image converted...(no saved)" //宏定义了显示输出图片的窗口名称
Mat in_img, out_img;            //定义输入输出图像的矩阵

//callback function for contrast trackBar
//定义了createTrackBar的回调函数，作用是改变图像的亮度

void updateContrast(int TBvalContrast,void *userData = 0)
{
    in_img.convertTo(out_img, -1, TBvalContrast / 50.0);
    imshow(OUT_WIN,out_img);
    return;
}


int main(int argc,char* argv[])
{
    int TBvalContrast = 50;//value of the TrackBar  初始化的值

    //(omitted for simplicity)
    in_img = imread("E:\\Testimage\\lena.bmp");  //这里的in_img 是一个全局变量
    in_img.copyTo(out_img);   //将输入图像复制给输出图像
    namedWindow(IN_WIN);      //显示输入图像的窗口名称
    moveWindow(IN_WIN, 0, 0); //将窗口移动到屏幕的左上角，避免重叠
    imshow(IN_WIN,in_img);
    namedWindow(OUT_WIN);
    //createTrackbar的参数，
    createTrackbar("Contrast", OUT_WIN, &TBvalContrast, 100, updateContrast);
    imshow(OUT_WIN,out_img);
    cout << "Press any Key to exit..." << endl;
    waitKey();
    return 0;
}
