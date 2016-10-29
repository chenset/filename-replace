#include <stdio.h>
#include <io.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <regex>

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


void movieProcess(const string &file) {
    smatch what;
    auto start = file.begin();
    auto end = file.end();

    std::cout << file << endl;
    while (regex_search(start, end, what, regex("\\d+"))) {
        std::cout << what[0] << std::endl;
        start += what.position() + what.length();
    }

}

int main(void) {
    string subPostfix[] = {"ssa", "ass", "smi", "str", "sub", "lrc", "sst", "txt", "xss", "psb", "ssb"};
    string moviePostfix[] = {"wmv", "asf", "asx", "rm", "rmvb", "mpg", "mpeg", "mpe", "3gp", "mov", "mp4", "m4v",
                             "avi",
                             "mkv", "flv", "vob"};


    inArray("mkv", begin(moviePostfix), end(moviePostfix));
    vector<string> subs, movies;

    _finddata_t fileDir;
    string path = "D:/test/";
    char *dir = "D:/test/*";
    int lfDir;

    if ((lfDir = _findfirst(dir, &fileDir)) != -1l) {
        do {
            if (strcmp(fileDir.name, ".") == 0 || strcmp(fileDir.name, "..") == 0 ||
                (fileDir.attrib & _A_SUBDIR) != 0) {
                continue;
            }

            string tmp = fileDir.name;
            tmp = path + tmp;
            string ext = getExt(fileDir.name);
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            if (inArray(ext, begin(moviePostfix), end(moviePostfix))) {
                movies.push_back(tmp);
            }
            if (inArray(ext, begin(subPostfix), end(subPostfix))) {
                subs.push_back(tmp);
            }
        } while (_findnext(lfDir, &fileDir) == 0);
    }
    _findclose(lfDir);


    std::cout << movies.size() << endl;
    std::cout << subs.size() << endl;


    for (auto i = movies.begin(); i != movies.end(); ++i) {
        movieProcess(*i);
    }

}
