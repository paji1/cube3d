#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void learnTopic(int minutes);

int main() {
    printf("Welcome to the Daily C Learning Program!\n");
    srand(time(NULL));
    char *topics[] = {
        "Basic syntax",
        "Variables and data types",
        "Functions",
        "Control flow statements",
        "Arrays and pointers"
    };
    int minutesPerTopic = 10;
    int totalMinutes = 60;
    int numTopics = totalMinutes / minutesPerTopic;
    for (int i = 0; i < numTopics; i++) {
        int topicIndex = rand() % 5;
        char *topic = topics[topicIndex];
        printf("Today's topic is: %s\n", topic);
        learnTopic(minutesPerTopic);
		sleep(60 * 10);
    }
    printf("Congratulations, you have completed today's program!\n");
    return 0;
}

void learnTopic(int minutes) {
    for (int i = 1; i <= minutes; i++) {
        printf("Learning for minute %d...\n", i);
        // Do some learning here
    }
    printf("Topic learned for %d minutes!\n", minutes);
}
