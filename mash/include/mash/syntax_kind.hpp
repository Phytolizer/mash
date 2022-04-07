#pragma once

#include <magic_enum.hpp>

namespace mash {

enum class syntax_kind {
    // Special tokens (literals)
    quoted_string,

    // Keywords
    contains_keyword,
    from_keyword,
    import_keyword,
    is_keyword,
    module_keyword,
    process_keyword,
    with_keyword,

    // Regular tokens (symbols)
    ampersand_token,
    colon_token,
    period_token,

    // Delimiters
    open_parenthesis_token,
    close_parenthesis_token,
};

}
