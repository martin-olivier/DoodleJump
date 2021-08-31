#include "Score.hpp"
#include <fstream>

void Score::Save(const std::string &path, size_t score)
{
    std::ofstream file_stream(path);
    if (!file_stream.is_open())
        std::cerr << "failed to open or create: " << path << std::endl;
    file_stream << score;
}

size_t Score::Load(const std::string &path)
{
    std::string file_content{};
    std::ifstream file_stream(path);
    if (!file_stream.is_open())
        return 0;
    std::getline(file_stream, file_content, '\0');
    try {
        return std::stoul(file_content);
    }
    catch (...) {
        return 0;
    }
}