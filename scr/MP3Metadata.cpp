/*
 * MP3Metadata.cpp
 *
 *  Created on: Jan 11, 2018
 *      Author: rzv0cn
 */

#include <MP3Metadata.h>

MP3Metadata::MP3Metadata()
{
   year = 0;
   zero_byte = '0';
   track = 0;
   genre = 255;
   is_tag_plus = false;
}

MP3Metadata::~MP3Metadata()
{

}

std::string MP3Metadata::GetTitle()
{
   return title;
}

void MP3Metadata::SetTitle(std::string Title)
{
   title = Title;
}

std::string MP3Metadata::GetArtist()
{
   return artist;
}

void MP3Metadata::SetArtist(std::string Artist)
{
   artist = Artist;
}

std::string MP3Metadata::GetAlbum()
{
   return album;
}

void MP3Metadata::SetAlbum(std::string Album)
{
   album = Album;
}

unsigned int MP3Metadata::GetYear()
{
   return year;
}

void MP3Metadata::SetYear(unsigned int Year)
{
   year = Year;
}

std::string MP3Metadata::GetComment()
{
   return comment;
}

void MP3Metadata::SetComment(std::string Comment)
{
   comment = Comment;
}

char MP3Metadata::GetZeroByte()
{
   return zero_byte;
}

void MP3Metadata::SetZeroByte(char ZeroByte)
{
   zero_byte = ZeroByte;
}

unsigned int MP3Metadata::GetTrack()
{
   return track;
}

void MP3Metadata::SetTrack(unsigned int Track)
{
   track = Track;
}

unsigned int MP3Metadata::GetGenre()
{
   return genre;
}

void MP3Metadata::SetGenre(unsigned int Genre)
{
   genre = Genre;
}

std::string MP3Metadata::GetPath()
{
   return path;
}

void MP3Metadata::SetPath(std::string Path)
{
   path = Path;
}

int MP3Metadata::ExtractMetadata(const std::string& Path)
{
   int error = 0;

   if(!Path.empty())
   {
      path.assign(Path);
      std::fstream file;

      error = OpenFile(file);
      if(0 == error)
      {
         long int bytes_read = 0L;
         error = ExtractTag(file, bytes_read);
         std::cout << "Tag: " << tag << ", bytes_read: " << bytes_read << std::endl;
         error = ExtractTitle(file, bytes_read);
         std::cout << "Title: " << title << ", bytes_read: " << bytes_read << std::endl;
         error = ExtractArtist(file, bytes_read);
         std::cout << "Artist: " << artist << ", bytes_read: " << bytes_read << std::endl;
         error = ExtractAlbum(file, bytes_read);
         std::cout << "Album: " << album << ", bytes_read: " << bytes_read << std::endl;

         file.close();
         std::cout << "Is open: " << file.is_open() << std::endl;
      }
      else
      {
         std::cout << "OpenFile failed" << std::endl;
      }
   }
   else
   {
      std::cout << "Path is empty" << std::endl;
   }

   return error;
}

int MP3Metadata::ExtractTag(std::fstream& File, long int& bytes_read)
{
   int error = 0;

   if(File.is_open())
   {
      char tag_aux[TAG_PLUS_LENGTH];
      File.seekg(-1*TOTAL_TAG_LENGTH, File.end);
      File.read(tag_aux,TAG_PLUS_LENGTH);

      if('+' == tag_aux[TAG_PLUS_LENGTH])
      {
         std::cout << "TAG+" << std::endl;
         bytes_read = TAG_PLUS_LENGTH;
         is_tag_plus = true;
      }
      else
      {
         std::cout << "TAG" << std::endl;
         bytes_read = TAG_LENGTH;
         is_tag_plus = false;

         tag_aux[TAG_LENGTH] = '\0';
         File.seekg(-1*TOTAL_TAG_LENGTH + TAG_LENGTH, File.end);
      }

      tag.assign(tag_aux);
   }
   else
   {
      std::cout << "File is not opened" << std::endl;
      error = -1;
   }
}

int MP3Metadata::ExtractTitle(std::fstream& File, long int& bytes_read)
{
   int error = 0;
   char *title_aux = NULL;

   if(File.is_open())
   {
      if(is_tag_plus)
      {
         title_aux = (char *)malloc(TITLE_TAG_PLUS_LENGTH*sizeof(char));
         if(NULL != title_aux)
         {
            File.read(title_aux, TITLE_TAG_PLUS_LENGTH);
            bytes_read += TITLE_TAG_PLUS_LENGTH;
         }
         else
         {
            std::cout << "title_aux NULL" << std::endl;
            error = -1;
         }
      }
      else
      {
         title_aux = (char *)malloc(TITLE_TAG_LENGTH*sizeof(char));
         if(NULL != title_aux)
         {
            File.read(title_aux, TITLE_TAG_LENGTH);
            bytes_read += TITLE_TAG_LENGTH;
         }
         else
         {
            std::cout << "title_aux NULL" << std::endl;
            error = -1;
         }
      }

      if(0 == error)
      {
         title.assign(title_aux);
         std::cout << "title: " << title << std::endl;

         free(title_aux);
         title_aux = NULL;
      }
   }
   else
   {
      std::cout << "File is not opened" << std::endl;
      error = -1;
   }

   return error;
}

