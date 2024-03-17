#include "Tags/Tag.h"

int main(int argc, char** argv) {
    Tag tag;
    tag.Parse(argc, argv);

    for (int i = 0; i < tag.frames_.size(); ++i) {
        tag.frames_[i]->GetInfo();
        std::cout << '\n';
        delete tag.frames_[i];
    }

    return 0;
}
