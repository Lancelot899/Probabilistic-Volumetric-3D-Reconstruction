// This is core/vil/io/vil_io_rgb.txx
#ifndef vil_io_rgb_txx_
#define vil_io_rgb_txx_
//:
// \file

#include "vil_io_rgb.h"

//========================================================================
//: Binary save vil_rgb to stream.
template<class T>
void vsl_b_write(vsl_b_ostream &os, const vil_rgb<T>& v)
{
  const short io_version_no = 1;
  vsl_b_write(os, io_version_no);
  vsl_b_write(os, v.R());
  vsl_b_write(os, v.G());
  vsl_b_write(os, v.B());
}

//========================================================================
//: Binary load vil_rgb from stream.
template<class T>
void vsl_b_read(vsl_b_istream &is, vil_rgb<T>& v)
{
  if (!is) return;

  short w;
  vsl_b_read(is, w);
  switch(w)
  {
  case 1:
    vsl_b_read(is, v.r);
    vsl_b_read(is, v.g);
    vsl_b_read(is, v.b);
    break;

  default:
    vcl_cerr << "I/O ERROR: vsl_b_read(vsl_b_istream&, vil_rgb<T>&)\n"
             << "           Unknown version number "<< w << '\n';
    is.is().clear(vcl_ios::badbit); // Set an unrecoverable IO error on stream
    return;
  }
}


//========================================================================
//: Output a human readable summary of a vil_rgb object to the stream
template<class T>
void vsl_print_summary(vcl_ostream &os, const vil_rgb<T>& v)
{
    os<<"Rgb : ( "<<v.R()<<" , "<<v.G()<<" , "<<v.B()<<" )";
}

#define VIL_IO_RGB_INSTANTIATE(T) \
template void vsl_print_summary(vcl_ostream &, const vil_rgb<T >&); \
template void vsl_b_read(vsl_b_istream &, vil_rgb<T >&); \
template void vsl_b_write(vsl_b_ostream &, const vil_rgb<T >&)

#endif // vil_io_rgb_txx_
