#pragma once
#include "Image_Class.h"
#include "UserChoice.h"
#include "FlipDirection.h"
#include "BrightnessMode.h"


using namespace std;

class ImageEditor
{
private:

    Image _image;

    void _rotate180()
    {
        Image rotated(_image.width, _image.height);

        for (int i = 0; i < _image.width; i++)
        {
            for (int j = 0; j < _image.height; j++)
            {
                for (int c = 0; c < _image.channels; c++)
                {
                    rotated(_image.width - 1 - i,
                        _image.height - 1 - j, c)
                        = _image(i, j, c);
                }
            }
        }

        _image = rotated;
    }

    void _detectEdges() {
        Image edges(_image.width, _image.height);

        for (int i = 0; i < _image.width; i++)
        {
            for (int j = 0; j < _image.height; j++)
            {
                int current = _image(i, j, 0);

                int right = current;
                int down = current;

                if (i + 1 < _image.width)
                    right = _image(i + 1, j, 0);

                if (j + 1 < _image.height)
                    down = _image(i, j + 1, 0);

                int difference = abs(current - right) + abs(current - down);

                if (difference > 50)
                {
                    edges(i, j, 0) = 0;
                    edges(i, j, 1) = 0;
                    edges(i, j, 2) = 0;
                }
                else
                {
                    edges(i, j, 0) = 255;
                    edges(i, j, 1) = 255;
                    edges(i, j, 2) = 255;
                }
            }
        }

        _image = edges;

    }


    void _rotate90And270(int rotationDegree)
    {
        Image rotated(_image.height, _image.width);

        for (int i = 0; i < _image.width; i++)
        {
            for (int j = 0; j < _image.height; j++)
            {
                for (int c = 0; c < _image.channels; c++)
                {
                    if (_is90Degree(rotationDegree))
                        rotated(_image.height - 1 - j, _image.width - i, c) = _image(i, j, c);
                    else
                        rotated(j, _image.width - 1 - i, c) = _image(i, j, c);
                }
            }
        }

        _image = rotated;
    }


    void _flipVertically()
    {
        for (int i = 0; i < _image.width; ++i) {
            for (int j = 0; j < _image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    _image(i, j, k) = _image(i, _image.height - j - 1, k);
                }
            }
        }
    }

    void _lighten()
    {
        for (int i = 0; i < _image.width; i++) {
            for (int j = 0; j < _image.height; j++) {
                int red = _image(i, j, 0) * 2;
                int green = _image(i, j, 1) * 2;
                int blue = _image(i, j, 2) * 2;
                if (red > 255) {
                    red = 255;
                }
                if (green > 255) {
                    green = 255;
                }
                if (blue > 255) {
                    blue = 255;
                }
                _image(i, j, 0) = red;
                _image(i, j, 1) = green;
                _image(i, j, 2) = blue;
            }
        }
    }


    void _darken()
    {
        for (int i = 0; i < _image.width; i++) {
            for (int j = 0; j < _image.height; j++) {
                _image(i, j, 0) /= 2;
                _image(i, j, 1) /= 2;
                _image(i, j, 2) /= 2;
            }
        }
    }

    void _flipHorizontally()
    {
        for (int i = 0; i < _image.width; ++i) {
            for (int j = 0; j < _image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    _image(i, j, k) = _image(_image.width - i - 1, j, k);
                }
            }
        }
    }



    bool _isValidDimensions(const int x, const int y, const int w, const int h)
    {
        return (x + w <= _image.width && y + h <= _image.height) && x > 0 && y > 0
            && w > 0 && h > 0;

    }


    bool _is180Degree(int rotationDegree) { return rotationDegree == 180; }
        
    bool _is270Degree(int rotationDegree) { return rotationDegree == 270; }
    
    bool _is90Degree(int rotationDegree) { return rotationDegree == 90; }
    
