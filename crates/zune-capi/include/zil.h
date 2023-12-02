#ifndef ZIL_IMAGE
#define ZIL_IMAGE

/* Generated with cbindgen:0.26.0 */

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


typedef enum ZImageColorspace {
  /**
   * Unknown image colorspace
   */
  UnknownColorspace = 0,
  /**
   * Red, Green , Blue
   */
  RGB,
  /**
   * Red, Green, Blue, Alpha
   */
  RGBA,
  /**
   * YUV colorspace
   */
  YCbCr,
  /**
   * Grayscale colorspace
   */
  Luma,
  /**
   * Grayscale with alpha colorspace
   */
  LumaA,
  YCCK,
  /**
   * Cyan , Magenta, Yellow, Black
   */
  CMYK,
  /**
   * Blue, Green, Red
   */
  BGR,
  /**
   * Blue, Green, Red, Alpha
   */
  BGRA,
  /**
   * Alpha, Blue Green, Red
   */
  ARGB,
} ZImageColorspace;

/**
 * Image depth information
 *
 * This enum gives information about image depths
 *
 * The image depths also give you the information for
 * which we represent image pixels
 *
 * U8  -> 8 bit depth, image is represented as uint8_t (unsigned char)
 * U16 -> 16 bit depth, image is represented as uint16_t ( unsigned short)
 * F32  -> using float32, image is represented as float
 */
typedef enum ZImageDepth {
  /**
   * Image depth is unknown
   */
  UnknownDepth = 0,
  /**
   *8-bit images
   */
  U8 = 1,
  /**
   * 16 bit images
   */
  U16 = 2,
  /**
   * Float 32 images
   */
  F32 = 4,
} ZImageDepth;

/**
 * Various image formats that are supported by the library
 * in one way or another
 *
 * Some of them have partial support, i.e there is only a decoder bundled in
 * while others have full support
 */
typedef enum ZImageFormat {
  /**
   * Any unknown format
   */
  UnknownFormat = 0,
  /**
   * Joint Photographic Experts Group
   */
  JPEG,
  /**
   * Portable Network Graphics
   */
  PNG,
  /**
   * Portable Pixel Map image
   */
  PPM,
  /**
   * Photoshop PSD component
   */
  PSD,
  /**
   * Farbfeld format
   */
  Farbfeld,
  /**
   * Quite Okay Image
   */
  QOI,
  /**
   * JPEG XL, new format
   */
  JPEG_XL,
  /**
   * Radiance HDR decoder
   */
  HDR,
  /**
   * Windows Bitmap Files
   */
  BMP,
} ZImageFormat;

/**
 * Various representations of things that may go wrong
 */
typedef enum ZStatusType {
  /**
   * Everything is okay, operation succeeded
   */
  Ok = 0,
  /**
   * The buffer passed to a function wasn't enough to
   * store the results
   */
  NotEnoughSpaceInDest,
  /**
   * An error that doesn't fit into a specific genre
   */
  Generic,
  /**
   * An error originating from decoding
   */
  DecodeErrors,
  /**
   * An error originating from Input output errors
   */
  IoErrors,
  /**
   * Malloc failed
   */
  MallocFailed,
  /**
   * Status is null, indicates the passed status value is null
   * useful when we have been asked for status code but
   * passed a null status
   */
  NullStatus,
  /**
   * Image is null
   *
   * An operation expecting a non_null image got a null image
   */
  ImageIsNull,
  /**
   * Image operation failed
   */
  ImageOperationError,
} ZStatusType;

/**
 * Represents a single image
 */
typedef struct Image Image;

/**
 * A status indicator that tells you more about things that went wrong
 *
 *
 * To create an instance use `zil_status_new`
 *
 * To get an enum which contains more details about the execution use `zil_status_code`
 * and to get the message raised by an exception use `zil_status_message`
 *
 * For quickly checking if an operation succeeded, you can use `zil_status_ok` that
 * returns a boolean indicating whether something worked, true if operation succeeded, false otherwise
 *
 * To free the structure use
 *
 */
typedef struct ZStatus {
  enum ZStatusType status;
  /**
   * A short message indicating what went wrong
   */
  uint32_t *message;
} ZStatus;

typedef struct Image ZImage;

/**
 * Image metadata details
 */
