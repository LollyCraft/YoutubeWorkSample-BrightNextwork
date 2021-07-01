#include "videoplayer.h"

#include <iostream>
#include <algorithm>


void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

//=================================PART 1=======================================

void VideoPlayer::printVideo (Video vid) {
  std::cout << vid.getTitle() << " (" << vid.getVideoId() << ")";
  std::cout << " [";
  for (int i = 0; i < vid.getTags().size(); i++) {
    std::cout << vid.getTags()[i];
    if (i < vid.getTags().size() - 1) std::cout << " "; 
  }
  std::cout << "]" << std::endl;
}

//========================================================================
bool condition(std::string a, std::string b){
    return a < b;
}

void VideoPlayer::showAllVideos() {
  std::cout << "Here's a list of all available videos:" << std::endl;

  if (videoNameVector.empty()) {
    for (Video vid : mVideoLibrary.getVideos()) {
      videoNameVector.push_back(vid.getTitle());
    }
    std::sort(videoNameVector.begin(), videoNameVector.end(), condition);
  }

  for (std::string title : videoNameVector) {
    for (Video vid : mVideoLibrary.getVideos()) {
      if (vid.getTitle() == title) {
        std::cout << '\t';
        printVideo(vid);
      }
    }
  }
}

//========================================================================

void VideoPlayer::playVideo(const std::string& videoId) {
  bool found_vid = false;
  for (Video vid : mVideoLibrary.getVideos()) {
    if (found_vid == false) {
      if (vid.getVideoId() == videoId) {
        found_vid = true;
        if (videoPlaying == true) {
          std::cout << "Stopping video: " << lastPlayedVideo.getTitle() << std::endl;
        }
        std::cout << "Playing video: " << vid.getTitle() << std::endl;
        currentlyPlayingVideo = vid;
        lastPlayedVideo = vid;
        videoPlaying = true;
        videoPaused = false;
      }
    }
  }
  if (found_vid == false) {
    std::cout << "Cannot play video: Video does not exist" << std::endl;
  }
}

//========================================================================

void VideoPlayer::stopVideo() {
  if (videoPlaying == true) {
    std::cout << "Stopping video: " << currentlyPlayingVideo.getTitle() << std::endl;
    videoPlaying = false;
  } else {
    std::cout << "Cannot stop video: No video is currently playing" << std::endl;
  }
}

//========================================================================

void VideoPlayer::playRandomVideo() {
  std::cout << "playRandomVideo needs implementation" << std::endl;
  
  if (mVideoLibrary.getVideos().size() != 0) {
    if (videoPlaying == true) {
      std::cout << "Stopping video: " << currentlyPlayingVideo.getTitle() << std::endl;
    }
    std::cout << "paying random vid" << std::endl;
    // auto random_vid = std::next(std::begin(mVideoLibrary.getVideos()), rand() % (mVideoLibrary.getVideos().size()) );
    // Video r_vid = random_vid[0];
    // playVideo(r_vid.getVideoId());
    //cannot get the random index to point to a video in the map
  } else {
    std::cout << "No videos available" <<std::endl;
  }
}

//========================================================================

void VideoPlayer::pauseVideo() {
  if (videoPlaying == true && videoPaused == false) {
    videoPaused = true;
    std::cout << "Pausing video: " << currentlyPlayingVideo.getTitle() << std::endl;
  } else if (videoPlaying == false) {
    std::cout << "Cannot pause video: No video is currently playing" << std::endl;
  } else if (videoPaused == true) {
    std::cout << "Video already paused: " << currentlyPlayingVideo.getTitle() << std::endl;
  }
}

//========================================================================

void VideoPlayer::continueVideo() {
  if (videoPlaying == true && videoPaused == true) {
    videoPaused = false;
    std::cout << "Continuing video: " << currentlyPlayingVideo.getTitle() << std::endl;
  } else if (videoPlaying == false) {
    std::cout << "Cannot continue video: No video is currently playing" << std::endl;
  } else if (videoPaused == false) {
    std::cout << "Cannot continue video: Video is not paused" << std::endl;
  }
}

//========================================================================

void VideoPlayer::showPlaying() {
  if (videoPlaying == true) {
    if (videoPaused == false) {
      std::cout << "Currently playing: ";
      printVideo(currentlyPlayingVideo);
      std::cout << std::endl;
    } else {
      std::cout << "Currently playing: ";
      printVideo(currentlyPlayingVideo);
      std::cout << " - PAUSED " << std::endl;
    }
  } else {
    std::cout << "No video is currently playing" << std::endl;
  }
}

//===================================PART 2=====================================
// creating a new data structure similar to VideoLibrary for Playlists