public:

    ImageEditor() = default ;

    ImageEditor(const Image& image)
    {
        this->_image = image;
    }

    bool save(const string newFileName) { return _image.saveImage(newFileName); }

    int imageHeight() { return _image.height; }

    int imageWidth() { return _image.width; }

    
        
    void grayScalse()
    {
        for (int i = 0; i < _image.width; i++)
        {
            for (int j = 0; j < _image.height; j++)
            {
                unsigned int avg = 0;
                for (int k = 0; k < _image.channels; k++)
                    avg += _image(i, j, k);

                avg /= 3;
                for (int k = 0; k < _image.channels; k++)
                {
                    _image.getPixel(i, j, k) = avg;
                }
            }
        }
    }


    void flip(const FlipDirection choice) {
        switch (choice)
        {
        case FlipDirection::VERTICALLY:
            _flipVertically();
            break;
        case FlipDirection::HORIZONTALLY:
            _flipHorizontally();
            break;
        default:
            break;
        }
    }


    void purpleRed()
    {
        for (int i = 0; i < _image.height; i++)
        {
            for (int j = 0; j < _image.width; j++)
            {
                unsigned int r = _image.getPixel(j, i, 0);
                unsigned int g = _image.getPixel(j, i, 1);
                unsigned int b = _image.getPixel(j, i, 2);
                _image(j, i, 0) = r;
                _image(j, i, 1) = g * 0.65;
                _image(j, i, 2) = (b + 30 > 255) ? 255 : b + 30;
            }
        }
    }



    void blackAndWhite()
    {
        for (int i = 0; i < _image.width; ++i) {
            for (int j = 0; j < _image.height; ++j) {
                double avg = 0;
                for (int k = 0; k < 3; k++) {
                    avg += _image(i, j, k);
                }
                avg /= 3;
                for (int k = 0; k < 3; k++) {
                    if (avg > 127.5) {
                        _image(i, j, k) = 255;
                    }
                    else if (avg < 127.5) {
                        _image(i, j, k) = 0;
                    }
                }
            }
        }

    }

    

    void rotate(const int rotationDegree)
    {
        if (_is180Degree(rotationDegree))
            _rotate180();
        else if (_is90Degree(rotationDegree) || _is270Degree(rotationDegree))
            _rotate90And270(rotationDegree);
    }


    void detectEdges()
    {
        blackAndWhite();
        _detectEdges();
    }


    void oldTV()
    {
        for (int i = 0; i < _image.width; i++)
        {
            for (int j = 0; j < _image.height; j++)
            {
                for (int c = 0; c < _image.channels; c++)
                {
                    if (j % 2 == 0)
                    {
                        _image.getPixel(i, j, c) *= 0.5;
                    }
                }
            }
        }
    }


    void blur() {
        Image temp = _image;

        for (int i = 0; i < _image.height; ++i) {
            for (int j = 0; j < _image.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int sum = 0;
                    int count = 0;

                    for (int di = -1; di <= 1; ++di) {
                        for (int dj = -1; dj <= 1; ++dj) {
                            int ni = i + di;
                            int nj = j + dj;

                            if (ni >= 0 && ni < _image.height &&
                                nj >= 0 && nj < _image.width) {
                                sum += _image(nj, ni, k);
                                count++;
                            }
                        }
                    }
                    _image(j, i, k) = sum / count;
                }
            }
        }
    }

    void mergeImages(Image& img1, Image& img2, int option) {
    if (img1.width == img2.width && img1.height == img2.height) {
        for (int i = 0; i < img1.height; ++i) {
            for (int j = 0; j < img1.width; ++j) {
                for (int k = 0; k < img1.channels; ++k) {
                    img1.imageData[i][j][k] = (img1.imageData[i][j][k] + img2.imageData[i][j][k]) / 2;
                }
            }
        }
    } else if (option == 1) {
        int maxW = std::max(img1.width, img2.width);
        int maxH = std::max(img1.height, img2.height);
        Image temp1(maxW, maxH, img1.channels);
        Image temp2(maxW, maxH, img2.channels);
        temp1.resizeImage(maxW, maxH);
        temp2.resizeImage(maxW, maxH);
        for (int i = 0; i < maxH; ++i) {
            for (int j = 0; j < maxW; ++j) {
                for (int k = 0; k < temp1.channels; ++k) {
                    temp1.imageData[i][j][k] = (temp1.imageData[i][j][k] + temp2.imageData[i][j][k]) / 2;
                }
            }
        }
        img1 = temp1;
    } else if (option == 2) {
        int minW = std::min(img1.width, img2.width);
        int minH = std::min(img1.height, img2.height);
        Image result(minW, minH, img1.channels);
        for (int i = 0; i < minH; ++i) {
            for (int j = 0; j < minW; ++j) {
                for (int k = 0; k < img1.channels; ++k) {
                    result.imageData[i][j][k] = (img1.imageData[i][j][k] + img2.imageData[i][j][k]) / 2;
                }
            }
        }
        img1 = result;
    }

    


    void darkenOrLighten(const BrightnessMode mode) {
        switch (mode)
        {
        case BrightnessMode::DARKEN:
            _darken();
            break;
        case BrightnessMode::LIGHTEN:
            _lighten();
            break;
        default:
            break;
        }
    }


    void invert() {
        for (int i = 0; i < _image.width; ++i) {
            for (int j = 0; j < _image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    _image(i, j, k) = 255 - _image(i, j, k);
                }
            }
        }
    }

    void resize(const int newWidth,const int newHeight) {
        Image new_image(newWidth, newHeight);
        double width_ratio, height_ratio;
        width_ratio = (static_cast<double>(_image.width) / static_cast<double>(newWidth));
        height_ratio = (static_cast<double>(_image.height) / static_cast<double>(newHeight));
            
        for (int i = 0; i < newWidth; i++) {
            for (int j = 0; j < newHeight; j++) {
                int srcX = static_cast<int>(round(i * width_ratio));
                int srcY = static_cast<int>(round(j * height_ratio));
                if (srcX > _image.width - 1) srcX = _image.width - 1;
                if (srcY > _image.height - 1) srcY = _image.height - 1;
                for (int k = 0; k < 3; k++) {
                    new_image(i, j, k) = _image(srcX, srcY, k);
                }
            }
        }

        _image = new_image;
    }




    bool crop(const int x , const int y , const int w, const int h)
    {
        if (!_isValidDimensions(x, y, w, h))
            return false;
        Image cropped(w, h);
        for (int j = 0; j < h; j++)
        {
            for (int i = 0; i < w; i++)
            {
                for (int c = 0; c < _image.channels; c++)
                {
                    cropped.getPixel(i,j,c) = _image.getPixel(x + i, y + j, c);
                }
            }
        }
        _image = cropped;
        return true;
    }


    //void skew() {
    //    double angle;
    //    cout << "Enter skew angle: ";
    //    cin >> angle;
    //    double red = angle * 3.14159265 / 180.0;
    //    double tanVal = tan(red);
    //    int origW = _image.width;
    //    int origH = _image.height;
    //    int shift = static_cast<int>(origH * abs(tanVal));
    //    Image skewedImg(origW + shift, origH);
    //    for (int y = 0; y < skewedImg.height; ++y) {
    //        for (int x = 0; x < skewedImg.width; ++x) {
    //            for (int k = 0; k < 3; ++k) {
    //                skewedImg(x, y, k) = 255;
    //            }
    //        }
    //    }for (int y = 0; y < origH; ++y) {
    //        int currentShift = static_cast<int>((origH - y) * tanVal);
    //        for (int x = 0; x < origW; ++x) {
    //            int newX = x + currentShift;
    //            if (newX >=  && newX < skewedImg.width) {
    //                for (int k = 0; k < 3; ++k) {
    //                    skewedImg(newX, y, k) = _image(x, y, k);
    //                }
    //            }
    //        }
    //    }
    //    _image = skewedImg;
    //}

    void oilPainting() {
        int radius = 3;
        int levels = 20;
        int width = _image.width;
        int height = _image.height;
        Image result(width, height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int intensityCount[256] = { 0 };
                int sumR[256] = { 0 };
                int sumG[256] = { 0 };
                int sumB[256] = { 0 };
                for (int ny = -radius; ny <= radius; ++ny) {
                    for (int nx = -radius; nx <= radius; ++nx) {
                        int curX = x + nx;
                        int curY = y + ny;
                        if (curX >= 0 && curX < width && curY >= 0 && curY < height) {
                            int r = _image(curX, curY, 0);
                            int g = _image(curX, curY, 1);
                            int b = _image(curX, curY, 2);
                            int currentIntensity = (r + g + b) / 3;
                            int intensityBin = (currentIntensity * levels) / 256;
                            if (intensityBin >= levels) intensityBin = levels - 1;
                            intensityCount[intensityBin]++;
                            sumR[intensityBin] += r;
                            sumG[intensityBin] += g;
                            sumB[intensityBin] += b;
                            int maxIndex = 0;
                            int maxCount = 0;
                            for (int i = 0; i < levels; ++i) {
                                if (intensityCount[i] > maxCount) {
                                    maxCount = intensityCount[i];
                                    maxIndex = i;
                                }
                            }if (maxCount > 0) {
                                result(x, y, 0) = sumR[maxIndex] / maxCount;
                                result(x, y, 1) = sumG[maxIndex] / maxCount;
                                result(x, y, 2) = sumB[maxIndex] / maxCount;
                            }
                        }
                    }
                }
            }
        }
        _image = result;
    }

}

