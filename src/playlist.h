#pragma once

#include <string>
#include <vector>
#include "video.h"

class Playlist {
 private:
    
 public:
    std::string name;
    std::vector<std::string> includedVideoIds;
    
    Playlist();
    Playlist(std::string iname);
    
};