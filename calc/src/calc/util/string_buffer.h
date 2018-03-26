#pragma once
#ifndef SIGNAL_UTIL_STRING_BUFFER_H
#define SIGNAL_UTIL_STRING_BUFFER_H
#include <stdarg.h>

/**
 * 格納される文字の型.
 */
typedef char char_t;

/**
 * 可変長の文字列を格納する構造体.
 * 文字を格納する場合はこちらを使用します。
 */
typedef struct string_buffer {
	int length;
	int capacity;
	char_t* text;
} string_buffer;

/**
 * 文字列バッファーを作成します.
 * @return
 */
#define string_buffer_new() (string_buffer_malloc(__FILE__, __LINE__))

/**
 * 文字列バッファーを作成します.
 * @param filename
 * @param lineno
 * @return
 */
string_buffer* string_buffer_malloc(const char* filename, int lineno);

/**
 * バッファの先頭に挿入します.
 * @param self
 * @param c
 */
void string_buffer_prepend(string_buffer* self, char_t c);

/**
 * バッファーの最後に追記します.
 * @param self
 * @param c
 */
void string_buffer_append(string_buffer* self, char_t c);

/**
 * フォーマットして追記します.
 * @param self
 * @param message
 * @param ...
 */
void string_buffer_appendf(string_buffer* self, const char* message, ...);

/**
 * フォーマットして追記します.
 * @param self
 * @param message
 * @param ap
 */
void string_buffer_vappendf(string_buffer* self, const char* message, va_list ap);

/**
 * 全て追記します.
 * @param self
 * @param s
 */
void string_buffer_appends(string_buffer* self, const char* s);

/**
 * shrink,freeを実行して文字列だけを返します.
 * @param self
 * @return
 */
char* string_buffer_release(string_buffer* self);

/**
 * バッファを拡張します.
 * @param self
 */
void string_buffer_reserve(string_buffer* self);

/**
 * 将来の拡張のために確保された余分な領域を開放します.
 * また、末尾をゼロ文字にします。
 * @param self
 */
void string_buffer_shrink(string_buffer* self);

/**
 * バッファーと中身を開放します.
 * @param self
 */
void string_buffer_delete(string_buffer* self);
#endif // !SIGNAL_UTIL_STRING_BUFFER_H
