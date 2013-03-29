/**
 * @file multi_tokenizer.h
 */

#ifndef _MULTI_TOKENIZER_
#define _MULTI_TOKENIZER_

#include <memory>
#include <string>
#include <vector>
#include "tokenizers/tokenizer.h"
#include "index/document.h"

namespace meta {
namespace tokenizers {

/**
 * The MultiTokenizer class contains more than one tokenizer. This is useful for
 * trying combined feature methods.
 *
 * For example, you could tokenize based on ngrams of words and parse tree
 * rewrite rules. The MultiTokenizer keeps track of all the features in one set
 * for however many internal Tokenizers it contains.
 */
class MultiTokenizer: public Tokenizer
{
    public:

        /**
         * Constructs a MultiTokenizer from a vector of other Tokenizers.
         * @param toks
         */
        MultiTokenizer(const std::vector<std::shared_ptr<Tokenizer>> & toks);

        /**
         * Tokenizes a file into a Document.
         * @param document - the Document to store the tokenized information in
         * @param docFreq - optional parameter to store IDF values in
         */
        void tokenize(index::Document & document,
                const std::shared_ptr<std::unordered_map<index::TermID, unsigned int>> & docFreq = nullptr);

    private:

        /** Holds all the Tokenizers in this MultiTokenizer */
        std::vector<std::shared_ptr<Tokenizer>> _tokenizers;

        /** Keeps track of the number of terms between all the contained Tokenizers. */
        size_t _maxTermID;
};

}
}

#endif