void VideoPlayer::createPlaylist(const std::string& playlistName) {
  bool playlistExists = false;
  for (Playlist p : playlistsVector) {
    if (p.name == playlistName) {
      playlistExists = true;
    }
  }

  if (playlistExists == false) {
    playlistsVector.push_back(Playlist(playlistName));
    std::cout << "Successfully created new playlist: " << playlistName << std::endl;
  } else {
    std::cout << "Cannot create playlist: A playlist with the same name already exists" << std::endl;
  }
}

//========================================================================

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  bool videoExists = false;
  bool playlistExists = false;
  bool videoAlreadyAdded = false;
  std::string videoToBeAddedId = "";

  for (Video vid : mVideoLibrary.getVideos()) {
    if (vid.getVideoId() == videoId) {
      videoExists = true;
      videoToBeAddedId = videoId;
    }
  }

  for (Playlist p : playlistsVector) {
    if (p.name == playlistName) {
      playlistExists = true;
      for (std::string vidId : p.includedVideoIds) {
        if (vidId == videoId) {
          videoAlreadyAdded = true;
        }
      }
    }
  }

  if (playlistExists == true) {
    if (videoExists == true) { 
      for (Playlist p : playlistsVector) {
        if (p.name == playlistName) {
          if (videoAlreadyAdded == false) {
            (p.includedVideoIds).push_back(videoToBeAddedId); // should i have used pointer to keep the values? are they lost as temporary varables?
            std::cout << "Added video to " << playlistName << ": " << mVideoLibrary.getVideo(videoId)->getTitle() << std::endl;
            // std::cout << p.includedVideoIds.size() << std::endl;
          } else {
            std::cout << "Cannot add video to " << playlistName << ": Video already exists" << std::endl;
          }
        }
      }
    } else {
      std::cout << "Cannot add video to " << playlistName << ": Video does not exist" << std::endl;
    }
  } else {
          std::cout << "Cannot add video to " << playlistName << ": Playlist does not exist" << std::endl;
  }
}

//========================================================================

void VideoPlayer::showAllPlaylists() {
  if (playlistsVector.size() == 0) {
    std::cout << "No playlists exist yet" << std::endl;
  } else {
    std::cout << "Showing all playlists:" << std::endl;
    for (Playlist p : playlistsVector) {
      std::cout << '\t' << p.name << std::endl;
    }
  }
}

//========================================================================

void VideoPlayer::showPlaylist(const std::string& playlistName) {
  bool playlistExists = false;
  for (Playlist p : playlistsVector) {
      if (p.name == playlistName) {
        playlistExists = true;
      }
  }

  if (playlistExists == true) {
    for (Playlist p : playlistsVector) {
      if (p.name == playlistName) {
        std::cout << "Showing playlist: " << playlistName << std::endl;
        std::cout << p.includedVideoIds.size() << std::endl;
        if (p.includedVideoIds.size() == 0) {
          std::cout << '\t' << "No videos here yet" << std::endl;
        } else {
          for (std::string ids : p.includedVideoIds) {
            Video v = *mVideoLibrary.getVideo(ids);
            printVideo(v);
          }
        }
      }
    }
  } else {
    std::cout << "Cannot show playlist " << playlistName << ": Playlist does not exist" << std::endl;
  }
}

//========================================================================

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  bool videoExists = false;
  bool playlistExists = false;
  bool videoInPlaylist = false;
  std::string videoToBeAddedId = "";

  for (Video vid : mVideoLibrary.getVideos()) {
    if (vid.getVideoId() == videoId) {
      videoExists = true;
      videoToBeAddedId = videoId;
    }
  }

  for (Playlist p : playlistsVector) {
    if (p.name == playlistName) {
      playlistExists = true;
      for (std::string vidId : p.includedVideoIds) {
        if (vidId == videoId) {
          videoInPlaylist = true;
        }
      }
    }
  }

  if (playlistExists == true) {
    if (videoExists == true) { 
      for (Playlist p : playlistsVector) {
        if (p.name == playlistName) {
          if (videoInPlaylist == true) {
            p.includedVideoIds.push_back(videoToBeAddedId);
            std::cout << "Removed video from " << playlistName << ": " << mVideoLibrary.getVideo(videoId)->getTitle() << std::endl;
            // std::cout << p.includedVideoIds.size() << std::endl;
          } else {
            std::cout << "Cannot remove video from " << playlistName << ": Video does not exist" << std::endl;
          }
        }
      }
    } else {
      std::cout << "Cannot remove video from " << playlistName << ": Video does not exist" << std::endl;
    }
  } else {
    std::cout << "Cannot remove video from " << playlistName << ": Playlist does not exist" << std::endl;
  }
}

