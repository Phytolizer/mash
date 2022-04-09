#pragma once

#include "mash/syntax_kind.hpp"

#include <cstddef>
#include <unicode/unistr.h>

namespace mash {

struct token {
    syntax_kind kind;
    icu::UnicodeString text;
    std::size_t position;

    inline token(syntax_kind kind, icu::UnicodeString&& text, std::size_t position)
        : kind(kind), text(std::move(text)), position(position) {}
};

} // namespace mash
