#pragma once
#include "qr_generator/qrcodegen.hpp"
#include "pngwriter.h"

using qrcodegen::QrCode;

enum AnchorShape {
    Square,
    Round
};

/// @brief Основной класс
class QrBeautifier {
    QrCode qr;
    pngwriter image;
    const char* text;

    /*! @brief Функция для создания и сохранения QR-кода
    */
    QrCode generateQRCode();
public:
    /*! @brief Пустой умолчательный конструктор
    * 
    * @param[in] text Текст QR-кода
    */
    QrBeautifier(const char* text);
    
    /*! @brief Функция для сохранения QR-кода
    */
    void saveImage();

    /*! @brief Функция для заливки QR-кода
    *
    * @param[in] red красный цвет 0-255
    * @param[in] green зеленый цвет 0-255
    * @param[in] blue синий цвет 0-255
    * @param[in] shape форма угловых маркеров
    */
    void makeSolidImage(int red, int green, int blue, AnchorShape shape);

    /*! @brief Функция для наложения поверх изображения
    *
    * @param[in] image_path Путь к изображению
    */
    void overlayImageWithQR(const char* image_path);

    /*! @brief Функция для встраивания картинки в QR-код
    *
    * @param[in] image_path Путь к изображению
    */
    void overlayQRWithImage(const char* image_path);

    /*! @brief Функция для генерации heatmap QR-кода
    *
    * @param[in] shape форма угловых маркеров
    */
    void heatmap(AnchorShape shape);
};
