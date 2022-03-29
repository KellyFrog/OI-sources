#ifndef __WORD_H__
#define __WORD_H__

#ifdef __cplusplus
extern "C" {
#endif
const char *guess(int num_testcase, int remaining_guesses, char initial_letter, bool *gold, bool *silver);
void init(int num_scramble, const char *scramble);
#ifdef __cplusplus
}
#endif

#endif
