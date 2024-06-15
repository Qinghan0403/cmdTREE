#include <iostream>
#include <string>
#include <windows.h>

void ListFiles(const std::string& folderPath, const std::string& parentFolder, int level) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    std::string searchPath = folderPath + "\\*.*";
    hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "无法找到文件！" << std::endl;
        return;
    }

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
                std::string subFolderPath = folderPath + "\\" + findData.cFileName;
                std::string subFolderParent = parentFolder + "\\" + findData.cFileName;

                // 打印缩进空格
                for (int i = 0; i < level; i++) {
                    std::cout << "   ";
                }

                std::cout << "|- [文件夹] " << findData.cFileName << std::endl;
                ListFiles(subFolderPath, subFolderParent, level + 1);  // 递归处理子文件夹
            }
        } else {
            // 打印缩进空格
            for (int i = 0; i < level; i++) {
                std::cout << "   ";
            }

            std::cout << "|- [文件] " << findData.cFileName << std::endl;
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        std::cout << "读取文件时发生错误！" << std::endl;
    }

    FindClose(hFind);
}

int main() {
    std::string folderPath;

    while (true) {
        std::cout << "请输入文件夹路径 (输入exit退出): ";
        std::getline(std::cin, folderPath);

        if (folderPath == "exit") {
            break;
        }

        std::cout << folderPath << std::endl; // 打印根文件夹路径
        ListFiles(folderPath, folderPath, 1);  // 从第一级目录开始递归遍历
        std::cout << std::endl; // 打印换行
    }

    return 0;
}
