#pragma once

#include "mash/token.hpp"

#include <concepts>
#include <unicode/schriter.h>
#include <unicode/unistr.h>

namespace mash {

class lexer {
    icu::UnicodeString m_source;

  public:
    explicit inline lexer(icu::UnicodeString&& source) : m_source(std::move(source)) {}

    class _ {
        const icu::UnicodeString& m_source;

        friend class lexer;
        explicit inline _(const icu::UnicodeString& source) : m_source(source) {}

      public:
        class iterator {
            const icu::UnicodeString* m_source;
            icu::StringCharacterIterator m_iter;
            token m_just_scanned;
            bool m_end;

            token scan();

            friend class _;
            explicit inline iterator(const icu::UnicodeString& source)
                : m_source(&source), m_iter(source), m_just_scanned(scan()), m_end(false) {}

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
        };

        static_assert(std::input_iterator<iterator>);

        iterator begin() const {
            return iterator{m_source};
        }
        iterator end() const {
            return iterator{};
        }
    };

    _ tokens() const;
};

} // namespace mash
