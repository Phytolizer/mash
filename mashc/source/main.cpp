#include <fmt/format.h>
#include <fmt/xchar.h>
#include <iostream>
#include <mash/lexer.hpp>
#include <unicode/unistr.h>

int main() {
    mash::lexer lex{icu::UnicodeString{u"():.@"}};

    for (mash::token tok : lex.tokens()) {
        std::string raw_text;
        tok.text.toUTF8String(raw_text);
        std::cout << magic_enum::enum_name(tok.kind) << " '" << raw_text << "'" << '\n';
    }

    for (const mash::diagnostic& diagnostic : lex.diagnostics()) {
        std::string diagnostic_text;
        icu::UnicodeString unicode_text;
        for (char32_t c : diagnostic) {
            unicode_text.append((UChar32)c);
        }
        unicode_text.toUTF8String(diagnostic_text);
        fmt::print("{}", diagnostic_text);
    }
}
