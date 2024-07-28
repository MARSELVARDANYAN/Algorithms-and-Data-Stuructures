class Solution {
public:
    std::string sortSentence(std::string s) {
        std::vector<std::string> words;
        std::stringstream ss(s);
        std::string word;

        while (ss >> word) {
            words.push_back(word);
        }

        std::sort(words.begin(), words.end(), [](const std::string &a, const std::string &b) {
            return a.back() < b.back();
        });

        std::string sortedSentence;
        for (size_t i = 0; i < words.size(); ++i) {
            words[i].pop_back();
            sortedSentence += words[i];
            if (i < words.size() - 1) {
                sortedSentence += " ";
            }
        }

        return sortedSentence;
    }
};