typedef struct ZImageMetadata {
  unsigned int width;
  unsigned int height;
  enum ZImageDepth depth;
  enum ZImageColorspace colorspace;
  enum ZImageFormat format;
} ZImageMetadata;

#if defined(DEFINE_ZIL_WINDOWS)
void __chkstk(void);
#endif

#if defined(DEFINE_ZIL_WINDOWS)
void _fltused(void);
#endif

/**
 * Free a memory region that was allocated by zil_malloc or internally by the library
 *
 * E.g. free a pointer returned by `zil_imread`
 *
 * \param ptr: A pointer allocated by `zil_malloc`
 *
 */
void zil_free(void *ptr);

/**
 * \brief Guess the format of an image
 *
 * This function inspects the first few bytes of an image file
 * to determine the actual image codec the file is in
 *
 * If the format cannot be deduced or it's unknown returns `ZImageFormat::UnknownDepth`
 *
 * @param bytes: A memory address containing image data, must point to a valid memory address
 * @param size: Size of the bytes parameter, must not exceed `bytes` length
 *
 * @returns ZImageFormat the image format of the bytes, or ZImageFormat::UnknownDepth if the image is unknown
 *
 */
enum ZImageFormat zil_guess_format(const unsigned char *bytes,
                                   long size);

/**
 *\brief Decode an image already in memory
 *
 * This decodes an image loaded to memory, and returns a pointer to the first pixel
 *
 * The size of the array is strictly `image_width * image_height * image_depth * channels`
 *
 * @param input: Input array of image bytes
 * @param input_size: Input size for the image bytes
 * @param width: Image width, will be filled after decoding with the decoded image width, can be null
 * @param height: Image height, will be filled after decoding with the decoded image height, can be null
 * @param depth: Image depth, will be filled after decoding with the decoded image depth, can be null
 * @param channels: Number of channels, will be filled after decoding with the decoded image channels, can be null
 * @param status: Image status,used to inform the caller if operations were successful
 *
 */
const char *zil_imdecode(const uint8_t *input,
                         size_t input_size,
                         size_t *width,
                         size_t *height,
                         enum ZImageDepth *depth,
                         size_t *channels,
                         struct ZStatus *status);

/**
 * Decode from a byte array in memory and write pixels to `output`
 *
 * Pixels written are strictly `image_width * image_height * image_depth * channels`
 *
 * @param input: Input array of image bytes
 * @param input_size: Input size for the image bytes
 * @param output: Output array where to write decoded pixels
 * @param output_size: Size of `output`
 * @param width: Image width, will be filled after decoding with the decoded image width, can be null
 * @param height: Image height, will be filled after decoding with the decoded image height, can be null
 * @param depth: Image depth, will be filled after decoding with the decoded image depth, can be null
 * @param channels: Number of channels, will be filled after decoding with the decoded image channels, can be null
 * @param status: Image status,used to inform the caller if operations were successful
 *
 */
void zil_imdecode_into(const uint8_t *input,
                       size_t input_size,
                       uint8_t *output,
                       size_t output_size,
                       size_t *width,
                       size_t *height,
                       enum ZImageDepth *depth,
                       size_t *channels,
                       struct ZStatus *status);

/**
 *\brief Creates a new depth that can be passed to functions that require
 * depth
 *
 * \returns ImageDepth with a value of ImageDepth::Unknown
 */
enum ZImageDepth zil_imdepth_new(void);

/**
 * Adjust the contrast of an image in place
 *
 * \param image: Non-null image
 * \param contrast: Amount to adjust contrast by
 * \param status: Reports whether image operation was successful, should not be null
 *
 * if any of `image` or `status` is null, nothing happens
 *
 */
void zil_imgproc_adjust_contrast(ZImage *image, float contrast, struct ZStatus *status);

/**
 * Auto orient image based on exif tag
 *
 * \param image: Non null image struct
 * \param status: Non null status reference
 *
 * This is a no op in case image doesn't have an exif orientation flag
 */
void zil_imgproc_auto_orient(ZImage *image, struct ZStatus *status);

