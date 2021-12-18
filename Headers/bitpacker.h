#ifndef BITPACKER_H
#define BITPACKER_H
#include <QByteArray>
using namespace std;
class BitPacker {
  QByteArray res;
  quint8 bitsLeft = 8;
  quint8 buf = 0;

  public:
  void operator+=(const std::string& s);

  QByteArray finish();
 };
#endif // BITPACKER_H
