# Quiz App in C++

A simple command-line quiz application written in C++. The app reads multiple-choice questions from a file, quizzes the user, and shows the final score.

## Features

- Load questions from a text file
- Support for multiple-choice (A/B/C/D)
- Track and display score
- Easy to extend with more questions

## How to Run

1. Clone or download the project
2. Make sure you have a file named `questions.txt` with properly formatted questions
3. Compile and run the app

### On Linux/macOS:
```bash
g++ main.cpp -o quiz
./quiz

### On Windows:
g++ main.cpp -o quiz.exe
quiz.exe
