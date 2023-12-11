#include "../headers/random_key.h"

float frequencies_expected[ALPHABET_SIZE] = {
    14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40, 0.02, 2.78, 4.74,
    5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.21, 0.01, 0.47
};

float calculate_score(float observed[], float expected[]) {
    float score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += pow((observed[i] - expected[i]), 2);
    }
    return score;
}

void guess_key(char* text) {
    int frequencies[ALPHABET_SIZE] = {0};
    int total_chars = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            frequencies[text[i] - base]++;
            total_chars++;
        }
    }

    float observed_frequencies[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        observed_frequencies[i] = (float)frequencies[i] / total_chars * 100;
    }

    printf("Tabela de Frequencias:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %.2f%%\n", i + 'a', observed_frequencies[i]);
    }

    float min_score = INFINITY;
    int best_shift = 0;

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        float shifted_observed_frequencies[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int index = (i + shift) % ALPHABET_SIZE;
            shifted_observed_frequencies[i] = observed_frequencies[index];
        }
        float score = calculate_score(shifted_observed_frequencies, frequencies_expected);
        if (score < min_score) {
            min_score = score;
            best_shift = shift;
        }
    }

    printf("Chave mais provavel: %d\n", best_shift);
    printf("Chave real: %d\n", best_shift);
}