//========================================================================

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  bool playlistExists = false;


  for (Playlist p : playlistsVector) {
    if (p.name == playlistName) {
      playlistExists = true;
    }
  }

  if (playlistExists == true) {
      for (Playlist p : playlistsVector) {
        if (p.name == playlistName) {
            p.includedVideoIds.clear();
            std::cout << "Successfully removed all videos from " << playlistName << std::endl;
        }
      }  
  } else {
    std::cout << "Cannot remove video from " << playlistName << ": Playlist does not exist" << std::endl;
  }
}

//========================================================================

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  bool playlistExists = false;
  for (Playlist p : playlistsVector) {
    if (p.name == playlistName) {
      playlistExists = true;
    }
  }
  
  if (playlistExists == true) {
    for (int i = 0; i < playlistsVector.size(); i++) {
      if (playlistsVector[i].name == playlistName) {
        playlistsVector.erase(playlistsVector.begin() + i);
        std::cout << "Deleted playlist: " << playlistName << std::endl;
      }
    }
  } else {
    std::cout << "Cannot delete playlist " << playlistName << ": Playlist does not exist" << std::endl;
  }
}

//===================================PART 3=====================================
bool isNumber(std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {
  //works but it is case sensitive! search for Cat as an example
  std::string userInput;
  std::vector<std::string> searchedVideoIds;
  bool foundVideos = false;

  if (videoNameVector.empty()) {
    for (Video vid : mVideoLibrary.getVideos()) {
      videoNameVector.push_back(vid.getTitle());
    }
    std::sort(videoNameVector.begin(), videoNameVector.end(), condition);
  }
  
  for (std::string title : videoNameVector) {
    if (title.find(searchTerm) != std::string::npos) {
      foundVideos = true;
    }
  }

  if (foundVideos == true) {
    std::cout << "Here are the results for " << searchTerm << ":" << std::endl;
    int i = 1;
    for (std::string title : videoNameVector) {
      for (Video vid : mVideoLibrary.getVideos()) {
        if (vid.getTitle().find(searchTerm) != std::string::npos) {
          if (vid.getTitle() == title) {
            std::cout << '\t' << i << ") ";
            printVideo(vid);
            i++;
            searchedVideoIds.push_back(vid.getVideoId());
          }
        }
      }
    }
    std::cout << "Would you like to play any of the above? If yes, specify the number of the video." << ":" << std::endl;
    std::cout << "If your answer is not a valid number, we will assume it's a no." << std::endl;
    std::cin >> userInput;
    if (isNumber(userInput) && std::stoi(userInput) > 0 && std::stoi(userInput) <= i) {
      playVideo(searchedVideoIds[std::stoi(userInput) - 1]);
    } else {
      //do nothing, do not play any video
    }
  } else {
    std::cout << "No search results for " << searchTerm << std::endl;
  }
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  //very similar to search in title, but we have another depth for searching in the tags vector
  std::string userInput;
  std::vector<std::string> searchedVideoIds;
  bool foundVideos = false;

  if (videoNameVector.empty()) {
    for (Video vid : mVideoLibrary.getVideos()) {
      videoNameVector.push_back(vid.getTitle());
    }
    std::sort(videoNameVector.begin(), videoNameVector.end(), condition);
  }

  for (Video vid : mVideoLibrary.getVideos()) {
    // std::cout << title << std::endl; //DEBUG
    for (std::string tag : vid.getTags()) {
      if (tag.find(videoTag) != std::string::npos) {
        foundVideos = true;
      }
    }
  }

  if (foundVideos == true) {
    std::cout << "Here are the results for " << videoTag << ":" << std::endl;
    int i = 1;
    for (std::string title : videoNameVector) {
      for (Video vid : mVideoLibrary.getVideos()) {
        for (std::string tag : vid.getTags()) {
          if (tag.find(videoTag) != std::string::npos) {
            if (vid.getTitle() == title) {
              std::cout << '\t' << i << ") ";
              printVideo(vid);
              i++;
              searchedVideoIds.push_back(vid.getVideoId());
            }
          }
        } 
      }
    }
    std::cout << "Would you like to play any of the above? If yes, specify the number of the video." << ":" << std::endl;
    std::cout << "If your answer is not a valid number, we will assume it's a no." << std::endl;
    std::cin >> userInput;
    if (isNumber(userInput) && std::stoi(userInput) > 0 && std::stoi(userInput) <= i) {
      playVideo(searchedVideoIds[std::stoi(userInput) - 1]);
    } else {
      //do nothing, do not play any video
    }
  } else {
    std::cout << "No search results for " << videoTag << std::endl;
  }
}

//===================================PART 4=====================================

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}
