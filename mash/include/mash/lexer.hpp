#pragma once

#include "mash/diagnostic.hpp"
#include "mash/diagnostic_bag.hpp"
#include "mash/token.hpp"

#include <concepts>
#include <gsl/pointers>
#include <span>
#include <unicode/schriter.h>
#include <unicode/unistr.h>

namespace mash {

class lexer {
    icu::UnicodeString m_source;
    diagnostic_bag m_diagnostics;

  public:
    explicit inline lexer(icu::UnicodeString&& source) : m_source(std::move(source)) {}

    class token_collection {
        diagnostic_bag& m_diagnostics;
        const icu::UnicodeString& m_source;

        friend class lexer;
        explicit inline token_collection(
                diagnostic_bag& diagnostics, const icu::UnicodeString& source)
            : m_diagnostics(diagnostics), m_source(source) {}

      public:
        class iterator {
            diagnostic_bag* m_diagnostics;
            const icu::UnicodeString* m_source;
            icu::StringCharacterIterator m_iter;
            std::size_t m_start;
            std::size_t m_current;
            icu::UnicodeString m_text;
            syntax_kind m_kind;
            token m_just_scanned;
            bool m_end;

            token scan();
            void scan_string();
            void scan_identifier();
            void next();

            friend class token_collection;
            explicit inline iterator(
                    gsl::not_null<diagnostic_bag*> diagnostics, const icu::UnicodeString& source)
                : m_diagnostics(diagnostics), m_source(&source), m_iter(source), m_start(0),
                  m_current(0), m_just_scanned(scan()), m_end(false) {}

          public:
            using difference_type = std::ptrdiff_t;
            using value_type = token;

            iterator()
                : m_iter(""), m_just_scanned(syntax_kind::end_of_file_token, {}, 0), m_end(true) {}

            const value_type& operator*() const {
                return m_just_scanned;
            }
            iterator& operator++() {
                m_just_scanned = scan();
                return *this;
            }
            iterator operator++(int) {
                auto it = *this;
                ++(*this);
                return it;
            }
            constexpr bool operator==(const iterator& other) const {
                if (m_end) {
                    return other.m_end;
                }
                return m_source == other.m_source && m_current == other.m_current;
            }
        };

        static_assert(std::input_iterator<iterator>);

        iterator begin() const {
            return iterator{&m_diagnostics, m_source};
        }
        iterator end() const {
            return iterator{};
        }
    };

    mash::lexer::token_collection tokens();
    std::span<const diagnostic> diagnostics() const;
};

} // namespace mash
