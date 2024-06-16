#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>

// 获取文件夹路径的对话框
std::wstring GetFolderPath() {
  WCHAR folderPath[MAX_PATH] = {0};
  BROWSEINFO bi;
  ZeroMemory(&bi, sizeof(bi));

  bi.lpszTitle = L"请选择文件夹";
  bi.ulFlags = BIF_RETURNTOPARENT | BIF_USENEWUI;

  LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
  if (pidl != NULL) {
    SHGetPathFromIDList(pidl, folderPath);
    CoTaskMemFree(pidl);
  }
  return folderPath;
}

int main() {
  // 获取文件夹路径
  std::wstring folderPath = GetFolderPath();
  if (folderPath.empty()) {
    MessageBox(NULL, L"未选择文件夹！", L"错误", MB_OK | MB_ICONERROR);
    return 1;
  }

  // 构建文件搜索路径
  std::wstring searchPath = folderPath + L"\\*.*";

  // 查找文件
  WIN32_FIND_DATA findData;
  HANDLE hFind = FindFirstFile(searchPath.c_str(), &findData);
  if (hFind == INVALID_HANDLE_VALUE) {
    MessageBox(NULL, L"查找文件失败！", L"错误", MB_OK | MB_ICONERROR);
    return 1;
  }

  // 打开输出文件
  std::ofstream outfile("file_list.txt");
  if (!outfile.is_open()) {
    MessageBox(NULL, L"无法创建文件！", L"错误", MB_OK | MB_ICONERROR);
    return 1;
  }

  // 写入文件名
  do {
    if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
      std::wstring filename(findData.cFileName);
      outfile << filename << std::endl;
    }
  } while (FindNextFile(hFind, &findData));

  // 关闭句柄和文件
  FindClose(hFind);
  outfile.close();

  MessageBox(NULL, L"文件列表已生成！", L"成功", MB_OK);
  return 0;
}
