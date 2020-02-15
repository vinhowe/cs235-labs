#include <sys/ioctl.h>
#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

std::string txtFilename(const std::string& name) { return name + ".txt"; }

bool isCharPunctuation(char in) {
  return std::string("().,;?!:").find(in) != std::string::npos;
}

std::string stringToLower(const std::string& in) {
  std::string output;

  for (auto character : in) {
    output += tolower(character);
  }

  return output;
}

std::list<std::string> stringListToLower(const std::list<std::string>& in) {
  std::list<std::string> outputList;

  for (const auto& item : in) {
    outputList.push_back(stringToLower(item));
  }
  return outputList;
}

void printDivider(const std::string& message = "") {
  int cols;
#ifdef TIOCGSIZE
  struct ttysize ts {};
  ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
  cols = ts.ts_cols;
#elif defined(TIOCGWINSZ)
  struct winsize ts {};
  ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
  cols = ts.ws_col;
#endif

  cols = cols == 0 ? 80 : cols;

  std::string separator;

  for (int i = 0; i < cols; i++) {
    separator += "-";
  }

  std::cout << separator << std::endl;

  if (!message.empty()) {
    std::cout << message << std::endl;
  }
}

std::vector<std::string> wordVectorFromTextFile(const std::string& filename) {
  std::ifstream fileIn(txtFilename(filename));

  std::ostringstream streamOut;
  std::vector<std::string> words;

  std::string word;
  while (fileIn >> word) {
    // Remove punctuation from end
    if (isCharPunctuation(word[word.size() - 1])) {
      word = word.substr(0, word.size() - 1);
    }

    // Remove punctuation from beginning
    if (isCharPunctuation(word[0])) {
      word = word.substr(1, word.size());
    }

    // Deal with em-dashes
    std::istringstream wordStream(word);
    char readingChar;
    std::string outputtingWord;
    int hyphenCount = 0;

    while (wordStream >> readingChar) {
      if (readingChar == '-') {
        hyphenCount++;
        // If we have more than one hyphen, we'll treat it like an em-dash
        if (hyphenCount > 1 && !outputtingWord.empty()) {
          if (!outputtingWord.empty()) {
            words.push_back(outputtingWord);
          }
          outputtingWord = "";
          continue;
        }
      } else {
        // In the case that there is only one word, joined by a hyphen
        if (hyphenCount == 1) {
          outputtingWord += '-';
        }
        hyphenCount = 0;

        // Convert characters to lowercase so that output text isn't randomly
        // capitalized
        outputtingWord += tolower(readingChar);
      }
    }
    if (!outputtingWord.empty()) {
      words.push_back(outputtingWord);
    }
  }

  return words;
}

void writeWordsToSetFile(const std::vector<std::string>& words,
                         const std::string& filename) {
  std::ofstream fileOut(txtFilename(filename + "_set"));

  // Creates set from vector
  std::set<std::string> wordSet(words.begin(), words.end());

  for (const auto& setWord : wordSet) {
    fileOut << setWord << std::endl;
  }

  fileOut.close();
}

void writeWordsToVectorFile(const std::vector<std::string>& words,
                            const std::string& filename) {
  std::ofstream fileOut(txtFilename(filename + "_vector"));

  for (const auto& setWord : words) {
    fileOut << setWord << std::endl;
  }

  fileOut.close();
}

std::map<std::string, std::string> firstNextWordMap(
    const std::vector<std::string>& words) {
  std::map<std::string, std::string> wordMap;

  // Implicitly initialized to ""
  std::string last;
  for (const auto& word : words) {
    wordMap[last] = word;
    last = word;
  }

  return wordMap;
}

std::map<std::string, std::vector<std::string>> nextWordMap(
    const std::vector<std::string>& words) {
  std::map<std::string, std::vector<std::string>> wordMap;

  std::string state;
  for (const auto& word : words) {
    wordMap[state].push_back(word);
    state = word;
  }

  return wordMap;
}

// Template for M-count vector
std::map<std::list<std::string>, std::vector<std::string>> listStateNextWordMap(
    std::vector<std::string>& words, int stateSize) {
  std::map<std::list<std::string>, std::vector<std::string>> wordMap;
  std::list<std::string> state;
  for (int i = 0; i < stateSize; i++) {
    // emplace_back doesn't create a temporary copy
    state.emplace_back("");
  }

  for (const auto word : words) {
    wordMap[state].push_back(word);
    state.push_back(word);
    // We need to use a list to be able to use `pop_front` because `std::list`
    // is not a linked list type
    state.pop_front();
  }

  return wordMap;
}

