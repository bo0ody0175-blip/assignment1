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
    case UserChoice::GRAYSCALE:
        editor.grayScalse();
        cout << "Image converted to Gray Scale successfully.\n";
        break;

    case UserChoice::BLACKANDWHITE:
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

    case UserChoice::OLDTV:
        editor.oldTV();
        cout << "Old TV image successfully.\n";
        break;
    case UserChoice::PURPLERED:
        editor.purpleRed();
        cout << "Purple image successfully.\n";
        break;
    default:
        break;
    }

}

void perform(ImageEditor& editor)
{
    displayOptions();
    UserChoice choice = (UserChoice)(Utility::readNumber(1, 8, "Enter choice (1, 2, 3,4,5,6,7 or 8): "));
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

