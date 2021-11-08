//******************************************************************************
// Copyright (c) 2018-2021 WANG,Jingkai. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//******************************************************************************

#include "boxer/boxer.h"
#include "clip/clip.h"
#include "except.h"
#include <filesystem>
#include <fstream>
#include <iterator>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif

void checkIfText();
std::shared_ptr<std::vector<std::string>> splitStringByLine(const std::string &text);
void checkIfMagnetURI(const std::vector<std::string> &urls);
void appendTrackers(const std::shared_ptr<std::vector<std::string>> &urls);
void setTextToClip(const std::shared_ptr<std::vector<std::string>> &urls);

#ifdef _WIN32
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
int main() {
    try {
        checkIfText();
        std::string text;
        clip::get_text(text);
        auto urls = splitStringByLine(text);
        checkIfMagnetURI(*urls);
        appendTrackers(urls);
        setTextToClip(urls);
    } catch (except &e) {
        boxer::show(e.what(), "runtime_error", boxer::Style::Warning);
    }
    return 0;
}

void checkIfText() {
    auto b = clip::has(clip::text_format());
    if (!b) {
        throw except("clipboard contents must be text.");
    }
}

std::shared_ptr<std::vector<std::string>> splitStringByLine(const std::string &text) {
    std::istringstream input;
    input.str(text);
    auto map = std::make_shared<std::vector<std::string>>();
    for (std::string line; std::getline(input, line);) {
#ifdef _WIN32
        if (!line.empty() && *line.rbegin() == '\r') {
            line.erase(line.length() - 1, 1);
        }
#endif
        if (!line.empty()) {
            map->push_back(line);
        }
    }
    return map;
}

void checkIfMagnetURI(const std::vector<std::string> &urls) {
    std::regex magnet_url_regex("^(magnet:\\?xt=urn:btih:)[0-9a-fA-F]{40}.*$");
    for (const auto &url : urls) {
        auto b = std::regex_match(url, magnet_url_regex);
        if (!b) {
            throw except("clipboard contents must be magnet urls.");
        }
    }
}

void appendTrackers(const std::shared_ptr<std::vector<std::string>> &urls) {
    std::ifstream ifs;
    ifs.open("tacker_tail.txt"); // open the input file

    if (!ifs.is_open()) {
        throw except("\"tacker_tail.txt\" is required.");
    }

    std::string file_content;
    std::getline(std::ifstream("tacker_tail.txt"), file_content);
    ifs.close();

    for (auto &url : *urls) {
        url += file_content;
    }
}

void setTextToClip(const std::shared_ptr<std::vector<std::string>> &urls) {
    auto s = "\n";
#ifdef _WIN32
    s = "\r\n";
#endif
    clip::set_text(std::accumulate((*urls).begin(), (*urls).end(), std::string(),
                                   [&s](const auto &a, const auto &b) { return a + (!a.empty() ? s : "") + b; }));
}