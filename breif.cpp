#if 0
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

#define IN_WIN "Orig. image"   //�궨������ʾ����ͼƬ�Ĵ�������
#define OUT_WIN "Image converted...(no saved)" //�궨������ʾ���ͼƬ�Ĵ�������
Mat in_img, out_img;            //�����������ͼ��ľ���

//callback function for contrast trackBar
//������createTrackBar�Ļص������������Ǹı�ͼ�������

void updateContrast(int TBvalContrast,void *userData = 0)
{
    in_img.convertTo(out_img, -1, TBvalContrast / 50.0);
    imshow(OUT_WIN,out_img);
    return;
}


int main(int argc,char* argv[])
{
    int TBvalContrast = 50;//value of the TrackBar  ��ʼ����ֵ

    //(omitted for simplicity)
    in_img = imread("E:\\Testimage\\lena.bmp");  //�����in_img ��һ��ȫ�ֱ���
    in_img.copyTo(out_img);   //������ͼ���Ƹ����ͼ��
    namedWindow(IN_WIN);      //��ʾ����ͼ��Ĵ�������
    moveWindow(IN_WIN, 0, 0); //�������ƶ�����Ļ�����Ͻǣ������ص�
    imshow(IN_WIN,in_img);
    namedWindow(OUT_WIN);
    //createTrackbar�Ĳ�����
    createTrackbar("Contrast", OUT_WIN, &TBvalContrast, 100, updateContrast);
    imshow(OUT_WIN,out_img);
    cout << "Press any Key to exit..." << endl;
    waitKey();
    return 0;
}
#endif 