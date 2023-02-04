void write_to_file(std::vector<multipole_creation> &result, const std::string output_file) {
    std::ofstream output(output_file);
    std::cout << output_file << std::endl;
    if (output.is_open()) {
        output << result[0].g_original << std::endl;
        for (const auto &oneRes : result) {
            output
//            << oneRes.g
                    << " edges: "
                    << oneRes.props.locs
                    << ", vertices: "
                    << oneRes.props.vertices
                    << ", colourable: "
                    << oneRes.isColorable
                    << ", perfect: "
                    << oneRes.isPerfect
                    << ", possible colourings: "
                    << oneRes.possible_colourings
                    << ", colourings size: "
                    << oneRes.possible_colourings.size()
                    << std::endl;
        }
    } else std::cerr << "Unable to open file" << std::endl;
}