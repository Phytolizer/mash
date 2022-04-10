#pragma once

#include <magic_enum.hpp>

namespace mash {

enum class syntax_kind {
    // Marker tokens
    bad_token,
    end_of_file_token,

    // Special tokens (literals)
    quoted_string,
    identifier_token,

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
