#include <iostream>

struct Node {
  Node* prev = nullptr;
  int value = 0;
};

struct Stack {
  Node* last = nullptr;
  int size = 0;
};

void Push(Stack* stack, int val) {
  auto q = new Node;
  q->value = val;
  q->prev = stack->last;
  stack->last = q;
  ++stack->size;
}

int Pop(Stack* stack) {
  if (stack->size == 0) {
    return 0;
  }
  int temp = stack->last->value;
  Node* q = stack->last;
  stack->last = stack->last->prev;
  delete q;
  --stack->size;
  return temp;
}

int Back(Stack* stack) {
  if (stack->size == 0) {
    return 0;
  }
  return stack->last->value;
}

int Size(Stack* stack) {
  return stack->size;
}

void Clear(Stack* stack) {
  if (stack->size > 0) {
    Pop(stack);
    Clear(stack);
  }
  delete stack->last;
}

int main() {
  auto* stack = new Stack;
  char symbol = ' ';
  while (std::cin >> symbol) {
    if (symbol != '*' && symbol != '-' && symbol != '+' && symbol != ' ') {
      int num = symbol - '0';
      Push(stack, num);
    } else {
      if (symbol == '*') {
        int x = Pop(stack);
        int y = Pop(stack);
        Push(stack, x * y);
      }
      if (symbol == '-') {
        int x = Pop(stack);
        int y = Pop(stack);
        Push(stack, y - x);
      }
      if (symbol == '+') {
        int x = Pop(stack);
        int y = Pop(stack);
        Push(stack, x + y);
      }
    }
  }
  std::cout << Back(stack);
  Clear(stack);
  delete stack;
  return 0;
}
