/*3.	��������, ��� ������ �� ���� ���������� �� ����� �� �����
��� ����� ������������ ���������� �� ������� �³������� �������������  */

#include <opencv2\opencv.hpp>
#include <ctime>

using namespace cv;
using namespace std;



class kodirovkaf
{
private:
    Mat foto;
    unsigned char* shifr1; //������ ��� ���������
    unsigned char* shifr2;
public:
    kodirovkaf(string nazva)
    {
        foto = imread(nazva, IMREAD_GRAYSCALE); //����������� ����������� � ������������� ����������� � �������� ������ (���������� �������������� ������)
        shifr1 = new unsigned char[foto.cols * foto.rows * 4]; // ����� � ������� 1 �����; �� ����� ������ 4 ����������� ����������
        shifr2 = new unsigned char[foto.cols * foto.rows * 4]; // ����� � ������� 2 �����
    }
    void sohran()
    {
        Mat shifr11(foto.cols * 2, foto.rows * 2, 0); // �������� �� ������ � ��������� ����� � ���������� ��'���
        Mat shifr22(foto.cols * 2, foto.rows * 2, 0); // 0 - �� ��� ���� ����� ���
        for (int row = 0; row < foto.rows * 2; row++)
        {
            for (int col = 0; col < foto.cols * 2; col++)
            {
                shifr11.at<uint8_t>(row, col) = shifr1[row * foto.cols * 2 + col]; // �������� ����������
                shifr22.at<uint8_t>(row, col) = shifr2[row * foto.cols * 2 + col];
            }
        }
        imwrite("part01.png", shifr11);
        imwrite("part02.png", shifr22);
    }
    void make_shifr()
    {
        for (int row = 0; row < foto.rows * 2; row++) // ������ ����� ���������� �������� 
        {
            for (int col = 0; col < foto.cols * 2; col = col + 2) // ��������� �� ����� ������� � ������ ������ �����
            {
                int random_val = rand() % 2;
                switch (random_val)
                {
                case 0:
                {
                    shifr1[row * foto.cols * 2 + col] = 255;
                    shifr1[row * foto.cols * 2 + col + 1] = 0;
                    break;
                }
                case 1:
                {
                    shifr1[row * foto.cols * 2 + col] = 0;
                    shifr1[row * foto.cols * 2 + col + 1] = 255;
                    break;
                }
                }
            }
        }
        for (int row = 0; row < foto.rows * 2; row++) // ��������� ������ ����������
        {
            for (int col = 0; col < foto.cols * 2; col = col + 2)
            {
                if (foto.at<uint8_t>(row / 2, col / 2) > 150) // ������� �� ����� �������
                {
                    shifr2[row * foto.cols * 2 + col] = shifr1[row * foto.cols * 2 + col];// ����
                    shifr2[row * foto.cols * 2 + col + 1] = shifr1[row * foto.cols * 2 + col + 1];
                }
                else
                {
                    shifr2[row * foto.cols * 2 + col] = shifr1[row * foto.cols * 2 + col + 1]; // ������
                    shifr2[row * foto.cols * 2 + col + 1] = shifr1[row * foto.cols * 2 + col];
                }
            }
        }
        for (int row = 0; row < foto.rows * 2; row++)
        {
            for (int col = 0; col < foto.cols * 2; col = col + 2)
            {
                if (col == 100)
                {

                    shifr2[row * foto.cols * 2 + col] = 0;
                    shifr2[row * foto.cols * 2 + col + 1] = 0;
                }
            }
        }
        };
    
};


class shifr_1_2
{
private:
    Mat shifr1; // ��������� ����������
    Mat shifr2;
    unsigned char* arr; 
public:
    shifr_1_2(string part01, string part02) 
    {
        shifr1 = imread(part01, IMREAD_GRAYSCALE); // ������ 1 ����������
        shifr2 = imread(part02, IMREAD_GRAYSCALE); // ������ 2 ����������
        arr = new unsigned char[shifr1.cols * shifr1.rows / 4]; // ����������� ������ �������� �� 4,
    }
    void sohran()
    {
        Mat unshifr(shifr1.cols / 2, shifr1.rows / 2, 0);
        for (int row = 0; row < shifr1.rows / 2; row++) // 
        {
            for (int col = 0; col < shifr1.cols / 2; col++)
            {
                unshifr.at<uint8_t>(row, col) = arr[row * shifr1.cols / 2 + col];
            }
        }
        imwrite("result.png", unshifr);
    }
    void orig_init()
    {
        for (int row = 0; row < shifr1.rows; row = row + 2) // �������� �� ��������� �� ������ ����� ��������� 4 ����� � ������� 4 ������� � 4 �������
        {
            for (int col = 0; col < shifr1.cols; col = col + 2)
            {

                if ((shifr1.at<uint8_t>(row, col) == shifr2.at<uint8_t>(row, col)) && (shifr1.at<uint8_t>(row, col + 1) == shifr2.at<uint8_t>(row, col + 1)) && (shifr1.at<uint8_t>(row + 1, col) == shifr2.at<uint8_t>(row + 1, col)) && (shifr1.at<uint8_t>(row + 1, col + 1) == shifr2.at<uint8_t>(row + 1, col + 1)))
                {
                    arr[row * shifr1.cols / 4 + col / 2] = 255;
                }
                else
                {
                    arr[row * shifr1.cols / 4 + col / 2] = 0;
                }
            }
        }
    }
};


int main()
{
    int a ;
    srand(time(0)); // ��� ������� ������� ������ ��������� �����
    kodirovkaf images("image1102.png");
    images.make_shifr();
    images.sohran();
    shifr_1_2 im("part01.png", "part02.png");
    im.orig_init();
    im.sohran();
    return 0;
}


