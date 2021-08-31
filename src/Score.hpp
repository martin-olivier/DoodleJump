#pragma once

#include <iostream>

namespace Score {
    void Save(const std::string &path, size_t score);
    size_t Load(const std::string &path);
}