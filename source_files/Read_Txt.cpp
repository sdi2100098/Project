#include "Library.hpp"
std::vector<std::vector<int>> ReadFileTXT(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening File");
        return {};
    }

    char line[256];
    std::vector<std::vector<int>> info;

    while (fgets(line, sizeof(line), file))
    {
        std::vector<int> row;

        std::istringstream iss(line);
        int number;
        while (iss >> number)
            row.push_back(number);

        info.push_back(row);
    }
    fclose(file);
    return info;
}