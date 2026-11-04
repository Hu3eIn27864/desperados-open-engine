#include "core/binary_reader.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
int main() {
    using doe::core::BinaryReader;
    constexpr std::array bytes{std::byte{0x12},std::byte{0x34},std::byte{0x56},
        std::byte{0x78},std::byte{0x9A},std::byte{0xBC},std::byte{0xDE}};
    BinaryReader reader{bytes};
    std::uint8_t u8=0; std::uint16_t u16=0; std::uint32_t u32=0;
    assert(reader.size()==bytes.size() && reader.remaining()==bytes.size());
    assert(reader.read_u8(u8) && u8==0x12U);
    assert(reader.read_u16_le(u16) && u16==0x5634U);
    assert(reader.read_u32_le(u32) && u32==0xDEBC9A78U);
    assert(reader.at_end());
    const auto old=reader.position();
    assert(!reader.read_u8(u8) && reader.position()==old);
    assert(!reader.seek(bytes.size()+1U) && reader.position()==old);
    assert(reader.seek(0U) && reader.skip(3U) && reader.position()==3U);
    assert(!reader.skip(bytes.size()));
    std::cout << "BinaryReader tests passed\n";
    return 0;
}
