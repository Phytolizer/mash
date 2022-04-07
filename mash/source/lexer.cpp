#include "mash/lexer.hpp"

mash::token mash::lexer::token_collection::iterator::scan() {
    m_start = m_current;
    m_text = "";
    m_kind = syntax_kind::bad_token;

    switch (m_iter.current()) {
        case icu::StringCharacterIterator::DONE:
            m_kind = syntax_kind::end_of_file_token;
            break;
        case u':':
            m_kind = syntax_kind::colon_token;
            next();
            break;
        case u'.':
            m_kind = syntax_kind::period_token;
            next();
            break;
        case u'(':
            m_kind = syntax_kind::open_parenthesis_token;
            next();
            break;
        case u')':
            m_kind = syntax_kind::close_parenthesis_token;
            next();
            break;
        case u'"':
            m_kind = syntax_kind::quoted_string;
            scan_string();
            break;
    }

    if (m_kind == syntax_kind::end_of_file_token) {
        m_end = true;
    }
    return {m_kind, std::move(m_text), m_start};
}

void mash::lexer::token_collection::iterator::scan_string() {
    while (true) {
        char16_t curr = m_iter.current();
        if (curr == u'\n' || curr == icu::StringCharacterIterator::DONE) {
            break;
        }
        if (curr == u'"') {
            next();
            break;
        }

        next();
    }
}

void mash::lexer::token_collection::iterator::next() {
    ++m_current;
    m_text.append(m_iter.nextPostInc());
}

mash::lexer::token_collection mash::lexer::tokens() const {
    return token_collection{m_source};
}
