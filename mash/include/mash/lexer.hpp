#pragma once

#include <unicode/unistr.h>

namespace mash {

class lexer {
    icu::UnicodeString m_source;

  public:
    explicit inline lexer(icu::UnicodeString&& source) : m_source(std::move(source)) {}
};

} // namespace mash
