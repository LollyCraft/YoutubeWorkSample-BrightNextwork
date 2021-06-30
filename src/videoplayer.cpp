#include "videoplayer.h"

#include <iostream>


void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

//========================================================================

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

void VideoPlayer::showAllVideos() {
  std::cout << "Here's a list of all available videos:" << std::endl;

  // for (Video vid1 : mVideoLibrary.getVideos()) {
  //   for (Video vid2 : mVideoLibrary.getVideos()) {
  //     if (vid1.getTitle()[0]> vid2.getTitle()[0]) {
  //       std::swap(vid1, vid2);
  //     }
  //   }
  // }

  for (Video vid : mVideoLibrary.getVideos()) {
    std::cout << '\t';
    printVideo(vid);
  }
}

//========================================================================

void VideoPlayer::playVideo(const std::string& videoId) {
  //std::cout << "playVideo needs implementation" << std::endl;
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
  //std::cout << "stopVideo needs implementation" << std::endl;
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
    // if (videoPlaying == true) {
    //   std::cout << "Stopping video: " << currentlyPlayingVideo.getTitle() << std::endl;
    // }
    std::cout << "paying random vid" << std::endl;
    // auto random_vid = std::next(std::begin(mVideoLibrary.getVideos()), rand() % (mVideoLibrary.getVideos().size()) );
    // Video r_vid = random_vid[0];
    // playVideo(r_vid.getVideoId());
  } else {
    std::cout << "No videos available" <<std::endl;
  }
}

//========================================================================

void VideoPlayer::pauseVideo() {
  //std::cout << "pauseVideo needs implementation" << std::endl;
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
  //std::cout << "continueVideo needs implementation" << std::endl;
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
  //std::cout << "showPlaying needs implementation" << std::endl;
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

//========================================================================

void VideoPlayer::createPlaylist(const std::string& playlistName) {
  // std::cout << "createPlaylist needs implementation" << std::endl;
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
  // std::cout << "addVideoToPlaylist needs implementation" << std::endl;
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

  if (videoExists == true) {
    for (Playlist p : playlistsVector) {
      if (p.name == playlistName) {
        playlistExists = true;
        for (std::string vidId : p.includedVideoIds) {
          if (vidId == videoId) {
            videoAlreadyAdded = true;
          }
        }
        if (playlistExists == true) {
          if (videoAlreadyAdded == false) {
            p.includedVideoIds.push_back(videoToBeAddedId);
            videoAlreadyAdded = true;
            std::cout << "Added video to " << playlistName << ": " << mVideoLibrary.getVideo(videoId)->getTitle() << std::endl;
          } else {
            std::cout << "Cannot add video to " << playlistName << ": Video already exists" << std::endl;
          }
        } else {
          std::cout << "Cannot add video to " << playlistName << ": Playlist does not exist" << std::endl;
        }
      }
    }
  } else {
    std::cout << "Cannot add video to " << playlistName << ": Video does not exist" << std::endl;
  }
}

//========================================================================

void VideoPlayer::showAllPlaylists() {
  // std::cout << "showAllPlaylists needs implementation" << std::endl;
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
  // std::cout << "showPlaylist needs implementation" << std::endl;
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
    std::cout << "Cannot show playlist " << playlistName << ": Paylist does not exist" << std::endl;
  }
}

//========================================================================

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::cout << "removeFromPlaylist needs implementation" << std::endl;
}

//========================================================================

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  std::cout << "clearPlaylist needs implementation" << std::endl;
}

//========================================================================

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  std::cout << "deletePlaylist needs implementation" << std::endl;
}

//========================================================================

void VideoPlayer::searchVideos(const std::string& searchTerm) {
  std::cout << "searchVideos needs implementation" << std::endl;
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  std::cout << "searchVideosWithTag needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}
