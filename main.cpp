#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>     // for timing
#include <ctime>      // for date/time
#include <iomanip>    // for formatting
#include <cstring>  // for strcspn()



using namespace std;

struct Question {
    string text;
    string options[4];
    char correct;
};

vector<Question> loadQuestions(const string& filename) {
    vector<Question> questions;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file.\n";
        return questions;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) break; // Stop if empty line (optional)

        Question q;
        q.text = line;

        bool incomplete = false;
        for (int i = 0; i < 4; ++i) {
            if (!getline(file, q.options[i])) {
                incomplete = true;
                break;
            }
        }
        if (incomplete) break;

        if (!getline(file, line)) break;  // read correct answer line
        q.correct = line.empty() ? ' ' : line[0];

        questions.push_back(q);
    }

    file.close();
    return questions;
}

void runQuiz(const vector<Question>& questions) {
    int score = 0;

    auto quizStart = chrono::steady_clock::now(); // Start total timer

    for (size_t i = 0; i < questions.size(); ++i) {
        const Question& q = questions[i];
        cout << "\nQ" << i + 1 << ": " << q.text << "\n";
        char choices[] = {'A', 'B', 'C', 'D'};
        for (int j = 0; j < 4; ++j) {
            cout << choices[j] << " " << q.options[j] << "\n";
        }

        auto start = chrono::steady_clock::now(); // Start question timer

        cout << "Your answer (A/B/C/D): ";
        char answer;
        cin >> answer;
        answer = toupper(answer);

        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();
        cout << "⏱️  You took " << duration << " seconds.\n";

        if (answer == q.correct) {
            cout << "✅ Correct!\n";
            ++score;
        } else {
            cout << "❌ Wrong! Correct answer: " << q.correct << "\n";
        }
    }

    auto quizEnd = chrono::steady_clock::now();
    auto totalTime = chrono::duration_cast<chrono::seconds>(quizEnd - quizStart).count();

    cout << "\n🎯 Your Final Score: " << score << " / " << questions.size() << "\n";
    cout << "⏱️  Total time taken: " << totalTime << " seconds\n";

    // Ask for name and save score
    string name;
    cout << "Enter your name to save the score: ";
    cin.ignore(); // flush leftover newline
    getline(cin, name);

    ofstream outFile("scores.txt", ios::app);
    if (outFile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now); // get date/time string
        dt[strcspn(dt, "\n")] = 0; // remove newline

        outFile << name << " scored " << score << "/" << questions.size()
                << " in " << totalTime << "s on " << dt << "\n";
        outFile.close();
        cout << "✅ Score saved to scores.txt\n";
    } else {
        cout << "⚠️ Could not save score.\n";
    }
}

int main() {
    vector<Question> questions = loadQuestions("questions.txt");
    if (questions.empty()) {
        cout << "No questions found. Exiting...\n";
        return 1;
    }

    cout << "=== Welcome to the Quiz App ===\n";
    runQuiz(questions);
    return 0;
}
