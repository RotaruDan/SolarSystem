//---------------------------------------------------------------------------
// Ana Gil Luezas
//---------------------------------------------------------------------------
#ifndef Pixmap24RGB_H
#define Pixmap24RGB_H

#include <Windows.h>
#include <gl/GL.h>

#include <fstream>
#include <string>
#include <exception>

class pixmap24RGB {
public:
   struct rgb_color
   {
     GLubyte red;
     GLubyte green;
     GLubyte blue;
   };

private:
   rgb_color * data_;
   GLsizei   width_;
   GLsizei   height_;
   static const GLsizei  Bytes_Per_Pixel = 3;

public:

   pixmap24RGB()  // noexcept  
   : data_(nullptr), width_(0), height_(0)
   {}

   pixmap24RGB(const std::string& filename) // throw(std::ios_base::failure, std::bad_alloc)
   : data_(nullptr), width_(0), height_(0)
   {
      load_bmpBGR(filename);
   }

   ~pixmap24RGB() 
   {
      libera();
   }
      
   GLsizei width() const // noexcept
   {
      return width_;
   }

   GLsizei height() const // noexcept
   {
      return height_;
   }

   GLsizei bytes_per_pixel() const // noexcept
   {
      return Bytes_Per_Pixel;
   }

   const rgb_color* map() const // noexcept
   { 
      return data_;
   }

   bool is_null() const // noexcept
   {
      return (data_  == nullptr); 
   }

   void load_bmpBGR(const std::string & file_name); // throw(std::ios_base::failure, std::exception);

   void save_bmpBGR(const std::string & file_name) const;  // throw(std::ios_base::failure);

   void get_pixel(const GLsizei x, const GLsizei y, rgb_color & rgb) const 
   {  
      rgb  = data_[y * width_ + x];
   }

   void set_pixel(const GLsizei x, const GLsizei y, const rgb_color & rgb) 
   {
      data_[y * width_ + x] = rgb;
   }

   void libera();  // noexcept;
   void create_pixmap(GLsizei   width,  GLsizei   height); // throw(std::bad_alloc);
   void row_bgr_rgb(char* rowAux, unsigned int r); // noexcept;
   void row_rgb_bgr(char* rowAux, unsigned int r) const; // noexcept;

   GLubyte* create_RGBA(GLubyte alpha = 255) const;  // throw(std::bad_alloc)   

protected:

   pixmap24RGB(const unsigned int width, const unsigned int height); // throw(std::bad_alloc)
   pixmap24RGB(const pixmap24RGB & pixmap); // throw(std::exception)
   pixmap24RGB & operator=(const pixmap24RGB & pixmap); // throw(std::exception)

   void load_headers(std::ifstream & stream,  unsigned int & width, unsigned int & height) const; // throw(std::ios_base::failure);
   void save_headers(std::ofstream & stream) const; // noexcept;
};

   
#endif
