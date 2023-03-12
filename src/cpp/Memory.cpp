//
//  Memory.cpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#include "Memory.hpp"

Memory::Byte Memory::read(Address address) const
{
    return data[address];
}

bool Memory::write(Address address, Byte byte)
{
    if (address < ROM_END) { return false; }
    data[address] = byte;
    return true;
}
