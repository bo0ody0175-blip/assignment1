/*


File name:  CS112_A1_Part1_20242309_S29,30_20240312_S29,30_20250089_S29,30_20250603_S29,30.cpp
Purpose: Photoshop Application that filters images
Teaching assistant: Mennat-Allah Madmouh
Authors:

1. Mahmoud Hussein Sayed -  S21,22 - ID:20242309 - solved: purple red,old tv,crop,detected edges
Emails:
20242309@stud.fci-cu.edu.eg
mh01155402100@gmail.com


2. Abdulrhman Mohammed Abdulrhman - S29,30 - ID:20240312 - solved: black and white , flip,resize
Emails:
20240312@stud.fci-cu.edu.eg


3. Al-Morsy Ibrahim Al-Morsy Ahmed -  S29,30 - ID:20250089 - solved: blur, rotate
Emails:
20250089@stud.fci-cu.edu.eg
morsyibrahim780@gmail.com


4. Mahmoud Ashraf Ahmed Mahmoud -  S29,30 - ID:20250603 - solved: gray scale, invert
Emails:
20250603@stud.fci-cu.edu.eg


 */


#include <iostream>
#include <string>
#include "ImageEditor.h" 
#include "Utility.h"
#include "ImageExtension.h"
#include "SaveOption.h"
#include "BrightnessMode.h"

using namespace std;

ImageEditor editor;
string fileName;
bool hasUnsavedChanges = false;
void displayOptions();
void perform();


void displayOptions()
{
    system("cls");
    cout << "Choose filter:\n";
    cout << "1. Convert to Gray Scale\n";
    cout << "2. Convert to Black and White\n";
    cout << "3. Invert Image\n";
    cout << "4. Flip Images\n";
    cout << "5. rotate image\n";
    cout << "6. Blur image\n";
    cout << "7. Old TV image\n";
    cout << "8. Purple red image\n";
    cout << "9. Skew image\n";
    cout << "10. Detect Image Edges\n";
    cout << "11. Oil painting\n";
    cout << "12. Crop\n";
    cout << "13. Resize\n";
    cout << "14. Darken or lighten\n";

    cout << "17. Load New Image \n";
    if (hasUnsavedChanges)
    {
        cout << "18. Save editing\n";
        cout << "19. Exit\n";
    }
    else 
        cout << "18. Exit\n";
}

void flip() 
{
    char ch = Utility::readChar("[a] to Flip Vertically\n[b] to Flip Horizontally\n");
    ch = tolower(ch);
    FlipDirection choice = (FlipDirection)ch;
    editor.flip(choice);
}


string readImageExtension(ImageExtension ex)
{
    switch (ex)
    {
    case ImageExtension::JPG: return ".jpg";
        
    case ImageExtension::PNG: return ".png";
        
    case ImageExtension::BMP: return ".bmp";
        
    case ImageExtension::TGA: return ".tga";
    default:
        break;
    }
}


string readFileName()
{
    fileName = Utility::readString("Pls enter image name: ");
    char UserExtensionChoice = Utility::readChar("Enter the extension ([a] .jpg ,[b] .png,[c] .bmp,[d] .tga): ");
    const string EXTENSION = readImageExtension((ImageExtension)UserExtensionChoice);
    fileName.append(EXTENSION);
    return fileName;
}


void saveEditing()
{
    if (!hasUnsavedChanges)
        return;
    char savingChoice = Utility::readChar( "Do you want to save on the same file or change the file name? (s = same / n = new name): ");
    savingChoice = tolower(savingChoice);
    SaveOption option = (SaveOption)savingChoice;
    bool isImageSaved = false;
    switch (option)
    {
    case SaveOption::NEW_NAME:
        fileName = readFileName();
        isImageSaved = (editor.save(fileName)) ? true : false;
        break;

    case SaveOption::SAME_FILE:
        isImageSaved = (editor.save(fileName)) ? true : false;
        break;

    default:
        cout << "Invalid Choice!";
        break;
    }
    if (isImageSaved)
    {
        hasUnsavedChanges = false;
        cout << "Image Saved successfully.";
    }
    else
        cout << "Not saved!";
}


ImageEditor loadNewImage()
{
    system("cls");
    fileName = readFileName();
    ImageEditor editor{ Image(fileName) };
    return editor;
}


