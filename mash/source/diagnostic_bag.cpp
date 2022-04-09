#include "mash/diagnostic_bag.hpp"

#include <fmt/format.h>
#include <fmt/xchar.h>

void mash::diagnostic_bag::report(diagnostic&& diagnostic) {
    m_diagnostics.emplace_back(std::move(diagnostic));
}

void mash::diagnostic_bag::report_bad_character(char32_t character) {
    std::string result;
    auto unicode = icu::UnicodeString{};
    unicode.append((UChar32)character);
    unicode.toUTF8String(result);
    report(diagnostic{fmt::format("bad character: '{}'", result)});
}

void mash::diagnostic_bag::report_bad_integer_literal(icu::UnicodeString&& text) {
    std::string raw_text;
    text.toUTF8String(raw_text);
    report(diagnostic{fmt::format("bad integer literal: '{}'", raw_text)});
}

std::span<const mash::diagnostic> mash::diagnostic_bag::diagnostics() const {
    return m_diagnostics;
}
