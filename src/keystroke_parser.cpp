#include "keystroke_parser.hpp"

void KeystrokeParser::reset() {
  m_currentKeystroke = m_keystrokes.head();
}

void KeystrokeParser::nextKeyCombination(const QKeyCombination& combination) {
  m_currentKeystroke = m_currentKeystroke->visit_or_nullptr(combination);
  if (m_currentKeystroke == nullptr) {
    reset();
  }
  if (m_currentKeystroke->hasValue()) {
    m_currentKeystroke->value()();
    reset();
  }
}

void KeystrokeParser::registerKeystroke(const Keystroke& keystroke,
                                        const ActionType& action) {
  m_keystrokes.addSequence(keystroke.begin(), keystroke.end(), action);
}
