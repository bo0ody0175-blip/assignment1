// file name: CS112_A3_Part2B_S15,16_20230211_20230100_20230246.cpp
// description: the program has 15 filters, user choose one or more of them to apply in his photo.
// digram link: https://drive.google.com/file/d/1Xxmudktv9_FtC5UErDJsO5e339FSkrOa/view?usp=sharing
// Team info :
// Abdelhman Emad Mahmoud      ID: 20230211      S:15,16
// Peter Girgs Sayed           ID: 20230100      S:15,16
// Ammar Ali Ghazi             ID: 20230246      S:15,16
// Filters (Grayscale & merge IMages & crop Image & Detect edges & skew)                  made by  Peter Girgs Sayed
// Filters (black and white & Flip Image & darken and lighten & resizing & purple look)   made by  Abdelrhman Emad Mahmoud
// Filters (invert IMage & rotate Image & add frame & Blur & TV IMages)                   made by  Ammar Ali Ghazi

#include "Image_Class.h"
#include <cmath>
#include <iostream>
#include <random>
#include <string>
using namespace std;

// Function to specifies extension
void choose_ext(string& extension) {
    cout << "inter photo name to store it: ";
    cin >> extension;
    cout << "choose extension:  [a] jpg     [b] bmp     [c] png     [d] tga\n";
    while (true) {
        string choice;
        cin >> choice;
        if (choice == "a" || choice == "A") {
            extension += ".jpg";
            break;
        }
        else if (choice == "b" || choice == "B") {
            extension += ".bmp";
            break;
        }
        else if (choice == "c" || choice == "C") {
            extension += ".png";
            break;
        }
        else if (choice == "d" || choice == "D") {
            extension += ".tga";
            break;
        }
        else {
            cout << "enter a valid choice \n";
        }
    }
}

// function to apply Gray scale filter on the Image
Image gray_scale(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; k++) {
                avg += image(i, j, k);
            }
            avg /= 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    return image;
}

// function to apply black and white filter on the Image
Image black_and_white(Image& image) {
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
    return image;
}

// funciont to invert Image
Image invert_image(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    return image;
}

// function to merge two photos
Image merge_images(Image& image1) {
    string filename_2;
    cout << "Pls enter second image path: ";
    cin >> filename_2;
    Image image2(filename_2);
    Image new_image(image2.width, image2.height);
    for (int i = 0; i < new_image.width; i++) {
        for (int j = 0; j < new_image.height; j++) {
            for (int k = 0; k < new_image.channels; k++) {
                new_image(i, j, k) =
                    image1(int(i * (double(image1.width)) / new_image.width),
                        int(j * (double(image1.height) / new_image.height)), k);
            }
        }
    }
    for (int i = 0; i < new_image.width; i++) {
        for (int j = 0; j < new_image.height; j++) {
            for (int k = 0; k < new_image.channels; k++) {
                new_image(i, j, k) = ((image2(i, j, k) + new_image(i, j, k)) / 2);
            }
        }
    }
    return new_image;
}

// function to flip image vertically or horizontally
Image flip(Image& image) {
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
    return image;
}

// check if the input is number
bool isNumber(string s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// function to rotate Image 90 or 180 or 270 degree
Image rotate_image(Image& image) {

    // get rotate degree
    int degree_rotate = 0;
    while (1) { // check validity of degree rotate
        string input = "";
        cout << "choose degree to rotate(90, 180, 270): ";
        getline(cin, input);
        if (isNumber(input) &&
            (stoi(input) == 90 || stoi(input) == 180 || stoi(input) == 270)) {
            degree_rotate = stoi(input);
            break;
        }
        else {
            cout << "# choose a valid degree," << endl;
        }
    }

    if (degree_rotate == 270) {
        Image image2(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                image2(j, image2.height - i - 1, 0) = image(i, j, 0);
                image2(j, image2.height - i - 1, 1) = image(i, j, 1);
                image2(j, image2.height - i - 1, 2) = image(i, j, 2);
            }
        }
        return image2;
    }
    else if (degree_rotate == 180) {
        Image image3(image.width, image.height);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                image3(image3.width - i - 1, image3.height - j - 1, 0) = image(i, j, 0);
                image3(image3.width - i - 1, image3.height - j - 1, 1) = image(i, j, 1);
                image3(image3.width - i - 1, image3.height - j - 1, 2) = image(i, j, 2);
            }
        }
        return image3;
    }
    else {
        Image image2(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                image2(image2.width - j - 1, i, 0) = image(i, j, 0);
                image2(image2.width - j - 1, i, 1) = image(i, j, 1);
                image2(image2.width - j - 1, i, 2) = image(i, j, 2);
            }
        }
        return image2;
    }
}

