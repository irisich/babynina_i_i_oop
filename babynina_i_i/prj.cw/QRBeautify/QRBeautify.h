#pragma once
#include "qr_generator/qrcodegen.hpp"
#include "pngwriter.h"

using qrcodegen::QrCode;

enum AnchorShape {
    Square,
    Round
};

/// @brief �������� �����
class QrBeautifier {
    QrCode qr;
    pngwriter image;
    const char* text;

    /*! @brief ������� ��� �������� � ���������� QR-����
    */
    QrCode generateQRCode();
public:
    /*! @brief ������ ������������� �����������
    * 
    * @param[in] text ����� QR-����
    */
    QrBeautifier(const char* text);
    
    /*! @brief ������� ��� ���������� QR-����
    */
    void saveImage();

    /*! @brief ������� ��� ������� QR-����
    *
    * @param[in] red ������� ���� 0-255
    * @param[in] green ������� ���� 0-255
    * @param[in] blue ����� ���� 0-255
    * @param[in] shape ����� ������� ��������
    */
    void makeSolidImage(int red, int green, int blue, AnchorShape shape);

    /*! @brief ������� ��� ��������� ������ �����������
    *
    * @param[in] image_path ���� � �����������
    */
    void overlayImageWithQR(const char* image_path);

    /*! @brief ������� ��� ����������� �������� � QR-���
    *
    * @param[in] image_path ���� � �����������
    */
    void overlayQRWithImage(const char* image_path);

    /*! @brief ������� ��� ��������� heatmap QR-����
    *
    * @param[in] shape ����� ������� ��������
    */
    void heatmap(AnchorShape shape);
};
