//
// Created by Dmytrenko Kyrylo on 05.04.2026.
//
#include "try_drill.h"
namespace ch9 {
    [[nodiscard]]std::ofstream open_output_stream(const std::string& file_name) {
        std::ofstream ofs {file_name};
        if (!ofs)
            error("can't open file");

        return ofs;
    }
    [[nodiscard]] std::ifstream open_input_stream(const std::string& file_name) {
        std::ifstream ifs {file_name};
        if (!ifs)
            error("can't open file");

        return ifs;
    }
}
