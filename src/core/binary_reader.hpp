#pragma once
#include <cstddef>
#include <cstdint>
#include <span>
namespace doe::core {
class BinaryReader final {
public:
    explicit BinaryReader(std::span<const std::byte> data) noexcept;
    [[nodiscard]] std::size_t position() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t remaining() const noexcept;
    [[nodiscard]] bool at_end() const noexcept;
    [[nodiscard]] bool seek(std::size_t offset) noexcept;
    [[nodiscard]] bool skip(std::size_t count) noexcept;
    [[nodiscard]] bool read_u8(std::uint8_t& value) noexcept;
    [[nodiscard]] bool read_u16_le(std::uint16_t& value) noexcept;
    [[nodiscard]] bool read_u32_le(std::uint32_t& value) noexcept;
    [[nodiscard]] bool read_bytes(std::span<std::byte> destination) noexcept;
private:
    std::span<const std::byte> data_;
    std::size_t position_{0};
};
} // namespace doe::core
