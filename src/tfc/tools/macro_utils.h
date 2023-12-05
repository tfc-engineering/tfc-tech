#ifndef TFCTECH_MACRO_UTILS_H
#define TFCTECH_MACRO_UTILS_H

/**Small utility macro for joining two words.*/
#define JoinWordsTemp(x, y) x##y
/**IDK why this is needed. Seems like counter doesnt work properly without it*/
#define JoinWords(x, y) JoinWordsTemp(x, y)

#endif // TFCTECH_MACRO_UTILS_H
