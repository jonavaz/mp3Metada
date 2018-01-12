#include <iostream>

#include <MP3Metadata.h>

int Process_Arguments(int argc, char **argv, std::string& path);

int main(int argc, char **argv)
{
   MP3Metadata metadata;
   std::string path;
   int error = 0;

   std::cout << "Main function" << std::endl;

   error = Process_Arguments(argc, argv, path);
   if(0 == error)
   {
      metadata.ExtractMetadata(path);
   }

   return error;
}

int Process_Arguments(int argc, char **argv, std::string& path)
{
   int error = 0;

   if(2 != argc)
   {
      std::cout << "Missing arguments" << std::endl;
      error = -1;
   }
   else
   {
      path.assign(argv[1]);
      std::cout << "path to open: " << path << std::endl;
   }

   return error;
}