void saveAndLoadImage()
{
    if (hasUnsavedChanges)
    {
        char ch = Utility::readChar("Do you want to save the current image before loading a new one ? (y / n) : ");
        ch = tolower(ch);

        if (Utility::equals(ch, 'y'))
            saveEditing();
    }
    editor = loadNewImage();
}

void darkenOrLighten()
{
    int brightnessUserChoice = Utility::readNumber(1,2,"Choose: [1] Lighten ,[2] Darken");
    BrightnessMode mode = (BrightnessMode)brightnessUserChoice;
    editor.darkenOrLighten(mode);
}


void resize()
{
    int newWidth = Utility::readNumber("pls enter your photo width\n");
    int newHeight = Utility::readNumber("pls enter your photo height\n");
    editor.resize(newWidth, newHeight);
}


void crop()
{
    int x, y, w, h;
    cout << "Image size: " << editor.imageWidth() << " x " << editor.imageHeight() << "\n";

    cout << "Enter the starting point (upper left corner) x y: ";
    cin >> x >> y;

    cout << "Enter the dimensions of the area to keep (W H): ";
    cin >> w >> h; 
    if (editor.crop(x,y,w,h))
        cout << "Image cropped successfully.\n";
    else 
        cout << "Invalid";
}


void perfromChoices(UserChoice choice)
{
    int rotationDegree = 0;
    switch (choice)
    {
    case UserChoice::GRAY_SCALE:
        editor.grayScalse();
        cout << "Image converted to Gray Scale successfully.\n";
        hasUnsavedChanges = true;
        perform();
        break;

    case UserChoice::BLACK_AND_WHITE:
        editor.blackAndWhite();
        cout << "Image converted to Black and White successfully.\n";
        hasUnsavedChanges = true;
        perform();
        break;

    case UserChoice::INVERT:
        editor.invert();
        cout << "Image inverted successfully.\n";
        hasUnsavedChanges = true;
        perform();
        break;


    case UserChoice::FLIP:
        flip();
        hasUnsavedChanges = true;
        cout << "Image flipped successfully.\n";
        perform();
        break;

    case UserChoice::ROTATE:
        rotationDegree = Utility::readNumber(90, 270, "Enter rotation angle(90, 180, or 270) :");
        editor.rotate(rotationDegree);
        hasUnsavedChanges = true;
        cout << "Image rotated successfully.\n";
        perform();
        break;

    case UserChoice::BLUR:
        editor.blur();
        hasUnsavedChanges = true;
        cout << "Darken image successfully.\n";
        perform();
        break;

    case UserChoice::OLD_TV:
        editor.oldTV();
        hasUnsavedChanges = true;
        cout << "Old TV image successfully.\n";
        perform();
        break;

    case UserChoice::PURPLE_RED:
        editor.purpleRed();
        hasUnsavedChanges = true;
        cout << "Purple image successfully.\n";
        perform();
        break;

    case UserChoice::DETECT_EDGES:
        editor.detectEdges();
        hasUnsavedChanges = true;
        cout << "Image edges detected successfully.\n";
        perform();
        break;

    case UserChoice::RESIZE:
        resize();
        hasUnsavedChanges = true;
        cout << "Image resized successfully.\n";
        perform();
        break;

    case UserChoice::OIL_PAINTING:
        editor.oilPainting();
        hasUnsavedChanges = true;
        cout << "Oil painting image successfully.\n";
        perform();
        break;

    case UserChoice::CROP:
        crop();
        hasUnsavedChanges = true;
        perform();
        break;

    case UserChoice::DARKEN_LIGHTEN:
        darkenOrLighten();
        hasUnsavedChanges = true;
        perform();
        break;

    case UserChoice::SAVE_IMAGE:
        saveEditing();
        perform();
        break;

    case UserChoice::LOAD_NEW_IMAGE:
        saveAndLoadImage();
        perform();
        break;

    case UserChoice::EXIT:
        cout << "Thank you for using the program. Goodbye!\n";
        break;
    default:
        cout << "Invalid Choice!";
        break;
    }

}


void perform()
{
    system("pause");
    displayOptions();
    int userChoice = (Utility::readNumber(1, 19, "Enter choice (1, 2, 3,4,5,6,7 or 8): "));
    if (!hasUnsavedChanges && Utility::equals(userChoice,18))
        userChoice++;
    UserChoice choice = (UserChoice)userChoice;
    perfromChoices(choice);
}


int main()
{
    editor = loadNewImage();
    perform();
    saveEditing();
    return 0;
}