/**
 * Apply a bilateral filter to an image
 *
 *\param d: Diameter of each pixel neighborhood that is used during filtering. If it is non-positive, it is computed from sigma_space.
 *
 *\param sigma_color: Filter sigma in the color space.
 *  A larger value of the parameter means that farther colors within the pixel neighborhood (see sigmaSpace)
 *  will be mixed together, resulting in larger areas of semi-equal color.
 *
 *\param sigma_space: Filter sigma in the coordinate space.
 *  A larger value of the parameter means that farther pixels will influence each other as
 *   long as their colors are close enough (see sigma_color ).
 *   When d>0, it specifies the neighborhood size regardless of sigma_space. Otherwise, d is proportional to sigma_space.
 */
void zil_imgproc_bilateral_filter(ZImage *image,
                                  int32_t d,
                                  float sigma_color,
                                  float sigma_space,
                                  struct ZStatus *status);

/**
 * \brief Blend two images together based an alpha value
 * which is used to determine the `opacity` of pixels during blending
 *
 *
 * The formula for blending is
 *
 * \code
 * dest =(src_alpha) * src  + (1-src_alpha) * dest
 * \endcode
 *
 * `src_alpha` is expected to be between 0.0 and 1.0
 *
 * \param image1: Image to which another image will be overlaid
 * \param image2: Image which will be overlaid on image 1, must have same dimensions,depth and colorspace
 * \param src_alpha: Source alpha, between 0 and 1, 1-> copy src to dest, 0 leave as is
 * \param status Image operation status, query this to tell you if the operation succeded
 */
void zil_imgproc_blend(ZImage *image1,
                       const ZImage *image2,
                       float src_alpha,
                       struct ZStatus *status);

/**
 * Change image bit depth of the image
 *
 * On successful execution, image depth will be the specified one by the `to` parameter
 *
 * /param image: Non-null image struct
 * /param to: Depth to convert this image into
 * /param status: Image operation status, after execution query this to determine if execution
 * was successful
 */
void zil_imgproc_change_depth(ZImage *image, enum ZImageDepth to, struct ZStatus *status);

/**
 * Change image colorspace to a different one
 *
 * On successful execution, image colorspace will be the one specified by the `to` parameter
 *
 * \param image: Non-null image struct
 * \param to: New colorspace for the image
 * \param status: Result of image operation, query this to see if operation was successful
 */
void zil_imgproc_convert_colorspace(ZImage *image,
                                    enum ZImageColorspace to,
                                    struct ZStatus *status);

/**
 * Crop an image, creating a smaller image from a bigger image
 *
 *
 * Origin (0,0) is from top left
 *
 * \param image: Image to be cropped
 * \param new_width: New width of expected image
 * \param new_height: New height of expected image
 * \param x: How far from x origin the new image should be
 * \param y: How far from the y origin the new image should be
 *
 * \param status: Image operation reporter
 *
 */
void zil_imgproc_crop(ZImage *image,
                      size_t new_width,
                      size_t new_height,
                      size_t x,
                      size_t y,
                      struct ZStatus *status);

/**
 * Adjust image exposure
 *
 * Formula used is
 *
 * \code
 * pix = clamp((pix - black) * exposure)
 * \endcode
 *
 * where `pix` is the current image pixel
 *
 * \param image: Non null image
 *
 * \param exposure: Amount to adjust by
 *
 * \param black_point: Amount to subtract from each pixel before converting,
 *
 * \param status: Image status
 *
 */
void zil_imgproc_exposure(ZImage *image, float exposure, float black_point, struct ZStatus *status);

/**
 * Flip an image by reflecting pixels on its x-axis
 *
 * \code
 * old image     new image
 * ┌─────────┐   ┌──────────┐
 * │a b c d e│   │j i h g f │
 * │f g h i j│   │e d c b a │
 * └─────────┘   └──────────┘
 * \endcode
 *
 * \param image: Image to flip
 * \param status: Image execution reporter
 */
void zil_imgproc_flip(ZImage *image, struct ZStatus *status);

/**
 * Flop an image by reflecting pixels on its y-axis
 *
 * \code
 * old image     new image
 * ┌─────────┐   ┌──────────┐
 * │a b c d e│   │e d b c a │
 * │f g h i j│   │j i h g f │
 * └─────────┘   └──────────┘
 *
 * \endcode
 *
 * \param image: Image to flop
 * \param status: Image execution reporter
 */