// function to darken and lighten image 
Image darken_lighten(Image& Photo) {
    string choice;
    cout << "please inter what do you want \n";
    cout << "[A] to Lighten your image\n";
    cout << "[B] to Darken your image\n>> ";
    cin >> choice;
    if (choice == "A" || choice == "a") {
        for (int i = 0; i < Photo.width; i++) {
            for (int j = 0; j < Photo.height; j++) {
                int red = Photo(i, j, 0) * 2;
                int green = Photo(i, j, 1) * 2;
                int blue = Photo(i, j, 2) * 2;
                if (red > 255) {
                    red = 255;
                }
                if (green > 255) {
                    green = 255;
                }
                if (blue > 255) {
                    blue = 255;
                }
                Photo(i, j, 0) = red;
                Photo(i, j, 1) = green;
                Photo(i, j, 2) = blue;
            }
        }
    }
    else if (choice == "B" || choice == "b") {
        for (int i = 0; i < Photo.width; i++) {
            for (int j = 0; j < Photo.height; j++) {
                Photo(i, j, 0) /= 2;
                Photo(i, j, 1) /= 2;
                Photo(i, j, 2) /= 2;
            }
        }
    }
    return Photo;
}

// function to crop image
Image crop(Image& image) {
    cout << "Please enter crop dimensions separated by space";
    int x, y;
    cin >> x >> y;
    Image cropped_image(x, y);

    cout << "Please enter staring point dimensions separated by space";
    int a, b;
    cin >> a >> b;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < image.channels; k++) {
                cropped_image(i, j, k) = image(a + i, b + j, k);
            }
        }
    }
    return cropped_image;
}

// function to add frame to the Image
Image frame(Image& image) {

    for (int i = 0; i < image.width / 100; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 0) = 93;
            image(i, j, 1) = 63;
            image(i, j, 2) = 211;

            image(image.width - i - 1, j, 0) = 93;
            image(image.width - i - 1, j, 1) = 63;
            image(image.width - i - 1, j, 2) = 211;
        }
    }

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height / 100; ++j) {
            image(i, j, 0) = 93;
            image(i, j, 1) = 63;
            image(i, j, 2) = 211;

            image(i, image.height - j - 1, 0) = 93;
            image(i, image.height - j - 1, 1) = 63;
            image(i, image.height - j - 1, 2) = 211;
        }
    }

    for (int i = 0; i < (image.width / 1000) + 1; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255;

                image(image.width - i - 1, j, k) = 255;
            }
        }
    }

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < (image.height / 1000) + 1; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255;

                image(i, image.height - j - 1, k) = 255;
            }
        }
    }

    int simple_fancy = 0;
    while (1) {
        string input = "";
        cout << "1)simple.\n2)fancy.\n>> ";
        getline(cin, input);
        if (isNumber(input) && (stoi(input) == 1 || stoi(input) == 2)) {
            simple_fancy = stoi(input);
            break;
        }
        else {
            cout << "# choose a valid choice," << endl;
        }
    }

    if (simple_fancy == 2) {
        for (int i = 0; i < (image.width / 1000) + 1; ++i) { // vertical two lines
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image((image.width / 100) + i, j, k) = 255;

                    image(image.width - i - (image.width / 100) - 1, j, k) = 255;

                    image((image.width / 100) + i - ((image.width / 100) / 2), j, k) =
                        255;

                    image(image.width - (image.width / 100) - i +
                        ((image.width / 100) / 2) - 1,
                        j, k) = 255;
                }
            }
        }

        for (int i = 0; i < image.width; ++i) { // hotizontal two lines
            for (int j = 0; j < (image.height / 1000) + 1; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, (image.height / 100) + j, k) = 255;

                    image(i, image.height - j - (image.height / 100) - 1, k) = 255;

                    image(i, (image.height / 100) + j - ((image.height / 100) / 2), k) =
                        255;

                    image(i,
                        image.height - (image.height / 100) - j +
                        ((image.height / 100) / 2) - 1,
                        k) = 255;
                }
            }
        }

        for (int i = image.width / 100; i < (image.width / 100) + 5; ++i) {
            for (int j = image.height / 100; j < (image.height / 100) + 5; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = 255;

                    image(image.width - i - 1, j, k) = 255;

                    image(i, image.height - j - 1, k) = 255;

                    image(image.width - i - 1, image.height - j - 1, k) = 255;
                }
            }
        }

        for (int i = (image.width / 100) + 12; i < (image.width / 100) + 15; ++i) {
            for (int j = image.height / 100; j < (image.height / 100) + 15; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = 255;

                    image(image.width - i - 1, j, k) = 255;

                    image(i, image.height - j - 1, k) = 255;

                    image(image.width - i - 1, image.height - j - 1, k) = 255;
                }
            }
        }

        for (int i = image.width / 100; i < (image.width / 100) + 15; ++i) {
            for (int j = (image.height / 100) + 12; j < (image.height / 100) + 15;
                ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = 255;

                    image(image.width - i - 1, j, k) = 255;

                    image(i, image.height - j - 1, k) = 255;

                    image(image.width - i - 1, image.height - j - 1, k) = 255;
                }
            }
        }

        for (int j = image.height / 100; j < (image.height / 100) + 8; ++j) {
            for (int k = 0; k < 3; ++k) {
                image((image.width / 100) + 8, j, k) = 255;

                image(image.width - (image.width / 100) - 8 - 1, j, k) = 255;

                image((image.width / 100) + 8, image.height - j - 1, k) = 255;

                image(image.width - (image.width / 100) - 8 - 1, image.height - j - 1,
                    k) = 255;
            }
        }

        for (int i = image.width / 100; i < (image.width / 100) + 9; ++i) {
            for (int k = 0; k < 3; ++k) {
                image(i, (image.height / 100) + 8, k) = 255;

                image(i, image.height - (image.height / 100) - 8 - 1, k) = 255;

                image(image.width - i - 1, (image.height / 100) + 8, k) = 255;

                image(image.width - i - 1, image.height - (image.height / 100) - 8 - 1,
                    k) = 255;
            }
        }
    }

    return image;
}

