#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

class GameState {

private:
    const std::vector<std::string>& m_story;
    int m_index = 0;
    bool m_isFinished = false;
    bool m_shouldDisplay = false;

public:
    GameState(const std::vector<std::string>& story) : m_story(story) {
        std::cout << "Welcome to this story! Type 'exit' to exit, 'next' (or nothing) to advance, or 'prev' to go back"
                     "." <<
        std::endl;
    }

    bool isFinished() {
        return m_isFinished;
    }

    void handleInput(const std::string& in) {
        m_shouldDisplay = true;
        if (in == "exit") {
            m_isFinished = true;
        } else if (in == "next" || in.empty()) {
            m_index++;
        } else if (in == "prev") {
            m_index--;
        } else {
            std::cerr << "Invalid input. Type 'exit' to exit, 'next' (or nothing) to advance, or 'prev' to go back."
            << std::endl;
            m_shouldDisplay = false;
        }
    }

    void updateState() {
        // In practice I think I would want to do htis in handleInput(), but I'm doing it here to demonstrate what a
        // state updating function might be like.

        // Clamp the index
        if (m_index < 0) {
            std::cerr << "(You're already at the start of the story, you cannot go any further back.)" << std::endl;
            m_index = 0;
            m_shouldDisplay = false;
        } else if (m_index >= m_story.size()) {
            m_isFinished = true;
        }
    }

    void render() {
        if (!m_isFinished && m_shouldDisplay) {
            std::cout << m_story[m_index] << std::endl;
        }
    }

};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "You must supply a story to read" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;

    while(std::getline(file, line)) {
        lines.push_back(line);
    }

    GameState gs(lines);
    while (!gs.isFinished()) {
        std::string input;
        std::getline(std::cin, input);
        gs.handleInput(input);
        gs.updateState();
        gs.render();
    }

    return 0;
}