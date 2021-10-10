#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

// принтира първите n реда от файл
void printHead(std::ifstream& i_stream, int n)
{
    int lines = 0;
    std::string line;
    while(lines < n && std::getline(i_stream, line))
    {
        std::cout << line << '\n';  
        lines++;
    }
}

// принтиране на последните n реда с начална позиция на пойнтъра в края на файла
void printTailVer1(std::ifstream& i_stream, int n)
{
    int lines = 0;

    while(lines < n && i_stream.tellg() > 0)
    {
        char c;
        i_stream.seekg(-2, std::ios::cur);
        i_stream.read(&c, 1);
        if (c == '\n')
        {
            lines++;
        }
    }

    while (!i_stream.eof())
    {
        char c;
        i_stream.read(&c, sizeof(char));
        std::cout << c; 
    }
}

// принтиране на последните n реда с начална позиция на пойнтъра в началото на файла
void printTailVer2(std::ifstream& i_stream, int n)
{
    i_stream.seekg(0, i_stream.end);

    int lines = 0;

    while(lines < n && i_stream.tellg() > 0)
    {
        char c;
        i_stream.seekg(-1, std::ios::cur);
        if (i_stream.peek() == '\n')
        {
            lines++;
        }
    }

    while (!i_stream.eof())
    {
        char c;
        i_stream.read(&c, sizeof(char));
        std::cout << c; 
    }
}

// принтиране на всички редове, които съдържат дадена дума
void printLinesContainingWord(std::ifstream& i_stream, const std::string word)
{
    std::string line;
    while(std::getline(i_stream, line))
    {
        if(line.find(word) != std::string::npos)
        {
            std::cout << line << '\n';
        }
    }
}

// сортира файл по редове и запазва сортираното съдържание в нов файл
void sort(std::string filename, std::string newFile)
{
    std::ifstream i_stream(filename);
    if (!i_stream.is_open())
    {
        throw std::runtime_error("Error opening file!");
    }
    
    std::string line;
    std::vector<std::string> lines;

    while(std::getline(i_stream, line))
    {
        line += "\n";
        lines.push_back(line);
    }
    sort(lines.begin(), lines.end());
    i_stream.close();

    std::ofstream o_stream(newFile, std::ios::trunc);
    for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        o_stream << *it;
    }

    o_stream.close();
}

// премахва повтарящите се редове в сортиран файл и запазва филтрирания текст в нов файл
void flattenSortedText(std::string filename, std::string newFile)
{
    std::ifstream i_stream(filename);
    if (!i_stream.is_open())
    {
        throw std::runtime_error("Error opening file!");
    }

    std::string line;
    std::vector<std::string> lines;

    while(std::getline(i_stream, line))
    {
        line += "\n";
        if (!lines.empty())
        {
            if (lines.back() == line)
            {
                continue;
            }
        }
        lines.push_back(line);
    }

    std::ofstream o_stream(newFile, std::ios::trunc);
    for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        o_stream << *it;
    }

    o_stream.close();
}

int main()
{
    // Example 1
    std::ifstream i_file("war-and-peace-chapter1.txt");
    if (!i_file.is_open())
    {
        throw std::runtime_error("Error opening file!");
    }
    printHead(i_file, 10);

    // Example 2
    // std::ifstream i_file("war-and-peace-chapter1.txt", std::ios::ate);
    // if (!i_file.is_open())
    // {
    //     throw std::runtime_error("Error opening file!");
    // }
    // printTailVer1(i_file, 10);
    // i_file.close();
    
    // Example 3
    // std::ifstream i_file("war-and-peace-chapter1.txt");
    // if (!i_file.is_open())
    // {
    //     throw std::runtime_error("Error opening file!");
    // }
    // printTailVer2(i_file, 10);
    // i_file.close();

    // Example 4
    // std::ifstream i_file("war-and-peace-chapter1.txt");
    // if (!i_file.is_open())
    // {
    //     throw std::runtime_error("Error opening file!");
    // }
    // std::string word = "family";
    // printLinesContainingWord(i_file, word);
    // i_file.close();
    
    // Example 5
    // sort("war-and-peace-chapter1.txt", "sorted-file.txt");

    // Example 6
    // flattenSortedText("unflattened.txt", "flattened.txt");
}