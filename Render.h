#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <string>

const std::string gscale1 = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^.y' ";

std::vector <std::vector<char>> render_to_char(std::vector<std::vector<double>> M) {
    double m = 0;
    for (auto & line : M) {
        for (auto & el : line) {
            if (el > m)
                m = el;
        }
    }
    std::vector <std::vector<char>> picture(M.size());
    for (size_t i = 0; i < M.size(); ++i) {
        picture[i] = std::vector<char>(M[0].size());
        for (size_t j = 0; j < M[0].size(); ++j) {
            picture[i][j] = (m) ? gscale1[gscale1.size() - (size_t) ((gscale1.size()-1)*(M[i][j]/m))] : ' ';
        }
    }
    return picture;
}

std::vector <std::vector<int>> render_to_t_colors(std::vector<std::vector<double>> M) {
    double m = 0;
    for (auto & line : M) {
        for (auto & el : line) {
            if (el > m)
                m = el;
        }
    }
    std::vector <std::vector<int>> picture(M.size());
    int size = 255-232;
    for (size_t i = 0; i < M.size(); ++i) {
        picture[i] = std::vector<int>(M[0].size());
        for (size_t j = 0; j < M[0].size(); ++j) {
            picture[i][j] = (m > 0.0000001) ? (232 + (size*(M[i][j]/m))) : 232;
        }
    }
    return picture;
}

#endif // RENDER_H