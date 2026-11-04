#include "core/binary_reader.hpp"
namespace doe::core {
BinaryReader::BinaryReader(const std::span<const std::byte> data) noexcept : data_(data) {}
std::size_t BinaryReader::position() const noexcept { return position_; }
std::size_t BinaryReader::size() const noexcept { return data_.size(); }
std::size_t BinaryReader::remaining() const noexcept { return data_.size() - position_; }
bool BinaryReader::at_end() const noexcept { return position_ == data_.size(); }
bool BinaryReader::seek(const std::size_t offset) noexcept {
    if (offset > data_.size()) return false;
    position_ = offset;
    return true;
}
bool BinaryReader::skip(const std::size_t count) noexcept {
    if (count > remaining()) return false;
    position_ += count;
    return true;
}
bool BinaryReader::read_u8(std::uint8_t& value) noexcept {
    if (remaining() < 1U) return false;
    value = std::to_integer<std::uint8_t>(data_[position_]);
    ++position_;
    return true;
}
bool BinaryReader::read_u16_le(std::uint16_t& value) noexcept {
    if (remaining() < 2U) return false;
    const auto b0 = std::to_integer<std::uint16_t>(data_[position_]);
    const auto b1 = std::to_integer<std::uint16_t>(data_[position_ + 1U]);
    value = static_cast<std::uint16_t>(b0 | static_cast<std::uint16_t>(b1 << 8U));
    position_ += 2U;
    return true;
}
bool BinaryReader::read_u32_le(std::uint32_t& value) noexcept {
    if (remaining() < 4U) return false;
    const auto b0 = std::to_integer<std::uint32_t>(data_[position_]);
    const auto b1 = std::to_integer<std::uint32_t>(data_[position_ + 1U]);
    const auto b2 = std::to_integer<std::uint32_t>(data_[position_ + 2U]);
    const auto b3 = std::to_integer<std::uint32_t>(data_[position_ + 3U]);
    value = b0 | (b1 << 8U) | (b2 << 16U) | (b3 << 24U);
    position_ += 4U;
    return true;
}
bool BinaryReader::read_bytes(const std::span<std::byte> destination) noexcept {
    if (destination.size() > remaining()) return false;
    for (std::size_t i = 0; i < destination.size(); ++i) destination[i] = data_[position_ + i];
    position_ += destination.size();
    return true;
}
} // namespace doe::core
