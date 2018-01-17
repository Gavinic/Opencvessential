
#if 0
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

#define IN_WIN "Drawing..."

Mat img,temp_img;

//CallBack Function for mouse evevts
void cbMouse(int event,int x,int y,int flags,void* userdata) //���������ú����Ļص�������Ҳ����ָ��������¼���Ҫ���ľ��������
{
    static int imark = 0;    //static �����ֲ���̬������Ҳ����˵imark ��ֵ������ȫ�����������������ݲ������ŵ��õĽ������������������ų������еĽ���������
    //�������˼���ǣ�imark��ֵ��ÿһ�ε���cbMouse֮���ı�ͱ��棬ֱ������������������ֵ����0
    char textm[] = "mark999";  //textm��һ��char���͵����飬���ĳ�ʼֵΪ��mark999��

    if (event == EVENT_LBUTTONDOWN)//�������
    {
        cv::circle(img, Point(x, y), 4, Scalar(0, 255,0), 2);//������ԭ�㣬�뾶����ɫ���߿�
       // cvCircle(&img, Point(x, y), 4, Scalar(0, 0, 255), 2);
        imark++;//imcrement the number of marks
        sprintf(textm,"mark %d",imark); //����ĺ����ǽ��ַ�����mark %d������%d ��imark��ֵ���������ַ�����textm
//        cvPutText(&img, textm, Point(x + 6, y), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));
        cv::putText(img, textm, Point(x + 6, y), FONT_HERSHEY_PLAIN, 1, Scalar(0,0,255), 2);
        imshow(IN_WIN, img); //�����imshow ��Ϊ����ʽ��ͨ�����Ľ��������
        cout << "press time "<< imark << endl;
       // imwrite("img.bmp", img);
    }
    return;
}

void cbMousecontrast(int event, int x, int y, int flags, void* userdata)
{
    static Point p1, p2;
    static bool p2set = false;

    if (event == EVENT_LBUTTONDOWN)
    {
        p1 = Point(x, y);
        p2set = false;
    }
    else if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON)
    {
        if (x > img.size().width)
        {
            x = img.size().width;
        }
        else if (x < 0)
        {
            x = 0;
        }

        if (y > img.size().height)
        {
            y = img.size().height;
        }
        else if (y < 0)
        {
            y = 0;
        }
        p2 = Point(x, y);
        p2set = true;

        img.copyTo(temp_img);
        rectangle(temp_img, p1, p2, Scalar(0, 0, 255));
        imshow(IN_WIN, temp_img);
    }
    else if (event == EVENT_LBUTTONUP)
    {
        Mat submat = img(Rect(p1, p2));
        submat.convertTo(submat, -1, 2.0, 0);          
        rectangle(img, p1, p2, Scalar(0, 0, 255));
        imshow(IN_WIN, img);
    }
    return;
}





void cbMousenrect(int event,int x,int y,int flags,void* userdata)
{
    static Point p1, p2;
    static bool p2set = false;
  
    if (event == EVENT_LBUTTONDOWN)
    {
        p1 = Point(x,y);
        p2set = false; 
    }
    else if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON)
    {
        if (x > img.size().width)
        {
            x = img.size().width;
        }
        else if (x < 0)
        {
            x = 0;
        }
        
        if (y > img.size().height)
        {
            y = img.size().height;
        }
        else if (y < 0)
        {
            y = 0;
        }
        p2 = Point(x,y);
        p2set = true;

        img.copyTo(temp_img);
        rectangle(temp_img, p1, p2, Scalar(0, 0, 255));
        imshow(IN_WIN, temp_img);
    }
    else if (event == EVENT_LBUTTONUP)
    {
        Mat submat = img(Rect(p1,p2));
        //submat.convertTo(submat, -1, 2.0, 0);

        vector<Mat>imageMat(3);
        vector<Mat>tempcanny(3);
        cv::split(submat, imageMat);

        for (int i = 0; i < 3;i++)
        {
            cv::Canny(imageMat.at(i), tempcanny.at(i),20,60,3);
        }
       
        cv::merge(tempcanny, submat);
      
        // namedWindow("B");
       // imshow("B",imageMat[0]);      
       // cvtColor(submat, submat, CV_BGR2GRAY); //֮�����޷���ʾ�ı�������gray�ǵ�ͨ����ͼ�񣬶�ԭʼ��ͼ������ͨ���ģ��������ݴ�С�����Ͳ�ƥ��
       //submat.copyTo(canny);
       //cv::Canny(submat, canny, 20, 50, 3);      
       //canny.copyTo(submat);
        
        rectangle(img,p1,p2,Scalar(0,0,255));
        imshow(IN_WIN,img);
    }
    return;
}


int main(int argc,char* argv[])
{
    //(omitted for brevity)
    static int counts = 0;
    img = imread("E:\\Testimage\\lena.bmp");
    namedWindow(IN_WIN);
    while (counts < 10)
    {
        if (counts % 2 == 0)
        {
            setMouseCallback(IN_WIN, cbMousenrect, NULL);
            counts++;       
            imshow(IN_WIN, img);            //�����imshow��ʾ�������ձ����Բ֮���ͼ��ֻ��Ϊ����ʾ�����������յ�Ч����Ҫ��cbMouse �е�imshow ���ֿ�
            cout << "last" << counts << endl;
            cout << "press any key to exit... " << endl;
            waitKey();
        }

        if (counts % 3 == 0)
        {
            setMouseCallback(IN_WIN, cbMouse, NULL);
            counts++;      
            imshow(IN_WIN, img);            //�����imshow��ʾ�������ձ����Բ֮���ͼ��ֻ��Ϊ����ʾ�����������յ�Ч����Ҫ��cbMouse �е�imshow ���ֿ�
            cout << "last" << counts << endl;
            cout << "press any key to exit... " << endl;
            waitKey();
        }
        else
        {
            setMouseCallback(IN_WIN, cbMousecontrast, NULL);
            counts++;
            imshow(IN_WIN, img);            //�����imshow��ʾ�������ձ����Բ֮���ͼ��ֻ��Ϊ����ʾ�����������յ�Ч����Ҫ��cbMouse �е�imshow ���ֿ�
            cout << "last" << counts << endl;
            cout << "press any key to exit... " << endl;
            waitKey();
        }
    }
   // setMouseCallback(IN_WIN,cbMouse,NULL);
  //  setMouseCallback(IN_WIN, cbMousenrect,NULL);
   
    return 0;
}

#endif