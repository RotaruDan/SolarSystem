//---------------------------------------------------------------------------
#include "pixmap24RGB.h"
//---------------------------------------------------------------------------

// cabeceras del archivo bmp
// tipo y valores para nuestro caso: bmp en modo bgr de 24 bits con los pixeles por filas bottom to top y columnas left to right.
struct bitmap_file_header  // en realidad no es un struct, hay que trabajar con los campos por separado, pero asi quedan agrupados
{ 
  /*WORD*/  unsigned short signature;  // 'BM'
  /*DWORD*/ unsigned int   size_file;  // unreliable ->  = (offset_map + size_map) bytes 
  /*WORD*/  unsigned short reserved1;  // 0
  /*WORD*/  unsigned short reserved2;  // 0
  /*DWORD*/ unsigned int   offset_map; // 54 (14 fileheader + 40 information_header) bytes (sizeof(bitmap_file_header)=16 por el padding, pero hay que trabajar campo a campo (14 = suma de campos))
};

struct bitmap_information_header
{
  /*DWORD*/ unsigned int size_info_header;  // 40 bytes = sizeof(bitmap_information_header)
  /*LONG*/  int width;  // columns (left to right order)
  /*LONG*/  int height; // rows (bottom to top order)
  /*WORD*/  unsigned short planes;  // 1 color planes 
  /*WORD*/  unsigned short bits_per_pixel;  // 24 bits -> 3(BGR) bytes
  /*DWORD*/ unsigned int compression;   // 0 = BI_RGB, no pixel array compression used
  /*DWORD*/ unsigned int size_map;   // (width * 3 + pading) * height  bytes
  /*LONG*/  int x_prpm;  // (Print resolution pixels/meter horizontal) unreliable
  /*LONG*/  int y_prpm;  // (Print resolution pixels/meter vertical) unreliable 
  /*DWORD*/ unsigned int clr_used;  // 0 (Number of colors in the palette)
  /*DWORD*/ unsigned int clr_important;   // 0 (means all colors are important)
};

void pixmap24RGB::load_headers(std::ifstream & stream,  unsigned int & width, unsigned int & height) const// throw(std::ios_base::failure);
{
      width = 0; height = 0;
      bitmap_file_header bfh;
      bitmap_information_header bih;
      //stream.read(reinterpret_cast<char*>(&bfh), 14);   // sizeof(bitmap_file_header) = 16 por el padding -> 14 = suma de los campos  
      stream.read(reinterpret_cast<char*>(&bfh.signature), 2); 
      stream.read(reinterpret_cast<char*>(&bfh.size_file), 4); 
      stream.read(reinterpret_cast<char*>(&bfh.reserved1), 2); 
      stream.read(reinterpret_cast<char*>(&bfh.reserved2), 2); 
      stream.read(reinterpret_cast<char*>(&bfh.offset_map),4); 
      
      stream.read(reinterpret_cast<char*>(&bih), 40);   // sizeof(bitmap_information_header) = 40 (padding 0)
      width = bih.width; 
      height = bih.height;

      if (bfh.signature != 0x4D42) // 'BM' 4D(M) 42(B)  (-> 19778 decimal)
      {
         throw std::ios_base::failure("pixmapRGBA::load_bmpBGR() ERROR: Invalid signature value");
      }
      if (bih.bits_per_pixel != 24)   // 3(BGR) bytes
      {
         throw std::ios_base::failure("pixmapRGBA::load_bmpBGR() ERROR: Invalid depth color (bits per pixel)");
      }
      if (bih.size_info_header != 40)   // size_of(bitmap_information_header)
      {
         throw std::ios_base::failure("pixmapRGBA::load_bmpBGR() ERROR: Invalid size information header");
      }
      if(bih.clr_used != 0) // paleta de colores
      {
        throw std::ios_base::failure("pixmapRGBA::load_bmpBGR() ERROR: Invalid number of colors in the palette");
      }
}

void pixmap24RGB::save_headers(std::ofstream & stream) const // noexcept;
{
      bitmap_file_header bfh;
      bitmap_information_header bih;

      bih.size_info_header = 40;  // sizeof(bitmap_information_header) 
      bih.width            = width_;
      bih.height           = height_;
      bih.planes           =  1;  // color planes
      bih.bits_per_pixel   = 24;  // 3(BGR) bytes
      bih.compression      =  0;  //BI_RGB
      bih.size_map         = ((bih.width * 3) + ((4 - ((3 * width_) % 4)) % 4)) * bih.height; // padding !!
      bih.x_prpm           =  0;  //  Print resolution 2835 = 72 dpi × 39.3701 inches per meter yields 2834.6472
      bih.y_prpm           =  0;  //  Print resolution 2835 = 72 dpi × 39.3701 inches per meter yields 2834.6472
      bih.clr_used         =  0;
      bih.clr_important    =  0;
                                       
      bfh.signature   = 0x4D42;  // 'BM' (19778 en decimal)   
      bfh.size_file   = 54 + bih.size_map; // offset_map + size_map      
      bfh.reserved1   = 0;
      bfh.reserved2   = 0;
      bfh.offset_map  = 54; // sizeof(bitmap_file_header) + sizeof(bitmap_information_header) = 40 + 16 (14 + padding) ->  suma de campos      

      //stream.write(reinterpret_cast<const char*>(&bfh), 14);  // sizeof(bitmap_file_header) = 16 por el padding -> 14 = suma de los campos  
      stream.write(reinterpret_cast<const char*>(&bfh.signature), 2); 
      stream.write(reinterpret_cast<const char*>(&bfh.size_file), 4); 
      stream.write(reinterpret_cast<const char*>(&bfh.reserved1), 2); 
      stream.write(reinterpret_cast<const char*>(&bfh.reserved2), 2); 
      stream.write(reinterpret_cast<const char*>(&bfh.offset_map),4); 

      stream.write(reinterpret_cast<const char*>(&bih), 40);  // sizeof(bitmap_information_header) = 40 (padding 0)
}

