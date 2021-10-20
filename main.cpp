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

int checkIfText();

int main() {
    auto ret = 0;
    ret = checkIfText();
    if (ret != 0) {
        boxer::show("Simple message boxes are very easy to create.", "Simple Example");
    }
    return ret;
}

int checkIfText() {
    auto b = clip::has(clip::text_format());
    if (!b) {
        return -1;
    }
    return 0;
}