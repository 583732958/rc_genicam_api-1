/*
 * Roboception GmbH
 * Munich, Germany
 * www.roboception.com
 *
 * Copyright (c) 2017 Roboception GmbH
 * All rights reserved
 *
 * Author: Heiko Hirschmueller
 */

#ifndef RCGCAPI_IMAGE
#define RCGCAPI_IMAGE

#include "buffer.h"

#include <memory>

namespace rcg
{

/**
  The image class encapsulates image information. It can be created from a
  buffer and provides a part of its information. It can be used to temporarily
  store the image so that the buffer can be freed.

  NOTE: A GenTLException is thrown in case of a severe error.
*/

class Image
{
  public:

    /**
      Copies the image information of the buffer.
    */

    Image(const Buffer *buffer);

    /**
      Pointer to pixel information of the image.

      @return Pointer to pixels.
    */

    const uint8_t *getPixels() const { return pixel.get(); }

    uint64_t getTimestampNS() const { return timestamp; }

    size_t getWidth() const { return width; }
    size_t getHeight() const { return height; }
    size_t getXOffset() const { return xoffset; }
    size_t getYOffset() const { return yoffset; }
    size_t getXPadding() const { return xpadding; }
    size_t getYPadding() const { return ypadding; }
    uint64_t getFrameID() const { return frameid; }
    uint64_t getPixelFormat() const { return pixelformat; }
    bool isBigEndian() const { return bigendian; }

  private:

    Image(class Image &); // forbidden
    Image &operator=(const Image &); // forbidden

    std::unique_ptr<uint8_t []> pixel;

    uint64_t timestamp;
    size_t width;
    size_t height;
    size_t xoffset;
    size_t yoffset;
    size_t xpadding;
    size_t ypadding;
    uint64_t frameid;
    uint64_t pixelformat;
    bool bigendian;
};

/**
  Conversion of one pixel from YCbCr411 format (6 bytes for four pixels) to
  RGB.

  @param rgb Pointer to an array of size 3 for storing the result.
  @param row Image row.
  @param i   Index of pixel in row that should be converted.
*/

void convYCbCr411toRGB(uint8_t rgb[3], const uint8_t *row, int i);

/**
  Conversion of a group of four pixels from YCbCr411 format (6 bytes for four
  pixels) to RGB. Conversion of four pixels is a bit more efficient than
  conversions of individual pixels.

  @param rgb Pointer to an array of size 3 for storing the result.
  @param row Image row.
  @param i   Index of first pixel in row that should be converted. The index
             must be a multiple of 4!
*/

void convYCbCr411toQuadRGB(uint8_t rgb[12], const uint8_t *row, int i);

}

#endif