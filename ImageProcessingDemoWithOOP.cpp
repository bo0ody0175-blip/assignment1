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
#include <string>
#include "ImageEditor.h" 
#include "Utility.h"

using namespace std;

void displayOptions()
{
    cout << "Choose filter:\n";
    cout << "1. Convert to Gray Scale\n";
    cout << "2. Convert to Black and White\n";
    cout << "3. Invert Image\n";
    cout << "4. Flip Images\n";
    cout << "5. rotate image\n";
    cout << "6. Blur image\n";
    cout << "7. Old TV image\n";
    cout << "8. Purple red image\n";
    cout << "17. Skew Image\n";
}

void flip(ImageEditor& editor) 
{
    char ch = Utility::readChar("[a] to Flip Vertically\n[b] to Flip Horizontally\n");
    ch = tolower(ch);
    FlipDirection choice = (FlipDirection)ch;
    editor.flip(choice);
}


void perfromChoices(UserChoice choice, ImageEditor& editor)
{
    int rotationDegree = 0;
    switch (choice)
    {
    case UserChoice::GRAY_SCALE:
        editor.grayScalse();
        cout << "Image converted to Gray Scale successfully.\n";
        break;

    case UserChoice::BLACK_AND_WHITE:
        editor.blackAndWhite();
        cout << "Image converted to Black and White successfully.\n";
        break;

    case UserChoice::INVERT:
        editor.invert();
        cout << "Image inverted successfully.\n";
        break;

    case UserChoice::FLIP:
        flip(editor);
        cout << "Image flipped successfully.\n";
        break;

    case UserChoice::ROTATE:
        rotationDegree = Utility::readNumber(90, 270, "Enter rotation angle(90, 180, or 270) :");
        editor.rotate(rotationDegree);
        cout << "Image rotated successfully.\n";
        break;

    case UserChoice::BLUR:
        editor.blur();
        cout << "Darken image successfully.\n";
        break;

    case UserChoice::OLD_TV:
        editor.oldTV();
        cout << "Old TV image successfully.\n";
        break;
    case UserChoice::PURPLE_RED:
        editor.purpleRed();
        cout << "Purple image successfully.\n";
        break;
    case UserChoice::DETECT_EDGES:
        editor.detectEdges();
        cout << "Image edges detected successfully.\n";
        break;
    case UserChoice::SKEW:
        editor.skew();
        cout<<"Image skewed successfully.\n";
        break;
        
    default:
        break;
    }

}

void perform(ImageEditor& editor)
{
    displayOptions();
    UserChoice choice = (UserChoice)(Utility::readNumber(1, 18, "Enter choice (1, 2, 3,4,5,6,7,8, or 17): "));
    perfromChoices(choice, editor);

}


void save(ImageEditor& editor)
{
    string newFileName = Utility::readString("\nPls enter image name to store new image\nand specify extension .jpg, .bmp, .png, .tga: ");
    if (editor.save(newFileName))
        cout << "Image Saved successfully." << endl;
    else
        cout << "Not saved!";
}

int main()
{
    string fileName = Utility::readString("Pls enter image name: ");
    ImageEditor editor{ Image(fileName) };
    perform(editor);
    save(editor);
    return 0;
}