void zil_imgproc_flop(ZImage *image, struct ZStatus *status);

/**
 * Gamma adjust an image
 *
 * Formula used is
 *
 * \code
 * max_value = maximum byte value
 * gamma_value =  passed gamma value
 * pixel = pixel.powf(gamma_value)/max_value;
 *
 * \endcode
 *
 * \param image: Image to apply gamma correction to
 * \param gamma: Gamma value
 * \param status: Image operations reporter
 *
 */
void zil_imgproc_gamma(ZImage *image, float gamma, struct ZStatus *status);

/**
 * Invert image pixels
 *
 * Formula
 *
 * \code
 * max_value -> maximum value of an image depth
 *
 * pixel = max_value-pixel
 *
 * \endcode
 *
 */
void zil_imgproc_invert(ZImage *image, struct ZStatus *status);

/**
 * Read image contents of a file and return a pointer to the decoded bytes
 *
 *
 * The allocator used is `libc::malloc`
 *
 * @param file: The file to decode
 *
 * @param width: Image width, after successful decoding the value stored will be the image width,
 * can be null
 *
 * @param height: Image height, after successful decoding, the value stored will be the image height,can be null
 *
 * @param depth: Image depth, after successful decoding, the value stored will be the image depth,can be null
 *
 * @param channels: Number of channels in the image, after successful decoding, the value stored will be the
 * image channels, can be null
 *
 * @param status: Image decoding status, query this before inspecting contents of buf, CANNOT be null
 *
 * \returns A pointer to the first element of the image pixels, the length of this array is strictly
 * `width * height * channels * depth`
 *
 * In case the decoder cannot decode, returns `null` and the reason
 * why it can't be decoded is given in `status` parameter
 *
 */
const char *zil_imread(const char *file,
                       size_t *width,
                       size_t *height,
                       enum ZImageDepth *depth,
                       size_t *channels,
                       struct ZStatus *status);

/**
 *\brief Load an image from a file and return it's contents
 *
 * if `status` parameter  is null, returns early
 *
 *
 * @param file: File path, MUST be null terminated
 *
 * @param buf: Output buffer, contents of decoding will be written here
 *
 * @param buf_size: Buffer size, the size of output buffer
 *
 * @param width: Image width, after successful decoding the value stored will be the image width,
 * can be null
 *
 * @param height: Image height, after successful decoding, the value stored will be the image height,can be null
 *
 * @param depth: Image depth, after successful decoding, the value stored will be the image depth,can be null
 *
 * @param channels: Number of channels in the image, after successful decoding, the value stored will be the
 * image channels, can be null
 *
 * @param status: Image decoding status, query this before inspecting contents of buf, CANNOT be null
 */
void zil_imread_into(const char *file,
                     uint8_t *output,
                     size_t output_size,
                     size_t *width,
                     size_t *height,
                     enum ZImageDepth *depth,
                     size_t *channels,
                     struct ZStatus *status);

/**
 * Allocate a region of memory
 *
 * This uses libc's malloc hence on most platforms it should be the system allocator
 *
 * \param size: Memory size
 */
void *zil_malloc(size_t size);

/**
 * Read image headers from a file and return common information such as width, height depth and colorspace
 *
 * \param file: Null terminated
 */
struct ZImageMetadata zil_read_headers_from_file(const char *file,
                                                 struct ZStatus *status);

/**
 * \brief  Decode image headers  of bytes already in memory
 *
 * This reads and returns common image metadata, like width, depth,colorspace
 * it does not attempt to return extra details of images such as exif
 *
 * \returns: A struct containing details and sets status to be successful In case of failure in decoding or status being null, returns a zeroed struct.
 *
 */
struct ZImageMetadata zil_read_headers_from_memory(const unsigned char *input,
                                                   unsigned long input_size,
                                                   struct ZStatus *status);

/**
 * Return the status code contained in the ZImStatus
 *
 * \param status The status struct for which to extract a status from
 *
 * \returns ZStatusCode, an enum that indicates if everything is okay or something went wrong
 */
enum ZStatusType zil_status_code(const struct ZStatus *status);

/**
 * Destroy a status indicator.
 *
 * This takes by value and drops the status param
 * freeing any memory allocated and used by this status struct
 *
 * \param status: The status to free
 */