int MP3Metadata::ExtractArtist(std::fstream& File, long int& bytes_read)
{
   int error = 0;
   char *artist_aux = NULL;

   if(File.is_open())
   {
      if(is_tag_plus)
      {
         artist_aux = (char *)malloc(ARTIST_TAG_PLUS_LENGTH*sizeof(char));
         if(NULL != artist_aux)
         {
            File.read(artist_aux, ARTIST_TAG_PLUS_LENGTH);
            bytes_read += ARTIST_TAG_PLUS_LENGTH;
         }
         else
         {
            std::cout << "artist_aux NULL" << std::endl;
            error = -1;
         }
      }
      else
      {
         artist_aux = (char *)malloc(ARTIST_TAG_LENGTH*sizeof(char));
         if(NULL != artist_aux)
         {
            File.read(artist_aux, ARTIST_TAG_LENGTH);
            bytes_read += ARTIST_TAG_LENGTH;
         }
         else
         {
            std::cout << "artist_aux NULL" << std::endl;
            error = -1;
         }
      }

      if(0 == error)
      {
         artist.assign(artist_aux);
         std::cout << "artist: " << artist << std::endl;

         free(artist_aux);
         artist_aux = NULL;
      }
   }
   else
   {
      std::cout << "File is not opened" << std::endl;
      error = -1;
   }

   return error;
}

int MP3Metadata::ExtractAlbum(std::fstream& File, long int& bytes_read)
{
   int error = 0;
   char *album_aux = NULL;

   if(File.is_open())
   {
      if(is_tag_plus)
      {
         album_aux = (char *)malloc(ALBUM_TAG_PLUS_LENGTH*sizeof(char));
         if(NULL != album_aux)
         {
            File.read(album_aux, ALBUM_TAG_PLUS_LENGTH);
            bytes_read += ALBUM_TAG_PLUS_LENGTH;
         }
         else
         {
            std::cout << "album_aux NULL" << std::endl;
            error = -1;
         }
      }
      else
      {
         album_aux = (char *)malloc(ALBUM_TAG_LENGTH*sizeof(char));
         if(NULL != album_aux)
         {
            File.read(album_aux, ALBUM_TAG_LENGTH);
            bytes_read += ALBUM_TAG_LENGTH;
         }
         else
         {
            std::cout << "album_aux NULL" << std::endl;
            error = -1;
         }
      }

      if(0 == error)
      {
         artist.assign(album_aux);
         std::cout << "artist: " << artist << std::endl;

         free(album_aux);
         album_aux = NULL;
      }
   }
   else
   {
      std::cout << "File is not opened" << std::endl;
      error = -1;
   }

   return error;
}

int MP3Metadata::ExtractYear(std::fstream& File, long int& bytes_read)
{
   int error = 0;
   char *album_aux = NULL;

   if(File.is_open())
   {
      if(is_tag_plus)
      {
         album_aux = (char *)malloc(ALBUM_TAG_PLUS_LENGTH*sizeof(char));
         if(NULL != album_aux)
         {
            File.read(album_aux, ALBUM_TAG_PLUS_LENGTH);
            bytes_read += ALBUM_TAG_PLUS_LENGTH;
         }
         else
         {
            std::cout << "album_aux NULL" << std::endl;
            error = -1;
         }
      }
      else
      {
         album_aux = (char *)malloc(ALBUM_TAG_LENGTH*sizeof(char));
         if(NULL != album_aux)
         {
            File.read(album_aux, ALBUM_TAG_LENGTH);
            bytes_read += ALBUM_TAG_LENGTH;
         }
         else
         {
            std::cout << "album_aux NULL" << std::endl;
            error = -1;
         }
      }

      if(0 == error)
      {
         artist.assign(album_aux);
         std::cout << "artist: " << artist << std::endl;

         free(album_aux);
         album_aux = NULL;
      }
   }
   else
   {
      std::cout << "File is not opened" << std::endl;
      error = -1;
   }

   return error;
}

int MP3Metadata::OpenFile(std::fstream& File)
{
   int error = 0;

   File.open(path.c_str(), std::fstream::in | std::fstream::binary);
   if(File.is_open())
   {
      std::cout << "File \"" << path << "\" could be opened" << std::endl;
      error = 0;
   }
   else
   {
      std::cout << "File \"" << path << "\" couldn't be opened" << std::endl;
      error = -1;
   }


   return error;
}
