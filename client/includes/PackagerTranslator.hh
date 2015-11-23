#ifndef PACKAGETRANSLATOR_HH
#define PACKAGETRANSLATOR_HH

#include <iostream>
#include "PackageStorage.hh"
#include "Buffer.hh"

class PackageTranslator {
private:
  PackageStorage* storage;

public:
  PackageTranslator();
  PackageTranslator(PackageStorage *storage);
  virtual ~PackageTranslator();

  Paquet* BufferToPaquet(const Buffer& buff);
  Buffer* PaquetToBuffer(const Paquet& paquet);

  // template<typename T>
  // void		writeData(size_t &ptr, const T *new_data, size_t len = 0) {

  //   if (!len && !std::is_same<T, char>::value) {
  //     len = sizeof(T);
  //   }
  //   if (ptr + len >= _size) {
  //     changeSize(ptr + len);
  //   }

  //   size_t i;
  //   for (i = 0; i < len; i += 1) {
  //     _data[ptr + i] = reinterpret_cast<const uint8_t *>(new_data)[i];
  //   }
  //   ptr += i;
  // }

  // template<typename T>
  // T		readData(size_t &ptr, T *buffer = 0, size_t len = 0) const {
  //   T		value = 0;
  //   uint8_t	*byte;

  //   if (!len && !std::is_same<T, char>::value) {
  //     len = sizeof(T);
  //   }

  //   byte = reinterpret_cast<uint8_t *>((buffer) ? (buffer) : (&value));

  //   if (ptr + len <= _size) {
  //     for (size_t i = 0; i < len; i += 1) {
  //       byte[i] = _data[ptr];
  //       ptr += 1;
  //     }
  //   }
  //   return (value);
  // }
};

#endif /* !PACKAGETRANSLATOR_HH */
