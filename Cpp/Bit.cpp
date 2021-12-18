#include "Bit.h"

auto to_bit_stream(const std::string& bytes)
{
    std::vector<std::uint8_t> stream;
    std::uint8_t shift{ 0 };
    std::uint8_t out{ 0 };

    // allocate enough bytes to hold the bits
    // speeds up the code a bit
    stream.reserve((bytes.size() + 7) / 8);

    // loop over all bytes
    for (const auto c : bytes)
    {
        // check input
        if (!((c == '0') || (c == '1'))) throw std::invalid_argument("invalid character in input");

        // shift output by one to accept next bit
        out <<= 1;

        // keep track of number of shifts
        // after 8 shifts a byte has been filled
        shift++;

        // or the output with a 1 if needed
        out |= (c == '1');

        // complete an output byte
        if (shift == 8)
        {
            stream.push_back(out);
            out = 0;
            shift = 0;
        }
    }

    return stream;
}