//-------------------------------------------------------------------------------------------

void pixmap24RGB::libera()
{
   width_ = 0;
   height_ = 0;
   delete[] data_;
   data_ = nullptr;
}

void pixmap24RGB::create_pixmap(GLsizei width, GLsizei height) // throw(std::bad_alloc)
{
  if(width != width_ || height != height_) 
    {  
      libera();
      try
      {  
         data_ = new rgb_color [width * height];  
         width_  = width;
         height_ = height;
      }
      catch(std::bad_alloc ) // & e
      { 
        throw std::exception("pixmap24RGB::create_pixmap() ERROR: Could not allocate memory (bad_alloc)"); // bad_alloc("")
      }
      if (data_ == nullptr)  
      {  
        width_  = 0;
        height_ = 0;
        throw std::exception("pixmap24RGB::create_pixmap() ERROR: Could not allocate memory (bad_alloc)"); //bad_alloc()
      }
  }   
}

void pixmap24RGB::load_bmpBGR(const std::string & file_name) // throw(std::ios_base::failure, std::bad_alloc)
{
      std::ifstream stream(file_name.c_str(), std::ios::binary);
      stream.exceptions( std::ifstream::failbit | std::ifstream::badbit );
      if (!stream.is_open())
      {   
         throw std::ios_base::failure("pixmap24RGB::load_bmpBGR() ERROR: Could not open file");
      }

      unsigned int width, height;
      load_headers(stream, width, height);

      create_pixmap(width, height); 
      unsigned int padding = (4 - ((3 * width) % 4)) % 4;    // padding de fila a multiplos de 4 de 3(BGR) 
      unsigned int rowSize = width * 3 + padding; // de archivo
             
      char* rowAux = new char [rowSize];  // para leer del archivo

      for (unsigned int i = 0; i < height_; ++i)
      {
         stream.read(rowAux,  rowSize); 
         row_bgr_rgb(rowAux, i);  // pasar a row i de pixmap
      }

      stream.close();
      delete [] rowAux;
} 
   
void pixmap24RGB::row_bgr_rgb(char* rowAux, unsigned int r) // noexcept;
{
   unsigned int j =  0, f = r* width_ + width_;  

   for (unsigned int i = r* width_; i <  f; i++)
      {
         data_[i].blue = rowAux[j++];
         data_[i].green = rowAux[j++];
         data_[i].red = rowAux[j++];
      }
}

void pixmap24RGB::row_rgb_bgr(char* rowAux, unsigned int r) const// noexcept;
{
   unsigned int j =  0, f = r* width_ + width_;  

   for (unsigned int i = r* width_; i <  f; i++)
      {
         rowAux[j++] = data_[i].blue;
         rowAux[j++] = data_[i].green;
         rowAux[j++] = data_[i].red;
      }
}

void pixmap24RGB::save_bmpBGR(const std::string& file_name) const// throw(std::ios_base::failure)
{
      std::ofstream stream(file_name.c_str(),std::ios::binary);
      stream.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
      if (!stream.is_open())
      {
         throw std::ios_base::failure("pixmap24RGB::save_bmpBGR() ERROR: Could not open file"); 
      }

      save_headers(stream);

      unsigned int padding = (4 - ((3 * width_) % 4)) % 4;  // padding de fila a multiplos de 4 de 3(BGR) 
      unsigned int rowSize = width_ * Bytes_Per_Pixel + padding;  // de archivo
     
      char* rowAux = new char [rowSize];  // para escribir en archivo

      for (unsigned int i = 0; i < height_; ++i)
      {  
        row_rgb_bgr(rowAux,i);  // pasar a row de archivo
        stream.write(rowAux, rowSize);
      }

      delete [] rowAux;
      stream.close();
}
   
pixmap24RGB::pixmap24RGB(const unsigned int width, const unsigned int height) // throw(std::bad_alloc)
: data_(nullptr), width_(0), height_(0) 
{
     create_pixmap(width, height);
}

pixmap24RGB::pixmap24RGB(const pixmap24RGB & pixmap) // throw(std::exception)
: data_(nullptr), width_(0), height_(0) 
{
      *this = pixmap;
}

pixmap24RGB & pixmap24RGB::operator=(const pixmap24RGB & pixmap) // throw(std::exception)
{
      if (this != &pixmap)
      {
         create_pixmap(pixmap.width_, pixmap.height_);
         unsigned int length = width_ * height_ ;
         for (unsigned int i = 0; i <  length; i++)   
         {
           data_[i] = pixmap.data_[i];
         }
      }

      return *this;
}

GLubyte* pixmap24RGB::create_RGBA(GLubyte alpha) const // throw(std::bad_alloc)
{
    if(data_ == nullptr) return nullptr;
    else
    { 
      GLubyte* pixmap;
      pixmap = new GLubyte [width_ * height_ * 4] ;
      if(pixmap == nullptr) throw std::bad_alloc();
      int p=0;
      for(unsigned int i=0; i< width_ * height_; i++ )
      {
        pixmap[p++]= data_[i].red;
        pixmap[p++]= data_[i].green;
        pixmap[p++]= data_[i].blue;
        pixmap[p++]= alpha;
      }
      return pixmap;
    }
}

