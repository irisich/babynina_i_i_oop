#pragma once
#include "qr_generator/qrcodegen.hpp"
#include "pngwriter.h"

using qrcodegen::QrCode;

enum AnchorShape {
    Square,
    Round
};

/// @brief Main class
class QrBeautifier {
    QrCode qr;
    pngwriter image;
    const char* text;

    /*! @brief Function to generate QR code and save it internally
    */
    QrCode generateQRCode();
public:
    /*! @brief Empty default constructor
    * 
    * @param[in] text QR code text
    */
    QrBeautifier(const char* text);
    
    /*! @brief Function to save QR to file
    */
    void saveImage();

    /*! @brief Function for creating solid-color QR-code
    *
    * @param[in] red Red color 0-255
    * @param[in] green Green color 0-255
    * @param[in] blue Blue color 0-255
    * @param[in] shape Desired anchor shape (corner blocks)
    */
    void makeSolidImage(int red, int green, int blue, AnchorShape shape);

    /*! @brief Function for adding QR code over image
    *
    * @param[in] image_path Path to the desired image
    */
    void overlayImageWithQR(const char* image_path);

    /*! @brief Function for encoding QR code with image data
    *
    * @param[in] image_path Path to the desired image
    */
    void overlayQRWithImage(const char* image_path);

    /*! @brief Function for generating heatmap-like QR code
    *
    * @param[in] shape Desired anchor shape (corner blocks)
    */
    void heatmap(AnchorShape shape);
};
