#pragma once
#include "Image_Class.h"
#include "UserChoice.h"
#include "FlipDirection.h"

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

    bool _is180Degree(int rotationDegree) { return rotationDegree == 180; }
        
    bool _is270Degree(int rotationDegree) { return rotationDegree == 270; }
    
    bool _is90Degree(int rotationDegree) { return rotationDegree == 90; }
    
public:

    ImageEditor(const Image& image)
    {
        this->_image = image;
    }

    bool save(const string newFileName) { return _image.saveImage(newFileName); }
        

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


    void invert() {
        for (int i = 0; i < _image.width; ++i) {
            for (int j = 0; j < _image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    _image(i, j, k) = 255 - _image(i, j, k);
                }
            }
        }
    }

    void skew(){
        double angle;
        cout<<"Enter skew angle: ";
        cin >> angle;
        double red = angle * 3.14159265 / 180.0 ;
        double tanVal = tan(red);
        int origW = _image.width;
        int origH = _image.height;
        int shift = static_cast<int>(origH * abs(tanVal));
        Image skewedImg(origW + shift, origH);
        for (int y=0; y<skewedImg.height; ++y) {
            for (int x=0; x<skewedImg.width; ++x) {
                for (int k=0; k<3; ++k) {
                    skewedImg(x,y,k) = 255;
                }
            }
        }for (int y=0; y<origH; ++y) {
            int currentShift = static_cast<int>((origH - y)* tanVal);
            for (int x=0; x<origW; ++x) {
                int newX = x + currentShift;
                if (newX >= && newX <skewedImg.width) {
                    for (int k=0; k<3; ++k) {
                        skewedImg(newX,y,k) = _image(x,y,k) ;  
                    }
                }
            }
        }_image = skewedImg;
    }

