#pragma once

#include "mash/diagnostic.hpp"

#include <span>
#include <unicode/unistr.h>
#include <vector>

namespace mash {

class diagnostic_bag {
    std::vector<diagnostic> m_diagnostics;
    void report(diagnostic&& diagnostic);

  public:
    void report_bad_character(char32_t character);
    void report_bad_integer_literal(icu::UnicodeString&& text);

    std::span<const diagnostic> diagnostics() const;
};

} // namespace mash