void writeWordsToWordMapFile(
    const std::map<std::string, std::string>& nextWords,
    const std::string& filename) {
  std::ofstream fileOut(txtFilename(filename + "_1_1"));

  for (const auto& [first, second] : nextWords) {
    fileOut << first << "," << second << std::endl;
  }

  fileOut.close();
}

void printNextWordLoop(std::map<std::string, std::string>& nextWords,
                       int wordCount, const std::string& initialState = "") {
  std::string state = stringToLower(initialState);

  if (!state.empty()) {
    // Print initial string if it exists
    std::cout << state << " ";
  }

  for (int i = 0; i < wordCount; i++) {
    std::cout << nextWords[state] << " ";
    state = nextWords[state];
  }
  std::cout << std::endl;
}

void printNextWordRandom(
    std::map<std::string, std::vector<std::string>>& nextWords, int wordCount,
    const std::string& initialState = "") {
  srand(time(nullptr));

  std::string state = stringToLower(initialState);

  if (!state.empty()) {
    // Print initial string if it exists
    std::cout << state << " ";
  }

  for (int i = 0; i < wordCount; i++) {
    int ind = rand() % nextWords[state].size();
    std::cout << nextWords[state][ind] << " ";
    state = nextWords[state][ind];
  }
  std::cout << std::endl;
}

void printNextWordListStateRandom(
    std::map<std::list<std::string>, std::vector<std::string>>
        listStateNextWords,
    int wordCountToGenerate, int stateSize,
    const std::list<std::string>& initialWords = {}) {
  std::list<std::string> state = stringListToLower(initialWords);

  if (!state.empty()) {
    // Print initial string if it exists
    for (const auto& word : state) {
      std::cout << word << " ";
    }
  }

  for (int i = 0;
       i < std::max(stateSize - initialWords.size(), (unsigned long)0l); i++) {
    state.emplace_back("");
  }

  for (int i = 0; i < wordCountToGenerate; i++) {
    int ind = rand() % listStateNextWords[state].size();
    std::cout << listStateNextWords[state][ind] << " ";
    state.push_back(listStateNextWords[state][ind]);
    state.pop_front();
  }
}

template <class keyType, class valueType>
valueType nthMapElement(std::map<keyType, valueType> inputMap,
                        int targetIndex) {
  int index = 0;
  for (auto [key, value] : inputMap) {
    if (index >= targetIndex) {
      return value;
    }
    index++;
  }
  // Return empty by default
  return {};
}

void printStringVector(const std::vector<std::string>& strings) {
  int index = 0;
  for (const auto& string : strings) {
    std::cout << string;
    if (index < strings.size() - 2) {
      std::cout << ", ";
    }
    index++;
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }

  std::string filename = argv[1];

  if (!std::filesystem::exists(txtFilename(filename))) {
    std::cerr << txtFilename(filename) << " doesn't exist" << std::endl;
  }

  int wordCountToGenerate = 900;
  //  std::string initialWord = "Nephi";

  std::vector<std::string> words = wordVectorFromTextFile(filename);
  writeWordsToSetFile(words, filename);
  writeWordsToVectorFile(words, filename);

  std::map<std::string, std::string> firstNextWords = firstNextWordMap(words);
  writeWordsToWordMapFile(firstNextWords, filename);

  printDivider("SERMON GENERATED USING \"NEXT WORD\" MAP:");
  printNextWordLoop(firstNextWords, wordCountToGenerate /*, initialWord*/);
  std::cout << std::endl;

  std::map<std::string, std::vector<std::string>> nextWords =
      nextWordMap(words);

  int nextWordsTestIndex = 6;

  printDivider("WORDS CORRESPONDING TO WORD AT INDEX " +
               std::to_string(nextWordsTestIndex) + " IN VECTOR:");

  std::vector<std::string> nthTestElementValue =
      nthMapElement(nextWords, nextWordsTestIndex);
  printStringVector(nthTestElementValue);
  std::cout << std::endl;

  printDivider(
      "SERMON GENERATED USING \"NEXT WORDS\" MAP WITH LAST WORD AS INPUT:");
  printNextWordRandom(nextWords, wordCountToGenerate /*, initialWord*/);
  std::cout << std::endl;

  int stateSize = 2;
  //  std::list<std::string> initialWords = {"I", "Nephi"};

  printDivider(
      "SERMON GENERATED USING \"NEXT WORDS\" MAP WITH LAST WORD AS INPUT WITH "
      "STATE SIZE " +
      std::to_string(stateSize) + ":");

  std::map<std::list<std::string>, std::vector<std::string>>
      listStateNextWords = listStateNextWordMap(words, stateSize);
  printNextWordListStateRandom(listStateNextWords, wordCountToGenerate,
                               stateSize /*, initialWords*/);
  std::cout << std::endl;
}