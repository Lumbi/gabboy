//
//  Data.hpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-14.
//

#ifndef Data_hpp
#define Data_hpp

#include <memory>

using Address = uint16_t;
using Byte = uint8_t;
using Word = uint16_t;

inline Byte lsb(Word word) { return word & 0xFF; }
inline Byte msb(Word word) { return word >> 8; }
inline Word word(Byte lsb, Byte msb) { return msb << 8 | lsb; };

#endif /* Data_hpp */
