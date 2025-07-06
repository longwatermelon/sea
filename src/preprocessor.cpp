#include "preprocessor.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>

namespace sea {
    string preprocess(const string &source_code, const string &base_dir) {
        static set<string> processed_files; // Track processed files to avoid circular includes
        string result = source_code;
        std::regex include_regex("^\\s*#include\\s+\"([^\"]+)\"\\s*$");
        std::istringstream stream(result);
        string line;
        vec<string> lines;
        
        // Process line by line
        while (std::getline(stream, line)) {
            std::smatch match;
            if (std::regex_match(line, match, include_regex)) {
                string filename = match[1].str();
                
                // Construct full path
                string full_path;
                if (base_dir.empty()) {
                    full_path = filename;
                } else {
                    full_path = base_dir + "/" + filename;
                }
                
                // Normalize path to handle relative components
                try {
                    full_path = std::filesystem::canonical(full_path);
                } catch (const std::filesystem::filesystem_error&) {
                    // If canonical fails, use the path as is
                }
                
                // Check for circular include
                if (processed_files.find(full_path) != processed_files.end()) {
                    lines.push_back("// Circular include detected: " + filename);
                    continue;
                }
                
                // Read the included file
                std::ifstream ifs(full_path);
                if (ifs.is_open()) {
                    processed_files.insert(full_path);
                    
                    std::stringstream buf;
                    buf << ifs.rdbuf();
                    ifs.close();
                    
                    string included_content = buf.str();
                    
                    // Get directory of included file for recursive includes
                    string included_dir = std::filesystem::path(full_path).parent_path();
                    
                    // Recursively preprocess the included content
                    string processed_content = preprocess(included_content, included_dir);
                    
                    processed_files.erase(full_path);
                    
                    // Add the processed content (split by lines to maintain line structure)
                    std::istringstream content_stream(processed_content);
                    string content_line;
                    while (std::getline(content_stream, content_line)) {
                        lines.push_back(content_line);
                    }
                } else {
                    lines.push_back("// Error: Could not open file " + filename);
                }
            } else {
                lines.push_back(line);
            }
        }
        
        // Reconstruct the result
        result.clear();
        for (size_t i = 0; i < lines.size(); ++i) {
            result += lines[i];
            if (i < lines.size() - 1) {
                result += "\n";
            }
        }
        
        return result;
    }
}
