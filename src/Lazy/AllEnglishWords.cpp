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