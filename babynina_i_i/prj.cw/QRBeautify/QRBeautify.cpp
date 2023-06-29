#include <pngwriter.h>
#include <iostream>

#include "QRBeautify.h"
#include "qr_generator/qrcodegen.hpp"

using namespace std;

using qrcodegen::QrCode;
using qrcodegen::QrSegment;

static int anchor_size = 7;

QrBeautifier::QrBeautifier(const char* text) {
    this->text = text;
    this->qr = generateQRCode();
}

QrCode QrBeautifier::generateQRCode() {
    const QrCode::Ecc errCorLvl = QrCode::Ecc::HIGH;

    const vector<QrSegment> segments = QrSegment::makeSegments(this->text);
    const QrCode qr = QrCode::encodeSegments(segments, errCorLvl);
    return qr;
}

void QrBeautifier::saveImage() {
    this->image.write_png();
}

void QrBeautifier::makeSolidImage(int red, int green, int blue, AnchorShape shape) {
    int border = 4;
    QrCode qr = this->qr;
    pngwriter image(1000,1000,1.0,"qr.png");
    double square_size = 1000 / (qr.getSize() + border * 2);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                image.filledsquare(square_size * (x + border) , 1000 - (border + y + 1) * square_size, square_size * (x + border) + square_size, 1000 - (border + y) * square_size, (double)red/256, (double)green/256, (double)blue/256);
            }	
        }
    }
    if (shape == AnchorShape::Round) {
        // bottom-left anchor
        image.filledsquare(square_size * (border), 1000 - square_size * (border + qr.getSize() - anchor_size), square_size * (border + anchor_size), 1000 - square_size * (border + qr.getSize()), 1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + qr.getSize() - 0.5 * anchor_size), square_size * anchor_size * 0.5, (double)red / 256, (double)green / 256, (double)blue / 256);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + qr.getSize() - 0.5 * anchor_size), square_size * (anchor_size - 2) * 0.5, 1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + qr.getSize() - 0.5 * anchor_size), square_size * (anchor_size - 4) * 0.5, (double)red / 256, (double)green / 256, (double)blue / 256);

        // top-left anchor
        image.filledsquare(square_size * (border), 1000 - square_size * (border), square_size * (border + anchor_size), 1000 - square_size * (border + anchor_size), 1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * anchor_size * 0.5, (double)red / 256, (double)green / 256, (double)blue / 256);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * (anchor_size - 2) * 0.5, 1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * (anchor_size - 4) * 0.5, (double)red / 256, (double)green / 256, (double)blue / 256);

        // top-right anchor
        image.filledsquare(square_size * (border + qr.getSize() - anchor_size), 1000 - square_size * (border), square_size * (border + qr.getSize()), 1000 - square_size * (border + anchor_size), 1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + qr.getSize() - 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * anchor_size * 0.5, (double)red / 256, (double)green / 256, (double)blue / 256);
        image.filledcircle(square_size * (border + qr.getSize() - 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * (anchor_size - 2) * 0.5, 1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + qr.getSize() - 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * (anchor_size - 4) * 0.5, (double)red / 256, (double)green / 256, (double)blue / 256);
    }
    this->image = image;
}

void QrBeautifier::overlayImageWithQR(const char* image_path) {
    int border = 1;
    QrCode qr = this->qr;
    double square_mult = 0.35; // 0 - full, 0.5 - empty
    pngwriter image(1,1,0,"qr.png");
    image.readfromfile(image_path);
    image.scale_wh(1000,1000);
    double square_size = 1000 / (qr.getSize() + border * 2);

    // top-left anchor
    image.filledsquare(square_size * (border), 1000 - square_size * (border + anchor_size), square_size * (border + anchor_size), 1000 - square_size * (border), 0, 0, 0);
    image.filledsquare(square_size * (border + 1), 1000 - square_size * (border + anchor_size - 1), square_size * (border + anchor_size - 1), 1000 - square_size * (border + 1), 1.0, 1.0, 1.0);
    image.filledsquare(square_size * (border + 2), 1000 - square_size * (border + anchor_size - 2), square_size * (border + anchor_size - 2), 1000 - square_size * (border + 2), 0, 0, 0);

    // bottom-left anchor
    image.filledsquare(square_size * (border), 1000 - square_size * (border + qr.getSize() - anchor_size), square_size * (border + anchor_size), 1000 - square_size * (border + qr.getSize()), 0, 0, 0);
    image.filledsquare(square_size * (border + 1), 1000 - square_size * (border + qr.getSize() - anchor_size + 1), square_size * (border + anchor_size - 1), 1000 - square_size * (border + qr.getSize() - 1), 1.0, 1.0, 1.0);
    image.filledsquare(square_size * (border + 2), 1000 - square_size * (border + qr.getSize() - anchor_size + 2), square_size * (border + anchor_size - 2), 1000 - square_size * (border + qr.getSize() - 2), 0, 0, 0);

    // top-right anchor
    image.filledsquare(square_size * (border + qr.getSize() - anchor_size), 1000 - square_size * (border), square_size * (border + qr.getSize()), 1000 - square_size * (border + anchor_size), 0, 0, 0);
    image.filledsquare(square_size * (border + qr.getSize() - anchor_size + 1), 1000 - square_size * (border + 1), square_size * (border + qr.getSize() - 1), 1000 - square_size * (border + anchor_size - 1), 1.0, 1.0, 1.0);
    image.filledsquare(square_size * (border + qr.getSize() - anchor_size + 2), 1000 - square_size * (border + 2), square_size * (border + qr.getSize() - 2), 1000 - square_size * (border + anchor_size - 2), 0, 0, 0);

    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                image.filledsquare(
                                                        square_size * (x + border)     + square_mult*square_size, 
                                                        1000 - (square_size * (border + y + 1) - square_mult*square_size), 
                                                        square_size * (border + x + 1) - square_mult*square_size, 
                                                        1000 - (square_size * (border + y)     + square_mult*square_size)
                                                    , 0, 0, 0);
            }
            else {
                image.filledsquare(
                                                        square_size * (x + border)     + square_mult*square_size, 
                                                        1000 - (square_size * (border + y + 1) - square_mult*square_size), 
                                                        square_size * (border + x + 1) - square_mult*square_size, 
                                                        1000 - (square_size * (border + y)     + square_mult*square_size)
                                                    , 1.0, 1.0, 1.0);           
            }
        }
    }
    this->image = image;
}