void zil_status_free(struct ZStatus *status);

/**
 * Returns a null terminated string that contains more details about
 * what went wrong
 *
 * \param status: The image status for which we are extracting the message from
 *
 * \returns: The message contained, if `status` is null, returns null
 */
const char *zil_status_message(const struct ZStatus *status);

/**
 * Create a new image status struct
 *
 * This can be passed around to functions that report progress via
 * status
 *
 * Remember to free it with `zil_status_free`
 */
struct ZStatus *zil_status_new(void);

/**
 * \brief Check if image operation succeeded
 *
 * @param status: Image status
 *
 * @returns true if everything is okay, if status is null or something went bad returns false
 */
bool zil_status_ok(const struct ZStatus *status);

/**
 * Create a new copy of the image independent from the previous
 * one and return it
 *
 * \param image: The image to clone
 * \returns: A fresh new copy of the image if everything goes well, otherwise null to indicate faliure
 */
ZImage *zil_zimg_clone(const ZImage *image);

/**
 * Get image colorspace from image
 */
enum ZImageColorspace zil_zimg_colorspace(ZImage *image, struct ZStatus *status);

/**
 * Get image depth from image
 */
enum ZImageDepth zil_zimg_depth(ZImage *image, struct ZStatus *status);

/**
 * Free an image
 *
 * This drops the image and associated memory buffers
 */
void zil_zimg_free(ZImage *image);

/**
 * Get output size, this returns the minimum array needed to hold a single
 * interleaved frame of an image
 *
 * \param image: A non-null image instance
 * \param status: A non-null status instance
 *
 * \returns the number of bytes needed to store the image or 0 in case image is null
 */
size_t zil_zimg_get_out_buffer_size(ZImage *image, struct ZStatus *status);

/**
 * Get image height from image
 */
size_t zil_zimg_height(ZImage *image, struct ZStatus *status);

/**
 * Create an empty dummy image struct
 *
 * This can now be passed to functions that require a pointer to a ZImage
 *
 * This is the preferred way to initialize this, not via memset or malloc+sizeof
 */
ZImage *zil_zimg_new(void);

/**
 * Open an image from disk into memory
 *
 * This is the method recommended to use when you want to decode an image and apply operations
 * to it
 *
 * \param file: A nul-terminated file containing an image
 * \param image: After decoding, this will point to the image
 * \param status: Status information
 */
void zil_zimg_open(const char *file, ZImage *image, struct ZStatus *status);

/**
 * Decode an image already in memory
 *
 *
 * \param input: Input memory containing encoded image bytes
 * \param input_size: The size of input
 * \param image: After decoding, this will point to the image
 * \param status: Status information
 */
void zil_zimg_read_from_memory(const uint8_t *input,
                               size_t input_size,
                               ZImage *image,
                               struct ZStatus *status);

/**
 * Get the image width from the image
 */
size_t zil_zimg_width(ZImage *image, struct ZStatus *status);

/**
 * \brief Write an image to disk
 *
 * Format is inferred from the file extension
 *
 * \param output_file: Output file to write into
 *
 * \param image: The image we will be writing
 *
 * \param status: Image operation status, query this to know if the operation succeeded
 */
void zil_zimg_write_to_disk(const char *output_file, const ZImage *image, struct ZStatus *status);

/**
 * \brief Write an image to disk
 *
 * Format is the one passed to the function
 *
 * \param output_file: Output file to write into
 *
 * \param image: The image we will be writing
 *
 * \param format: The image format to use for encoding
 *
 * \param status: Image operation status, query this to know if the operation succeeded
 */
void zil_zimg_write_to_disk_with_format(const char *output_file,
                                        const ZImage *image,
                                        enum ZImageFormat format,
                                        struct ZStatus *status);

/**
 * Write image bytes to output array of output size
 *
 * This writes interleaved raw pixels to buffer and returns bytes written
 *
 * This is the preffered method to extract raw bytes from the image and can work with any
 * image type, provided you alias it here, i.e if you say for example want float hdr data
 *
 * convert pointer to u8 and multiply output size by sizeof float
 */
size_t zil_zimg_write_to_output(const ZImage *image,
                                uint8_t *output,
                                size_t output_size,
                                struct ZStatus *status);

#endif /* ZIL_IMAGE */
