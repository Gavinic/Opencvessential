
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
void cbMouse(int event,int x,int y,int flags,void* userdata) //设置鼠标调用函数的回调函数，也就是指定鼠标点击事件需要做的具体的事情
{
    static int imark = 0;    //static 申明局部静态变量，也就是说imark 的值保存在全局数据区，它的数据不会随着调用的结束而结束，而是随着程序运行的结束而结束
    //这里的意思就是，imark的值在每一次调用cbMouse之后会改变和保存，直到整个函数结束它的值才清0
    char textm[] = "mark999";  //textm是一个char类型的数组，它的初始值为“mark999”

    if (event == EVENT_LBUTTONDOWN)//按下左键
    {
        cv::circle(img, Point(x, y), 4, Scalar(0, 255,0), 2);//画布，原点，半径，颜色，线宽
       // cvCircle(&img, Point(x, y), 4, Scalar(0, 0, 255), 2);
        imark++;//imcrement the number of marks
        sprintf(textm,"mark %d",imark); //这里的含义是将字符串“mark %d”其中%d 是imark的值，保存在字符数组textm
//        cvPutText(&img, textm, Point(x + 6, y), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));
        cv::putText(img, textm, Point(x + 6, y), FONT_HERSHEY_PLAIN, 1, Scalar(0,0,255), 2);
        imshow(IN_WIN, img); //这里的imshow 是为了显式的通过鼠标的交互来描点
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
       // cvtColor(submat, submat, CV_BGR2GRAY); //之所以无法显示的本质在于gray是单通道的图像，而原始的图像是三通道的，这样数据大小和类型不匹配
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
            imshow(IN_WIN, img);            //这里的imshow显示的是最终标好了圆之后的图像。只是为了显示出来。看最终的效果，要与cbMouse 中的imshow 区分开
            cout << "last" << counts << endl;
            cout << "press any key to exit... " << endl;
            waitKey();
        }

        if (counts % 3 == 0)
        {
            setMouseCallback(IN_WIN, cbMouse, NULL);
            counts++;      
            imshow(IN_WIN, img);            //这里的imshow显示的是最终标好了圆之后的图像。只是为了显示出来。看最终的效果，要与cbMouse 中的imshow 区分开
            cout << "last" << counts << endl;
            cout << "press any key to exit... " << endl;
            waitKey();
        }
        else
        {
            setMouseCallback(IN_WIN, cbMousecontrast, NULL);
            counts++;
            imshow(IN_WIN, img);            //这里的imshow显示的是最终标好了圆之后的图像。只是为了显示出来。看最终的效果，要与cbMouse 中的imshow 区分开
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