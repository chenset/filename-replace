#include <stdio.h>
#include <io.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>
#include <QApplication>
#include "textfinder.h"

using namespace std;


/**
 * 获取文件后缀名
 * @param filename
 * @return 获取不到返回 ""
 */
string getExt(const string &filename) {
    char *ext;
    string returnStr = "";
    ext = strrchr(filename.c_str(), '.');
    if (ext == nullptr) { return ""; }

    int len = strlen(ext);
    if (len < 2) { return ""; }

    for (auto i = 0; i < len; ++i) {  // 去掉"."号
        if (i == 0) { continue; }
        returnStr += ext[i];
    }

    return returnStr;
}

/**
 * @param str
 * @param start  begin(arr[])
 * @param last  end(arr[])
 * @return
 */
bool inArray(string str, string *start, string *last) {
    for (; start != last; ++start) {
        if (str == *start) {
            return true;
        }
    }
    return false;
}

vector<string> strSplit(const string &str, const string &split) {
    vector<string> res;
    size_t splitLen = split.length();
    size_t pos;
    string findStr = str;
    do {
        pos = findStr.find(split);
        res.push_back(findStr.substr(0, pos));
        findStr = findStr.substr(pos + splitLen);
    } while (pos != string::npos);
    return res;
}

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(textfinder);
    QApplication app(argc, argv);

    TextFinder *textFinder = new TextFinder;
    textFinder->show();

    return app.exec();
}