// function to detect edges
Image detect_image_edges(Image& image) {
    image = gray_scale(image);
    image = black_and_white(image);
    int width = image.width;
    int height = image.height;
    Image edges(width, height);

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int Gx = image(x + 1, y, 0) - image(x - 1, y, 0);
            int Gy = image(x, y + 1, 0) - image(x, y - 1, 0);

            if (abs(Gx) + abs(Gy) > 128) {
                edges(x, y, 0) = edges(x, y, 1) = edges(x, y, 2) = 0;
            }
            else {
                edges(x, y, 0) = edges(x, y, 1) = edges(x, y, 2) = 255;
            }
        }
    }

    return edges;
}

// function to resize the Image
Image resize(Image& image) {
    int new_width, new_height;
    cout << "pls enter your photo width\n";
    cin >> new_width;
    cout << "pls enter your photo height ";
    cin >> new_height;
    Image new_image (new_width, new_height);
    double width_ratio, height_ratio;
    width_ratio =
        (static_cast<double>(image.width) / static_cast<double>(new_width));
    height_ratio =
        (static_cast<double>(image.height) / static_cast<double>(new_height));
    for (int i = 0; i < new_width; i++) {
        for (int j = 0; j < new_height; j++) {
            for (int k = 0; k < 3; k++) {
                new_image(i, j, k) =
                    image(round(i * width_ratio), round(j * height_ratio), k);
            }
        }
    }

    return new_image;
}

// function to blur the Image
Image blur(Image& image) {
    int n = 3;                                 // Blur radius
    int count = ((2 * n) + 1) * ((2 * n) + 1); // kernal size
    for (int y = n; y < image.width - n; ++y) {
        for (int x = n; x < image.height - n; ++x) {
            for (int k = 0; k < 3; ++k) {
                int sum = 0;
                for (int ky = -n; ky <= n; ++ky) {
                    for (int kx = -n; kx <= n; kx++) {
                        int ny = y + ky;
                        int nx = x + kx;
                        sum += image(ny, nx, k);
                    }
                }
                image(y, x, k) = sum / count;
            }
        }
    }

    return image;
}

int randomBetween(int low, int high) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(low, high);
    return dis(gen);
}

// function to apply old TV noise filter
Image tv(Image& image) {
    for (int i = 0; i < image.width; i += 2) {
        for (int j = 0; j < image.height; j += 2) {
            for (int k = 0; k < 3; ++k) {
                if (image(i, j, k) > 64) {
                    image(i, j, k) = (image(i, j, k) + randomBetween(192, 255)) % 255;
                }
            }
        }
    }
    return image;
}

// function to make the photo purple
Image purple_look(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int purple = 0;

            purple += image(i, j, 0);
            purple += image(i, j, 2);
            purple /= 2;
            if (purple > 255) {
                purple = 255;
            }
            image(i, j, 0) = purple;
            image(i, j, 2) = purple;
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int red = image(i, j, 0) * 1.8;
            if (red > 255) {
                red = 255;
            }
            image(i, j, 0) = red;
        }
    }
    return image;
}