void QrBeautifier::overlayQRWithImage(const char* image_path) {
    int border = 1;
    QrCode qr = this->qr;
    pngwriter image(1,1,0,"qr.png");
    image.readfromfile(image_path);
    image.scale_wh(1000,1000);
    double square_size = 1000 / (qr.getSize() + border * 2);
    image.filledsquare(0, 1000, 1000, 1000 - border * square_size, 1.0, 1.0, 1.0);
    image.filledsquare(0, 1000, border * square_size, 0, 1.0, 1.0, 1.0);
    image.filledsquare((border + qr.getSize()) * square_size, 0, 1000, 1000, 1.0, 1.0, 1.0);
    image.filledsquare(0, 0, 1000, 1000 - (border + qr.getSize()) * square_size, 1.0, 1.0, 1.0);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (!qr.getModule(x, y)) {
                image.filledsquare(square_size * (x + border) , 1000 - (border + y + 1) * square_size, square_size * (x + border) + square_size, 1000 - (border + y) * square_size, 1.0, 1.0, 1.0);
            }	
        }
    }
    this->image = image;
}

void QrBeautifier::heatmap(AnchorShape shape) {
    int border = 4;
    QrCode qr = this->qr;
    pngwriter image(1000,1000,1.0,"qr.png");
    double square_size = 1000 / (qr.getSize() + border * 2);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                switch ((int)qr.getModule(x-1, y) + (int)qr.getModule(x+1, y) + (int)qr.getModule(x, y-1) + (int)qr.getModule(x, y+1)) {
                case 4:
                case 3:
                    image.filledsquare(square_size * (x + border) , 1000 - (border + y + 1) * square_size, square_size * (x + border) + square_size, 1000 - (border + y) * square_size, 220.0/256,30.0/256,30.0/256);
                    break;
                case 2:
                    image.filledsquare(square_size * (x + border) , 1000 - (border + y + 1) * square_size, square_size * (x + border) + square_size, 1000 - (border + y) * square_size, 244.0/256,180.0/256,8.0/256);
                    break;
                case 1:
                case 0:
                    image.filledsquare(square_size * (x + border) , 1000 - (border + y + 1) * square_size, square_size * (x + border) + square_size, 1000 - (border + y) * square_size, 8.0/256,47.0/256,152.0/256);
                    break;
                }
            }	
        }
    }
    if (shape == AnchorShape::Round) {
        // bottom-left anchor
        image.filledsquare(square_size * (border), 1000 - square_size * (border + qr.getSize() - anchor_size), square_size * (border + anchor_size), 1000 - square_size * (border + qr.getSize()),  1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + qr.getSize() - 0.5 * anchor_size), square_size * anchor_size * 0.5, 220.0/256,30.0/256,30.0/256);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + qr.getSize() - 0.5 * anchor_size), square_size * (anchor_size - 2) * 0.5,  1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + qr.getSize() - 0.5 * anchor_size), square_size * (anchor_size - 4) * 0.5, 220.0/256,30.0/256,30.0/256);

        // top-left anchor
        image.filledsquare(square_size * (border), 1000 - square_size * (border), square_size * (border + anchor_size), 1000 - square_size * (border + anchor_size),  1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * anchor_size * 0.5, 220.0/256,30.0/256,30.0/256);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * (anchor_size - 2) * 0.5,  1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * (anchor_size - 4) * 0.5, 220.0/256,30.0/256,30.0/256);
        
        // top-right anchor
        image.filledsquare(square_size * (border + qr.getSize() - anchor_size), 1000 - square_size * (border), square_size * (border + qr.getSize()), 1000 - square_size * (border + anchor_size), 1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + qr.getSize() - 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * anchor_size * 0.5, 220.0/256,30.0/256,30.0/256);
        image.filledcircle(square_size * (border + qr.getSize() - 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * (anchor_size - 2) * 0.5, 1.0, 1.0, 1.0);
        image.filledcircle(square_size * (border + qr.getSize() - 0.5 * anchor_size), 1000 - square_size * (border + 0.5 * anchor_size), square_size * (anchor_size - 4) * 0.5, 220.0/256,30.0/256,30.0/256);
    }
    this->image = image;
}
