#pragma once

#include <unistd.h>
#include <stdint.h>

namespace fastio {

static const int kBufSize = 1 << 16;

class Reader {
    int fd;
    uint8_t buf[kBufSize];
    int idx;
    int size;
public:
    explicit Reader(int fileDescriptor = 0) : fd(fileDescriptor), idx(0), size(0) {}

    inline uint8_t getChar() {
        if (idx >= size) {
            ssize_t r = ::read(fd, buf, kBufSize);
            if (r <= 0) return 0;
            size = static_cast<int>(r);
            idx = 0;
        }
        return buf[idx++];
    }

    template<typename T>
    inline bool readInt(T &out) {
        uint8_t c; T sign = 1; T val = 0;
        do { c = getChar(); if (!c) return false; } while (c <= ' ');
        if (c == '-') { sign = -1; c = getChar(); }
        for (; c >= '0'; c = getChar()) {
            if (c > '9') break;
            val = static_cast<T>(val * 10 + (c - '0'));
        }
        out = static_cast<T>(val * sign);
        return true;
    }

    inline bool readWord(char* out, int maxLen) {
        uint8_t c;
        do { c = getChar(); if (!c) return false; } while (c <= ' ');
        int i = 0;
        for (; c > ' '; c = getChar()) {
            if (!c) break;
            if (i + 1 < maxLen) out[i++] = static_cast<char>(c);
        }
        out[i] = '\0';
        return true;
    }
};

class Writer {
    int fd;
    uint8_t buf[kBufSize];
    int idx;
public:
    explicit Writer(int fileDescriptor = 1) : fd(fileDescriptor), idx(0) {}
    ~Writer() { flush(); }

    inline void putChar(uint8_t c) {
        if (idx >= kBufSize) flush();
        buf[idx++] = c;
    }

    template<typename T>
    inline void writeInt(T x, char end = '\n') {
        if (x == 0) { putChar('0'); if (end) putChar(end); return; }
        if (x < 0) { putChar('-'); x = -x; }
        uint8_t tmp[32]; int n = 0;
        while (x) { tmp[n++] = static_cast<uint8_t>('0' + (x % 10)); x /= 10; }
        while (n--) putChar(tmp[n]);
        if (end) putChar(end);
    }

    inline void writeStr(const char* s, char end = '\n') {
        for (; *s; ++s) putChar(static_cast<uint8_t>(*s));
        if (end) putChar(end);
    }

    inline void flush() {
        if (idx) { (void)::write(fd, buf, idx); idx = 0; }
    }
};

} // namespace fastio