// function to skew the photo
Image skew_image(Image& image) {
    cout << "enter a angel to skew image" << endl;
    double angle;
    cin >> angle;
    angle = (angle / 180) * 3.14;
    int width = image.width;
    int height = image.height;
    int newWidth = width + static_cast<int>(abs(height * tan(angle))) * 2;
    int newHeight = height;
    Image skewed(newWidth, newHeight);
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            double srcX = x - (newWidth - width) / 2;
            double srcY = y;
            double srcXSkewed = srcX - srcY * tan(angle);
            double srcYSkewed = srcY;
            int srcXNearest = static_cast<int>(round(srcXSkewed));
            int srcYNearest = static_cast<int>(round(srcYSkewed));
            if (srcXNearest >= 0 && srcXNearest < width && srcYNearest >= 0 &&
                srcYNearest < height) {
                for (int c = 0; c < 3; ++c) {
                    skewed(x, y, c) = image(srcXNearest, srcYNearest, c);
                }
            }
            else {
                skewed(x, y, 0) = skewed(x, y, 1) = skewed(x, y, 2) = 255;
            }
        }
    }
    Image new_skewed(width + static_cast<int>(abs(height * tan(angle))), height);
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth - static_cast<int>(abs(height * tan(angle)));
            ++x) {
            for (int c = 0; c < new_skewed.channels; c++) {
                new_skewed(x, y, c) =
                    skewed(x + static_cast<int>(abs(height * tan(angle))), y, c);
            }
        }
    }
    return new_skewed;
}

int main() {
    cout << "welcome, that program add some filters to your picture,\n";
    string filename1;
    Image image;
    while (true) {
        string choice;
        cout << "choose what do you want [a] load image  [b] exit.\n>> ";
        cin >> choice;
        if (choice == "a" || choice == "A") {
            while (true) {
                cout << "Pls enter your photo name to edit it: ";
                cin >> filename1;
                try {
                    if (image.loadNewImage(filename1)) {
                        break;
                    }
                }
                catch (...) {
                }
            }

            while (true) {
                cout << "please choose filter: \n"
                    "a)filter_1(gray_scale).                  ""b)filter_2(black_and_white).   c)filter_3(invert_image).\n"
                    "d)filter_4(merge_images).                e)filter_5(Flip ""Image).        f)filter_6(rotate_image).\n"
                    "g)filter_7(Darken and Lighten Image).    h)filter_8(crop).    ""          i)filter_9(?Adding a Frame).\n"
                    "j)filter_10(detect image edges).         ""k)filter_11(resizing_image).   l)filter_12(Blur Images).\n"
                    "m)filter_15(TV images).                  ""n)filter_16(purple_look).      o)skew_18.\n"
                    "p) exit \n>> ";
                string choice;
                cin >> choice;
                cin.clear();
                cin.ignore(100, '\n');
                if (choice == "p" || choice == "P") {
                    break;
                }
                else if (choice == "A" || choice == "a") {
                    image = gray_scale(image);
                }
                else if (choice == "B" || choice == "b") {
                    image = black_and_white(image);
                }
                else if (choice == "C" || choice == "c") {
                    image = invert_image(image);
                }
                else if (choice == "D" || choice == "d") {
                    image = merge_images(image);
                }
                else if (choice == "E" || choice == "e") {
                    image = flip(image);
                }
                else if (choice == "F" || choice == "f") {
                    image = rotate_image(image);
                }
                else if (choice == "G" || choice == "g") {
                    image = darken_lighten(image);
                }
                else if (choice == "H" || choice == "h") {
                    image = crop(image);
                }
                else if (choice == "I" || choice == "i") {
                    image = frame(image);
                }
                else if (choice == "J" || choice == "j") {
                    image = detect_image_edges(image);
                }
                else if (choice == "K" || choice == "k") {
                    image = resize(image);
                }
                else if (choice == "L" || choice == "l") {
                    image = blur(image);
                }
                else if (choice == "M" || choice == "m") {
                    image = tv(image);
                }
                else if (choice == "n" || choice == "n") {
                    image = purple_look(image);
                }
                else if (choice == "o" || choice == "O") {
                    image = skew_image(image);
                }
                else {
                    cout << "# enter valid choice,\n";
                    continue;
                }

                cout << "[a] continue editing   [b]save and return to start menu   "
                    "[c] don't save\n";
                string choice1;
                cin >> choice1;
                if (choice1 == "a" || choice1 == "A") {
                    continue;
                }
                else if (choice1 == "b" || choice1 == "B") {
                    string image_name;
                    choose_ext(image_name);
                    image.saveImage(image_name);
                    break;
                }
                else {
                    break;
                }
            }
        }
        else if (choice == "b" || choice == "B") {
            break;
        }
        else {
            cout << "# enter valid choice," << endl;
        }
    }
    return 0;
}