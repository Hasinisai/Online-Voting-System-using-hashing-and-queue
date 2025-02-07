#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VOTERS 100
#define MAX_CANDIDATES 3
int hashTable[MAX_VOTERS] = {0};
int queue[MAX_VOTERS];
int front = -1, rear = -1;
typedef struct {
    int id;
    char name[30];
    int votes;
} Candidate;
Candidate candidates[MAX_CANDIDATES] = {
    {1, "Candidate A", 0},
    {2, "Candidate B", 0},
    {3, "Candidate C", 0}
};
int hash(int voterID) {
    return voterID % MAX_VOTERS;
}
void enqueue(int vote) {
    if (rear == MAX_VOTERS - 1) {
        printf("Queue is full!\n");
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = vote;
}
int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue[front++];
}
int hasVoted(int voterID) {
    int index = hash(voterID);
    return hashTable[index] == 1;
}
void markAsVoted(int voterID) {
    int index = hash(voterID);
    hashTable[index] = 1;
}
void vote(int voterID, int candidateID) {
    if (hasVoted(voterID)) {
        printf("Voter %d has already voted!\n", voterID);
        return;
    }
    if (candidateID < 1 || candidateID > MAX_CANDIDATES) {
        printf("Invalid candidate ID!\n");
        return;
    }
    markAsVoted(voterID);
    enqueue(candidateID);
    printf("Voter %d voted for %s\n", voterID, candidates[candidateID - 1].name);
}
void processVotes() {
    int vote;
    while ((vote = dequeue()) != -1) {
        candidates[vote - 1].votes++;
    }
}
void displayResults() {
    printf("\n--- Voting Results ---\n");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%s received %d votes\n", candidates[i].name, candidates[i].votes);
    }
}
int main() {
int choice, voterID, candidateID;
while (1) {
        printf("\n1. Vote\n2. Process Votes\n3. Show Results\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Voter ID: ");
                scanf("%d", &voterID);
                printf("Enter Candidate ID (1 - %d): ", MAX_CANDIDATES);
                scanf("%d", &candidateID);
                vote(voterID, candidateID);
                break;

            case 2:
                processVotes();
                printf("Votes processed.\n");
                break;

            case 3:
                displayResults();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
