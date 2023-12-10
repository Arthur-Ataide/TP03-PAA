char* decrypt(char* text, int shift) {
    return encrypt(text, ALPHABET_SIZE - shift);
}