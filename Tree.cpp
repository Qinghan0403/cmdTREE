#include <iostream>
#include <string>
#include <windows.h>

void ListFiles(const std::string& folderPath, const std::string& parentFolder, int level) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    std::string searchPath = folderPath + "\\*.*";
    hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "�޷��ҵ��ļ���" << std::endl;
        return;
    }

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
                std::string subFolderPath = folderPath + "\\" + findData.cFileName;
                std::string subFolderParent = parentFolder + "\\" + findData.cFileName;

                // ��ӡ�����ո�
                for (int i = 0; i < level; i++) {
                    std::cout << "   ";
                }

                std::cout << "|- [�ļ���] " << findData.cFileName << std::endl;
                ListFiles(subFolderPath, subFolderParent, level + 1);  // �ݹ鴦�����ļ���
            }
        } else {
            // ��ӡ�����ո�
            for (int i = 0; i < level; i++) {
                std::cout << "   ";
            }

            std::cout << "|- [�ļ�] " << findData.cFileName << std::endl;
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        std::cout << "��ȡ�ļ�ʱ��������" << std::endl;
    }

    FindClose(hFind);
}

int main() {
    std::string folderPath;

    while (true) {
        std::cout << "�������ļ���·�� (����exit�˳�): ";
        std::getline(std::cin, folderPath);

        if (folderPath == "exit") {
            break;
        }

        std::cout << folderPath << std::endl; // ��ӡ���ļ���·��
        ListFiles(folderPath, folderPath, 1);  // �ӵ�һ��Ŀ¼��ʼ�ݹ����
        std::cout << std::endl; // ��ӡ����
    }

    return 0;
}
