#include <iostream>
#include <mash/lexer.hpp>

int main() {
    mash::lexer lex{icu::UnicodeString::fromUTF8("():.")};

    for (mash::token tok : lex.tokens()) {
        std::string raw_text;
        tok.text.toUTF8String(raw_text);
        std::cout << magic_enum::enum_name(tok.kind) << " '" << raw_text << "'" << '\n';
    }
}
