#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

using namespace cv;
int main()
{
    //////////////////// 1 part ///////////////////////
    Mat rectangle(60, 768, CV_8U, Scalar(0));
    int gray_color = 0;
    for (int r = 0; r + 3 < rectangle.cols; r += 3)
    {
        rectangle.col(r).setTo(gray_color);
        rectangle.col(r+1).setTo(gray_color);
        rectangle.col(r+2).setTo(gray_color);
        gray_color++; // повышем градиент
    }

    Mat float_image, rectangle_gamma;
    rectangle.convertTo(float_image, CV_32FC1, 1 / 255.0 , 0);
    // гамма-корреляция

    cv::pow(float_image, 2.5, rectangle_gamma);
    rectangle_gamma.convertTo(rectangle_gamma, CV_8U, 255.0, 0);

    Mat final_part_1(Size(rectangle.cols, rectangle.rows * 2), rectangle.type(), Scalar(0));

    rectangle.copyTo(final_part_1.rowRange(0, rectangle.rows).colRange(0, rectangle.cols));
    rectangle_gamma.copyTo(final_part_1.rowRange(rectangle_gamma.rows, rectangle_gamma.rows * 2).colRange(0, rectangle_gamma.cols));
    imshow("final_part_1", final_part_1);

    ////////////////// 2 part ///////////////////////////
    gray_color = 5;
    for (int r = 0; r + 30 < rectangle.cols; r += 30)
    {
        for(int step = 0; step < 30; step++)
        {
            rectangle.col(r + step).setTo(gray_color);
        }
        gray_color += 10; // повышем градиент
    }

    rectangle.convertTo(float_image, CV_32FC1, 1 / 255.0 , 0);
    // гамма-корреляция

    cv::pow(float_image, 2.5, rectangle_gamma);
    rectangle_gamma.convertTo(rectangle_gamma, CV_8U, 255.0, 0);

    Mat final_part_2(Size(rectangle.cols, rectangle.rows * 2), rectangle.type(), Scalar(0));

    rectangle.copyTo(final_part_2.rowRange(0, rectangle.rows).colRange(0, rectangle.cols));
    rectangle_gamma.copyTo(final_part_2.rowRange(rectangle_gamma.rows, rectangle_gamma.rows * 2).colRange(0, rectangle_gamma.cols));
    imshow("final_part_2", final_part_2);


    rectangle.release();
    float_image.release();
    rectangle_gamma.release();
    final_part_1.release();
    final_part_2.release();

    ////////////////// 3 part ///////////////////////////
    Mat png_img = imread("/home/alex/sea.png");

    imwrite("/home/alex/sea_40.jpg", png_img, {CV_IMWRITE_JPEG_QUALITY, 40});
    imwrite("/home/alex/sea_90.jpg", png_img, {CV_IMWRITE_JPEG_QUALITY, 90});

    Mat jpg_40 = imread("/home/alex/sea_40.jpg");
    Mat jpg_90= imread("/home/alex/sea_90.jpg");

    imshow("diff_40", (png_img - jpg_40) * 50);
    imshow("diff_90", (png_img - jpg_90) * 50);
    imshow("png", png_img);

    waitKey(1000000);
}
