// Standard
//#include <filesystem>
#include <iostream>
#include <fstream>

// Standard, OS-Speciifc
#include <Windows.h>
#include <commdlg.h>

// 1st Party
#include "AllEnglishWords.h"

static std::string OpenFileDialog()
{
    // Prepare structure for the Open File Dialog
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // Ensure valid file path
    ofn.lpstrTitle = "Select a File";

    // Show the File Dialog
    if (GetOpenFileName(&ofn))
    {
        // Return the selected file path
        return std::string(fileName);
    }
    else
    {
        // No file selected or canceled
        return "";
    }
}

AllEnglishWords::AllEnglishWords()
{
	// Open words file
    std::string filePath = OpenFileDialog();
    std::ifstream file(filePath);
    if (!file)
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return;
    }

	// For each word
    std::string word;
    while (std::getline(file, word))
    {
        // Insert word into Trie
        Insert(word);
    }
}

void AllEnglishWords::Test()
{
    // Painting 1
    /*std::string letter1 = "ptlsmwbc";
    std::string letter2 = "rtaeiouh";
    std::string letter3 = "oivlrnts";
    std::string letter4 = "adthsikv";
    std::string letter5 = "onlrcsae";
    std::string letter6 = "dgrwteyn";*/

    // Painting 2
    /*std::string letter1 = "pfrlhcsv";
    std::string letter2 = "iouhlrae";
    std::string letter3 = "gaocmtrp";
    std::string letter4 = "dleiustr";
    std::string letter5 = "iutrlhae";
    std::string letter6 = "ltnraezh";
    std::string letter7 = "dernysgh";*/

    // Painting 3
    std::string letter1 = "mnrtdghl";
    std::string letter2 = "hryaeiou";
    std::string letter3 = "nsomrauf";
    std::string letter4 = "eioupgta";
    std::string letter5 = "lnorstcg";
    std::string letter6 = "aeiohnlt";
    std::string letter7 = "cedstolu";
    std::string letter8 = "tyhesnrk";

    for (int i1 = 0; i1 < letter1.size(); ++i1)
    {
        for (int i2 = 0; i2 < letter2.size(); ++i2)
        {
            for (int i3 = 0; i3 < letter3.size(); ++i3)
            {
                for (int i4 = 0; i4 < letter4.size(); ++i4)
                {
                    for (int i5 = 0; i5 < letter5.size(); ++i5)
                    {
                        for (int i6 = 0; i6 < letter6.size(); ++i6)
                        {
                            for (int i7 = 0; i7 < letter7.size(); ++i7)
                            {
                                for (int i8 = 0; i8 < letter8.size(); ++i8)
                                {
                                    std::string testWord = {
                                        letter1[i1]
                                        , letter2[i2]
                                        , letter3[i3]
                                        , letter4[i4]
                                        , letter5[i5]
                                        , letter6[i6]
                                        , letter7[i7]
                                        , letter8[i8]
                                    };

                                    if (Find(testWord))
                                    {
                                        std::cout << /*"Possible word: " << */testWord << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
