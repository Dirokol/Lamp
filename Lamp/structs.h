#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint-gcc.h>

struct __attribute__((packed)) Head
{
    uint8_t     ts;
    uint16_t    length;
};

/**
 * @brief The requestOn struct
 *  Запрос на включение фонаря
 */
struct __attribute__((packed)) requestOn
{
    enum {
        KIND = 0x12
    };
    Head    m_head;
};

/**
 * @brief The requestOff struct
 *  Запрос на отключение фонаря
 */
struct __attribute__((packed)) requestOff
{
    enum {
        KIND = 0x13
    };
    Head    m_head;
};

/**
 * @brief The requestColor struct
 *  Запрос на определение цвета для фонаря
 */
struct __attribute__((packed)) requestColor
{
    enum {
        KIND = 0x20
    };
    Head    m_head;
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
};

#endif // STRUCTS_H
