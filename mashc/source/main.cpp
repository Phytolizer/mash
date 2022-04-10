#include <fmt/format.h>
#include <iostream>
#include <mash/lexer.hpp>
#include <unicode/unistr.h>

int main() {
    mash::lexer lex{icu::UnicodeString{u"module \"test\" contains:"}};

    for (mash::token tok : lex.tokens()) {
        std::string raw_text;
        tok.text.toUTF8String(raw_text);
        fmt::print("{} '{}'\n", magic_enum::enum_name(tok.kind), raw_text);
    }

    for (const mash::diagnostic& diagnostic : lex.diagnostics()) {
        fmt::print("{}\n", diagnostic);
    }
}
