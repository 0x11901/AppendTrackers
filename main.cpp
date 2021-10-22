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

void checkIfText();
void checkIfMagnetURI(const std::string &text);

int main() {
    try {
        checkIfText();
        std::string text;
        clip::get_text(text);
        checkIfMagnetURI(text);
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

void checkIfMagnetURI(const std::string &text) { std::regex txt_regex("[a-z]+\\.txt"); }
