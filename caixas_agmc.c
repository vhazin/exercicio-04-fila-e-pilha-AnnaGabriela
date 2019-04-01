#include <stdio.h>
#include <stdlib.h>

#define TARGET_BOX 1

typedef struct stack {
    int size;
} stack;

void getRemovedAmount(stack *[], int, int, int);

int main() {
    int amount_boxes, amount_stacks;

    while(1) {
        scanf("%d %d", &amount_boxes, &amount_stacks);

        if (amount_boxes == 0 && amount_stacks == 0) exit(0);

        stack *stacks[amount_stacks];
        int target_stack, target_box_level;

        for (int stack_number = 0; stack_number < amount_stacks; stack_number++) {
            stack *new_stack = malloc(sizeof(stack));
            int current_stack_amount;
            scanf("%d", &current_stack_amount);
            stacks[stack_number] = new_stack;
            new_stack->size = current_stack_amount;
            for (int box_level = 0; box_level < current_stack_amount; box_level++) {
                int current_box;
                scanf("%d", &current_box);
                if (current_box == TARGET_BOX) {
                    target_stack = stack_number;
                    target_box_level = box_level;
                }
            }
        }
        
        // check if the target box is on the first or last stack
        if (target_stack == 0 || target_stack == amount_stacks - 1) {
            printf("%d ", 0);
            break;
        }

        const int target_index = target_stack;
        const int last_stack = amount_stacks - 1;
        getRemovedAmount(stacks, target_index, target_box_level, last_stack);
    }

    return 0;
}

int removeUpwards(stack *stack, int box_level) {
    return (stack->size - box_level);
}

int bestOption(int left, int right) {
    return left <= right ? left : right;
}

void getRemovedAmount(stack *stacks[], int target_index, int target_box_level, int last_stack) {
    int removed_right = 0;
    int removed_left = 0;

    for (int index = last_stack; index >= target_index; index--) {
        removed_right += removeUpwards(stacks[index], target_box_level);
    }

    for (int index = target_index; index >= 0; index--) {
        removed_left += removeUpwards(stacks[index], target_box_level);
    }

    printf("%d ", bestOption(removed_left - 1, removed_right - 1));
}

/* TEST CASES

INPUT: 4 3 1 3 2 1 2 1 4
OUTPUT: 2

INPUT: 4 3 1 3 2 2 1 1 4
OUTPUT: 0

INPUT: 5 3 2 3 5 1 1 2 2 4
OUTPUT: 1

*/
