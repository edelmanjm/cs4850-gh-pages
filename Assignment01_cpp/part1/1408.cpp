// Pulled from a Leetcode problem I did at some point

#include <algorithm>
#include <string>
#include <vector>

class Solution {
public:
    std::vector<std::string> stringMatching(std::vector<std::string>& words) {
        std::vector<std::string> ret;

        std::sort(words.begin(), words.end(), [](auto& s0, auto& s1) {
            return s0.size() < s1.size();
        });
        for (int i = 0; i < words.size(); i++) {
            int j = i + 1;
            while (j < words.size()) {
                if (words[j].find(words[i]) != std::string::npos) {
                    ret.push_back(words[i]);
                    break;
                }
                j++;
            }
        }

        return ret;
    }
};

int main() {
    std::vector<std::string> test{"mass","as","hero","superhero"};
    std::vector<std::string> results = (Solution()).stringMatching(test);
    if (std::find(results.begin(), results.end(), "hero") == results.end()) {
        return 1;
    }
    return 0;
}