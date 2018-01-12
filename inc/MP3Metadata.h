/*
 * MP3Metadata.h
 *
 *  Created on: Jan 11, 2018
 *      Author: rzv0cn
 */

#ifndef INC_MP3METADATA_H_
#define INC_MP3METADATA_H_

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#define TAG_LENGTH 3
#define TITLE_TAG_LENGTH 30
#define ARTIST_TAG_LENGTH TITLE_TAG_LENGTH
#define ALBUM_TAG_LENGTH TITLE_TAG_LENGTH
#define COMMENT_TAG_LENGTH TITLE_TAG_LENGTH

#define TOTAL_TAG_LENGTH 128

#define TAG_PLUS_LENGTH 4
#define TITLE_TAG_PLUS_LENGTH 60
#define ARTIST_TAG_PLUS_LENGTH TITLE_TAG_LENGTH
#define ALBUM_TAG_PLUS_LENGTH TITLE_TAG_LENGTH
#define GENRE_TAG_PLUS_LENGTH 30

#define TOTAL_TAG_PLUS_LENGTH 227

class MP3Metadata
{
   private:
      std::string tag;   // 3 or 4 chars
      bool        is_tag_plus;
      std::string title;   // 30 chars
      std::string artist;  // 30 chars
      std::string album;   // 30 chars
      unsigned int year;  // 4  Digits
      std::string comment; // 30 chars
      char zero_byte;      // If a track number is stored, this byte contains a binary 0
      unsigned int track;  // The number of the track on the album, or 0. Invalid if previous byte is not a binary 0.
      unsigned int genre;  // Index in a list of genres, or 255.

      std::string path; //

   public:
      MP3Metadata();
      virtual ~MP3Metadata();

      std::string GetTitle();
      void SetTitle(std::string Title);
      std::string GetArtist();
      void SetArtist(std::string Artist);
      std::string GetAlbum();
      void SetAlbum(std::string Album);
      unsigned int GetYear();
      void SetYear(unsigned int Year);
      std::string GetComment();
      void SetComment(std::string Comment);
      char GetZeroByte();
      void SetZeroByte(char ZeroByte);
      unsigned int GetTrack();
      void SetTrack(unsigned int Track);
      unsigned int GetGenre();
      void SetGenre(unsigned int Genre);
      std::string GetPath();
      void SetPath(std::string Path);

      int ExtractMetadata(const std::string& Path);
      int ExtractTag(std::fstream& File, long int& bytes_read);
      int ExtractTitle(std::fstream& File, long int& bytes_read);
      int ExtractArtist(std::fstream& File, long int& bytes_read);
      int ExtractAlbum(std::fstream& File, long int& bytes_read);
      int ExtractYear(std::fstream& File, long int& bytes_read);

      int OpenFile(std::fstream& File);

};

#endif /* INC_MP3METADATA_H_ */
