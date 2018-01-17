#if 0
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int contrast(int value)
{
    const char in_win[] = "Orig.image";
    const char out_win[] = "Image converted...(no saved)";
    int TBvalContrast = value;
    Mat out_img;

    /*if (argc != 2)
    {
    cout << "Usage: <cmd><input image_file>" << endl;
    return -1;
    }*/
    Mat in_img = imread("E:\\Testimage\\lena.bmp");
    if (in_img.empty())
    {
        cout << "Error !!! Image cannot be loaded..." << endl;
        return -1;
    }

    namedWindow(in_win);
    moveWindow(in_win, 0, 0);

    imshow(in_win, in_img);
    waitKey(30);

    namedWindow(out_win);
    createTrackbar("Contrast", out_win, &TBvalContrast, 100);
    cout << "Press ESC key to exit..." << endl;
    while (true)
    {
        in_img.convertTo(out_img, -1, TBvalContrast / 50.0);
        imshow(out_win, out_img);
        if (waitKey(50) == 27)
        {
            break;
        }

    }
}





int main(int argc, char* argv[])
{
   
    contrast(50);
    
    return 0;

}

#endif