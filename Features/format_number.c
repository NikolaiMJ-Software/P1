#include "../connecter.h"
// Helper function to format numbers with commas
void format_number(int number, char* buffer) {
    char temp[20];
    // Convert the number to a string
    sprintf(temp, "%d", number);
    int len = strlen(temp);
    // Check if buffer is large enough
    buffer[0] = '\0';
    int tempIndex = 0, bufferIndex = 0;
    // Loop to copy characters and insert commas
    for (int i = 0; i < len; i++) {
        if (i > 0 && (len - i) % 3 == 0) {
            buffer[bufferIndex++] = ',';
        }
        buffer[bufferIndex++] = temp[tempIndex++];
    }
}