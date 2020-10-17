// SPDX-License-Identifier: BSD-2-Clause

// This code is part of the sfizz library and is licensed under a BSD 2-clause
// license. You should have receive a LICENSE.md file along with the code.
// If not, contact the sfizz maintainers at https://github.com/sfztools/sfizz

#pragma once

namespace sfz {

namespace config {

    constexpr unsigned int defaultAlignment { 16 };

    constexpr unsigned tableSize = 1024;
    constexpr double tableRefSampleRate = 44100.0 * 1.1; // +10% aliasing permissivity

} // namespace config

} // namespace sfz
