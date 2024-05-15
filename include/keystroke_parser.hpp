#ifndef RANG_INCLUDE_KEYSTROKE_PARSER_HPP_
#define RANG_INCLUDE_KEYSTROKE_PARSER_HPP_

#include "utility/trie.hpp"

using Keystroke = QList<QKeyCombination>;

class KeystrokeParser {
  public:
    using ActionType = std::function<void()>;

    void registerKeystroke(const Keystroke& keystroke, const ActionType& action);
    void nextKeyCombination(const QKeyCombination& combination);
    void reset();

  private:
    Trie<QKeyCombination, ActionType> m_keystrokes;
    Trie<QKeyCombination, ActionType>::Node* m_currentKeystroke{m_keystrokes.head()};
};

#endif  // RANG_INCLUDE_KEYSTROKE_PARSER_HPP_
