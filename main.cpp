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
#include <regex>
#include <sstream>
#include <string>

void checkIfText();
std::vector<std::string> splitStringByLine(const std::string &text);
void checkIfMagnetURI(const std::vector<std::string> &urls);

int main() {
    try {
        checkIfText();
        std::string text;
        clip::get_text(text);
        auto urls = splitStringByLine(text);
        checkIfMagnetURI(urls);
    } catch (except &e) {
        boxer::show(e.what(), "runtime_error");
    } catch (...) {
        boxer::show("unknown error.", "unknown_error");
    }
    return 0;
}

void checkIfText() {
    auto b = clip::has(clip::text_format());
    if (!b) {
        throw except("clipboard contents must be text.");
    }
}

std::vector<std::string> splitStringByLine(const std::string &text) {
    std::istringstream input;
    input.str(text);
    std::vector<std::string> map;
    for (std::string line; std::getline(input, line);) {
#ifdef _WIN32
        if (!line.empty() && *line.rbegin() == '\r') {
            line.erase(line.length() - 1, 1);
        }
#endif
        map.push_back(line);
    }
    return map;
}

void checkIfMagnetURI(const std::vector<std::string> &urls) {
    std::regex txt_regex("[a-z]+\\.txt");
    for (const auto &url : urls) {
        printf("1");
    }
}
