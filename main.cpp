#include <iostream>

// (not) using namespace std;
// https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice

struct ApplicationIO {
  std::istream &in;
  std::ostream &out;
};

// Convert string to lowercase, letter by letter
std::string LowercaseString(const std::string &input) {
  std::string output;

  for (char a : input) {
    output.push_back(tolower(a));
  }

  return output;
}

template<typename T = std::string>
T ReadInput(T errorValue, ApplicationIO io) {
  T input;

  io.in >> input;
  io.in.ignore();

  // If stream error, clear
  // This will happen whenever cin attempts to feed a value into `output` that
  // is not of type T. If T = int and input is "seventeen", a stream error
  // will occur.
  if (io.in.fail()) {
    // remove invalid input from stream
    io.in.clear();

    // This is the generally accepted way to clear the input stream when
    // using newlines to separate input blocks.
    // numeric_limits<streamsize>::max() is a function that returns the
    // maximum size of the stream in the given context of the application
    io.in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return errorValue;
  }

  return input;
}

// Specialization that allows for string with spaces using getline
template<>
std::string ReadInput<std::string>(std::string errorValue,
                                   ApplicationIO io) {
  std::string input;

  try {
    getline(io.in, input);
  } catch (std::istream::failure &e) {
    return errorValue;
  }
  return input;
}

// Works for any possible cin output type--use PromptLine when input may contain
// spaces
// Optional input io argument allows easy stream routing for
// testing
// defaultValue argument provides return case if input was invalid
template<typename T = std::string>
T Prompt(const std::string &prompt, const T errorValue,
         ApplicationIO io) {
  T output;

  io.out << prompt << " ";
  output = ReadInput<T>(errorValue, io);
  io.out << std::endl;

  return output;
}

template<typename Iterator, typename F>
void ForEachWithIndex(Iterator begin, Iterator end,
                      F itemFunc) {
  int i = 0;
  // Must be mutable to modify i
  std::for_each(begin, end, [i, itemFunc](auto item) mutable { itemFunc(i,
                                                                        item);
    i++;
  });
}

int main() {
  std::cout << "Hello world!";
}