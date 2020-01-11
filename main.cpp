/*3.	Програма, яка приймає на вхід зображення та формує на виході
два інших зашифрованих зображення за методом «Візуальна криптографія»  */

#include <opencv2\opencv.hpp>
#include <ctime>

using namespace cv;
using namespace std;



class kodirovkaf
{
private:
    Mat foto;
    unsigned char* shifr1; //масиви для зображень
    unsigned char* shifr2;
public:
    kodirovkaf(string nazva)
    {
        foto = imread(nazva, IMREAD_GRAYSCALE); //преобразует изображение в одноканальное изображение в оттенках серого (внутреннее преобразование кодека)
        shifr1 = new unsigned char[foto.cols * foto.rows * 4]; // рядки і стовпці 1 шифру; на кожен піксель 4 закодованих зображення
        shifr2 = new unsigned char[foto.cols * foto.rows * 4]; // рядки і стовпці 2 шифру
    }
    void sohran()
    {
        Mat shifr11(foto.cols * 2, foto.rows * 2, 0); // проходим по рядках і переводим масив в матовський об'єкт
        Mat shifr22(foto.cols * 2, foto.rows * 2, 0); // 0 - це щоб було чорно біле
        for (int row = 0; row < foto.rows * 2; row++)
        {
            for (int col = 0; col < foto.cols * 2; col++)
            {
                shifr11.at<uint8_t>(row, col) = shifr1[row * foto.cols * 2 + col]; // заповнює зображення
                shifr22.at<uint8_t>(row, col) = shifr2[row * foto.cols * 2 + col];
            }
        }
        imwrite("part01.png", shifr11);
        imwrite("part02.png", shifr22);
    }
    void make_shifr()
    {
        for (int row = 0; row < foto.rows * 2; row++) // робимо перше зображення рандомно 
        {
            for (int col = 0; col < foto.cols * 2; col = col + 2) // проходимо по парах довжина і ширина завжди парна
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
        for (int row = 0; row < foto.rows * 2; row++) // кодуэться парами зображення
        {
            for (int col = 0; col < foto.cols * 2; col = col + 2)
            {
                if (foto.at<uint8_t>(row / 2, col / 2) > 150) // провірка на світлу клітинку
                {
                    shifr2[row * foto.cols * 2 + col] = shifr1[row * foto.cols * 2 + col];// білий
                    shifr2[row * foto.cols * 2 + col + 1] = shifr1[row * foto.cols * 2 + col + 1];
                }
                else
                {
                    shifr2[row * foto.cols * 2 + col] = shifr1[row * foto.cols * 2 + col + 1]; // чорний
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
    Mat shifr1; // закодовані зображення
    Mat shifr2;
    unsigned char* arr; 
public:
    shifr_1_2(string part01, string part02) 
    {
        shifr1 = imread(part01, IMREAD_GRAYSCALE); // зчитуєм 1 зображення
        shifr2 = imread(part02, IMREAD_GRAYSCALE); // зчитуєм 2 зображення
        arr = new unsigned char[shifr1.cols * shifr1.rows / 4]; // робимомасив данних поділений на 4,
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
        for (int row = 0; row < shifr1.rows; row = row + 2) // пробігаємо всі закодовані по рядках зразу перевірямо 4 піксіля і зрівнюєм 4 першого і 4 другого
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
    srand(time(0)); // при кожному запуску заново рандомить числа
    kodirovkaf images("image1102.png");
    images.make_shifr();
    images.sohran();
    shifr_1_2 im("part01.png", "part02.png");
    im.orig_init();
    im.sohran();
    return 0;
}


