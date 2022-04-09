#include "mash/diagnostic_bag.hpp"

#include <fmt/format.h>
#include <fmt/xchar.h>

void mash::diagnostic_bag::report(diagnostic&& diagnostic) {
    m_diagnostics.emplace_back(std::move(diagnostic));
}

void mash::diagnostic_bag::report_bad_character(char32_t character) {
    report(diagnostic{fmt::format(U"bad character: '{}'", character)});
}

void mash::diagnostic_bag::report_bad_integer_literal(icu::UnicodeString&& text) {
    std::vector<UChar32> text_chars;
    text_chars.resize(text.countChar32());
    UErrorCode error = U_ZERO_ERROR;
    text.toUTF32(text_chars.data(), static_cast<std::int32_t>(text_chars.size()), error);
    if (!U_SUCCESS(error)) {
        throw std::runtime_error{"error converting integer literal to UTF-32"};
    }
    std::vector<char32_t> chars;
    chars.reserve(text_chars.size());
    std::copy(text_chars.begin(), text_chars.end(), std::back_inserter(chars));
    report(diagnostic{fmt::format(U"bad integer literal: '{}'",
            std::basic_string_view<char32_t>(chars.begin(), chars.end()))});
}

std::span<const mash::diagnostic> mash::diagnostic_bag::diagnostics() const {
    return m_diagnostics;
}
