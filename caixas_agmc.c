#include <stdio.h>
#include <stdlib.h>

#define TARGET_BOX 1

typedef struct stack {
    int size;
} stack;

void getRemovedAmount(stack *[], int, int, int);
int isFirstOrLast(int, int);
int hasFreeSide(stack*[], int);

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

        const int target_index = target_stack;
        const int last_stack = amount_stacks - 1;
        int isHead = (stacks[target_index]->size == target_box_level+1);
        
        // check if the target box is on the first or last stack
        if (isFirstOrLast(target_index, amount_stacks) || (isHead && hasFreeSide(stacks, target_index))) {
            printf("%d ", 0);
            continue;
        }

        getRemovedAmount(stacks, target_index, target_box_level, last_stack);
    }

    return 0;
}

int isFirstOrLast(int target_index, int amount_stacks) {
    return (target_index == 0 || target_index == amount_stacks - 1);
}

int removeUpwards(stack *stack, int box_level) {
    return stack->size - box_level;
}

int bestOption(int left, int right) {
    return left <= right ? left : right;
}

int hasFreeSide(stack *stacks[], int target_index) {
    stack *left = stacks[target_index - 1];
    stack *target = stacks[target_index];
    stack *right = stacks[target_index + 1];
    return ((left->size < target->size) || (right->size < target->size));
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
