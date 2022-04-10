#include "mash/lexer.hpp"

#include <unicode/uchar.h>

mash::token mash::lexer::token_collection::iterator::scan() {
    m_start = m_current;
    m_text = u"";
    m_kind = syntax_kind::bad_token;

    switch (m_iter.current()) {
        case icu::StringCharacterIterator::DONE:
            m_kind = syntax_kind::end_of_file_token;
            break;
        case U':':
            m_kind = syntax_kind::colon_token;
            next();
            break;
        case U'.':
            m_kind = syntax_kind::period_token;
            next();
            break;
        case U'(':
            m_kind = syntax_kind::open_parenthesis_token;
            next();
            break;
        case U')':
            m_kind = syntax_kind::close_parenthesis_token;
            next();
            break;
        case U'"':
            m_kind = syntax_kind::quoted_string;
            scan_string();
            break;
        default:
            if (u_isalpha(m_iter.current())) {
                m_kind = syntax_kind::identifier_token;
                scan_identifier();
            }
    }

    if (m_kind == syntax_kind::bad_token) {
        m_diagnostics->report_bad_character(m_iter.current32());
        next();
    }
    if (m_kind == syntax_kind::end_of_file_token) {
        m_end = true;
    }
    return {m_kind, std::move(m_text), m_start};
}

void mash::lexer::token_collection::iterator::scan_string() {
    next();

    while (true) {
        UChar32 curr = m_iter.current32();
        if (curr == U'\n' || curr == icu::StringCharacterIterator::DONE) {
            break;
        }
        if (curr == U'"') {
            next();
            break;
        }

        next();
    }
}

void mash::lexer::token_collection::iterator::scan_identifier() {
    while (true) {
        UChar32 curr = m_iter.current32();
        if (curr == icu::StringCharacterIterator::DONE) {
            break;
        }
        if (u_isalpha(curr) || u_isdigit(curr) || curr == U'_') {
            next();
            continue;
        }
        break;
    }

    if (m_text == u"contains") {
        m_kind = syntax_kind::contains_keyword;
    } else if (m_text == u"from") {
        m_kind = syntax_kind::from_keyword;
    } else if (m_text == u"import") {
        m_kind = syntax_kind::import_keyword;
    } else if (m_text == u"is") {
        m_kind = syntax_kind::is_keyword;
    } else if (m_text == u"module") {
        m_kind = syntax_kind::module_keyword;
    } else if (m_text == u"process") {
        m_kind = syntax_kind::process_keyword;
    } else if (m_text == u"with") {
        m_kind = syntax_kind::with_keyword;
    }
}

void mash::lexer::token_collection::iterator::next() {
    ++m_current;
    m_text.append(m_iter.next32PostInc());
}

mash::lexer::token_collection mash::lexer::tokens() {
    return token_collection{m_diagnostics, m_source};
}

std::span<const mash::diagnostic> mash::lexer::diagnostics() const {
    return m_diagnostics.diagnostics();
}
