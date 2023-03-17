//
//  Debug.hpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-16.
//

#ifndef Debug_hpp
#define Debug_hpp

#include "Data.hpp"
#include <array>

template<int X, int Y>
void debug_print_buffer_2D(std::array<Byte, X * Y>& buffer) {
    printf(" "); for (int i = 0; i < X * 3; i++) { printf("-"); } printf("\n");
    for (int y = 0; y < Y; y++) {
        printf("|");
        for (int x = 0; x < X; x++) {
            printf("%02X ", buffer[x + y * X]);
        }
        printf("|\n");
    }
    printf(" "); for (int i = 0; i < X * 3; i++) { printf("-"); } printf("\n");
}

#endif /* Debug_hpp */
