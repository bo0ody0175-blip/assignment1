
/*


File name:  CS112_A1_Part1_20242309_S29,30_20240312_S29,30_20250089_S29,30_20250603_S29,30.cpp
Purpose: Photoshop Application that filters images
Teaching assistant: Mennat-Allah Madmouh
Authors:

1. Mahmoud Hussein Sayed -  S29,30 - ID:20242309 - solved purple red,old tv
Emails:
20242309@stud.fci-cu.edu.eg
mh01155402100@gmail.com


2. Abdulrhman Mohammed Abdulrhman - S29,30 - ID:20240312 - solved black_and_white , flip
Emails:
20240312@stud.fci-cu.edu.eg


3. Al-Morsy Ibrahim Al-Morsy Ahmed -  S29,30 - ID:20250089 - solved blur, rotate
Emails:
20250089@stud.fci-cu.edu.eg
morsyibrahim780@gmail.com


4. Mahmoud Ashraf Ahmed Mahmoud -  S29,30 - ID:20250603 - solved gray scale, invert 
Emails:
20250603@stud.fci-cu.edu.eg


 */


#include <iostream>
#include "Image_Class.h"
#include "UserChoice.h"

using namespace std;


void blackAndWhite(Image& image)
{
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            double avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < 3; k++) {
                if (avg > 127.5) {
                    image(i, j, k) = 255;
                }
                else if (avg < 127.5) {
                    image(i, j, k) = 0;
                }
            }
        }
    }

}


void grayScale(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}



void invert(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}



void flip(Image& image) {
    string choice;
    cout << "[a] to Flip Vertically";
    cout << "\n[b] to Flip Horizontally\n";
    cin >> choice;
    Image image1 = image;
    if (choice == "a" || choice == "A") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = image1(i, image.height - j - 1, k);
                }
            }
        }
    }
    else if (choice == "b" || choice == "B") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = image1(image.width - i - 1, j, k);
                }
            }
        }
    }

}


void blur(Image& image) {
    Image temp = image;

    for (int i = 0; i < image.height; ++i) {
        for (int j = 0; j < image.width; ++j) {
            for (int k = 0; k < 3; ++k) {
                int sum = 0;
                int count = 0;

                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        int ni = i + di;
                        int nj = j + dj;

                        if (ni >= 0 && ni < image.height &&
                            nj >= 0 && nj < image.width) {
                            sum += image(nj, ni,k);
                            count++;
                        }
                    }
                }

                image(j, i,k) = sum / count;
            }
        }
    }
}

void rotate(Image& image) {
    int angle;
    cout << "Enter rotation angle(90, 180, or 270):";
    cin >> angle;
    if (angle == 90) {
        Image rotated(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotated.setPixel(image.height - 1 - j, i, k, image.getPixel(i, j, k));
                    image = rotated;



                }
            }
        }
    }
    else if (angle == 180) {
        Image rotated(image.width, image.height);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotated.setPixel(image.width - 1 - i, image.height - 1 - j, k, image.getPixel(i, j, k));
                    image = rotated;
                }
            }
        }
    }
    else if (angle == 270) {
        Image rotated(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotated.setPixel(j, image.width - 1 - i, k, image.getPixel(i, j, k));
                    image = rotated;
                }
            }
        }
    }
}


void oldTV(Image& image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int c = 0; c < image.channels; c++)
            {
                if (j % 2 == 0)
                {
                    image.getPixel(i, j, c) *= 0.5;
                }
            }
        }
    }
}

void purple(Image& image)
{
    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            unsigned int r = image.getPixel(j, i, 0);
            unsigned int g = image.getPixel(j, i, 1);
            unsigned int b = image.getPixel(j, i, 2);
            image(j, i, 0) = r;
            image(j, i, 1) = g * 0.65;
            image(j, i, 2) = (b + 30 > 255) ? 255 : b + 30;
        }
    }
}



void performChoice(UserChoice choice, Image& image)
{
    switch (choice)
    {
    case UserChoice::GRAYSCALE:
        grayScale(image);
        cout << "Image converted to Gray Scale successfully.\n";
        break;

    case UserChoice::BLACKANDWHITE:
        blackAndWhite(image);
        cout << "Image converted to Black and White successfully.\n";
        break;
    case UserChoice::INVERT:
        invert(image);
        cout << "Image inverted successfully.\n";
        break;

    case UserChoice::FLIP:
        flip(image);
        cout << "Image flipped successfully.\n";
        break;

    case UserChoice::ROTATE:
        rotate(image);
        cout << "Image rotated successfully.\n";
        break;

    case UserChoice::BLUR:
        blur(image);
        cout << "Blur image successfully.\n";
        break;

    case UserChoice::OLDTV:
        oldTV(image);
        cout << "Old TV image successfully.\n";
        break;
    case UserChoice::PURPLE:
        purple(image);
        cout << "Purple image successfully.\n";
        break;
    default:
        break;
    }
}


bool isValidChoice(int choice)
{
    return choice > 0 && choice < 9;
}


int main() {
    string filename = "";
    cout << "Pls enter image name: ";
    cin >> filename;

    Image image(filename);

    cout << "Choose filter:\n";
    cout << "1. Convert to Gray Scale\n";
    cout << "2. Convert to Black and White\n";
    cout << "3. Invert Image\n";
    cout << "4. Merge Images\n";
    cout << "5. rotate image\n";
    cout << "6. Blur(image)\n";
    cout << "7. Old TV image\n";
    cout << "8. Purple red image\n";
    cout << "Enter choice (1, 2, 3,4,5,6,7 or 8): ";

    int choice;
    cin >> choice;

    if (isValidChoice(choice))
    {
        performChoice((UserChoice)choice, image);

        cout << "\nPls enter image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
        cin >> filename;

        if (image.saveImage(filename))
            cout << "Image Saved successfully." << endl;
        else
            cout << "Not saved!";
    }
    else
        cout << "Invalid choice.\n";
    return 0;
}
