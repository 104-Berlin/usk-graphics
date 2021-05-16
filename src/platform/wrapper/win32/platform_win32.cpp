#include "../graphics_wrapper.h"

#include <Windows.h>

using namespace Graphics;

struct CharBuffer
{
    char* Buffer;

    void Init(size_t size)
    {
        Buffer = new char[size];
    }

    void Delete()
    {
        delete[] Buffer;
    }
};

CharBuffer GetFilterList(const std::vector<std::string>& filters)
{
    // Example filter string: "(*.jpg;*.png;*.bmp)\0*.jpg;*.png;*.bmp\0"
        // Get the buffer length
        //               2 * "("     all the ";"          all the "*" and "."  Null Termination
    size_t bufferLength = 2 + (filters.size() - 1) * 2 + filters.size() * 4 +       2;
    for (const std::string& f : filters)
    {
        bufferLength += f.length() * 2;
    }
    // (*esc)\0*esc\0
    CharBuffer buffer;
    buffer.Init(bufferLength);
    char* ptr = buffer.Buffer;

    *ptr = '(';
    ptr++;

    for (size_t i = 0; i < filters.size(); i++)
    {
        const std::string& f = filters[i];

        *ptr = '*';
        ptr++;
        *ptr = '.';
        ptr++;
        memcpy(ptr, f.c_str(), f.length());
        ptr += f.length();

        if (i < filters.size() - 1)
        {
            *ptr = ';';
            ptr++;
        }
    }

    *ptr = ')';
    ptr++;

    *ptr = '\0';
    ptr++;

    for (size_t i = 0; i < filters.size(); i++)
    {
        const std::string& f = filters[i];

        *ptr = '*';
        ptr++;
        *ptr = '.';
        ptr++;
        memcpy(ptr, f.c_str(), f.length());
        ptr += f.length();

        if (i < filters.size() - 1)
        {
            *ptr = ';';
            ptr++;
        }
    }


    *ptr = '\0';
    ptr++;
    return buffer;
}



std::vector<std::string> Wrapper::OpenFileDialog(const std::string& title, const std::vector<std::string>& filters, const std::string& defaultPath)
{
    CharBuffer filter = GetFilterList(filters);

    OPENFILENAME ofn = {0}; 
    TCHAR szFile[260]={0};
    // Initialize remaining fields of OPENFILENAME structure
    ofn.lStructSize = sizeof(ofn); 
    ofn.hwndOwner = NULL; 
    ofn.lpstrFile = szFile; 
    ofn.nMaxFile = sizeof(szFile); 
    ofn.lpstrFilter = filter.Buffer;
    ofn.nFilterIndex = 1; 
    ofn.lpstrFileTitle = NULL; 
    ofn.nMaxFileTitle = 0; 
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


    if(GetOpenFileName(&ofn) == TRUE)
    { 
    // use ofn.lpstrFile here
        filter.Delete();
        return {ofn.lpstrFile};
    }
    filter.Delete();
    return {};
}

std::string Wrapper::SaveFileDialog(const std::string& title, const std::vector<std::string>& allowedEndings)
{
    CharBuffer filter = GetFilterList(allowedEndings);

    OPENFILENAME ofn = { 0 };
    TCHAR szFile[260] = { 0 };
    // Initialize remaining fields of OPENFILENAME structure
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter.Buffer;
    if (allowedEndings.size() > 0) {
        ofn.lpstrDefExt = allowedEndings[0].c_str();
    }
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    //ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetSaveFileName(&ofn) == TRUE)
    {
        // use ofn.lpstrFile here
        filter.Delete();
        return ofn.lpstrFile;
    }
    filter.Delete();
    return {};
}
