#include "playlist.h"

Playlist::Playlist () {

}

Playlist::Playlist(std::string iname) :
    name(std::move(iname)) {
}